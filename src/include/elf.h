/*
 *  elf.h
 *  Boom
 *
 *  Created by Walt Pach on 2/10/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __SYSTEM_ELF_H
#define __SYSTEM_ELF_H

#include <stdint.h>
#include <system.h>

#define ELF_NIDENT      16
#define ELFMAG0          0
#define ELFMAG1         'E'
#define ELFMAG2         'L'
#define ELFMAG3         'F'

#define ELFDATA2LSB     (1) // Little endian
#define ELFCLASS32      (1) // 32-Bit architecture.
#define EM_386          (3) // x86 Machine type
#define EV_CURRENT      (1) // ELF Current Version

#define SHN_UNDEF       (0x00)
#define ELF32_SY_BIND(INFO) ((INFO) >> 4)
#define ELF32_ST_TYPE(INFO) ((INFO) & 0x0F)
#define ELF32_R_SYM(INFO)	((INFO) >> 8)
#define ELF32_R_TYPE(INFO)	((u8int)(INFO))
#define DO_386_32(S, A)	((S) + (A))
#define DO_386_PC32(S, A, P)	((S) + (A) - (P))

#define ELF_RELOC_ERR -1

typedef struct {
	u8int       e_ident[ELF_NIDENT];
	Elf32_Half	e_type;
	Elf32_Half	e_machine;
	Elf32_Word	e_version;
	Elf32_Addr	e_entry;
	Elf32_Off	e_phoff;
	Elf32_Off	e_shoff;
	Elf32_Word	e_flags;
	Elf32_Half	e_ehsize;
	Elf32_Half	e_phentsize;
	Elf32_Half	e_phnum;
	Elf32_Half	e_shentsize;
	Elf32_Half	e_shnum;
	Elf32_Half	e_shstrndx;
} Elf32_Ehdr;

typedef struct{
    Elf32_Word  sh_name;
    Elf32_Word  sh_type;
    Elf32_Word  sh_flags;
    Elf32_Addr  sh_addr;
    Elf32_Off   sh_offset;
    Elf32_Word  sh_size;
    Elf32_Word  sh_link;
    Elf32_Word  sh_info;
    Elf32_Word  sh_addralign;
    Elf32_Word  sh_entsize;
} Elf32_Shdr;

typedef struct{
    Elf32_Word  st_name;
    Elf32_Addr  st_value;
    Elf32_Word  st_size;
    u8int       st_info;
    u8int       st_other;
    Elf32_Half  st_shndx;
} Elf32_Sym;

typedef struct {
	Elf32_Addr		r_offset;
	Elf32_Word		r_info;
} Elf32_Rel;

typedef struct {
	Elf32_Addr		r_offset;
	Elf32_Word		r_info;
	Elf32_Sword		r_addend;
} Elf32_Rela;

typedef struct {
	Elf32_Word		p_type;
	Elf32_Off		p_offset;
	Elf32_Addr		p_vaddr;
	Elf32_Addr		p_paddr;
	Elf32_Word		p_filesz;
	Elf32_Word		p_memsz;
	Elf32_Word		p_flags;
	Elf32_Word		p_align;
} Elf32_Phdr;

enum RtT_Types {
	R_386_NONE		= 0, // No relocation
	R_386_32		= 1, // Symbol + Offset
	R_386_PC32		= 2  // Symbol + Offset - Section Offset
};
enum Elf_Ident{
    EI_MAG0         = 0,  // 0x7F
    EI_MAG1         = 1,  // 'E'
    EI_MAG2         = 2,  // 'L'
    EI_MAG3         = 3,  // 'F'
    EI_CLASS        = 4,  // Architecture (32/64)
    EI_DATA         = 5,  // Byte order
    EI_VERSION      = 6,  // ELF Version
    EI_OSABI        = 7,  // OS Specific
    EI_ABIVERSION   = 8,  // OS Specific
    EI_PAD          = 9,  // Padding
};

enum Elf_Type{
    ET_NONE         = 0,    // Unknown Type
    ET_REL          = 1,    // Relocatable file
    ET_EXEC         = 2     // Executable file
};

enum ShT_Types{
    SHT_NULL        = 0,    // Null section
    SHT_PROGBITS    = 1,    // Program information
    SHT_SYMTAB      = 2,    // Symbol table
    SHT_STRTAB      = 3,    // String table
    SHT_RELA        = 4,    // Relocation (w/ addend)
    SHT_NOBITS      = 8,    // No present in file
    SHT_REL         = 9,    // Relocation (no addend)
};

enum ShT_Attributes{
    SHF_WRITE       = 0x01, // Writable section
    SHF_ALLOC       = 0x02 // Exists in memory
};

enum StT_Bindings{
    STB_LOCAL       = 0, // Local scope
    STB_GLOBAL      = 1, // Global scope
    STB_WEAK        = 2  // Weak, (ie. __attribute__((weak)))
};


enum StT_Types{
    STT_NOTYPE      = 0, // No type
    STT_OBJECT      = 1, // Variables, arrays, etc.
    STT_FUNC        = 2  // Methods or functions.
};


extern boolean elf_check_file(Elf32_Ehdr *hdr);
extern boolean elf_check_supported(Elf32_Ehdr *hdr);
extern void *elf_load_file(void *file);
static inline void *elf_load_rel(Elf32_Ehdr *hdr);
static inline Elf32_Shdr *elf_sheader(Elf32_Ehdr *hdr);
static inline Elf32_Shdr *elf_section(Elf32_Ehdr *hdr, int index);
static inline char *elf_str_table(Elf32_Ehdr *hdr);
static inline char *elf_lookup_string(Elf32_Ehdr *hdr, int offset);
static int elf_get_symval(Elf32_Ehdr *hdr, int table, u32int index);
static int elf_do_reloc(Elf32_Ehdr *hdr, Elf32_Rel *rel, Elf32_Shdr *reltab);
static int elf_load_stage1(Elf32_Ehdr *hdr);
static int elf_load_stage2(Elf32_Ehdr *hdr);

#endif