QEMU := qemu-system-i386
IMAGE := images/benos.img
BOOTLOADER := bootloader/build/boot.bin
KERNEL := kernel/build/kernel.bin

image: $(IMAGE)

$(IMAGE): build
	mkdir -p images
	dd if=/dev/zero of=$@ bs=512 count=2880
	mformat -i $@ -f 1440 -B $(BOOTLOADER) ::
	mcopy -i $@ $(KERNEL) ::

build:
	$(MAKE) -C bootloader
	$(MAKE) -C kernel

clean:
	$(MAKE) -C bootloader clean
	$(MAKE) -C kernel clean

clean-all: clean
	rm -rf images

run:
	$(QEMU) -drive format=raw,file=$(IMAGE),index=0,if=floppy

.PHONY: build image clean clean-all run