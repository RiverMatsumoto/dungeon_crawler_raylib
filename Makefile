# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug_x64
endif

ifndef verbose
  SILENT = @
endif

raylib_makefile = raylib-master/Makefile

ifeq ($(config),debug_x64)
  raylib_config = debug_x64
  game_premake_config = debug_x64

else ifeq ($(config),debug_x86)
  raylib_config = debug_x86
  game_premake_config = debug_x86

else ifeq ($(config),debug_arm64)
  raylib_config = debug_arm64
  game_premake_config = debug_arm64

else ifeq ($(config),release_x64)
  raylib_config = release_x64
  game_premake_config = release_x64

else ifeq ($(config),release_x86)
  raylib_config = release_x86
  game_premake_config = release_x86

else ifeq ($(config),release_arm64)
  raylib_config = release_arm64
  game_premake_config = release_arm64

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := raylib game-premake

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

raylib:
ifneq (,$(raylib_makefile))
	@cp ./raylibMakefile ./raylib-master/Makefile -f
endif
ifneq (,$(raylib_config))
	@echo "==== Downloading raylib ===="
	@git submodule update --init --recursive
	@echo "==== Building raylib ($(raylib_config)) ===="
	@${MAKE} --no-print-directory -C raylib-master -f Makefile config=$(raylib_config)
endif

game-premake: raylib
ifneq (,$(game_premake_config))
	@echo "==== Building game-premake ($(game_premake_config)) ===="
	@${MAKE} --no-print-directory -C game -f Makefile config=$(game_premake_config)
endif

clean:
	@${MAKE} --no-print-directory -C raylib-master -f Makefile clean
	@${MAKE} --no-print-directory -C game -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_x64"
	@echo "  debug_x86"
	@echo "  debug_arm64"
	@echo "  release_x64"
	@echo "  release_x86"
	@echo "  release_arm64"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   raylib"
	@echo "   game-premake"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"

run: all
	@echo Running game-premake
	./bin/Debug/game-premake.exe