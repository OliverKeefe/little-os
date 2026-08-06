# Little OS
## A small operating system for RISC-V architecture
Little OS is a small, 32-bit operating system for RISC-V ("Reduced Instruction Set Computer Five") systems. In the future this will be expanded to 64-bit. 

You can read the RISC-V ISA specifications here:
[Ratified Specification](https://riscv.org/specifications/ratified/)

## Install Dependencies / Dev Tooling

### Ubuntu / Debian

```shell
sudo apt update -y && \
sudo apt install -y clang llvm lld qemu-system-riscv32 curl
```

OpenSBI

```shell
curl -LO https://github.com/qemu/qemu/raw/v8.0.4/pc-bios/opensbi-riscv32-generic-fw_dynamic.bin 
```
