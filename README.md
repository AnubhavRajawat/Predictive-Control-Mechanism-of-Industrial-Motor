# 🛠️ Predictive Control Mechanism for Industrial Motors using ESP32

[![Node-RED](https://img.shields.io/badge/Node--RED-Flow-red)](#nodered-dashboard)
[![ESP32](https://img.shields.io/badge/ESP32-Compatible-blue)](#hardware-used)

A real-time monitoring system for industrial motors using ESP32, multiple sensors, MQTT, and a Node-RED dashboard. This system helps detect early signs of motor failure like vibration anomalies, overheating, or RPM drops—enabling predictive maintenance.

Developed an IoT-based system for real-time monitoring and predictive maintenance of industrial motors using ESP32. Integrated sensors like ADXL345 (vibration), DHT22 (temperature & humidity), LM35 (temperature), and E18-D80NK (proximity) to detect anomalies. Data was vis

---

## 🔧 Hardware Used

- ✅ **ESP32** Dev Board  
- 📈 **ADXL345** – Vibration monitoring (X, Y, Z axes)  
- 🌡️ **LM35** – Analog temperature sensor  
- 🌫️ **DHT22** – Digital humidity and temperature sensor  
- ⚙️ **IR Proximity Sensor** – RPM monitoring via interrupts  

---

## 📦 Project Structure

main/
│
├── 📄 README.md
├── 📁 code/
│   └── esp32_motor_monitor.ino
│
├── 📁 docs/
│   ├── system_architecture.png
│   ├── sensors_description.md
│   └── node_RED_dashboard_screenshot.png
│
├── 📁 data/
│   └── sample_readings.csv
│
├── 📁 dashboard/
│   ├── node_RED_flow.json
│   └── instructions.md
│
├── 📁 media/
│   └── output_demo.mp4
│   └── Hardware_implementation
|   └──circuit_diagram
│
└── 📄 .gitignore


---

## 🚀 Features

- 📡 Real-time sensor data via MQTT
- 📊 Visual dashboard using Node-RED
- 📁 Sample dataset for testing (CSV format)
- 🎥 Output demonstration video
- 📋 Modular & extensible firmware

---

## 🖥️ Node-RED Dashboard

> Live visualization of all metrics including:
- Real-time vibration charts (X, Y, Z)
- RPM gauges
- Temperature and humidity indicators

📥 **Import `node_RED_flow.json` into Node-RED**  
📸 See `docs/node_RED_dashboard_screenshot.png` for layout example.

---

## 🔌 MQTT Topics

| Topic                 | Data Sent               |
|----------------------|-------------------------|
| `motor/vibration/x`  | Vibration on X-axis     |
| `motor/vibration/y`  | Vibration on Y-axis     |
| `motor/vibration/z`  | Vibration on Z-axis     |
| `motor/tempC`        | LM35 Temperature (°C)   |
| `motor/dht/tempC`    | DHT22 Temperature (°C)  |
| `motor/dht/humidity` | Humidity (%)            |
| `motor/rpm`          | Shaft speed (RPM)       |

---

## 🧾 Documentation

- [Sensor Descriptions](docs/sensors_description.md)  
- [Node-RED Setup Instructions](docs/instructions.md)

---

## 📽️ Demo

🎬 Watch the system in action: `docs/output_demo.mp4`

---

## 🙌 Contributions

Pull requests and suggestions are welcome! If you find a bug or have a feature request, feel free to open an issue.

---

⭐ Star this repo if you find it helpful!
