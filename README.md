# PDAputer

PDA-style interface for M5Stack Cardputer — ESP32-S3, LVGL, PlatformIO.

---
<p align="center">
  <span style="color: yellow;">If you like this, consider supporting it:</span>
</p>

<p align="center">
  <a href="https://www.buymeacoffee.com/nishad2m8" target="_blank">
    <img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me a Coffee" style="height: 35px;">
  </a>
  <a href="https://www.youtube.com/channel/UCV_35rUyf4N5mHZXaxaFKiQ" target="_blank">
    <img src="https://img.shields.io/badge/Subscribe%20on%20YouTube-FF0000?style=flat&logo=youtube" alt="Subscribe on YouTube" style="height: 35px;">
  </a>
</p>


---

![alt text](PDAputer-EEZ/preview.gif)

## Apps

<details>
<summary><strong>Status</strong></summary>

| App        | Status |
|------------|--------|
| Settings   | ✔    |
| FM Radio   | ✔    |
| Music      | ✔    |
| Calendar   | ✔    |
| Notes      | ✘    |
| AI Chat    | ✘    |
| Web Radio  | ✘    |
| Games      | ✘    |
| LoRa Chat  | ✘    |
| GPS        | ✘    |
| Remote     | ✘    |

</details>

## SD Card Config

Place a FAT32-formatted SD card with the following structure:

```
/PDAputer
├── config.txt
├── FM Radio
│   └── stations.txt
└── Music
    ├── track1.mp3
    ├── track2.mp3
    └── ...
```

<details>
<summary><span style="color: yellow;">config.txt</span></summary>

```ini
# PDAputer Configuration

device_name = PDA
wifi_ssid = your_ssid
wifi_password = your_password
timezone = EST5EDT,M3.2.0,M11.1.0
brightness = 128
tone = 128
time_format = 12
```

</details>

<details>
<summary>stations.txt</summary>

```ini
# FM Radio Presets (frequency in MHz)

1 = 98.5
2 = 101.3
3 = 0.0
```

Save presets on device with `Fn+1`, `Fn+2`, `Fn+3`.

</details>

**Music** — Drop `.mp3` files into `/PDAputer/Music/` (max 64 tracks). ID3v2 metadata is read from MP3s.

## Keyboard Map

**Main Menu**

| Key | Action |
|-----|--------|
| `,` `.` | Scroll left / right |
| `Enter` | Launch app |
| `m` | Toggle mute |

<details>
<summary><strong>FM Radio</strong></summary>

| Key | Action |
|-----|--------|
| `;` | Seek up |
| `.` | Seek down |
| `/` | Fine tune up |
| `,` | Fine tune down |
| `1` `2` `3` | Load preset |
| `Fn+1` `Fn+2` `Fn+3` | Save preset |
| `p` | Play / Pause |
| `m` | Mute |
| `s` | Stereo / Mono |
| `b` | Switch band (FM/JP) |
| `` ` `` | Back |

</details>

<details>
<summary><strong>Music</strong></summary>

| Key | Action |
|-----|--------|
| `p` | Play / Pause |
| `;` | Previous track |
| `.` | Next track |
| `,` | Seek back 5s |
| `/` | Seek forward 5s |
| `+` | Volume up |
| `-` | Volume down |
| `s` | Shuffle |
| `m` | Mute |
| `` ` `` | Back |

</details>

<details>
<summary><strong>Settings</strong></summary>

| Key | Action |
|-----|--------|
| `;` | Navigate up |
| `.` | Navigate down |
| `Enter` | Edit / Confirm |
| `` ` `` | Cancel / Back |

</details>

<details>
<summary><strong>Calendar</strong></summary>

| Key | Action |
|-----|--------|
| `` ` `` | Back |

</details>


## Project Structure


- **PDAputer-PIO/** — PlatformIO firmware project (ESP32-S3)
- **PDAputer-EEZ/** — EEZ Studio UI project files (`.eez-project`)

## Build

1. Open `PDAputer-PIO` in VS Code with PlatformIO
2. Compile and upload

### EEZ Studio

Open `PDAputer-EEZ/PDAputer-EEZ.eez-project` in [EEZ Studio](https://www.envox.eu/studio/studio-introduction/) to edit the UI layout.
