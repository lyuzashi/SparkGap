# MQTT Smarthome Sonoff Basic Switch

```bash
$ git submodule init 
$ git submodule update
$ make flash
```

GPIO0 must be held low on power on to reset into flash mode.

This can be done on a Sonoff Basic by holding the reset button.

## Build

Two build paths are being considered

### makeEspArduino

[makeEspArduino](https://github.com/plerup/makeEspArduino) discovers the Arduino IDE app and attempts to use its
libraries, build and upload tooling along with the configuration specified in this project's Makefile.

Some IDE features - such as preprocessing to declare methods - are not included.

These shortcomings could potentially be fixed by projects such as
* [uDino-Preprocessor](https://github.com/michaelbaisch/uDino-Preprocessor)

Requires Arduino installed on system with ESP libraries downloaded in IDE.

### Arduino-CLI

Official [Arduino CLI](https://github.com/arduino/arduino-cli), which is currently in alpha, so may have some issue.

Steps:

1. Download Arduino CLI, name binary `arduino`
2. Include ESP8266 board manager URLs in `.cli-config.yml`
3. Update board index  
  `arduino --config-file ./.cli-config.yml core update-index `
4. Install ESP8266 core  
  `arduino --config-file ./.cli-config.yml core install esp8266:esp8266`

`fqbn` can now be `esp8266:esp8266:generic` or `esp8266:esp8266:esp8285`

```
arduino --config-file ./.cli-config.yml compile --fqbn esp8266:esp8266:generic code.ino
```
## Features

**Goal**: zero config

* WPS WiFi setup – no hardcoded credentials
* mDNS Discovery of MQTT broker
* Connects with hostname as username and MAC address as password
* Supports modules:
  - Sonoff Basic
  - Sonoff 4 Channel
  - Magic Home (ESP8285)
* Follows the 
[MQTT Smarthome Architecture](https://github.com/mqtt-smarthome/mqtt-smarthome/blob/master/Architecture.md)

## MQTT Topics

### Sonoff Basic
* Subscribes to `relays/set/[hostname]/on`
* Subscribes to `relays/set/[hostname]/led`
* Subscribes to `relays/get/[hostname]/on`
* Subscribes to `relays/get/[hostname]/led`
* Subscribes to `relays/get/[hostname]/button`
* Publishes to `relays/status/[hostname]/on`
* Publishes to `relays/status/[hostname]/led`
* Publishes to `relays/status/[hostname]/button`

### Sonoff 4 Channel
* Subscribes to `relays/set/[hostname] +channel/on`
* Subscribes to `relays/set/[hostname] +channel/led`
* Subscribes to `relays/get/[hostname] +channel/on`
* Subscribes to `relays/get/[hostname] +channel/led`
* Subscribes to `relays/get/[hostname] +channel/button`
* Publishes to `relays/status/[hostname] +channel/on`
* Publishes to `relays/status/[hostname] +channel/led`
* Publishes to `relays/status/[hostname] +channel/button`

Where `+channel` is a relay number 1-4.

### Magic Home
* Subscribes to `lights/set/[hostname] +channel/on`
* Subscribes to `lights/set/[hostname] +channel/brightness`
* Subscribes to `lights/get/[hostname] +channel/on`
* Subscribes to `lights/get/[hostname] +channel/brightness`
* Subscribes to `lights/get/[hostname]/sensor`
* Publishes to `lights/status/[hostname] +channel/on`
* Publishes to `lights/status/[hostname] +channel/brightness`
* Publishes to `lights/status/[hostname]/sensor`

Where `+channel` is an output number 1-3.  
Brightness is a state independent of on.  
Sensor is a digital input.