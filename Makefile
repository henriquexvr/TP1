# ============================================================
# Makefile - Wrapper for CMake build system
# ============================================================
# NOTE: This project now uses CMake for better cross-platform support
#
# For direct CMake usage:
#   Unix/Linux/macOS: bash build.sh
#   Windows:          build.bat
#   Manual:           mkdir build && cd build && cmake .. && cmake --build .
#
# This Makefile is kept for convenience
# ============================================================

.PHONY: all clean build help

BUILD_DIR := build
BINARY := $(BUILD_DIR)/normalize

help:
	@echo "================================="
	@echo "normalize - Build Commands"
	@echo "================================="
	@echo "make build  - Build the project"
	@echo "make clean  - Remove build artifacts"
	@echo "make help   - Show this message"
	@echo ""
	@echo "Note: This project uses CMake"
	@echo "For direct CMake usage, see README.md"
	@echo "================================="

all: build

build: 
	@echo "Building with CMake..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build . --config Release
	@echo "✓ Build complete! Binary at: $(BINARY)"

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "✓ Clean complete!"