ASSEMBLER = nasm																											# Assember binary to run.
C_COMPILER= i686-pc-elf-gcc																									# C Compiler (eg. GCC) to use.
LINKER= i686-pc-elf-ld																										# Object linker to use (eg. LD).

ASSEMBLER_FLAGS = -f elf -o																									# Assembler flags to use.
ASSEMBLER_MEM_FLAGS = -c -o																									# Flags for the memory component assember.
C_FLAGS = -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o	# C Compiler flags to use.
LINKER_FLAGS= -T ./link.ld -o																								# Object linker flags to use.

ASSEMBLE = assemble																											# Section to assemble the code.
COMPILE = compile																											# Section to compile the code.
LINK = link

OBJECT_DIR = ./objects
SOURCE_DIR = ./src


# File specific configuration:
KERNEL = $(SOURCE_DIR)/kernel/kernel.c
GDT = $(SOURCE_DIR)/kernel/gdt.c
IRQ = $(SOURCE_DIR)/kernel/irq.c
ISRS = $(SOURCE_DIR)/kernel/isrs.c
IDT = $(SOURCE_DIR)/kernel/idt.c
IO = $(SOURCE_DIR)/kernel/io.c
STRING =  $(SOURCE_DIR)/string.c
KEYBOARD = $(SOURCE_DIR)/drivers/hardware/keyboard.c
SCREEN =  $(SOURCE_DIR)/drivers/hardware/screen.c
TIMER = $(SOURCE_DIR)/drivers/timer.c
STRING = $(SOURCE_DIR)/string.c
KHEAP = $(SOURCE_DIR)/kernel/memory/kheap.c
PAGING = $(SOURCE_DIR)/kernel/memory/paging.c

C_SOURCES = $(KERNEL) $(GDT) $(IRQ) $(ISRS) $(IDT) $(IO) $(STRING) $(KEYBOARD) $(SCREEN) $(TIMER) $(PAGING) $(KHEAP)
C_OBJECTS=$(C_SOURCES:.c=.o) $(OBJECT_DIR)/start.o $(OBJECT_DIR)/mem.o

#ifdef DEBUG
	$(C_FLAGS) =  -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o
#elseh
#	$(C_FLAGS) = -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o
#endif

all: $(ASSEMBLE) $(C_OBJECTS) $(LINK)

assemble:
	@echo "Now assembling kernel start poing."
	@echo "Please type your sudo password to save the object file: "
	@sudo $(ASSEMBLER) $(ASSEMBLER_FLAGS) $(OBJECT_DIR)/start.o $(SOURCE_DIR)/kernel/start.asm
	@echo "Done assembling kernel start point."
	
	@echo "Now assembling kernel memory sections."
	@$(C_COMPILER) $(ASSEMBLER_MEM_FLAGS) $(OBJECT_DIR)/mem.o $(SOURCE_DIR)/kernel/memory/mem.s
link: $(C_OBJECTS)
	@i686-pc-elf-ld -T ./link.ld -o kernel.bin $(C_OBJECTS)
	
clean: 
	-@$(RM) $(C_OBJECTS)
	
.c.o:
	@$(C_COMPILER) $(C_FLAGS) $@ $<