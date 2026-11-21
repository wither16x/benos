# Build

This is a guide on how to build BenOS.

## Steps

1. Install the required dependencies, which are `make` and `nasm`. If your package manager is APT, then you can run [`get-deps.sh`](/get-deps.sh)?
2. Build tbe image by running `make` from the root of the repository.
3. **(optional)** Run the image in qemu:
```sh
make run
```