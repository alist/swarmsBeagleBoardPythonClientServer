# Beagleboard user button
# Copyright 2009 mechomaniac.com
import struct
import time
import os
inputDevice = "/dev/input/event0"
# format of the event structure (int, int, short, short, int)
inputEventFormat = 'iihhi'
inputEventSize = 16

#out = open("/home/root/user-button.txt", "w")

didStart = False
#light means we're ready!
os.system("echo 1 > /sys/class/leds/beagleboard\:\:usr1/brightness")
print "waiting for user button for SWARMSbb initialization"
file = open(inputDevice, "rb") # standard binary file input
event = file.read(inputEventSize)
while event:
  (time1, time2, type, code, value) = struct.unpack(inputEventFormat, event)
  if value == 1 and didStart == False:
	os.system("echo 0 > /sys/class/leds/beagleboard\:\:usr1/brightness")
	print "user setup button pressed!"
	os.system("cd /home/root/alex/drivePy/startup/")
	os.system("./netConfig.sh")
	time.sleep(.5) 
	os.system("/home/root/alex/drivePy/launchDrivePy.sh")
	didStart = True
  elif value == 1 and didStart == True:
	os.system("/home/root/alex/drivePy/startup/SWARMSd stop")
	didStart = False
  event = file.read(inputEventSize)
file.close()
