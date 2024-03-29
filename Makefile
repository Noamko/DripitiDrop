# Configuration
BOARD := esp32c3
SRC := DripitiDrop.ino
AVR := esp32:esp32
BUILD_DIR := build
SERIAL_PORT := $(shell arduino-cli board list | awk 'NR-1 {print $1; exit}')
BOARD_TYPE := $(AVR):$(BOARD)
CONFIG := FlashMode=dio,CDCOnBoot=cdc

# Targets
.PHONY: build upload clean all
all: compile_commands.json
$(BOARD):
	@echo "Building..."
	mkdir -p $(BUILD_DIR)
	arduino-cli compile --fqbn $(BOARD_TYPE):$(CONFIG) $(SRC) -v --build-path $(BUILD_DIR)

compile_commands.json: $(BOARD)
	@echo "Generating compile_commands.json..."
	cp $(BUILD_DIR)/compile_commands.json .
	@echo "done."

upload:
	@echo "Uploading..."
	arduino-cli upload -p $(SERIAL_PORT) --fqbn $(BOARD_TYPE):$(CONFIG) $(SRC) -v --input-dir $(BUILD_DIR)
	
update-remote:
	ssh home "cd projects/DripitiDrop && git pull && make upload"
	
clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR)

