# Configuration
BOARD := esp32c3
SRC := DripitiDrop.ino
AVR := esp32:esp32
BUILD_DIR := build
SERIAL_PORT := /dev/$(shell ls /dev | grep -E -i 'usb' | head -n 1)
BOARD_TYPE := $(AVR):$(BOARD)
CONFIG := FlashMode=dio,CDCOnBoot=cdc

# Targets
.PHONY: build upload clean all
all: $(BOARD) upload
$(BOARD):
	@echo "Building..."
	mkdir -p $(BUILD_DIR)
	arduino-cli compile --fqbn $(BOARD_TYPE):$(CONFIG) $(SRC) -v --build-path $(BUILD_DIR)

upload:
	@echo "Uploading..."
	arduino-cli upload -p $(SERIAL_PORT) --fqbn $(BOARD_TYPE):$(CONFIG) $(SRC) -v --input-dir $(BUILD_DIR)
	

clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR)

