# Build

This is a guide on how to build BenOS.

## Build a disk image

Required dependencies:
* nasm
* make
* wcc
* wlink

In order to compile the bootloader, the kernel and build a disk image, you must run the Makefile at the root of the repository using `make`. It should compile the bootloader and the kernel and create a disk image in `images/`.  

## Build programs

There are pre-made programs in `programs/` which are meant to be integrated to the disk image. You must build them before building the disk image. Run

```sh
make -C programs
```