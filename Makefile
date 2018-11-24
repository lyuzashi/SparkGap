ROOT := $(realpath $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))
SKETCH = $(ROOT)/src/SparkGap.ino

ESP_ROOT=$(ROOT)/utils/esp8266
CUSTOM_LIBS=$(ROOT)/libs

EXCLUDE_DIRS=$(wildcard $(ARDUINO_LIBS)/*/tests) $(wildcard $(CUSTOM_LIBS)/*/tests)

UPLOAD_PORT ?= $(shell ls -1tr /dev/tty.usb* 2>/dev/null | tail -1)

# For versions <= 2.4.0
# FLASH_DEF=1M0
# For versions 2.4.3+
FLASH_DEF=1M
UPLOAD_SPEED="115200"

FLASH_MODE=dout
LWIP_VARIANT=Prebuilt (v1.4 Higher Bandwidth)

NAME=GardenLights

BUILD_EXTRA_FLAGS="-DTYPE_BASIC"
BUILD_EXTRA_FLAGS+="-DNAME=\"$(NAME)\""

include $(ROOT)/utils/makeEspArduino/makeEspArduino.mk
