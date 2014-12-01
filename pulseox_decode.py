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

# Start reading
