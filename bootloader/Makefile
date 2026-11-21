NASM := nasm

NASMFLAGS := -f bin -Ilib

SRC := $(shell find src -name '*.asm')
BIN := $(patsubst src/%.asm,build/%.bin,$(SRC))

TARGET := build/boot.bin

all: $(TARGET)

$(TARGET): $(BIN)
	mkdir -p build
	cat $< > $@

build/%.bin: src/%.asm
	mkdir -p build
	$(NASM) $(NASMFLAGS) -o $@ $<

clean:
	rm -rf build

.PHONY: all clean