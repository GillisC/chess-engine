BUILD_DIR := build

CMAKE := $(shell which cmake)

.PHONY: all config build run clean

all: build main

config:
	@echo "Configuring the project..."
	@$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug

build:
	@echo "Building the project..."
	@$(CMAKE) --build $(BUILD_DIR) --parallel 8

main:
	@cd ./build && ./ChessEngine 

clean:
	@rm -rf ./build

