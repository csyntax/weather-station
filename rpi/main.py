#!/usr/bin/python3

import lcd
import rfm
import firebase
from datetime import datetime

display = lcd.lcd()

display.lcd_display_string('Init app', 1)

while True:
    try:
        data = rfm.listen_for_data(display)
        now = datetime.now().replace(microsecond=0).isoformat()
        firebase.push_to_firebase(now, data)
        display.lcd_clear()
        display.lcd_display_string('Success push to server')
    except(TypeError):
        pass