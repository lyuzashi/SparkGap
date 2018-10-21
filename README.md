# MQTT Smarthome Sonoff Basic Switch

```bash
$ git submodule init 
$ git submodule update
$ make flash
```

GPIO0 must be held low on power on to reset into flash mode.

This can be done on a Sonoff Basic by holding the reset button.

Requires Arduino installed on system with ESP libraries downloaded in IDE

## Features

Goal: zero config

* WPS WiFi setup – no hardcoded credentials
* mDNS Discovery of MQTT broker
* Connects with hostname as username and MAC address as password
* Subscribes to [hostname]/set/on and publishes to [hostname]/status/on, following the 
[MQTT Smarthome Architecture](https://github.com/mqtt-smarthome/mqtt-smarthome/blob/master/Architecture.md)