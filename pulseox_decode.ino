/*****************************************************************
  CMS50D Pulse oximeter Hack

  Author: Dhruv Joshi

  This is a means to 'hack' the oxygen saturation values from a CMS50D fingertip pulse oximeter, which specifically uses 7-segment displays. 
  Arduino UNO or Micro are being used. THe pulse ox is being powered by the 3.3V pin from the board itself. The 7-segment mapping is assumed 
  to be as follows:

  	a
       ___
   f  |   |  b
      |___|  
   e  | g |  c
      |___|
        d

  And the mapping is being done to digital pins 4 - 12 as follows (9 pins total, 7 for anodes and 2 for two displays to display o2sat values in the range 0-99...

  4 - tens place
  5 - units place

  6 - a
  7 - b
  8 - f
  9 - g
 10 - c
 11 - e
 12 - d

  I'll try to make it generic so that if this order is changed, then one can easily make the changesis changed, then one can easily make the changes..

  Aa stands for Anode 'a' and so on.. CA and CB stand for the tens and units place of the oxygen saturation value respectively.

*/


#define CB 3
#define CC 4

#define Aa 6
#define Ab 7
#define Ac 10
#define Ad 12
#define Ae 11
#define Af 8
#define Ag 9

int data[2]; // 7-bit data for each of the two displays
int anData;  // Anode data, made by concatenating the bits together. So basically a snapshot of the digital pins Aa through Ag at a time

int segmentA = 0, segmentB = 0, count = 0;	// segment display buffers and counter

void setup() {
  Serial.begin(9600);
  
  // setting pinmodes
  pinMode(CA, INPUT);
  pinMode(CB, INPUT);
  
  pinMode(Aa, INPUT);
  pinMode(Ab, INPUT);
  pinMode(Ac, INPUT);
  pinMode(Ad, INPUT);
  pinMode(Ae, INPUT);
  pinMode(Af, INPUT);
  pinMode(Ag, INPUT);
}

void loop() {
  // concatenate the digital pins..
  anData = digitalRead(Aa) | digitalRead(Ab)<<1 | digitalRead(Ac)<<2 | digitalRead(Ad)<<3 | digitalRead(Ae)<<4 | digitalRead(Af)<<5 | digitalRead(Ag)<<6;
    
  // switch the cathode values to when the desired one is on, and take the corresponding decoded numeric value from the concatenated anodes
  switch(digitalRead(CA) |  digitalRead(CB)<<1) {
    case 1: {
      data[0] = Seg2Bin(anData);
      break;
    } 
    case 2: {
      data[1] = Seg2Bin(anData);
      break;
    }
    default: {
      break;
    }
  }
  delay(1);
  
  
  if (data[1] != 0) {    // do not consider value '0'
    segmentB = data[1];
  }
  
  
  if (data[0] != 0) {    // do not consider value '0'
    segmentA = data[0];
  }
 
  if (count >= 100) { 
    // after 1000 counts, the values settle to what we observe on the display
    Serial.println(10*segmentA + segmentB);    // print the "O2 sat"
    count = 0;
  }
  count++;
}

int Seg2Bin(int in) {
  // converts the concatenated digital pins into decimal unitary numbers
  // compare binary with gfedcba

  switch(in) {
    case 0b1110111: {
      return 0;
    }
    case 0b0010010: {
      return 1;
    }
    case 0b1011011: {
      return 2;
    }
    case 0b1001111: {
      return 3;
    }
    case 0b1100110: {
      return 4;
    }
    case 0b1101101: {
      return 5;
    }
    case 0b1111101: {
      return 6;
    }
    case 0b0000111: {
      return 7;
    }
    case 0b1111111: {
      return 8;
    }
    case 0b1101111: {
      return 9;
    }
    default: {
      return 0;
    }
  }
}
