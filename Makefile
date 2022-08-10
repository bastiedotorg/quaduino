.PHONY: flash0 flash1 flash2 flash3

all: flash0 flash1 flash2 flash3

flash0:
	@echo "Flashing ttyUSB0..."
	@pio run --target upload --upload-port /dev/ttyUSB0 > /dev/null
	@echo "Flashed ttyUSB0 successfully!"

flash1:
	@echo "Flashing ttyUSB1..."
	@pio run --target upload --upload-port /dev/ttyUSB1 > /dev/null
	@echo "Flashed ttyUSB1 successfully!"

flash2:
	@echo "Flashing ttyUSB2..."
	@pio run --target upload --upload-port /dev/ttyUSB2 > /dev/null
	@echo "Flashed ttyUSB2 successfully!"

flash3:
	@echo "Flashing ttyUSB3..."
	@pio run --target upload --upload-port /dev/ttyUSB3 > /dev/null
	@echo "Flashed ttyUSB3 successfully!"

