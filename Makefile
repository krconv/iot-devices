NAME = $(shell echo $(DEVICE) | tr '[A-Z]' '[a-z]' | tr '_' '-')
OTA_HOST = $(NAME).local

build: $(NAME).bin

%.bin: iot-devices.ino $(shell find . \( -name *.h -or -name *.cpp \) -print)
	arduino-cli compile --fqbn esp8266:esp8266:generic --build-property "compiler.cpp.extra_flags=\"-DBUILD__$(DEVICE)\"" --output-dir ./ .
	@rm -f $@
	@mv iot-devices.ino.bin $@
	@rm -f iot-devices.ino.elf iot-devices.ino.map

upload: $(NAME).bin
	python ~/Documents/Arduino/hardware/expressif/esp32/tools/espota.py -i $(OTA_HOST) -I $(shell ifconfig en0 | grep "inet " | grep -o -E '((\d+\.?)+)' | head -n1) -p 8266 -f $(NAME).bin
