# Sensor Descriptions for Industrial Motor Monitoring System

This project uses the following sensors to monitor the condition of an industrial motor in real-time:

---

### 📌 1. ADXL345 - Accelerometer
- **Function**: Measures vibration across X, Y, and Z axes.
- **Interface**: I2C
- **Range Used**: ±2g
- **Usage**: Detect unusual vibrations that may indicate wear, imbalance, or misalignment.

---

### 📌 2. LM35 - Analog Temperature Sensor
- **Function**: Measures temperature in °C.
- **Output**: Analog voltage proportional to temperature (10mV/°C).
- **Usage**: Monitors motor surface temperature to prevent overheating.

---

### 📌 3. DHT22 - Digital Temperature and Humidity Sensor
- **Function**: Measures ambient temperature and relative humidity.
- **Interface**: Digital (single wire)
- **Accuracy**:
  - Temperature: ±0.5°C
  - Humidity: ±2–5% RH
- **Usage**: Tracks environmental conditions around the motor.

---

### 📌 4. IR Proximity Sensor (RPM Measurement)
- **Function**: Detects shaft rotation pulses to calculate RPM.
- **Connection**: Digital pin with interrupt.
- **Usage**: Measures motor speed to identify performance degradation or faults.

---

### 🧠 Combined Usage
All sensors feed real-time data to an MQTT broker and are visualized through a Node-RED dashboard for predictive maintenance.
