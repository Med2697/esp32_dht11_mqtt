# 📡 ESP32 DHT11 MQTT Project

## 📌 Description
This IoT project uses the ESP32, a DHT11 sensor, and the MQTT protocol to publish temperature and humidity data to an MQTT broker (HiveMQ Cloud). The project is divided into two parts:

1. **ESP32 (C++)**: Code for reading data from the DHT11 sensor and publishing it to the MQTT broker.
2. **Python**: Script for receiving data from the MQTT broker and controlling an LED via MQTT messages.

## 📁 Project Structure
```
esp32_dht11_mqtt/
├── ESP32/                # C++ code for the ESP32
├── Python/               # Python code for the MQTT client
├── .gitignore            # Files ignored by Git (config.h, config.py, cert.crt)
```

## 🚀 Features
- 📊 Read temperature and humidity data via the DHT11 sensor.
- 🌐 Securely send data via MQTT to HiveMQ Cloud.
- 💡 Control an LED by sending MQTT commands from a Python script.
- 🔒 Secure communication using SSL/TLS.

## 📦 Installation (Python)
1. **Install Python dependencies:**
```bash
pip install paho-mqtt
```
2. **Create a `config.py` file (not shared on GitHub):**
```python
# config.py
MQTT_SERVER = "Your_MQTT_SERVER"
MQTT_PORT = 8883
MQTT_USER = "Your_MQTT_USER"
MQTT_PASSWORD = "Your_MQTT_PASSWORD"
ca_cert_path = "path/to/your/certificate/cert.crt"
```

## 📌 Author
- **Mohamed KHENAFIF**

## 📜 License
This project is licensed under the MIT License.
