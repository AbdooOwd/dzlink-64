ROM_BASENAME = dzlink
ROM_FILENAME = $(ROM_BASENAME).z64

BUILD_DIR = ./build
SOURCE_DIR = ./src
ASSETS_DIR = ./assets
FILESYSTEM_DIR = ./filesystem

# programs
N64_EMULATOR = ares

C_SOURCES = $(shell find $(SOURCE_DIR) -name "*.c")
OBJ_FILES = $(C_SOURCES:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

# assets
assets_glb = $(shell find $(ASSETS_DIR) -name "*.glb")
assets_conv = $(assets_glb:$(ASSETS_DIR)/%.glb=$(FILESYSTEM_DIR)/%.t3dm)


include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk


all: build
build: $(ROM_FILENAME)

debug_echo:
	echo $(OBJ_FILES)
	echo $(assets_glb)
	echo $(assets_conv)

# ROM stuff
$(ROM_FILENAME): N64_ROM_TITLE = "DZ Link"
$(ROM_FILENAME): $(BUILD_DIR)/$(ROM_BASENAME).dfs
$(BUILD_DIR)/$(ROM_BASENAME).elf: $(OBJ_FILES)
$(BUILD_DIR)/$(ROM_BASENAME).dfs: $(assets_conv)

# filesystem & game data
$(FILESYSTEM_DIR)/%.t3dm: $(ASSETS_DIR)/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -o $(FILESYSTEM_DIR) $@


# helper rules

run: build
	$(N64_EMULATOR) $(ROM_FILENAME)

clean:
	rm $(ROM_FILENAME)
	rm -r $(BUILD_DIR)
	rm -r $(FILESYSTEM_DIR)

# TODO: what is dis???
-include $(wildcard $(BUILD_DIR)/*.d))

.PHONY: all build clean run
