# Circuit Connections

This file contains the pin-to-pin connections used in the Power Theft Detection System using ESP32.

---

## Power Supply Connections

| Component / Pin | Connected To |
|---|---|
| 9V Battery Positive | ESP32 VIN |
| 9V Battery Negative | ESP32 GND |
| Common Ground | ESP32, ACS712, Relay, Buzzer, LCD GND |

A common ground connection is very important. ESP32, ACS712 current sensor, relay module, buzzer, and LCD should share the same ground reference.

---

## ACS712 Current Sensor Connections

| ACS712 Pin | ESP32 Pin |
|---|---|
| VCC | ESP32 5V |
| GND | ESP32 GND |
| OUT | ESP32 GPIO 34 |

### Explanation

The ACS712 current sensor measures the current flowing through the load.  
The OUT pin gives an analog voltage output. This output is connected to GPIO 34 of ESP32 because GPIO 34 is an ADC input pin.

---

## Relay Module Connections

| Relay Module Pin | ESP32 Pin |
|---|---|
| VCC | ESP32 5V |
| GND | ESP32 GND |
| IN | ESP32 GPIO 25 |

### Explanation

The relay module acts as an automatic switch.  
It is controlled by ESP32 through GPIO 25. When theft or abnormal current is detected, the relay disconnects the load.

---

## Buzzer Connections

| Buzzer Pin | ESP32 Pin |
|---|---|
| Positive | ESP32 GPIO 26 |
| Negative | ESP32 GND |

### Explanation

The buzzer is used for alert indication.  
When abnormal current is detected, ESP32 sends a signal to GPIO 26 and the buzzer turns ON.

---

## 16x2 LCD Display Connections

This project uses a normal 16x2 parallel LCD display in 4-bit mode.

| LCD Pin | Function | ESP32 Pin |
|---|---|---|
| VSS | Ground | GND |
| VDD | Power | 5V |
| V0 | Contrast | Potentiometer middle pin |
| RS | Register Select | GPIO 14 |
| RW | Read/Write | GND |
| EN | Enable | GPIO 27 |
| D4 | Data Pin | GPIO 18 |
| D5 | Data Pin | GPIO 19 |
| D6 | Data Pin | GPIO 23 |
| D7 | Data Pin | GPIO 22 |
| A | Backlight Positive | 5V through resistor |
| K | Backlight Negative | GND |

### Explanation

The LCD is connected in 4-bit mode.  
Only D4, D5, D6, and D7 data pins are used. This saves ESP32 GPIO pins.

---

## Load Connection

| Connection | Description |
|---|---|
| Power Supply Positive | Connected through ACS712 current sensor |
| ACS712 Output Side | Connected toward load path |
| Relay Output | Controls load ON/OFF |
| Load Negative | Connected to common ground |

The load is controlled through the relay module. When abnormal current is detected, the relay disconnects the load.

---

## Pin Summary

| Module | ESP32 Pin |
|---|---|
| ACS712 OUT | GPIO 34 |
| Relay IN | GPIO 25 |
| Buzzer Positive | GPIO 26 |
| LCD RS | GPIO 14 |
| LCD EN | GPIO 27 |
| LCD D4 | GPIO 18 |
| LCD D5 | GPIO 19 |
| LCD D6 | GPIO 23 |
| LCD D7 | GPIO 22 |

---

## Important Notes

- This project uses a normal 16x2 parallel LCD, not an I2C LCD.
- ACS712 OUT is connected to GPIO 34 because it is an analog input pin.
- The relay module is assumed to be active LOW.
- A common ground must be connected between all modules.
- This prototype is designed for DC demonstration purposes.
- Do not connect this circuit directly to high-voltage AC mains without proper safety isolation and supervision.