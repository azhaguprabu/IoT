from threading import Thread
import time
import RPi.GPIO as GPIO

var = 0
pairvalue = 0

def Alert_Buzzer():
    global pairvalue
    while True:
        if var==0:
            GPIO.output(3, 0)
            if pairvalue==1:
                pairvalue = 0
                print "No Intruder {0} {1}".format(var,time.strftime("%H:%M:%S"))
        elif var==1:
            GPIO.output(3, 1)
            if pairvalue==0:
                print "Intruder Detected {0} {1}".format(var,time.strftime("%H:%M:%S"))
                pairvalue = 1
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
#Buzzer
GPIO.setup(3,GPIO.OUT)

thread1 = Thread( target=Read_Sensor )
thread2 = Thread( target=Alert_Buzzer )

thread1.start()
thread2.start()
thread1.join()
thread2.join()
