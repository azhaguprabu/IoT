#!/usr/bin/env python


import RPi.GPIO as GPIO  # Import GPIO Module
from time import sleep  # Import sleep Module for timing

GPIO.setmode(GPIO.BCM)  # Configures how we are describing our pin numbering
GPIO.setwarnings(False)  # Disable Warnings

OutputPins = [22, 23]  # Set the GPIO pins that are required

#Set our GPIO pins to outputs and set them to off

for i in OutputPins:
    GPIO.setup(i, GPIO.OUT)
    GPIO.output(i, False)

while (True):
# Step through each GPIO pin and set On
    for i in OutputPins:
        GPIO.output(i, True)
# Sleep for 5 seconds
    sleep(5)
# Step through each GPIO pin and set Off
    for i in OutputPins:
        GPIO.output(i, False)
    sleep(5)
