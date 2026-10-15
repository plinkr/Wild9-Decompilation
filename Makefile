SHELL := /usr/bin/env bash

PYTHON ?= python3
VENV ?= .venv
PY := $(VENV)/bin/python
PIP := $(PY) -m pip

ROOT := $(CURDIR)
SELF_MAKEFILE := $(firstword $(MAKEFILE_LIST))

TARGET := iso/us/SLUS_004.25

CONFIG_DIR := config/slus_004.25
CONFIG := $(CONFIG_DIR)/splat.yaml

SYMBOLS := symbols/slus_004.25.txt
RELOCS := symbols/slus_004.25.relocs.txt

BUILD := build
ASM_BUILD := $(BUILD)/asm
DATA_BUILD := $(ASM_BUILD)/data
SRC_BUILD := $(BUILD)/src
FUNCTION_BUILD := $(BUILD)/functions

ELF := $(BUILD)/slus_004.25.elf
BIN := $(BUILD)/SLUS_004.25
MAP := $(BUILD)/slus_004.25.map

ORIGINAL_ELF := $(BUILD)/slus_004.25.original.elf
ORIGINAL_BIN := $(BUILD)/SLUS_004.25.original
ORIGINAL_LD_SCRIPT := $(BUILD)/slus_004.25.original.ld

UNDEF_FUNCS := undefined_funcs_auto.txt
UNDEF_SYMS := undefined_syms_auto.txt

