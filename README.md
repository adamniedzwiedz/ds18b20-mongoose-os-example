# Mongoose OS the DS18B20 dust sensor example (C/C++)

For the details look at the [library](https://github.com/adamniedzwiedz/ds18b20-mongoose-os-lib)

## Typical connection.

<p align="center">
  <img src="https://github.com/adamniedzwiedz/ds18b20-mongoose-os-example/blob/master/ds18b20_connection.png">
</p>

## Overview

This example shows how to read a temperature using the *DS18B20* sensor with ESP8266 and Mongoose OS.

First create *mgos_ds18b20* object by providing the *data pin* `ds18b20_create(ONEWIRE_PIN)`

Then set the resolution if you want `scratchpad.resolution = DS18B20_12_BIT` and write it `ds18b20_write_scratchpad(ds18b20, scratchpad)`

To start a measure call `ds18b20_start_conversion`. The second argument is a callback method where the *temperature* value will come when the measure is finished.

## How to install this app
- [Download](https://github.com/adamniedzwiedz/ds18b20-mongoose-os-example/archive/master.zip) and unpack or clone `git clone https://github.com/adamniedzwiedz/ds18b20-mongoose-os-example` the project
- Install [mos tool](https://mongoose-os.com/software.html)
- Open command line window and go to the project folder and run `mos build --platform esp8266`
- Run `mos flash`
