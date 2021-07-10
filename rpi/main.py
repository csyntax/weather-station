#!/usr/bin/python3

import rfm
import firebase
from datetime import datetime

while True:
    try:
        data = rfm.listen_for_data()
        now = datetime.now().replace(microsecond=0).isoformat()

        firebase.push_to_firebase(now, data)
    except(TypeError):
        pass
