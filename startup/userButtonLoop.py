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

print "waiting for user button for SWARMSbb initialization"
file = open(inputDevice, "rb") # standard binary file input
event = file.read(inputEventSize)
while event:
  (time1, time2, type, code, value) = struct.unpack(inputEventFormat, event)
  if value == 1:
	print "user setup button pressed!"
	os.system("cd /home/root/alex/drivePy/startup/")
	os.system("./netConfig.sh")
	time.sleep(.5) 
	os.system("/home/root/alex/drivePy/launchDrivePy.sh")
  event = file.read(inputEventSize)
file.close()
