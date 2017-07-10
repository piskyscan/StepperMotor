#!/usr/bin/env python2.7

import pigpio
import time
from time import sleep

import RPi.GPIO as GPIO


state = 1
pi = pigpio.pi()       # pi1 accesses the local Pi's GPIO
time_stamp = time.time()
tickcount = 0
startHz = 5
lastTime = 0




def my_callback(a,b,c):
        global tickcount       # put in to debounce
        global startHz       # Current speed
        global state
        global lastTime
        
        if (state ==0):
                if (lastTime > 0):
                        print "Left",c

        state = 1
        lastTime = c
        
                
                

def my_callback1(a,b,c):
        
        global tickcount       # put in to debounce
        global startHz       # Current speed
        global state
        global lastTime

        if (state == 1):
                if (lastTime > 0):
                        print "Right",c

        state = 0
        lastTime = c
        
def up():
        GPIO.setmode(GPIO.BCM)

        outport1 = 17
        outport2 = 27
        outport3 = 22
        outport4 = 18
        
        for x in range(0, 200):
                offset = x % 8
#        pwm = GPIO.PWM(outport, startHz) # 100 Hz

                GPIO.output(outport1, seq[offset][0])  
                GPIO.output(outport2, seq[offset][1])  
                GPIO.output(outport3, seq[offset][2])  
                GPIO.output(outport4, seq[offset][3])  


        
inport = 25
inport2 = 24
outport1 = 17
outport2 = 27
outport3 = 22
outport4 = 18

outport5 = 5
outport6 = 6
outport7 = 13
outport8 = 26

timeStep = 0.005
steps = 50


        
GPIO.setmode(GPIO.BCM)
GPIO.setup(inport, GPIO.IN,pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(inport2, GPIO.IN,pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(outport1, GPIO.OUT)
GPIO.setup(outport2, GPIO.OUT)
GPIO.setup(outport3, GPIO.OUT)
GPIO.setup(outport4, GPIO.OUT)


GPIO.setup(outport5, GPIO.OUT)
GPIO.setup(outport6, GPIO.OUT)
GPIO.setup(outport7, GPIO.OUT)
GPIO.setup(outport8, GPIO.OUT)


print "ON"

seq = [
        [1,0,0,0],
        [1,1,0,0],
        [0,1,0,0],
        [0,1,1,0],
        [0,0,1,0],
        [0,0,1,1],
        [0,0,0,1],
        [1,0,0,1]]


# Lets see what this does


# pi.set_PWM_dutycycle(4, 18)



# pi.callback(inport, GPIO.RISING, my_callback)  
# pi.callback(inport2, GPIO.RISING, my_callback1)

import curses
stdscr = curses.initscr()
curses.cbreak()
stdscr.keypad(1)

stdscr.addstr(0,10,"Hit 'q' to quit")
stdscr.refresh()

key = ''
while key != ord('q'):
    key = stdscr.getch()
    stdscr.addch(20,25,key)
    stdscr.refresh()
    if key == curses.KEY_UP: 
	for x in range(0, steps):
	        offset = x % 8

	        GPIO.output(outport1, seq[offset][0])  
	        GPIO.output(outport2, seq[offset][1])  
	        GPIO.output(outport3, seq[offset][2])  
	        GPIO.output(outport4, seq[offset][3])  
	        sleep(timeStep)

        
    elif key == curses.KEY_DOWN: 
	for x in range(0, steps):
        	offset = 7 - (x % 8)

	        GPIO.output(outport1, seq[offset][0])  
	        GPIO.output(outport2, seq[offset][1])  
	        GPIO.output(outport3, seq[offset][2])  
        	GPIO.output(outport4, seq[offset][3])  
	        sleep(timeStep)


    elif key == curses.KEY_LEFT: 
	for x in range(0, steps):
	        offset = x % 8
	        GPIO.output(outport5, seq[offset][0])  
	        GPIO.output(outport6, seq[offset][1])  
	        GPIO.output(outport7, seq[offset][2])  
	        GPIO.output(outport8, seq[offset][3])  
	        sleep(timeStep)

    elif key == curses.KEY_RIGHT: 
	for x in range(0, steps):
	        offset = 7 - (x % 8)
	        GPIO.output(outport5, seq[offset][0])  
	        GPIO.output(outport6, seq[offset][1])  
	        GPIO.output(outport7, seq[offset][2])  
	        GPIO.output(outport8, seq[offset][3])  
	        sleep(timeStep)

curses.endwin()


# pwm.stop()  
GPIO.cleanup()    

print "OFF"

