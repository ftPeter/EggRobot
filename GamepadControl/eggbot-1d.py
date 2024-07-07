"""
    eggbot-1d.py
    Peter F. Klemperer
    July 6, 2024

    Program for controlling the 1D eggbot from my blue PS4 controller

    Example command to send to the eggbot:
    <P,0.0>  - move pendulum to 0 degrees
"""

import hid

gamepad = hid.device()
# magic numbers for my blue ps4 controller
gamepad.open(0x054c, 0x05c4) 
gamepad.set_nonblocking(True)

import serial

ser = serial.Serial("/dev/tty.usbmodem2101")


while True:
    report = gamepad.read(64)
    if report:
        stick_ranged = ( report[3] / 256.0 ) * 2.0 - 1.0
        print("Right stick: {} to {}.".format(report[3], stick_ranged))
        ser.write('<P,{}>\n'.format(stick_ranged).encode('utf-8'))

