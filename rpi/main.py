#!/usr/bin/python3

import lcd
import rfm
import firebase
from time import sleep
from datetime import datetime

def init():
    display = lcd.lcd()

    display.lcd_clear()
    display.lcd_display_string('Init app', 1)
    display.lcd_display_string('Wait for data', 2)

    return display

def load(display):
    try:
        display.lcd_clear()
        display.lcd_display_string('Wait for data', 1)
        data = rfm.listen_for_data(display)
        now = datetime.now().replace(microsecond=0).isoformat()
        firebase.push_to_firebase(now, data)
        display.lcd_clear()
    except(TypeError):
        pass

while True:
    display = init()
    sleep(3)
    load(display)