ROOT := $(realpath $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))
SKETCH = $(ROOT)/longpress.ino

UPLOAD_PORT ?= $(shell ls -1tr /dev/tty.usb* 2>/dev/null | tail -1)

FLASH_DEF = 1M0
FLASH_MODE=  dout

include $(ROOT)/utils/makeEspArduino/makeEspArduino.mk