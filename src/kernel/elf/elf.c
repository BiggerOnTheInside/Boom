/*
 *  elf.c
 *  Boom
 *
 *  Created by Walt Pach on 2/10/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdint.h>
#include <system.h>
#include <elf.h>

boolean elf_check_file(Elf32_Ehdr *hdr){
    if(!hdr){
        return false;
    }
    
    if(hdr->e_ident[EI_MAG0] != ELFMAG0){
        ERROR("ELF Header EI_MAG0 incorrect.");
        
        return false;
    }
    
    if(hdr->e_ident[EI_MAG1] != ELFMAG1){
        ERROR("ELF Header EI_MAG1 incorrect.");
        
        return false;
    }
    
    if(hdr->e_ident[EI_MAG2] != ELFMAG2){
        ERROR("ELF Header EI_MAG2 incorrect.");
        
        return false;
    }
    
    if(hdr->e_ident[EI_MAG3] != ELFMAG3){
        ERROR("ELF Header EI_MAG3 incorrect.");
        
        return false;
    }
    
    return true;
}

boolean elf_check_supported(Elf32_Ehdr *hdr){
    if(!elf_check_file(hdr)){
        ERROR("Invalid ELF file.");
        
        return false;
    }
    
    if(hdr->e_ident[EI_CLASS] != ELFCLASS32){
        ERROR("Unsupported ELF file class.");
    
        return false;
    }
    
    if(hdr->e_ident[EI_DATA] != ELFDATA2LSB){
        ERROR("Unsupported ELF file byte order.");
    
        return false;
    }
    
    if(hdr->e_machine != EM_386){
        ERROR("Unsupported ELF file targer.");
        
        return false;
    }
    
    if(hdr->e_ident[EI_VERSION] != EV_CURRENT){
        ERROR("Unsupported ELF file version.");
        
        return false;
    }
    
    if(hdr->e_type != ET_REL && hdr->e_type != ET_EXEC){
        ERROR("Unsupported ELF file type.");
        
        return false;
    }
    
    return true;
}

static inline void *elf_load_rel(Elf32_Ehdr *hdr){
    int result;

    result = elf_load_stage1(hdr);

    if(result == ELF_RELOC_ERR){
        ERROR("Unable to load ELF file.");

        return NULL;
      }

    result = elf_load_stage2(hdr);

    if(result == ELF_RELOC_ERR){
         ERROR("Unable to load ELF file.");

        return NULL;
    }

    // TODO: Parse the program header (if present).
    return (void *)hdr->e_entry;
}

void *elf_load_file(void *file){
    Elf32_Ehdr *hdr = (Elf32_Ehdr *)file;
    
    if(!elf_check_supported(hdr)){
        ERROR("ELF file cannot be loaded.");
        
        return;
    }
    
    switch(hdr->e_type){
        case ET_EXEC:
            // TODO: Implement
            return NULL;
        case ET_REL:
            return elf_load_rel(hdr);
    }
    
    return NULL;
}

static inline Elf32_Shdr *elf_sheader(Elf32_Ehdr *hdr){
    return (Elf32_Shdr *)((int)hdr + hdr->e_shoff);
}

static inline Elf32_Shdr *elf_section(Elf32_Ehdr *hdr, int index){
    return &elf_sheader(hdr)[index];
}

static inline char *elf_str_table(Elf32_Ehdr *hdr){
    if(hdr->e_shstrndx == SHN_UNDEF){
        return NULL;
    }
    
    return (char *)hdr + elf_section(hdr, hdr->e_shstrndx)->sh_offset;
}

static inline char *elf_lookup_string(Elf32_Ehdr *hdr, int offset){
    char *strtab = elf_str_table(hdr);
    
    if(strtab == NULL){
        return NULL;
    }
    
    return strtab + offset;
}

static int elf_get_symval(Elf32_Ehdr *hdr, int table, u32int index){
    if(table == SHN_UNDEF || index == SHN_UNDEF){
        return 0;
    }
    
    Elf32_Shdr *symtab = elf_section(hdr, table);
    
    if(index >= symtab->sh_size){
        ERROR("Symbol index out of range.");
        putch('\t');
        puts_decimal(table);
        putch(':');
        puts_hex(index);
    }
    
    int symaddr = (int) hdr + symtab->sh_offset;
    Elf32_Sym *symbol = &((Elf32_Sym *)symaddr)[index];
    
    if(symbol->st_shndx == SHN_UNDEF){
        // External symbol, lookup value
        Elf32_Shdr *strtab = elf_section(hdr, symtab->sh_link);
        const char *name = (const char*)hdr + strtab->sh_offset + symbol->st_name;
        
        extern void *elf_lookup_symbol(const char *name);
        void *target = elf_lookup_symbol(name);
        
        if(target == NULL){
            // Extern symbol not found
            if(ELF32_ST_BIND(symbol->st_info) & STB_WEAK){
                // Weak symbol initialized as 0
                return 0;
            }
            else{
                char *a = strcat("Undefined external symbol ", name);
                
                ERROR(a);
                
                return ELF_RELOC_ERR;
            }
        }
        else{
            return (int)target;
        }
    }
    else if(symbol->st_shndx == SHN_ABS){
        // Absolute symbol
        return symbol->st_value;
    }
    else{
        // Internally defined symbol
        Elf32_Shdr *target = elf_section(hdr, symbol->st_shndx);
        
        return (int)hdr + symbol->st_value + target->sh_offset;
    }
}

static int elf_load_stage1(Elf32_Ehdr *hdr){
    Elf32_Shdr *shdr = elf_sheader(hdr);
    
    unsigned int i;
    
    for(i = 0; i < hdr->e_shnum; i++){
        Elf32_Shdr *section = &shdr[i];
        
        // If the section isn't present in the file
        if(section->sh_type == SHT_NOBITS){
            // Skip it if the section is empty
            if(!section->sh_size){
                continue;
            }
            
            // If the section should appear in memory
            if(section->sh_flags & SHF_ALLOC){
                void *mem = malloc(section->sh_size);
                
                memset(mem, 0, section->sh_size);
                
                // Assign the memory offset to the section offset.
                section->sh_offset = (int)mem - (int) hdr;
                
                DEBUG("Allocated memory for a section.");
            }
        }
    }
    
    return 0;
}

static int elf_load_stage2(Elf32_Ehdr *hdr) {
	Elf32_Shdr *shdr = elf_sheader(hdr);
    
	unsigned int i, idx;
	// Iterate over section headers
	for(i = 0; i < hdr->e_shnum; i++) {
		Elf32_Shdr *section = &shdr[i];
        
		// If this is a relocation section
		if(section->sh_type == SHT_REL) {
			// Process each entry in the table
			for(idx = 0; idx < section->sh_size / section->sh_entsize; idx++) {
				Elf32_Rel *reltab = &((Elf32_Rel *)((int)hdr + section->sh_offset))[idx];
				int result = elf_do_reloc(hdr, reltab, section);
				// On error, display a message and return
				if(result == ELF_RELOC_ERR) {
					ERROR("Failed to relocate symbol.");
					return ELF_RELOC_ERR;
				}
			}
		}
	}
	return 0;
}

static int elf_do_reloc(Elf32_Ehdr *hdr, Elf32_Rel *rel, Elf32_Shdr *reltab) {
	Elf32_Shdr *target = elf_section(hdr, reltab->sh_info);
    
	int addr = (int)hdr + target->sh_offset;
	int *ref = (int *)(addr + rel->r_offset);
    
	// Symbol value
	int symval = 0;
    
	if(ELF32_R_SYM(rel->r_info) != SHN_UNDEF) {
		symval = elf_get_symval(hdr, reltab->sh_link, ELF32_R_SYM(rel->r_info));
		if(symval == ELF_RELOC_ERR) return ELF_RELOC_ERR;
	}    
    
    // Relocate based on type
	switch(ELF32_R_TYPE(rel->r_info)) {
		case R_386_NONE:
			// No relocation
			break;
		case R_386_32:
			// Symbol + Offset
			*ref = DO_386_32(symval, *ref);
			break;
		case R_386_PC32:
			// Symbol + Offset - Section Offset
			*ref = DO_386_PC32(symval, *ref, (int)ref);
			break;
		default:
			// Relocation type not supported, display error and return
			ERROR("Unsupported Relocation Type");
			return ELF_RELOC_ERR;
	}
    
	return symval;
}
