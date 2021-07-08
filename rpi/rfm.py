import re
import busio
import board
from digitalio import DigitalInOut

import lcd
import adafruit_ssd1306
import adafruit_rfm9x

CS = DigitalInOut(board.CE1)
RESET = DigitalInOut(board.D25)
SPI = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)

rfm9x = adafruit_rfm9x.RFM9x(SPI, CS, RESET, 868.0)
rfm9x.tx_power = 17
rfm9x.enable_crc = True

display = lcd.lcd()

def get_data_from_packet(packet):
    packet = str(packet, 'utf-8')
    (temp, pre, hum, gas) = packet.split(',')

    print(temp)
    print(pre)
    print(hum)
    print(gas)

    temp = re.match(r'T: ([^"]+) degC', temp).group(1)
    pre = re.match(r' P: ([^"]+) hPa', pre).group(1)
    hum = re.match(r' H: ([^"]+) rH', hum).group(1)
    gas = re.match(r' G: ([^"]+) Omh', gas).group(1)

    return (temp, pre, hum, gas)

def listen_for_data():
    packet = rfm9x.receive()

    if not packet is None:
       (temp, pre, hum, gas)= get_data_from_packet(packet)

       print(temp)
       print(pre)
       print(hum)
       print(gas)

       #rfm9x.send(bytes("OK", "utf-8"))

       rssi = rfm9x.last_rssi

       display.lcd_display_string("Signal: {0} dB".format(rssi), 1)

       return (temp, pre, hum, gas)
    else:
       return None
