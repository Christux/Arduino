#!/usr/bin/env python
# -*- coding: utf8 -*-

#
# Copyright Christux 2017
#

# Serial client for arduino's sketch
import serial
import time
import sys
import signal

# Define web client abstract class
class ArduinoSerial():

	def __init__(self,device,br):
		self.sdevice=serial.Serial(device,br) #Open serial port
		print("Start serial arduino")
		time.sleep(2) #Wait to serial openning
		
		# Catch end signals
		signal.signal(signal.SIGINT, self.close)
		signal.signal(signal.SIGTERM, self.close)
	
	# Send signal
	def send(self,animation):
		self.sdevice.write(str(animation))
		return self.sdevice.readline()

	# Close serial device
	def close(self):
		print("Close arduino serial")
		self.sdevice.close()
		

# Test object
class Test(ArduinoSerial):

	def run(self) :
    
		nAnim=6
    
		i=0
		while i<nAnim:

			data_received = self.send(i+1)
			print("Animation #"+data_received)
   			time.sleep(5)
    
			i+=1
		return

 
# Main function
if __name__ == '__main__':

	test = Test('/dev/tty.usbmodem641', 9600)
	test.run()
	test.close()
	