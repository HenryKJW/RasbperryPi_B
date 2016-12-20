#!/usr/bin/python
# -*- coding: <utf-8> -*-
#
# Measure the distance between RCW-0006 and nearest wall or solid object.
#
# Author : henry
# Date   : 11/18/2016

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
TRIGGER_PIN = 16  #D6-16-GPIO23
ECHO_PIN    = 18  #D7-18-GPIO24
GPIO.setup(TRIGGER_PIN,  GPIO.OUT)
GPIO.setup(ECHO_PIN,     GPIO.IN)
GPIO.output(TRIGGER_PIN, GPIO.LOW)
v = 343		# (331 + 0.6*20)

def measure():
    GPIO.output(TRIGGER_PIN, GPIO.HIGH)
    time.sleep(0.00004)	# 40us(10uS~50us,best setting 40us~50us)
    GPIO.output(TRIGGER_PIN, GPIO.LOW)
    pulse_start = time.time()

    while GPIO.input(ECHO_PIN) == GPIO.LOW:
        pulse_start = time.time()

    while GPIO.input(ECHO_PIN) == GPIO.HIGH:
        pulse_end = time.time()

    t = pulse_end - pulse_start

    d = t * v
    d = d/2
    return d*100

def measure_average():
    d1 = measure()
    time.sleep(0.1)
    d2 = measure()
    time.sleep(0.1)
    d3 = measure()
#    print "Distance : %.1f" % distance
#    print "d1:%.1f, d2:%.1f, d3:%.1f" %(d1,d2,d3)
    distance = (d1 + d2 + d3) / 3
    return distance
    
if __name__ == "__main__":
    try:
        while True :
            distance = measure_average()
            #Show rcw_0006_measure_distance
            print "Distance : %.1f" % distance
            time.sleep(1)
        
    except KeyboardInterrupt:
        print "Exception: KeyboardInterrupt"

    finally:
        GPIO.cleanup() 
