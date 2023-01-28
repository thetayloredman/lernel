-par -bad -bap -bbb -sc -br -ce -cdw -slc -npcs -nss -ncs -nbc -brs -brf -sar
-nut -i4 -lp -ppi3 -bbo -hnl -gts -npsl -c0 -d0 -cd0 -cp0

// TODO: Make a possible system to extract typedefs?
// The current method: find . -type f | xargs grep typedef
-T elf32_shdr_t
-T elf32_sym_t
-T multiboot_uint8_t
-T multiboot_uint16_t
-T multiboot_uint32_t
-T multiboot_uint64_t
-T multiboot_aout_symbol_table_t
-T multiboot_elf_section_header_table_t
-T multiboot_info_t
-T multiboot_memory_map_t
-T multiboot_module_t
-T cpu_registers_t
-T uint8_t
-T uint16_t
-T uint32_t
-T int8_t
-T int16_t
-T int32_t
-T uintptr_t
-T page_directory_entry_32_t
-T page_table_entry_32_t