#!/usr/bin/python3
import json
import os
import sys
import serial
from pynput.keyboard import Key, Controller

keyboard = Controller()

def readConfig():
    settingsFile = os.path.join(cwd, "config.json")
    with open(settingsFile) as json_file:
        data = json.load(json_file)
    return data

# Get the current working
# directory (CWD)
try:
    this_file = __file__
except NameError:
    this_file = sys.argv[0]
this_file = os.path.abspath(this_file)
if getattr(sys, 'frozen', False):
    cwd = os.path.dirname(sys.executable)
else:
    cwd = os.path.dirname(this_file)

print("Current working directory:", cwd)

# Read Config File
config = readConfig()
baudrate = config["baudrate"]
uart = config["uart"]
keyPress = config["keyPress"]

# setup Seiral
ser = serial.Serial(
        # Serial Port to read the data from
        port = uart,
        #Rate at which the information is shared to the communication channel
        baudrate = baudrate,
        # Number of serial commands to accept before timing out
        timeout=1
)

try:
    while 1:
        x=ser.readline().strip().decode()
        #print(x)
        if x.isnumeric():
            xInt = int(x)
            keyboard.press(keyPress[xInt])
            keyboard.release(keyPress[xInt])

except KeyboardInterrupt:
    killOmx()
killOmx()
