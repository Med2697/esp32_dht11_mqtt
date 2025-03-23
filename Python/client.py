import paho.mqtt.client as mqtt
import ssl
from config import MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD, ca_cert_path  # Import depuis config.py



SUBSCRIBE_TOPIC = "led"

def on_conn(client, userdata, flags, rc):
    if rc == 0:
        print("Connecté au broker MQTT")
        client.subscribe("esp32/temp")
        client.subscribe("esp32/hum")
        client.subscribe("esp32/led")
    else:
        print("Échec de connexion. Code : ", rc)

def on_mess(client, userdata, msg):
    message = msg.payload.decode()
    print(f"📥 Message reçu sur le topic {msg.topic}: {message}")

def control_led(command):
    client.publish(SUBSCRIBE_TOPIC, command)
    print(f"📤 Commande envoyée : {command}")

client = mqtt.Client()
client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
#client.tls_set(cert_reqs=ssl.CERT_NONE)  
client.tls_set(ca_cert_path)
#client.tls_insecure_set(True)

client.on_connect = on_conn
client.on_message = on_mess

client.connect(MQTT_SERVER, MQTT_PORT)
client.loop_start()

try:
    while True:
        command = input("Tape 'ON' pour allumer la LED, 'OFF' pour l'éteindre, ou 'exit' pour quitter : ")
        if command.lower() == 'exit':
            break
        elif command.upper() in ['ON', 'OFF']:
            control_led(command.upper())
        else:
            print("Commande invalide. Utilise 'ON', 'OFF', ou 'exit'.")
finally:
    client.loop_stop()
    client.disconnect()
    print("✅ Déconnecté du broker MQTT.")