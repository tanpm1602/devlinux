# 🌱 Smart Plant Watering System (SPWS)

This project simulates an intelligent watering system capable of reading sensor data, making watering decisions based on configurable parameters, and displaying operating status through an RGB LED indicator.

---

## 🚀 Features

### 1. Operating Modes
The system has two modes that can be switched using a single button:

- **Automatic Mode**  
  - The pump turns **ON** when soil moisture is **below** the threshold.  
  - The pump turns **OFF** when soil moisture is **above** the threshold.

- **Manual Mode**  
  - The pump is manually activated via a button press and runs for a preconfigured duration.  
  - When switching to manual mode while the pump is running in automatic mode, the pump **must be stopped immediately**.

---

### 2. RGB LED Status Indication
| LED Color | Meaning |
|------------|----------|
| 💧 Cyan | Normal / Idle state |
| 🟡 Yellow | Pump is running |
| 🔴 Red (blinking) | Low soil moisture warning |
| 🔴 Red (steady) | System error |

---

## ⚙️ Requirements
- Linux environment (**recommended**)
- **GCC** compiler
- **Makefile**

### Install GCC and Make on Ubuntu:
```bash
sudo apt update
sudo apt install gcc
sudo apt install make
```

---

## 🧱 Build Instructions

Inside the `variable_and_datatypes` folder, compile the program:

```bash
make
```

---

## ▶️ Run the Simulation

Execute the program:

```bash
./build/spws
```

### Simulated Button Controls:
| Key | Function |
|------|-----------|
| `a` | Switch to **Automatic** mode |
| `m` | Switch to **Manual** mode |
| `1` | Turn **ON** pump (manual mode) |
| `0` | Reset button (simulates normally open button release) |

---

## 🧩 Notes
This is a **simulation program**.  
To adapt it for real hardware, modify the source files in the `hal` directory according to your **microcontroller** and **hardware configuration**.

---

## 📘 License
This project is distributed under the **MIT License**.
