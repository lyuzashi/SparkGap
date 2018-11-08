ROOT := $(realpath $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))
SKETCH = $(ROOT)/SparkGap.ino

EXCLUDE_DIRS=$(wildcard $(ARDUINO_LIBS)/*/tests)

UPLOAD_PORT ?= $(shell ls -1tr /dev/tty.usb* 2>/dev/null | tail -1)

FLASH_DEF=1M0
FLASH_MODE=dout
LWIP_VARIANT=Prebuilt (v1.4 Higher Bandwidth)

NAME=GardenLights

BUILD_EXTRA_FLAGS="-DTYPE_BASIC"
BUILD_EXTRA_FLAGS+="-DNAME=\"$(NAME)\""

include $(ROOT)/utils/makeEspArduino/makeEspArduino.mk
