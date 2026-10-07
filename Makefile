CROSS_COMPILE = aarch64-linux-gnu-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump

CFLAGS = -Wall -Wextra -ffreestanding -nostdlib -mgeneral-regs-only \
         -Iinclude -Iplatform/qemu_virt -MMD
LDFLAGS = -T kernel.ld -nostdlib

SOURCES_C   := $(shell find arch kernel platform/qemu_virt -name '*.c')
SOURCES_ASM := $(shell find arch kernel platform/qemu_virt -name '*.S')
OBJS        := $(SOURCES_C:.c=.o) $(SOURCES_ASM:.S=.o)

all: kernel.elf kernel.elf.dis

kernel.elf: $(OBJS) kernel.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

kernel.elf.dis: kernel.elf
	$(OBJDUMP) -d $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(OBJS:.o=.d)

run: kernel.elf
	qemu-system-aarch64 -M virt -cpu cortex-a72 -m 512M -nographic -kernel kernel.elf

debug: kernel.elf
	qemu-system-aarch64 -M virt -cpu cortex-a72 -m 512M -nographic -kernel kernel.elf -s -S

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) kernel.elf kernel.elf.dis

.PHONY: all clean run debug