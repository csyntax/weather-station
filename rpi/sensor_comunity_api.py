from datetime import datetime
import requests

API_URL = 'https://api.sensor.community/v1/push-sensor-data/'

SENSOR_ID = '64026'
VERSION = '1'

def get_data_for_map(data):
    (temp, pres, hum) = data

    return {
        'Temperature': temp,
        'Humidity': hum,
        'Pa': pres,
    }

def push_to_map(raw_data):
    sensor_data = get_data_for_map(raw_data)

    data = {
        "sensor": SENSOR_ID,
        "sampling_rate": 60000,
        "timestamp": datetime.now(),
        "sensordatavalues": [sensor_data],
        "software_version": VERSION
    }

    req = requests.post(API_URL, data)

    print(req.text)


data = (23.5, 0, 0)

push_to_map(data)