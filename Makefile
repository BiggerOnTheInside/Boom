# Locations
C_HEADER_FILES_DIRECTORY    = ./src/include
C_SOURCE_FILES_DIRECTORY    = ./src

C_SOURCE_FOLDER             = ./src
ASM_OBJECT_FOLDER           = ./obj


# Configuration Options
C_COMPILER                  = i686-pc-elf-gcc
ASSEMBLER                    = nasm
S_ASSEMBER                  = i686-pc-elf-gcc
LINKER                      = i686-pc-elf-ld

# Change '-w' to '-Wall' to print warning messages.
C_COMPILER_FLAGS            = -w -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o
ASSEMBLER_FLAGS             = -f elf -o
S_ASSEMBER_FLAGS            = -c -o
LINKER_FLAGS                = -T ./link.ld -o $(BINARY)
BINARY                      = ./kernel.out
EMULATOR                    = qemu
EMULATOR_FLAGS              = -kernel $(BINARY)


# Files:
    # Drivers.
    IDE         = $(C_SOURCE_FOLDER)/drivers/hardware/ata/ide.c
    SCREEN      = $(C_SOURCE_FOLDER)/drivers/hardware/screen.c
    KEYBOARD    = $(C_SOURCE_FOLDER)/drivers/hardware/keyboard.c
    TIMER       = $(C_SOURCE_FOLDER)/drivers/timer.c

    # Kernel.
    KHEAP       = $(C_SOURCE_FOLDER)/kernel/memory/kheap.c
    PAGING      = $(C_SOURCE_FOLDER)/kernel/memory/paging.c
    ARRAY       = $(C_SOURCE_FOLDER)/kernel/memory/ordered_array.c
    GDT         = $(C_SOURCE_FOLDER)/kernel/gdt.c
    IRQ         = $(C_SOURCE_FOLDER)/kernel/irq.c
    ISRS        = $(C_SOURCE_FOLDER)/kernel/isrs.c
    IDT         = $(C_SOURCE_FOLDER)/kernel/idt.c
    KERNEL      = $(C_SOURCE_FOLDER)/kernel/kernel.c
    IO          = $(C_SOURCE_FOLDER)/kernel/io.c
    STRING		= $(C_SOURCE_FOLDER)/string.c
	
# Globals
C_SOURCES                   = $(KERNEL) $(KHEAP) $(PAGING) $(ARRAY) $(GDT) $(IRQ) $(ISRS) $(IDT) $(IO) $(IDE) $(SCREEN) $(KEYBOARD) $(TIMER) $(STRING)
OBJECTS                     = $(ASM_OBJECT_FOLDER)/start.o $(C_SOURCES:.c=.o)




# Actions
ASSEMBLE                    = assemble
LINK                        = link

all: clear clean $(ASSEMBLE) $(OBJECTS) $(LINK)

clear:
	@clear

assemble:
	@echo "[Assemble] Starting assembler proccess."
	
	@echo "[Assemble] Assembling start point."
	@sudo $(ASSEMBLER) $(ASSEMBLER_FLAGS) $(ASM_OBJECT_FOLDER)/start.o $(C_SOURCE_FOLDER)/kernel/start.asm
	@echo "[Assemble] Done assembling start point."
	
	@echo "[Assemble] Done assembling sources."
	

link: $(OBJECTS)
	@echo "[Link] Starting linking proccess."
	
	@echo "[Link] Linking source object files together into binary."
	@$(LINKER) $(LINKER_FLAGS) $(OBJECTS)
	@echo "[Link] Done linking source objects together."
	
	@echo "[Link] Done linking objects."

clean:
	@echo "[Clean] Deleting object files."
	-@$(RM) $(OBJECTS)
	@echo "[Clean] Done deleting object files."
    
github:
	@echo "[GitHub] Begining upload."
	@make clean
	@git add .
	@git commit -a -m "Updating Sources"
	-@git remote remove origin
	@git remote add origin https://github.com/BiggerOnTheInside/Boom.git
	@git push origin master
	@echo "[GitHub] Done uploading."
	
run:
	@echo "[Run] Making sources."
	@make
	@echo "[Run] Done making sources."
	
	@echo "[Run] Cleaning objects."
	@make clean
	@echo "[Run] Done cleaning objects."
	
	@echo "[Run] Starting emulator."
	-@$(EMULATOR) $(EMULATOR_FLAGS)
	@echo "[Run] Emulator stopped."
	
	@echo "[Run] Finished running."
	
.c.o:
	@echo "[Compiler] Compiling C source file."
	@$(C_COMPILER) $(C_COMPILER_FLAGS) $@ $<
	@echo "[Compiler] Done compiling C source file."