# CustomOS

A bare-metal ARM64 kernel from scratch — built for QEMU virt emulation, targeting Raspberry Pi 4.

## Prerequisites

```
sudo pacman -S qemu-system-aarch64 aarch64-linux-gnu-gcc aarch64-linux-gnu-binutils make
```

## Project structure

```
CustomOS/
├── Makefile                     # Build targets (see below)
├── kernel.ld                    # Linker script — links at 0x40080000
├── run.sh                       # QEMU launch script (optional)
├── kernel/
│   ├── main.c                   # kernel_main() — entry point in C
│   ├── scheduler.c              # (you fill in)
│   ├── memory.c                 # (you fill in)
│   ├── process.c                # (you fill in)
│   ├── syscall.c                # (you fill in)
│   └── vfs.c                    # (you fill in)
├── arch/aarch64/
│   ├── boot.S                   # Bootstrap: EL3 → EL2 → EL1, stack, BSS zero
│   ├── exceptions.S             # (you fill in)
│   ├── mmu.c                    # (you fill in)
│   └── context_switch.S         # (you fill in)
├── platform/
│   ├── qemu_virt/               # QEMU virt machine drivers
│   │   ├── uart.c               # PL011 UART — putc, puts, getc, puthex
│   │   └── platform.h           # MMIO base addresses (UART at 0x09000000)
│   └── raspberrypi4/            # Raspberry Pi 4 drivers (you fill in)
│       ├── uart.c
│       ├── interrupt_controller.c
│       └── timer.c
└── include/
    └── kernel.h                 # Shared declarations
```

## How to build

```bash
make                           # Build kernel.elf + disassembly
make clean                     # Remove all build artifacts
```

## How to run in QEMU

```bash
make run
```

This launches:
```
qemu-system-aarch64 -M virt -cpu cortex-a72 -m 512M -nographic -kernel kernel.elf
```

- `-M virt`       — QEMU's generic ARM64 virtual machine
- `-cpu cortex-a72` — ARM Cortex-A72 (same CPU family as Pi 4)
- `-m 512M`       — 512 MB of RAM
- `-nographic`     — serial console on your terminal (no GUI window)
- `-kernel kernel.elf` — loads your ELF and jumps to its entry point

### To exit QEMU

Press `Ctrl-A` then `x`.

## How to debug with GDB

```bash
make debug
```

QEMU will wait for a GDB connection on port 1234 (`-s -S`). In another terminal:

```bash
aarch64-linux-gnu-gdb kernel.elf
(gdb) target remote :1234
(gdb) break kernel_main
(gdb) continue
```

## Boot flow

```
QEMU loads kernel.elf at 0x40080000
        │
        ▼
  boot.S  (_start)
        │
        ├── EL3? → set SCR_EL3, drop to EL2
        ├── EL2? → set HCR_EL2, drop to EL1
        └── EL1  → set stack pointer, zero BSS
                    │
                    ▼
              bl kernel_main   (kernel/main.c)
                    │
                    ▼
              uart_puts("Hello from EL1!")
                    │
                    ▼
              for (;;)   (wait forever)
```

## Porting to Raspberry Pi 4

### Differences from QEMU virt

| Component | QEMU virt | Raspberry Pi 4 |
|---|---|---|
| UART base | `0x09000000` (PL011) | `0xFE201000` (PL011) or `0xFE215000` (mini UART) |
| Interrupt controller | GICv2/v3 at `0x08000000` | BCM2711 custom |
| Boot method | QEMU loads ELF | VideoCore GPU loads `kernel8.img` |
| Kernel image format | ELF | raw binary with Linux boot header |

### Steps

1. Add `platform/raspberrypi4/` with the correct MMIO addresses
2. Add a `platform.h` that maps to Pi 4's memory layout
3. Add a build target that outputs a raw binary:
   ```
   aarch64-linux-gnu-objcopy -O binary kernel.elf kernel8.img
   ```
4. Place `kernel8.img` on a FAT32 SD card with a `config.txt` containing:
   ```
   arm_64bit=1
   kernel=kernel8.img
   ```

## Architecture notes

- **Exception levels**: EL1 (kernel), EL0 (user processes when implemented)
- **UART**: PL011, polling mode (no interrupts yet)
- **Stack**: 64 KB at `__stack_top` (just after BSS)
- **MMU**: off (flat mapping with device memory when enabled)
- **Build flags**: `-ffreestanding -nostdlib -mgeneral-regs-only`