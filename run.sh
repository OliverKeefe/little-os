#!/bin/bash
set -xue

QEMU=qemu-system-riscv32

# Path to clang and compiler flags
CC=clang  # Ubuntu users: use CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib"

# Build the kernel
$CC $CFLAGS -Wl,-Tkernel/kernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel/kernel.c \
    kernel/process.c \
    common/common.c

# Start QEMU
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
    -kernel kernel.elf