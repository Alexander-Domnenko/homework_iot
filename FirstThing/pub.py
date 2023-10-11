import paho.mqtt.client as mqtt_client
import random

broker = "broker.emqx.io"

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)


client = mqtt_client.Client(f'lab_{random.randint(10000, 99999)}')
client.on_connect = on_connect
client.connect(broker)

while True:
    command = input("Enter 'd' or 'u': ")
    if command.lower() == "d" or command.lower() == "u":
        state = command
    else:
        print("Invalid input. Please enter 'd' or 'u'.")
    client.publish("lab/debug/led_state", state)
    print(f"publish state is {state}")
