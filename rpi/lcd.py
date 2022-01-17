# -*- coding: utf-8 -*-
# original code found at:
# https://gist.github.com/denisfromhr/cc863375a6e19dce359d

"""
compiled, mashed and generally mutilated 2014-2015 by denis pleic
made available under gnu general public license

# modified python i2c library for raspberry pi
# as found on http://www.recantha.co.uk/blog/?p=4849
# joined existing 'i2c_lib.py' and 'lcddriver.py' into a single library
# added bits and pieces from various sources
# by denisfromhr (denis pleic)
# 2015-02-10, ver 0.1

"""

from smbus2 import SMBus
from time import *

# i2c bus (0 -- original pi, 1 -- rev 2 pi)
i2cbus = 1

# lcd address
address = 0x27

class i2c_device:
   def __init__(self, addr, port=i2cbus):
      self.addr = addr
      self.bus = SMBus(port)

# write a single command
   def write_cmd(self, cmd):
      self.bus.write_byte(self.addr, cmd)
      sleep(0.0001)

# write a command and argument
   def write_cmd_arg(self, cmd, data):
      self.bus.write_byte_data(self.addr, cmd, data)
      sleep(0.0001)

# write a block of data
   def write_block_data(self, cmd, data):
      self.bus.write_block_data(self.addr, cmd, data)
      sleep(0.0001)

# read a single byte
   def read(self):
      return self.bus.read_byte(self.addr)

# read
   def read_data(self, cmd):
      return self.bus.read_byte_data(self.addr, cmd)

# read a block of data
   def read_block_data(self, cmd):
      return self.bus.read_block_data(self.addr, cmd)


# commands
lcd_cleardisplay = 0x01
lcd_returnhome = 0x02
lcd_entrymodeset = 0x04
lcd_displaycontrol = 0x08
lcd_cursorshift = 0x10
lcd_functionset = 0x20
lcd_setcgramaddr = 0x40
lcd_setddramaddr = 0x80

# flags for display entry mode
lcd_entryright = 0x00
lcd_entryleft = 0x02
lcd_entryshiftincrement = 0x01
lcd_entryshiftdecrement = 0x00

# flags for display on/off control
lcd_displayon = 0x04
lcd_displayoff = 0x00
lcd_cursoron = 0x02
lcd_cursoroff = 0x00
lcd_blinkon = 0x01
lcd_blinkoff = 0x00

# flags for display/cursor shift
lcd_displaymove = 0x08
lcd_cursormove = 0x00
lcd_moveright = 0x04
lcd_moveleft = 0x00

# flags for function set
lcd_8bitmode = 0x10
lcd_4bitmode = 0x00
lcd_2line = 0x08
lcd_1line = 0x00
lcd_5x10dots = 0x04
lcd_5x8dots = 0x00

# flags for backlight control
lcd_backlight = 0x08
lcd_nobacklight = 0x00

en = 0b00000100 # enable bit
rw = 0b00000010 # read/write bit
rs = 0b00000001 # register select bit

class lcd:
   #initializes objects and lcd
   def __init__(self):
      self.lcd_device = i2c_device(address)

      self.lcd_write(0x03)
      self.lcd_write(0x03)
      self.lcd_write(0x03)
      self.lcd_write(0x02)

      self.lcd_write(lcd_functionset | lcd_2line | lcd_5x8dots | lcd_4bitmode)
      self.lcd_write(lcd_displaycontrol | lcd_displayon)
      self.lcd_write(lcd_cleardisplay)
      self.lcd_write(lcd_entrymodeset | lcd_entryleft)
      sleep(0.2)


   # clocks en to latch command
   def lcd_strobe(self, data):
      self.lcd_device.write_cmd(data | en | lcd_backlight)
      sleep(.0005)
      self.lcd_device.write_cmd(((data & ~en) | lcd_backlight))
      sleep(.0001)

   def lcd_write_four_bits(self, data):
      self.lcd_device.write_cmd(data | lcd_backlight)
      self.lcd_strobe(data)

   # write a command to lcd
   def lcd_write(self, cmd, mode=0):
      self.lcd_write_four_bits(mode | (cmd & 0xf0))
      self.lcd_write_four_bits(mode | ((cmd << 4) & 0xf0))

   # write a character to lcd (or character rom) 0x09: backlight | rs=dr<
   # works!
   def lcd_write_char(self, charvalue, mode=1):
      self.lcd_write_four_bits(mode | (charvalue & 0xf0))
      self.lcd_write_four_bits(mode | ((charvalue << 4) & 0xf0))
  
   # put string function with optional char positioning
   def lcd_display_string(self, string, line=1, pos=0):
    if line == 1:
      pos_new = pos
    elif line == 2:
      pos_new = 0x40 + pos
    elif line == 3:
      pos_new = 0x14 + pos
    elif line == 4:
      pos_new = 0x54 + pos

    self.lcd_write(0x80 + pos_new)

    for char in string:
      self.lcd_write(ord(char), rs)

   # clear lcd and set to home
   def lcd_clear(self):
      self.lcd_write(lcd_cleardisplay)
      self.lcd_write(lcd_returnhome)

   # define backlight on/off (lcd.backlight(1); off= lcd.backlight(0)
   def backlight(self, state): # for state, 1 = on, 0 = off
      if state == 1:
         self.lcd_device.write_cmd(lcd_backlight)
      elif state == 0:
         self.lcd_device.write_cmd(lcd_nobacklight)

   # add custom characters (0 - 7)
   def lcd_load_custom_chars(self, fontdata):
      self.lcd_write(0x40);
      for char in fontdata:
         for line in char:
            self.lcd_write_char(line)         
