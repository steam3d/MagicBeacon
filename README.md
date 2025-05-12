![](./.assets/preview.png)

# MagicBeacon

MagicBeacon is a [Flipper Zero](https://flipperzero.one) application that emulates Bluetooth Low Energy (BLE) payloads broadcasted by AirPods.

---

## 💾 Installation

### 1. Install UFBT

**Linux / macOS:**

```bash
python3 -m pip install --upgrade ufbt
```

**Windows:**

```bash
python -m pip install --upgrade ufbt
```

### 2. Set up VS Code (optional)

```bash
ufbt vscode_dist
```

### 3. Build the project

```bash
ufbt build
```

### 4. Upload to Flipper

Copy the `magic_becon.fap` file to the Bluetooth apps folder on the Flipper's SD card:

```
/apps/Bluetooth/magic_becon.fap
```

## 🚀 Getting Started

### Modes:

* **Payload from template** — generate packets using built-in templates.
* **Payload from file** — load packets from a text file.

### File format:

* **First line** — MAC address (e.g., `0C:2D:0A:21:42:1D`)
* **Remaining lines** — one payload packet per line.
* **Limit:** Up to 27 bytes per line (54 hex characters without spaces or delimiters).

#### Example file:

```
0C:2D:0A:21:42:1D
0719011B2075AAB83100001D6D1EEDE9B3ABF70A664ED3CA96D191
0719011B2075AAB83100001D6D1EEDE9B3ABF70A664ED3CA96D191
0719011B2075AAB83100001D6D1EEDE9B3ABF70A664ED3CA96D191
```

### Usage

1. Select the payload source: template or file.
2. Configure parameters in the app interface.
3. Enable **Advertising** to start broadcasting.
4. Payload is updated automatically when parameters change.
5. In **Edit payload** mode, you can manually modify the payload:

   * Enable **Live payload** to apply changes instantly.
6. To change the MAC address:

   * Disable **Advertising**, change the address, then enable it again.
