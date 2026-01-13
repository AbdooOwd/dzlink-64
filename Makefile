ROM_BASENAME = dzlink
ROM_FILENAME = $(ROM_BASENAME).z64
BUILD_DIR = ./build
SOURCE_DIR = ./src

# programs
N64_EMULATOR = ares

C_SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
OBJ_FILES = $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))

all: build
.PHONY: all

build: $(ROM_FILENAME)
.PHONY: build

include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk

$(ROM_FILENAME): N64_ROM_TITLE = "DZ Link"

$(BUILD_DIR)/$(ROM_BASENAME).elf: $(OBJ_FILES)


run: build
	$(N64_EMULATOR) $(ROM_FILENAME)

clean:
	rm $(ROM_FILENAME)
	rm -r $(BUILD_DIR)
.PHONY: clean

# TODO: what is dis???
-include $(wildcard $(BUILD_DIR)/*.d))
