# PDAputer

A PDA-style interface for the M5Stack Cardputer built with LVGL and PlatformIO.

> **Status:** Work in progress - UI framework and navigation implemented, individual app screens not yet functional.

## Apps (WIP)

- Setting
- AI Chat
- FM Radio
- Web Radio
- Music
- Games
- LoRa Chat
- GPS

## Hardware

- M5Stack Cardputer (ESP32-S3)
- 240x135 LCD display
- Built-in keyboard and speaker

## Project Structure

- **PDAputer-PIO/** — PlatformIO firmware project (ESP32-S3)
- **PDAputer-EEZ/** — EEZ Studio UI project files (`.eez-project`)

## Build

1. Open `PDAputer-PIO` in VS Code with PlatformIO
2. Compile and upload

### EEZ Studio

Open `PDAputer-EEZ/PDAputer-EEZ.eez-project` in [EEZ Studio](https://www.envox.eu/studio/studio-introduction/) to edit the UI layout.

## Credits

nishad2m8