HEADER_SRC := asm/header.s
MAIN_ASM_SRC := asm/800.s
NONMATCH_DIR := asm/nonmatchings/main
MAIN_ASM_INCLUDES := $(wildcard $(NONMATCH_DIR)/*.s)
DATA_SRCS := $(wildcard asm/data/*.s)

HEADER_OBJ := $(ASM_BUILD)/header.o
MAIN_ASM_OBJ := $(ASM_BUILD)/800.o
DATA_OBJS := $(patsubst asm/data/%.s,$(DATA_BUILD)/%.o,$(DATA_SRCS))

MAIN_C := src/main.c
MAIN_C_DEPS := $(MAIN_C) $(wildcard src/functions/*.c) $(wildcard include/*.h)

MAIN_I := $(SRC_BUILD)/main.i
MAIN_GCC_S := $(SRC_BUILD)/main.gcc.s
MAIN_MASPSX_S := $(SRC_BUILD)/main.s
MAIN_O := $(SRC_BUILD)/main.o

FUNCTION ?=
FUNCTION_C := src/functions/$(FUNCTION).c
FUNCTION_SRC_DIR := src/functions
PROTOTYPE_HEADERS := include/functions.h
FUNCTION_BIN := $(FUNCTION_BUILD)/$(FUNCTION).bin

ASPSX_VERSION := 2.77
SMALL_DATA_LIMIT := 8

SPLAT_STAMP := $(BUILD)/.splat.stamp
SPLIT_STAMP := $(BUILD)/.split-functions.stamp

# ---------------------------------------------------------------------------
# Toolchain: GCC 2.8.1 PSX and binutils 2.42, both extracted in-tree
# ---------------------------------------------------------------------------
TOOLCHAIN_DIR := tools/toolchain
GCC_DIR       := $(TOOLCHAIN_DIR)/gcc-2.8.1-psx
BINUTILS_DIR  := $(TOOLCHAIN_DIR)/binutils-2.42

GCC_STAMP      := $(TOOLCHAIN_DIR)/.gcc-2.8.1-psx.stamp
BINUTILS_STAMP := $(TOOLCHAIN_DIR)/.binutils-2.42.stamp
TOOLCHAIN_STAMPS := $(GCC_STAMP) $(BINUTILS_STAMP)

BINUTILS_USR_BIN := $(CURDIR)/$(BINUTILS_DIR)/usr/bin
BINUTILS_USR_LIB := $(CURDIR)/$(BINUTILS_DIR)/usr/lib/x86_64-linux-gnu
BINUTILS_RT_LIB  := $(CURDIR)/$(BINUTILS_DIR)/runtime/usr/lib/x86_64-linux-gnu

# Make the private binutils visible to every recipe, so the build works even
# when scripts/binutils-env.sh has not been sourced in the current shell.
export PATH := $(BINUTILS_USR_BIN):$(PATH)
export LD_LIBRARY_PATH := $(BINUTILS_USR_LIB):$(BINUTILS_RT_LIB):$(LD_LIBRARY_PATH)

CC := $(GCC_DIR)/gcc
CPP := $(GCC_DIR)/cpp
MASPSX := $(PY) tools/maspsx/maspsx.py

AS := mipsel-linux-gnu-as
LD := mipsel-linux-gnu-ld
OBJCOPY := mipsel-linux-gnu-objcopy
CLANG_FORMAT ?= clang-format
NM := mipsel-linux-gnu-nm

ASFLAGS := \
	-EL \
	-march=r3000 \
	-mtune=r3000 \
	-no-pad-sections \
	-O1 \
	-G0 \
	-Iinclude

CCFLAGS := \
	-g0 \
	-O2 \
	-G$(SMALL_DATA_LIMIT) \
	-B$(GCC_DIR)/

FUNCTION_CCFLAGS := \
	-g0 \
	-O2 \
	-G$(SMALL_DATA_LIMIT) \
	-B$(GCC_DIR)/

CPPFLAGS := \
	-P \
	-Iinclude

MASPSXFLAGS := \
	--aspsx-version=$(ASPSX_VERSION) \
	-G$(SMALL_DATA_LIMIT)

ORIGINAL_LDFLAGS := \
	-EL \
	-nostdlib \
	--no-check-sections \
	-T $(ORIGINAL_LD_SCRIPT) \
	-T $(UNDEF_SYMS) \
	-T $(UNDEF_FUNCS) \
	-Map $(BUILD)/slus_004.25.original.map

.PHONY: \
	all \
	help \
	venv \
	install \
	tools \
	toolchain \
	check-toolchain \
	versions \
	info \
	fingerprint \
	verify-input \
	create-config \
	split \
	split-functions \
	prepare \
	generate-includes \
	asm \
	c \
	match \
	check-prototypes \
	promote \
	format \
	original-verify \
	link \
	build \
	verify \
	clean \
	distclean \
	sort-declarations \
	objdiff-targets \
	objdiff-targets-after-split \
	objdiff-base \
	objdiff-config \
	objdiff-report

.DEFAULT_GOAL := all

# Splat outputs and per-function .s files are used through $(wildcard) below,
# which is evaluated at parse time. When either is missing, run prepare first
# and re-invoke make so a fresh parse sees the generated files.
ifeq ($(SPLAT_BOOTSTRAPPED),)
ifneq ($(and $(wildcard $(SPLAT_STAMP)),$(wildcard $(SPLIT_STAMP))),)
all: $(TOOLCHAIN_STAMPS) build
else
all: $(TOOLCHAIN_STAMPS)
	@$(MAKE) --no-print-directory prepare
	@$(MAKE) --no-print-directory SPLAT_BOOTSTRAPPED=1 all
endif
else
all: $(TOOLCHAIN_STAMPS) build
endif

help:
	@printf '%s\n' \
		'make venv              Create the local Python virtual environment' \
		'make install           Install pinned Python dependencies' \
		'make tools             Initialize the Git submodules' \
		'make toolchain         Install GCC 2.8.1 PSX and binutils 2.42 in-tree' \
		'make check-toolchain   Report whether the in-tree toolchain is present' \
		'make versions          Print Python/splat/spimdisasm versions' \
		'make info              Inspect SLUS_004.25 and print PS-X EXE header fields' \
		'make fingerprint       Record SHA-1/SHA-256 of the local executable' \
		'make verify-input      Verify that the local SLUS_004.25 exists' \
		'make create-config     Generate and normalize the initial Splat config' \
		'make split             Run Splat and regenerate per-function ASM' \
		'make split-functions   Regenerate asm/nonmatchings/main/ from asm/800.s' \
		'make prepare           Generate Splat and split outputs when needed' \
		'make generate-includes Regenerate src/main.c INCLUDE_ASM stubs' \
		'make asm               Assemble header/800/data objects' \
		'make c                 Build src/main.c -> main.o' \
		'make format            Format C/H files and add the AGPL SPDX header' \
		'make match FUNCTION=func_XXXXXXXX  Build and compare one function' \
		'make check-prototypes  Verify header prototypes against C definitions' \
		'make promote FUNCTION=func_XXXXXXXX Replace matching ASM with C' \
		'make original-verify   Build the all-assembly reference and compare it' \
		'make link              Link the canonical all-assembly ELF' \
		'make build             Build final SLUS_004.25 binary' \
		'make verify            Compare build/SLUS_004.25 with the original' \
		'make clean             Remove generated build files' \
		'make distclean         Remove generated build files and the virtualenv'

venv:
	@test -x "$(PY)" || "$(PYTHON)" -m venv "$(VENV)"

install: venv
	$(PIP) install --upgrade pip
	$(PIP) install -r requirements.txt

tools:
	git submodule update --init --recursive

# ---------------------------------------------------------------------------
# GCC 2.8.1 PSX (decompals/old-gcc release 0.17, precompiled)
# ---------------------------------------------------------------------------
$(GCC_STAMP):
	@set -e; \
	if [ -x "$(GCC_DIR)/cc1" ] && [ -x "$(GCC_DIR)/gcc" ]; then \
		echo "GCC 2.8.1 PSX already installed at $(GCC_DIR); skipping download."; \
		touch "$@"; \
		exit 0; \
	fi; \
	mkdir -p "$(TOOLCHAIN_DIR)"; \
	URL="https://github.com/decompals/old-gcc/releases/download/0.17/gcc-2.8.1-psx.tar.gz"; \
	SHA256="f6f6e883942d4d3289d048236c672e71ed410e546aaae8ff655952f1567e1be0"; \
	TMP_DIR="$$(mktemp -d)"; \
	ARCHIVE="$$TMP_DIR/gcc-2.8.1-psx.tar.gz"; \
	trap 'rm -rf "$$TMP_DIR"' EXIT; \
	echo "== Installing GCC 2.8.1 PSX =="; \
	curl -fL "$$URL" -o "$$ARCHIVE"; \
	echo "$$SHA256  $$ARCHIVE" | sha256sum -c -; \
	rm -rf "$(GCC_DIR)"; \
	mkdir -p "$(GCC_DIR)"; \
	tar -xzf "$$ARCHIVE" -C "$(GCC_DIR)" --strip-components=1; \
	test -x "$(GCC_DIR)/cc1"; \
	echo "GCC 2.8.1 PSX installed at $(GCC_DIR)"; \
	touch "$@"

# ---------------------------------------------------------------------------
# binutils 2.42 (Ubuntu Noble amd64 .deb, extracted in-tree)
# ---------------------------------------------------------------------------
$(BINUTILS_STAMP):
	@set -e; \
	if [ -x "$(BINUTILS_DIR)/usr/bin/mipsel-linux-gnu-as" ] \
	   && [ -x "$(BINUTILS_DIR)/usr/bin/mipsel-linux-gnu-ld" ] \
	   && [ -f "$(BINUTILS_DIR)/runtime/usr/lib/x86_64-linux-gnu/libsframe.so.1" ]; then \
		echo "binutils 2.42 already installed at $(BINUTILS_DIR); skipping download."; \
		touch "$@"; \
		exit 0; \
	fi; \
	mkdir -p "$(TOOLCHAIN_DIR)/distfiles"; \
	BINUTILS_DEB="$(CURDIR)/$(TOOLCHAIN_DIR)/distfiles/binutils-mipsel-linux-gnu_2.42-2ubuntu1cross5_amd64.deb"; \
	LIBSFRAME_DEB="$(CURDIR)/$(TOOLCHAIN_DIR)/distfiles/libsframe1_2.42_amd64.deb"; \
	echo "== Installing binutils 2.42 =="; \
	curl -L --fail -o "$$BINUTILS_DEB" \
		"https://archive.ubuntu.com/ubuntu/pool/universe/b/binutils-mipsen/binutils-mipsel-linux-gnu_2.42-2ubuntu1cross5_amd64.deb"; \
	curl -L --fail -o "$$LIBSFRAME_DEB" \
		"https://archive.ubuntu.com/ubuntu/pool/main/b/binutils/libsframe1_2.42-4ubuntu2.10_amd64.deb"; \
	rm -rf "$(BINUTILS_DIR)"; \
	mkdir -p "$(BINUTILS_DIR)"; \
	( cd "$(BINUTILS_DIR)" && ar x "$$BINUTILS_DEB" ); \
	tar --zstd -xf "$(BINUTILS_DIR)/data.tar.zst" -C "$(BINUTILS_DIR)"; \
	rm -f "$(BINUTILS_DIR)/data.tar.zst" "$(BINUTILS_DIR)/control.tar.zst" "$(BINUTILS_DIR)/debian-binary"; \
	mkdir -p "$(BINUTILS_DIR)/runtime"; \
	( cd "$(BINUTILS_DIR)/runtime" && ar x "$$LIBSFRAME_DEB" ); \
	tar --zstd -xf "$(BINUTILS_DIR)/runtime/data.tar.zst" -C "$(BINUTILS_DIR)/runtime"; \
	rm -f "$(BINUTILS_DIR)/runtime/data.tar.zst" "$(BINUTILS_DIR)/runtime/control.tar.zst" "$(BINUTILS_DIR)/runtime/debian-binary"; \
	test -x "$(BINUTILS_DIR)/usr/bin/mipsel-linux-gnu-as"; \
	test -x "$(BINUTILS_DIR)/usr/bin/mipsel-linux-gnu-ld"; \
	test -f "$(BINUTILS_DIR)/runtime/usr/lib/x86_64-linux-gnu/libsframe.so.1"; \
	echo "binutils 2.42 installed at $(BINUTILS_DIR)"; \
	touch "$@"

toolchain: $(TOOLCHAIN_STAMPS)

check-toolchain:
	@echo "== Toolchain status =="
	@if [ -x "$(GCC_DIR)/cc1" ] && [ -x "$(GCC_DIR)/gcc" ]; then \
		echo "  GCC 2.8.1 PSX   : present  ($(GCC_DIR))"; \
	else \
		echo "  GCC 2.8.1 PSX   : missing"; \
	fi
	@if [ -x "$(BINUTILS_DIR)/usr/bin/mipsel-linux-gnu-as" ] \
	   && [ -x "$(BINUTILS_DIR)/usr/bin/mipsel-linux-gnu-ld" ]; then \
		echo "  binutils 2.42   : present  ($(BINUTILS_DIR))"; \
	else \
		echo "  binutils 2.42   : missing"; \
	fi
	@if [ -f "$(GCC_STAMP)" ]; then \
		echo "  GCC stamp       : $(GCC_STAMP)"; \
	else \
		echo "  GCC stamp       : absent"; \
	fi
	@if [ -f "$(BINUTILS_STAMP)" ]; then \
		echo "  binutils stamp  : $(BINUTILS_STAMP)"; \
	else \
		echo "  binutils stamp  : absent"; \
	fi

versions: install
	$(PY) --version
	$(PY) -c 'import splat, spimdisasm; print("splat:", splat.__version__); print("spimdisasm:", spimdisasm.__version__)'

verify-input:
	@test -f "$(TARGET)" || { \
		echo "Missing $(TARGET)" >&2; \
		echo "Put your extracted Wild 9 SLUS_004.25 under $(TARGET)." >&2; \
		exit 1; \
	}

info: verify-input
	$(PY) scripts/inspect_psx_exe.py "$(TARGET)"

fingerprint: verify-input
	@mkdir -p "$(CONFIG_DIR)"
	@sha1sum "$(TARGET)" | cut -d" " -f1 > "$(CONFIG_DIR)/SLUS_004.25.sha1"
	@sha256sum "$(TARGET)" | cut -d" " -f1 > "$(CONFIG_DIR)/SLUS_004.25.sha256"
	@echo "Wrote $(CONFIG_DIR)/SLUS_004.25.sha1"
	@echo "Wrote $(CONFIG_DIR)/SLUS_004.25.sha256"

create-config: verify-input install
	@set -e; \
	mkdir -p "$(ROOT)/build"; \
	tmpdir="$$(mktemp -d "$(ROOT)/build/splat-config.XXXXXX")"; \
	trap 'rm -rf "$$tmpdir"' EXIT; \
	(cd "$$tmpdir" && "$(ROOT)/$(PY)" -m splat create_config "$(ROOT)/$(TARGET)"); \
	generated="$$(find "$$tmpdir" -maxdepth 1 -name '*.yaml' -print -quit)"; \
	test -n "$$generated"; \
	mkdir -p "$(CONFIG_DIR)" symbols; \
	cp "$$generated" "$(CONFIG)"; \
	if [ -f "$$tmpdir/symbol_addrs.txt" ]; then cp "$$tmpdir/symbol_addrs.txt" "$(SYMBOLS)"; fi; \
	if [ -f "$$tmpdir/reloc_addrs.txt" ]; then cp "$$tmpdir/reloc_addrs.txt" "$(RELOCS)"; fi; \
	"$(PY)" scripts/normalize_splat_config.py "$(CONFIG)" "$(CONFIG)" "$(SYMBOLS)" "$(RELOCS)" "$(TARGET)"; \
	echo; \
	echo "Review $(CONFIG), $(SYMBOLS), and $(RELOCS) before committing."

$(SPLAT_STAMP): $(CONFIG) | verify-input
	@test -x "$(PY)" || { \
		echo "Missing Python environment: $(PY)" >&2; \
		echo "Run 'make install' first." >&2; \
		exit 1; \
	}
	@mkdir -p "$(BUILD)"
	$(PY) -m splat split "$(CONFIG)"
	@perl -0pi -e \
		's{(build/asm/800\.o\(\.text\);\n)[[:space:]]*\. = ALIGN\(\., 16\);\n}{$$1}' \
		linker/slus_004.25.ld
	cp "linker/slus_004.25.ld" "$(ORIGINAL_LD_SCRIPT)"
	@touch "$@"

$(ORIGINAL_LD_SCRIPT): $(SPLAT_STAMP)

# asm/800.s and asm/header.s are side effects of $(SPLAT_STAMP); the recipe
# only fails loudly when someone deletes the .s but keeps the stamp.
$(HEADER_SRC) $(MAIN_ASM_SRC): $(SPLAT_STAMP)
	@test -f "$@" || { \
		echo "Missing $@; run 'make clean && make' to regenerate." >&2; \
		exit 1; \
	}

$(SPLIT_STAMP): $(MAIN_ASM_SRC) scripts/split_800_functions.py
	@mkdir -p "$(BUILD)"
	@rm -rf "$(NONMATCH_DIR)"
	$(PY) scripts/split_800_functions.py "$(MAIN_ASM_SRC)" "$(NONMATCH_DIR)"
	@touch "$@"

# Same side-effect pattern as above, for the per-function .s files.
$(NONMATCH_DIR)/%.s: $(SPLIT_STAMP)
	@test -f "$@" || { \
		echo "Missing $@; run 'make split-functions' to regenerate." >&2; \
		exit 1; \
	}

prepare: $(SPLAT_STAMP) $(SPLIT_STAMP)

split: verify-input install $(CONFIG)
	@$(MAKE) --no-print-directory prepare

split-functions: $(SPLIT_STAMP)

# main.c is hand-maintained after promotion, so this is opt-in only.
generate-includes: $(MAIN_ASM_SRC) scripts/generate_include_asm.py
	$(PY) scripts/generate_include_asm.py "$(MAIN_ASM_SRC)" "$(MAIN_C)"

$(HEADER_OBJ): $(HEADER_SRC) $(SPLAT_STAMP) | $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(AS) $(ASFLAGS) "$<" -o "$@"

$(MAIN_ASM_OBJ): $(MAIN_ASM_SRC) $(SPLAT_STAMP) | $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(AS) $(ASFLAGS) "$<" -o "$@"

$(DATA_BUILD)/%.o: asm/data/%.s $(SPLAT_STAMP) | $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(AS) $(ASFLAGS) "$<" -o "$@"

asm: $(HEADER_OBJ) $(MAIN_ASM_OBJ) $(DATA_OBJS)

$(MAIN_I): $(MAIN_C_DEPS) | $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(CPP) $(CPPFLAGS) "$(MAIN_C)" -o "$@"

$(MAIN_GCC_S): $(MAIN_I) | $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(CC) $(CCFLAGS) -S "$<" -o "$@"

$(MAIN_MASPSX_S): \
	$(MAIN_GCC_S) \
	$(MAIN_ASM_SRC) \
	$(MAIN_ASM_INCLUDES) \
	$(SPLAT_STAMP) \
	$(SPLIT_STAMP) \
	scripts/prepare_main_asm.py \
	| $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(PY) scripts/prepare_main_asm.py \
		--gcc-asm "$<" \
		--reference-asm "$(MAIN_ASM_SRC)" \
		--output "$@" \
		--maspsx "$(ROOT)/tools/maspsx/maspsx.py" \
		--aspsx-version "$(ASPSX_VERSION)" \
		--small-data-limit "$(SMALL_DATA_LIMIT)" \
		--expand-div

$(MAIN_O): $(MAIN_MASPSX_S) | $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(AS) $(ASFLAGS) "$<" -o "$@"

c: $(MAIN_O)

$(FUNCTION_BUILD)/%.i: src/functions/%.c | $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(CPP) $(CPPFLAGS) "$<" -o "$@"

$(FUNCTION_BUILD)/%.gcc.s: $(FUNCTION_BUILD)/%.i | $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(CC) $(FUNCTION_CCFLAGS) -S "$<" -o "$@"

$(FUNCTION_BUILD)/%.s: \
	$(FUNCTION_BUILD)/%.gcc.s \
	$(MAIN_ASM_SRC) \
	$(SPLAT_STAMP) \
	scripts/prepare_function_asm.py \
	| $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(PY) scripts/prepare_function_asm.py \
		--gcc-asm "$<" \
		--reference-asm "$(MAIN_ASM_SRC)" \
		--function "$*" \
		--output "$@" \
		--maspsx "$(ROOT)/tools/maspsx/maspsx.py" \
		--aspsx-version "$(ASPSX_VERSION)" \
		--small-data-limit "$(SMALL_DATA_LIMIT)" \
		--expand-div

$(FUNCTION_BUILD)/%.o: $(FUNCTION_BUILD)/%.s | $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(AS) $(ASFLAGS) "$<" -o "$@"

$(FUNCTION_BUILD)/%.bin: \
	$(FUNCTION_BUILD)/%.o \
	$(ORIGINAL_ELF) \
	scripts/link_function.py \
	$(ORIGINAL_LD_SCRIPT) \
	| $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(PY) scripts/link_function.py \
		"$*" \
		"$<" \
		"$(ORIGINAL_ELF)" \
		"$(ORIGINAL_LD_SCRIPT)" \
		"$@"

match:
	@test -n "$(FUNCTION)" || { \
		echo "Usage: make match FUNCTION=func_800101A4" >&2; \
		exit 1; \
	}
	@test -f "$(FUNCTION_C)" || { \
		echo "Missing $(FUNCTION_C)" >&2; \
		echo "Create the decompiled function as a standalone C file." >&2; \
		exit 1; \
	}
	@$(MAKE) --no-print-directory "$(FUNCTION_BIN)"
	$(PY) scripts/match_function.py \
		"$(FUNCTION)" \
		"$(TARGET)" \
		"$(ORIGINAL_ELF)" \
		"$(FUNCTION_BIN)"

check-prototypes:
	$(PY) scripts/check_prototypes.py \
		--header "$(PROTOTYPE_HEADERS)" \
		--source-dir "$(FUNCTION_SRC_DIR)" \
		--main-c "$(MAIN_C)"

promote:
	@test -n "$(FUNCTION)" || { \
		echo "Usage: make promote FUNCTION=func_800101A4" >&2; \
		exit 1; \
	}
	@test -f "$(FUNCTION_C)" || { \
		echo "Missing $(FUNCTION_C)" >&2; \
		exit 1; \
	}
	@set -e; \
	$(MAKE) --no-print-directory match FUNCTION="$(FUNCTION)"; \
	backup="$(BUILD)/main.c.promote-backup"; \
	mkdir -p "$(BUILD)"; \
	cp "$(MAIN_C)" "$$backup"; \
	trap 'cp "$$backup" "$(MAIN_C)"; rm -f "$$backup"' EXIT HUP INT TERM; \
	$(PY) scripts/promote_function.py "$(MAIN_C)" "$(FUNCTION)"; \
	$(MAKE) --no-print-directory check-prototypes; \
	$(MAKE) --no-print-directory c; \
	$(MAKE) --no-print-directory build; \
	$(MAKE) --no-print-directory verify; \
	$(MAKE) --no-print-directory objdiff-report; \
	trap - EXIT HUP INT TERM; \
	rm -f "$$backup"

format:
	@command -v "$(CLANG_FORMAT)" >/dev/null || { \
		echo "Missing clang-format" >&2; \
		exit 1; \
	}
	@set -e; \
	find src include -type f \( -name '*.c' -o -name '*.h' \) -print0 | \
	while IFS= read -r -d '' file; do \
		tmp="$$(mktemp)"; \
		if [ "$$(sed -n '1p' "$$file")" != "// SPDX-License-Identifier: AGPL-3.0-or-later" ]; then \
			printf '%s\n\n' '// SPDX-License-Identifier: AGPL-3.0-or-later' > "$$tmp"; \
			cat "$$file" >> "$$tmp"; \
			mv "$$tmp" "$$file"; \
		else \
			rm -f "$$tmp"; \
		fi; \
	done
	@find src include -type f \( -name '*.c' -o -name '*.h' \) -print0 | \
		xargs -0 "$(CLANG_FORMAT)" --style=file -i
	$(PYTHON) scripts/sort_declarations.py include/functions.h include/globals.h

sort-declarations:
	$(PYTHON) scripts/sort_declarations.py include/functions.h include/globals.h

$(ORIGINAL_ELF): \
	$(HEADER_OBJ) \
	$(MAIN_ASM_OBJ) \
	$(DATA_OBJS) \
	$(ORIGINAL_LD_SCRIPT) \
	$(UNDEF_FUNCS) \
	$(UNDEF_SYMS) \
	| $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(dir $@)"
	$(LD) $(ORIGINAL_LDFLAGS) \
		"$(HEADER_OBJ)" \
		"$(MAIN_ASM_OBJ)" \
		$(DATA_OBJS) \
		-o "$@"

$(ORIGINAL_BIN): $(ORIGINAL_ELF)
	@mkdir -p "$(dir $@)"
	$(OBJCOPY) -O binary "$<" "$@"

original-verify: verify-input $(ORIGINAL_BIN)
	@echo "== Original all-assembly reference =="
	@stat -c '%n %s bytes' "$(TARGET)" "$(ORIGINAL_BIN)"
	@sha1sum "$(TARGET)" "$(ORIGINAL_BIN)"
	@if cmp -s "$(TARGET)" "$(ORIGINAL_BIN)"; then \
		echo "MATCH"; \
	else \
		echo "MISMATCH"; \
		echo "First differences:"; \
		cmp -l "$(TARGET)" "$(ORIGINAL_BIN)" | head -40 || true; \
		exit 1; \
	fi

$(ELF): $(ORIGINAL_ELF)
	@mkdir -p "$(dir $@)"
	cp "$(ORIGINAL_ELF)" "$@"

link: $(ELF)

$(BIN): $(ORIGINAL_BIN) $(MAIN_C) $(wildcard src/functions/*.c)
	@set -e; \
	mkdir -p "$(dir $@)"; \
	cp "$(ORIGINAL_BIN)" "$@"; \
	functions="$$(sed -n 's/^[[:space:]]*#include[[:space:]]*"functions\/\(func_[0-9A-Fa-f]*\)\.c"[[:space:]]*$$/\1/p' "$(MAIN_C)")"; \
	for fn in $$functions; do \
		echo "== Verifying promoted $$fn =="; \
		$(MAKE) --no-print-directory match FUNCTION="$$fn"; \
		addr="$$( $(NM) -n "$(ORIGINAL_ELF)" | awk -v symbol="$$fn" '$$3 == symbol { print $$1; exit }' )"; \
		test -n "$$addr" || { \
			echo "Missing address for $$fn in original ELF" >&2; \
			exit 1; \
		}; \
		addr_num="$$((16#$$addr))"; \
		rom_offset="$$((addr_num - 0x80010000 + 0x800))"; \
		test "$$rom_offset" -ge 0 || { \
			echo "Invalid ROM offset for $$fn" >&2; \
			exit 1; \
		}; \
		bin="$(FUNCTION_BUILD)/$$fn.bin"; \
		test -f "$$bin" || { \
			echo "Missing verified function binary: $$bin" >&2; \
			exit 1; \
		}; \
		size="$$(stat -c '%s' "$$bin")"; \
		target_size="$$(stat -c '%s' "$@")"; \
		test "$$size" -gt 0 || { \
			echo "Empty function binary for $$fn" >&2; \
			exit 1; \
		}; \
		end="$$(($$rom_offset + $$size))"; \
		test "$$end" -le "$$target_size" || { \
			echo "Function $$fn extends beyond output binary" >&2; \
			exit 1; \
		}; \
		echo "Patching $$fn at ROM offset 0x$$(printf '%X' "$$rom_offset") ($$size bytes)"; \
		dd if="$$bin" of="$@" bs=1 seek="$$rom_offset" conv=notrunc status=none; \
	done

build: $(TOOLCHAIN_STAMPS) $(BIN)

verify: verify-input $(BIN)
	@echo
	@echo "== Size =="
	@stat -c '%n %s bytes' "$(TARGET)" "$(BIN)"
	@echo
	@echo "== SHA-1 =="
	@sha1sum "$(TARGET)" "$(BIN)"
	@echo
	@echo "== Binary comparison =="
	@if cmp -s "$(TARGET)" "$(BIN)"; then \
		echo "MATCH"; \
	else \
		echo "MISMATCH"; \
		echo; \
		echo "First differences:"; \
		cmp -l "$(TARGET)" "$(BIN)" | head -40 || true; \
		exit 1; \
	fi

clean:
	rm -rf "$(BUILD)"
	rm -rf "$(NONMATCH_DIR)"

distclean: clean
	rm -rf "$(VENV)"

OBJDIFF_BUILD := $(BUILD)/objdiff
OBJDIFF_TARGET_BUILD := $(OBJDIFF_BUILD)/target
OBJDIFF_TARGET_SRC_BUILD := $(OBJDIFF_BUILD)/target-src
OBJDIFF_CONFIG := objdiff.json
OBJDIFF_REPORT := .decomp/report.json

FUNCTION_SRCS := $(wildcard src/functions/*.c)
FUNCTION_OBJS := $(patsubst src/functions/%.c,$(FUNCTION_BUILD)/%.o,$(FUNCTION_SRCS))

OBJDIFF_TARGET_SRCS := $(wildcard $(NONMATCH_DIR)/func_*.s)
OBJDIFF_TARGET_OBJS := $(patsubst $(NONMATCH_DIR)/%.s,$(OBJDIFF_TARGET_BUILD)/%.o,$(OBJDIFF_TARGET_SRCS))

objdiff-targets: split
	@$(MAKE) --no-print-directory objdiff-targets-after-split

objdiff-targets-after-split: $(OBJDIFF_TARGET_OBJS)

$(OBJDIFF_TARGET_BUILD)/%.o: $(NONMATCH_DIR)/%.s \
	$(SPLIT_STAMP) \
	include/macro.inc \
	$(SELF_MAKEFILE) \
	| $(TOOLCHAIN_STAMPS)
	@mkdir -p "$(OBJDIFF_TARGET_SRC_BUILD)" "$(dir $@)"
	@tmp="$(OBJDIFF_TARGET_SRC_BUILD)/$*.s.tmp"; \
	out="$(OBJDIFF_TARGET_SRC_BUILD)/$*.s"; \
	{ \
		printf '%s\n' '.include "macro.inc"'; \
		printf '%s\n' '.set noat'; \
		printf '%s\n' '.set noreorder'; \
		printf '%s\n' '.section .text, "ax"'; \
		cat "$<"; \
	} > "$$tmp"; \
	mv "$$tmp" "$$out"; \
	$(AS) $(ASFLAGS) "$$out" -o "$@"

objdiff-base: $(FUNCTION_OBJS)

objdiff-config: objdiff-targets objdiff-base
	$(PY) scripts/generate_objdiff_config.py

objdiff-report: objdiff-config
	@command -v objdiff-cli >/dev/null || { \
		echo "Missing objdiff-cli in PATH." >&2; \
		exit 1; \
	}
	@mkdir -p "$(dir $(OBJDIFF_REPORT))"
	objdiff-cli report generate -p . -o "$(OBJDIFF_REPORT)" -f json
	@$(PY) -c 'import json; p="$(OBJDIFF_REPORT)"; d=json.load(open(p, encoding="utf-8")); m=d["measures"]; print("Objdiff: %.2f%% code, %d/%d functions" % (m.get("matched_code_percent", 0.0), m.get("matched_functions", 0), m.get("total_functions", 0)))'