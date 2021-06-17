import re
import time
import busio
import board
from digitalio import DigitalInOut

import adafruit_ssd1306
import adafruit_rfm9x

CS = DigitalInOut(board.CE1)
RESET = DigitalInOut(board.D25)
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
rfm9x = adafruit_rfm9x.RFM9x(spi, CS, RESET, 915.0)
rfm9x.tx_power = 17

prev_packet = None

def get_data_from_packet(packet):
    packet = str(packet, 'utf-8')
    packet = packet.split(',')
    
    (temp, pre, hum) = packet

    print(temp)
    print(pre)
    print(hum)
    
    temp = re.match(r'T: ([^"]+) degC', temp).group(1)
    pre = re.match(r' P: ([^"]+) hPa', pre).group(1)
    hum = re.match(r' H: ([^"]+) rH', hum).group(1)
    
    return (temp, pre, hum)

def send_to_google_firebase(data):
    pass

while True:
    packet = rfm9x.receive()

    if not packet is None:
       (prev_packet, packet) = (packet, None)
       (temp, press, hum)= get_data_from_packet(prev_packet)
       
       print(temp)
       print(press)
       print(hum)
