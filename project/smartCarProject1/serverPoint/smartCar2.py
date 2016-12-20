#!/usr/bin/python
# -*- coding: <utf-8> -*-

#Get the GPIO module
import RPi.GPIO as GPIO
#Get the time module
import time
from time import sleep
#Get the socket module
import socket
#Some IP constants for this, the server
UDP_IP="192.168.20.1"	#IP Address
UDP_PORT = 8888		#default port : 8888
#PWM PIN
PWM_Max = 100
PWM_Min = 30
PWM_Value = 100      # Value:0-100
PWM_Frequence = 100  # Frequence:100Hz
#Get rid of warnings
GPIO.setwarnings(False)
#Set the GPIO mode
GPIO.setmode(GPIO.BOARD)
#Set the pins to be outputs
GPIO.setup(11,GPIO.OUT)
GPIO.setup(12,GPIO.OUT)
GPIO.setup(13,GPIO.OUT)
GPIO.setup(15,GPIO.OUT)
P11 = GPIO.PWM(11,PWM_Frequence)
P12 = GPIO.PWM(12,PWM_Frequence)
P11.start(0)
P12.start(0)
#rcw_0006_measure_distance
GPIO.setmode(GPIO.BOARD)
TRIGGER_PIN = 16
ECHO_PIN    = 18
GPIO.setup(TRIGGER_PIN,  GPIO.OUT)
GPIO.setup(ECHO_PIN,     GPIO.IN)
GPIO.output(TRIGGER_PIN, GPIO.LOW)
v = 343         # (331 + 0.6*20)

def measure() :
    GPIO.output(TRIGGER_PIN, GPIO.HIGH)
    time.sleep(0.00002) # 10uS 
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

def measure_average() :
    d1 = measure()
    time.sleep(0.05)
    d2 = measure()
    time.sleep(0.05)
    d3 = measure()
    distance = (d1 + d2 + d3) / 3

    return distance

#A routine to control a pair of pins
def ControlAPairOfPins(FirstPin,FirstState,SecondPin,SecondState,PwmData):
    print("Controlling pins")
    if FirstState == "1":
        #GPIO.output(int(FirstPin),True)
        if FirstPin=="11":
            P11.ChangeDutyCycle(PwmData)
        else:
            P12.ChangeDutyCycle(PwmData)
    else:
        #GPIO.output(int(FirstPin),False)
        if FirstPin=="11":
            P11.ChangeDutyCycle(0)
        else:
            P12.ChangeDutyCycle(0)
    if SecondState == "1":
        GPIO.output(int(SecondPin),True)
    else:
        GPIO.output(int(SecondPin),False)
            #Just retur
    return

####Main body of code
#Set up the IP related details
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
print "Pi_Robot server started ...."

try:
    while True:
    #Show rcw_0006_measure_distance
        distance = measure_average()
        print "Distance : %.1f" % distance
    #Wait for a UDP command to be received
        print("Waiting for UDP command")
        MyChar, addr = sock.recvfrom(1024) #buffer size is 1024
        print "I received: " + MyChar
        if MyChar == "forward":
            ControlAPairOfPins("12","1","13","1",PWM_Max)
            ControlAPairOfPins("11","1","15","1",PWM_Max)
            sleep(0.1)
            ControlAPairOfPins("12","1","13","1",PWM_Value)
            ControlAPairOfPins("11","1","15","1",PWM_Value)
            print "Forward"
        elif MyChar == "stop":
            ControlAPairOfPins("12","0","13","0",PWM_Value)
            ControlAPairOfPins("11","0","15","0",PWM_Value)
            print "Stop"
        elif MyChar == "back":
            ControlAPairOfPins("12","1","13","0",PWM_Max)
            ControlAPairOfPins("11","1","15","0",PWM_Max)
            sleep(0.1)
            ControlAPairOfPins("12","1","13","0",PWM_Value)
            ControlAPairOfPins("11","1","15","0",PWM_Value)
            print "Back"
        elif MyChar == "left":
            ControlAPairOfPins("12","1","13","1",PWM_Max)
            sleep(0.1)        	
            ControlAPairOfPins("12","1","13","1",50)
            ControlAPairOfPins("11","0","15","0",50)
            print "Left"
        elif MyChar == "right":
            ControlAPairOfPins("11","1","15","1",PWM_Max)
            sleep(0.1)  
            ControlAPairOfPins("12","0","13","0",50)
            ControlAPairOfPins("11","1","15","1",50)
            print "Right"
        elif MyChar == "speedup":
            if PWM_Value <= PWM_Max - 5:
                PWM_Value = PWM_Value + 5
            else:
                PWM_Value = PWM_Max
            print "speedup:" 
            print PWM_Value
        elif MyChar == "speeddown":
            if PWM_Value >= PWM_Min + 5:
                PWM_Value = PWM_Value - 5
            else:
                PWM_Value = PWM_Min;
            print "speeddown:"
            print PWM_Value
        else:
            print "Not a command"
        print("Run Next command")

except KeyboardInterrupt:
    GPIO.output(11,0)
    GPIO.output(12,0)
    GPIO.output(13,0)
    GPIO.output(15,0)
    P11.stop()
    P12.stop()
    GPIO.cleanup()
    
