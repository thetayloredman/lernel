RM = rm
CP = cp
MKDIR = mkdir
LD = ld
AS = nasm
CC = gcc

CC_ARGS = -nostdinc -I. -m32 -Wno-builtin-declaration-mismatch -fno-stack-protector -ffreestanding $(ADDITIONAL_CC_ARGS)
AS_ARGS = -f elf32 $(ADDITIONAL_AS_ARGS)
QEMU_MEM = 512
QEMU_ARGS = -m $(QEMU_MEM) $(ADDITIONAL_QEMU_ARGS)

# for debug targets
AS_GDB_ARGS = -F dwarf -g
CC_GDB_ARGS = -gdwarf
QEMU_GDB_ARGS = -S -s -d int

BIN = lernel
ISO = lernel.iso
ISO_DIR = iso

# NOTE: we run -iex "continue" twice. this is because GRUB seems to run at an address that matches
#       up with our _start function. if eventually this moves, remove the second -iex "continue".
GDB_AUTOSTART_ARGS = -iex "file ./$(BIN)" -iex "target remote localhost:1234" -iex "break _start" -iex "continue" -iex "continue"
QEMU_GDB_AUTOSTART_ARGS = -S -s

.PHONY: all
all: lernel iso

%.o: %.asm
	$(AS) $(AS_ARGS) $^ -o $@

%.o: %.c
	$(CC) $(CC_ARGS) -c $^ -o $@

lernel: linker.ld boot.o boot-virt.o main.o tty.o ports.o panic.o regs.o ksyms.o strings.o paging-utils.o paging.o
	$(LD) -m elf_i386 -T linker.ld -o $(BIN) boot.o boot-virt.o main.o tty.o ports.o panic.o regs.o ksyms.o strings.o paging-utils.o paging.o

iso: lernel lernel.map
	$(MKDIR) -p $(ISO_DIR)/boot/grub
	$(CP) $(BIN) $(ISO_DIR)/boot
	$(CP) $(BIN).map $(ISO_DIR)/boot
	$(CP) grub.cfg $(ISO_DIR)/boot/grub
	grub-file --is-x86-multiboot $(ISO_DIR)/boot/$(BIN)
	grub-mkrescue -o $(ISO) $(ISO_DIR)

lernel.map: lernel
	nm $(BIN) > $(BIN).map

.PHONY: run
run: iso
	qemu-system-i386 -cdrom $(ISO) $(QEMU_ARGS)

.PHONY: run-gdb
run-gdb: AS_ARGS+=$(AS_GDB_ARGS)
run-gdb: CC_ARGS+=$(CC_GDB_ARGS)
run-gdb: QEMU_ARGS+=$(QEMU_GDB_ARGS)
run-gdb: iso run

.PHONY: run-gdb-open
run-gdb-open: AS_ARGS+=$(AS_GDB_ARGS)
run-gdb-open: CC_ARGS+=$(CC_GDB_ARGS)
run-gdb-open: iso
run-gdb-open:
	bash -c "trap 'trap - SIGINT SIGTERM ERR EXIT; kill 0' SIGINT SIGTERM ERR EXIT; $(MAKE) run-gdb-open-notrap"
.PHONY: run-gdb-open-notrap
run-gdb-open-notrap:
	(qemu-system-i386 -cdrom $(ISO) $(QEMU_ARGS) $(QEMU_GDB_AUTOSTART_ARGS) &)
	gdb $(GDB_AUTOSTART_ARGS)

.PHONY: clean
clean:
	$(RM) -rf *.o $(BIN) $(BIN).map $(ISO_DIR) $(ISO)

.PHONY: format
format:
	./indent.sh
