from threading import Thread
import time
import RPi.GPIO as GPIO
import requests
 
var = 0
pairvalue = 0

def Alert_Buzzer():
    global pairvalue
    while True:
        if var==0:
            GPIO.output(7,0)
            GPIO.output(13,1)
            if pairvalue==1:
                pairvalue = 0
                #print "No Intruder {0} {1}".format(var,time.strftime("%H:%M:%S"))
                payload = {'key': '2DHLE2S41N', 'val': 1}
                r = requests.get('http://www.newgatewaysolution.com/iot/set.php',params=payload)
        elif var==1:
            GPIO.output(13,0)
            GPIO.output(7,1)
            if pairvalue==0:
                pairvalue = 1
                #print "Intruder Detected {0} {1}".format(var,time.strftime("%H:%M:%S"))
                payload = {'key': '2DHLE2S41N', 'val': 0}
                r = requests.get('http://www.newgatewaysolution.com/iot/set.php',params=payload)
        time.sleep(1)

def Read_Sensor():
    global var
    while True: 
        var = GPIO.input(11)
        time.sleep(0.1)

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
#Sensor Pin
GPIO.setup(11,GPIO.IN)
#RED LED
GPIO.setup(7,GPIO.OUT)
#GREEN LED
GPIO.setup(13,GPIO.OUT)

thread1 = Thread( target=Read_Sensor )
thread2 = Thread( target=Alert_Buzzer )

thread1.start()
thread2.start()
thread1.join()
thread2.join()
