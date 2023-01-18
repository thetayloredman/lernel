RM = rm
CP = cp
MKDIR = mkdir
LD = ld
AS = nasm
CC = gcc

CC_ARGS = -nostdinc -I. -m32 -Wno-builtin-declaration-mismatch -fno-stack-protector $(ADDITIONAL_CC_ARGS)
AS_ARGS = -f elf32 $(ADDITIONAL_AS_ARGS)
QEMU_MEM = 512
QEMU_ARGS = -m $(QEMU_MEM) $(ADDITIONAL_QEMU_ARGS)

BIN = lernel
ISO = lernel.iso
ISO_DIR = iso

.PHONY: all
all: lernel iso

%.o: %.asm
	$(AS) $(AS_ARGS) $^ -o $@

%.o: %.c
	$(CC) $(CC_ARGS) -c $^ -o $@

lernel: linker.ld boot.o main.o tty.o ports.o panic.o regs.o ksyms.o strings.o
	$(LD) -m elf_i386 -T linker.ld -o $(BIN) boot.o main.o tty.o ports.o panic.o regs.o ksyms.o strings.o

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

.PHONY: clean
clean:
	$(RM) -rf *.o $(BIN) $(BIN).map $(ISO_DIR) $(ISO)

.PHONY: format
format:
	./indent.sh
