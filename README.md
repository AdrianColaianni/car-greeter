# Car Greeter

This is a small program for the ESP32-S3-AUDIO-Board which will play a random audio file off it's microSD card on boot.  I'm using it to play a tune whenever I start my car.

## Setup

The directory structure for the microSD is as follows

```
greet1.mp3
greet2.mp3
alt
├─greet3.mp3
└─greet4.mp3
reg
├─otg1.mp3
└─otg2.mp3
```

One file in the base dir is played at random at startup, except in 10% of cases where a random file from `alt` is played.  After that, the board waits for 5 minutes, and then there is a 1 / 10,000 chance every second that a sound from `reg` will play.  I could have gone with better names for these directories, but I didn't feel like it.

## Documentation

I purchased [this](https://www.amazon.com/dp/B0FP5QYZM9) board from Amazon, and struggled to find good documentation so I've included some below

- [Waveshare's Guide](https://www.waveshare.com/wiki/ESP32-S3-AUDIO-Board)
- [ESP32-S3 Docs](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/)

To do this yourself, follow the [installation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html) guide for ESP-IDF and then start with a [demo](https://files.waveshare.com/wiki/ESP32-S3-AUDIO-Board/ESP32-S3-AUDIO-Board-Demo.zip) from Waveshare.  I had little success working with the Arduino code, but your mileage may vary.

## Future Ideas with this board
- There is space & circuitry for a battery, allowing this to run on the go
- My code does not utilize WiFi or Bluetooth at all
- Waveshare sells boards with [LCD displays](https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-1.85C) built in -- also on [Amazon](https://www.amazon.com/Waveshare-ESP32-S3-1-85inch-Development-Bluetooth/dp/B0F18D8S27?s=electronics)
