MAKEFLAGS += --no-print-directory

QEMU       := qemu-system-i386
IMAGE      := images/benos.img
BOOTLOADER := bootloader/build/boot.bin
KERNEL     := kernel/build/kernel.bin

image: build
	@echo "Building image: $(IMAGE)"
	@mkdir -p images
	@dd if=/dev/zero of=$(IMAGE) bs=512 count=2880 status=none
	@mkfs.fat -F 12 -R 2 -r 224 -s 1 -f 2 -n BENOS $(IMAGE)
	@dd if=$(BOOTLOADER) of=$(IMAGE) bs=512 count=2 conv=notrunc status=none
	@mcopy -i $(IMAGE) $(KERNEL) ::
	@for file in base/* ; do \
		mcopy -i $(IMAGE) $$file :: ; \
	done
	@for file in programs/*/*.bin ; do \
		[ -e "$$file" ] || continue ; \
		mcopy -i $(IMAGE) "$$file" :: ; \
	done

build:
	@echo "Building bootloader..."
	@$(MAKE) -C bootloader
	@echo "Building kernel..."
	@$(MAKE) -C kernel

clean:
	@echo "Cleaning..."
	@$(MAKE) -C bootloader clean
	@$(MAKE) -C kernel clean

clean-all: clean
	@rm -rf images

run: image
	@echo "Running $(IMAGE) in $(QEMU)..."
	@$(QEMU) -drive format=raw,file=$(IMAGE),index=0,if=floppy

.PHONY: build image clean clean-all run