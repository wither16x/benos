NASM := nasm
CC := wcc
LD := wlink

NASMFLAGS := -f obj
CFLAGS    := -0 -s -zl -zls -zq -os -d0 -zp1 -wx -za99 -Iinclude

ASM_SRC := $(shell find src -name '*.asm')
C_SRC   := $(shell find src -name '*.c')
HDRS    := $(shell find src -name '*.h')

ASM_OBJ := $(patsubst src/%.asm,build/%.obj,$(ASM_SRC))
C_OBJ   := $(patsubst src/%.c,build/%.obj,$(C_SRC))

START_OBJ := build/start.obj
OTHER_OBJ := $(filter-out $(START_OBJ),$(ASM_OBJ) $(C_OBJ))
OBJS      := $(START_OBJ) $(OTHER_OBJ)

comma := ,
empty :=
space := $(empty) $(empty)
FILES := $(subst $(space),$(comma),$(OBJS))

TARGET := build/kernel.bin

all: $(TARGET)

$(TARGET): $(OBJS) kernel.lnk
	@mkdir -p $(dir $@)
	@echo "$(LD) $@"
	@$(LD) @kernel.lnk name $@ option map=build/kernel.map file $(FILES)

build/%.obj: src/%.asm
	@mkdir -p $(dir $@)
	@echo "$(NASM) $<"
	@$(NASM) $(NASMFLAGS) -o $@ $<

build/%.obj: src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	@echo "$(CC) $<"
	@$(CC) $(CFLAGS) -fo=$@ $<

clean:
	@rm -rf build

.PHONY: all clean