SHELL := /usr/bin/env bash

PYTHON ?= python3
VENV ?= .venv
PY := $(VENV)/bin/python
PIP := $(PY) -m pip
ROOT := $(CURDIR)
TARGET := iso/us/SLUS_004.25
CONFIG_DIR := config/slus_004.25
CONFIG := $(CONFIG_DIR)/splat.yaml
SYMBOLS := symbols/slus_004.25.txt
RELOCS := symbols/slus_004.25.relocs.txt

.PHONY: help venv install tools versions info fingerprint verify-input create-config split clean

help:
	@printf '%s\n' \
		'make venv          Create the local Python virtual environment' \
		'make install       Install pinned Python dependencies' \
		'make tools         Initialize the Git submodules' \
		'make versions      Print Python/splat/spimdisasm versions' \
		'make info          Inspect SLUS_004.25 and print PS-X EXE header fields' \
		'make fingerprint   Record SHA-1/SHA-256 of the local executable' \
		'make verify-input  Verify that the local SLUS_004.25 exists' \
		'make create-config Generate and normalize the initial Splat config' \
		'make split         Run Splat with the reviewed project config' \
		'make clean         Remove generated local Python state'

venv:
	@test -x $(PY) || $(PYTHON) -m venv $(VENV)

install: venv
	$(PIP) install --upgrade pip
	$(PIP) install -r requirements.txt

tools:
	git submodule update --init --recursive

versions: install
	$(PY) --version
	$(PY) -c 'import splat, spimdisasm; print("splat64:", splat.__version__); print("spimdisasm:", spimdisasm.__version__)'

info: verify-input
	$(PYTHON) scripts/inspect_psx_exe.py $(TARGET)

fingerprint: verify-input
	@mkdir -p config/slus_004.25
	@sha1sum $(TARGET) | cut -d" " -f1 > config/slus_004.25/SLUS_004.25.sha1
	@sha256sum $(TARGET) | cut -d" " -f1 > config/slus_004.25/SLUS_004.25.sha256
	@echo "Wrote config/slus_004.25/SLUS_004.25.sha1"
	@echo "Wrote config/slus_004.25/SLUS_004.25.sha256"

verify-input:
	@test -f $(TARGET) || { echo "Missing $(TARGET)" >&2; echo "Put your own extracted Wild 9 SLUS_004.25 under $(TARGET)." >&2; exit 1; }

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
	"$(PYTHON)" scripts/normalize_splat_config.py "$(CONFIG)" "$(CONFIG)" "$(SYMBOLS)" "$(RELOCS)" "$(TARGET)"; \
	echo; \
	echo "Review $(CONFIG), $(SYMBOLS), and $(RELOCS) before committing."

split: verify-input install
	@test -f $(CONFIG) || { echo "Missing $(CONFIG). Run 'make create-config' first." >&2; exit 1; }
	$(PY) -m splat split $(CONFIG)

clean:
	rm -rf $(VENV)
