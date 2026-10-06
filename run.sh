#!/bin/bash
set -xue

QEMU=qemu-system-riscv32

# Path to clang and compiler flags
CC=clang  # Ubuntu users: use CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib"

OBJCOPY=/usr/bin/llvm-objcopy-21

# Build shell app
$CC $CFLAGS -Wl,-Tuser/user.ld -Wl,-Map=shell.map -o shell.elf user/shell.c user/user.c common/common.c
$OBJCOPY --set-section-flags .bss=alloc,contents -O binary shell.elf shell.bin
$OBJCOPY -Ibinary -Oelf32-littleriscv shell.bin user/shell.bin.o

# Build the kernel
$CC $CFLAGS -Wl,-Tkernel/kernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel/kernel.c \
    kernel/process.c \
    kernel/page.c \
    common/common.c \
    user/shell.bin.o

# Start QEMU
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
    -kernel kernel.elf