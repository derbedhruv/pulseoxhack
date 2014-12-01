#!/usr/bin/env python

############################################################################################################
# Hacking a pulse oximeter to get its outputs
# Alankar Kotwal <alankarkotwal13@gmail.com>
#
# Details about Galileo pin-mapping:
# https://communities.intel.com/servlet/JiveServlet/downloadBody/21920-102-2-25976/GalileoIOMappingRev2.pdf
#
# Details about accessing GPIOs from Python:
# http://www.pridopia.co.uk/intel-galileo.html
#
# Pin details:
# Pin		| Input name
# ========= | ==========
# IO2		| CA
# IO3		| CB
# IO4		| CC
# IO5		| Aa
# IO6		| Ab
# IO7		| Ac
# IO8		| Ad
# IO9		| Ae
# IO10		| Af
# IO11		| Ag
############################################################################################################

import 	GPIO_Intel as GPIO
import time, sys, os

# Define the output
spo2Tens  = 0
spo2Units = 0
spo2      = 0

# Create a GPIO object
io = GPIO.Intel()

# Setup pin directions
io.setup('IO2', 'in')
io.setup('IO3', 'in')
io.setup('IO4', 'in')
io.setup('IO5', 'in')
io.setup('IO6', 'in')
io.setup('IO7', 'in')
io.setup('IO8', 'in')
io.setup('IO9', 'in')
io.setup('IO10', 'in')
io.setup('IO11', 'in')

# Setup pin dictionary
pins = {'CA': 'IO2',
		'CB': 'IO3',
		'CC': 'IO4',
		'Aa': 'IO5',
		'Ab': 'IO6',
		'Ac': 'IO7',
		'Ad': 'IO8',
		'Ae': 'IO9',
		'Af': 'IO10',
		'Ag': 'IO11'}

# Setup a 7-segment to binary dictionary
conv = {0b1110111: 0,
		0b0100100: 1,
		0b1011101: 2,
		0b1101101: 3,
		0b0101110: 4,
		0b1101011: 5,
		0b1111011: 6,
		0b0100101: 7,
		0b1111111: 8,
		0b1101111: 9}

# Start reading
while 1:
	anData = int(io.input(pins['Aa'])) | int(io.input(pins['Ab']))<<1 | int(io.input(pins['Ac']))<<2 | int(io.input(pins['Ad']))<<3 | int(io.input(pins['Ae']))<<4 | int(io.input(pins['Af']))<<5 | int(io.input(pins['Ag']))<<6
	catData = int(io.input(pins['CA'])) | int(io.input(pins['CB']))<<1 | int(io.input(pins['CC']))<<2

	if catData == 2:
		spo2Tens = conv[catData]
	elif catData == 4:
		spo2Units = conv[catData]
	else:
		pass
	
	if spo2Tens!=0 and spo2Units!=0:
		spo2 = 10*spo2Tens + spo2Units
	
	print spo2
