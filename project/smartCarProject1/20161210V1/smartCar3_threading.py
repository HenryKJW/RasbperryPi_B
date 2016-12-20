#!/usr/bin/python
# -*- coding: <utf-8> -*-

#Get the GPIO module
import RPi.GPIO as GPIO
#Get the threading, time module
import threading,time
from time import sleep
#Get the socket module
import socket
#Get Self Module
import rcw_0006_measure_distance as rcw0006
import arduinoSensorI2C as ardSensor

#Some IP constants for this, the server
UDP_IP="192.168.20.1"	#IP Address
UDP_PORT = 8888		#default port : 8888

#PWM PIN
PWM_Max = 100
PWM_Min = 30
PWM_Value = 100      # Value:0-100
PWM_Frequence = 100  # Frequence:100Hz

#disable warnings
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

#arduino Sensor
#Buzzer
BuzzerOnOff=True
#Leaser
LeaserOnOff=False
#Led
LEDControlMode=0	#0-LED Off,1-LED Color(R),2-LED Color(G),3-LED Color(B),4-LED Time
LEDRedColor=0  		#0-no change,1-change Arduion(R=0)
LEDGreenColor=0  	#0-no change,1-change Arduion(G=1)
LEDBlueColor=0  	#0-no change,1-change Arduion(B=2)
RedPWM=0		# (light) 0~255 (drak)
GreenPWM=0	# (light) 0~255 (drak)
BluePWM=0		# (light) 0~255 (drak)
LEDaroundTime=0	# R -> G -> B

#threading code
ThreadingRuningStatus=1	#1-run, 0-stop
MCUlock = threading.Lock()
def RCW0006doAdd():
    global MCUlock,BuzzerOnOff
    while ThreadingRuningStatus==1:
        distance = rcw0006.measure_average()
        #Show rcw_0006_measure_distance
        #print "Distance : %.1f" % distance
        if distance<15 :
            if BuzzerOnOff==True:
                MCUlock.acquire()
                ardSensor.BuzzerOn(5)	#100ms
                MCUlock.release()
                time.sleep(0.8)
        elif distance<30 :
            if BuzzerOnOff==True:
                MCUlock.acquire()
                ardSensor.BuzzerOn(2)	#100ms
                MCUlock.release()
                time.sleep(0.5)
        else:
            time.sleep(1)
def LEDdoAdd():
    global MCUlock,LEDRedColor,LEDGreenColor,LEDBlueColor,RedPWM,GreenPWM,BluePWM,LEDaroundTime
    while ThreadingRuningStatus==1:
        if LEDaroundTime==0:
            if LEDRedColor==1:
                MCUlock.acquire()
                ardSensor.LedOff()
                ardSensor.LedOn(0,RedPWM)
                LEDRedColor=0
                MCUlock.release()
            elif LEDGreenColor==1:
                MCUlock.acquire()
                ardSensor.LedOff()
                ardSensor.LedOn(1,GreenPWM)
                LEDGreenColor=0
                MCUlock.release()
            elif LEDBlueColor==1:
                MCUlock.acquire()
                ardSensor.LedOff()
                ardSensor.LedOn(2,BluePWM)
                LEDBlueColor=0
                MCUlock.release()
            
        else:
            MCUlock.acquire()
            ardSensor.LedOn(0,0)
            MCUlock.release()
            time.sleep(LEDaroundTime)
            MCUlock.acquire()
            ardSensor.LedOff()
            MCUlock.release()            
            MCUlock.acquire()
            ardSensor.LedOn(1,0)
            MCUlock.release()
            time.sleep(LEDaroundTime)
            MCUlock.acquire()
            ardSensor.LedOff()
            MCUlock.release()            
            MCUlock.acquire()
            ardSensor.LedOn(2,0)
            MCUlock.release()
            time.sleep(LEDaroundTime)
            MCUlock.acquire()
            ardSensor.LedOff()
            MCUlock.release()
            
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
    threading.Thread(target = RCW0006doAdd,args=(),name='thread-rcw006').start()
    threading.Thread(target = LEDdoAdd,args=(),name='thread-led').start()
    while True:
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
        elif MyChar == "Sound":
            if BuzzerOnOff==True:
                BuzzerOnOff=False
            else: 
                BuzzerOnOff=True
            print "BuzzerOnOff:%d" %BuzzerOnOff
        elif MyChar == "Leaser":
            if LeaserOnOff==True:
                LeaserOnOff=False
                MCUlock.acquire()
                ardSensor.LeaserOn(LeaserOnOff)				#status- 1=On, 2=Off
                MCUlock.release()
            else:
                LeaserOnOff=True
                MCUlock.acquire()
                ardSensor.LeaserOn(LeaserOnOff)				#status- 1=On, 2=Off
                MCUlock.release()
            print "LeaserOnOff:%d" %LeaserOnOff
        elif MyChar == "LED Color":
            LEDaroundTime=0
            if LEDControlMode==1:
                LEDControlMode=2
                LEDGreenColor=1
            elif LEDControlMode==2:
                LEDControlMode=3
                LEDBlueColor=1
            elif LEDControlMode==3:
                LEDControlMode=1
                LEDRedColor=1
            else:
                LEDControlMode=1
                LEDRedColor=1
            time.sleep(0.5)
            print "LEDControlMode:%d" %(LEDControlMode)
        elif MyChar == "LED Time":
            LEDControlMode=4
            if LEDaroundTime==0:
                LEDaroundTime=1
            else:
                LEDaroundTime=0
            print "LEDControlMode:%d,LEDaroundTime:%d" %(LEDControlMode,LEDaroundTime)
        elif MyChar == "LedOn+":
            if LEDControlMode==4:
                LEDaroundTime+=1
                print "LedOn+ LEDaroundTime:%d" %LEDaroundTime
            elif LEDControlMode==1:
                if RedPWM >=20:
                    RedPWM-=20
                else:
                    RedPWM=0
                LEDRedColor=1
                print "LedOn+ RedPWM:%d" %RedPWM
            elif LEDControlMode==2:
                if GreenPWM >=20:
                    GreenPWM-=20
                else:
                    GreenPWM=0
                LEDGreenColor=1
                print "LedOn+ GreenPWM:%d" %GreenPWM
            elif LEDControlMode==3:
                if BluePWM >=20:
                    BluePWM-=20
                else:
                    BluePWM=0
                LEDBlueColor=1
                print "LedOn+ BluePWM:%d" %BluePWM
        elif MyChar == "LedOn-":
            if LEDControlMode==4:
                if LEDaroundTime>=1:
                    LEDaroundTime-=1
                else:
                    LEDaroundTime=1
                print "LedOn- LEDaroundTime:%d" %LEDaroundTime
            elif LEDControlMode==1:
                if RedPWM <=235:
                    RedPWM+=20
                else:
                    RedPWM=255
                LEDRedColor=1
                print "LedOn+ RedPWM:%d" %RedPWM
            elif LEDControlMode==2:
                if GreenPWM <=235:
                    GreenPWM+=20
                else:
                    GreenPWM=255
                LEDGreenColor=1
                print "LedOn+ GreenPWM:%d" %GreenPWM
            elif LEDControlMode==3:
                if BluePWM <=235:
                    BluePWM+=20
                else:
                    BluePWM=255
                LEDBlueColor=1
                print "LedOn+ BluePWM:%d" %BluePWM
        elif MyChar == "LedOff":
            LEDControlMode=0
            LEDaroundTime=0
            MCUlock.acquire()            
            ardSensor.LedOff()            
            MCUlock.release()
            print "LedOff"           
        else:
            print "Not a command"
        print("Run Next command")

except KeyboardInterrupt:
    print "Exception: KeyboardInterrupt"

finally:
    ThreadingRuningStatus=0
    GPIO.output(11,0)
    GPIO.output(12,0)
    GPIO.output(13,0)
    GPIO.output(15,0)
    P11.stop()
    P12.stop()
    GPIO.cleanup()
    
