#define CA 2
#define CB 3
#define CC 4

#define Aa 5
#define Ab 6
#define Ac 7
#define Ad 8
#define Ae 9
#define Af 10
#define Ag 11

int data[6]; // 7-bit data for each of the displays
int anData;  // Anode data

int segmentB = 0, segmentC = 0, count = 0;	// segment display buffers and counter

void setup() {
  Serial.begin(9600);
  
  pinMode(CA, INPUT);
  pinMode(CB, INPUT);
  pinMode(CC, INPUT);
  
  pinMode(Aa, INPUT);
  pinMode(Ab, INPUT);
  pinMode(Ac, INPUT);
  pinMode(Ad, INPUT);
  pinMode(Ae, INPUT);
  pinMode(Af, INPUT);
  pinMode(Ag, INPUT);
}

void loop() {
  anData = digitalRead(Aa) | digitalRead(Ab)<<1 | digitalRead(Ac)<<2 | digitalRead(Ad)<<3 | digitalRead(Ae)<<4 | digitalRead(Af)<<5 | digitalRead(Ag)<<6;
  /*
  Serial.print(digitalRead(Aa));
  Serial.print("|");
  Serial.print(digitalRead(Ab));
  Serial.print("|");
  Serial.print(digitalRead(Ac));
  Serial.print("|");
  Serial.print(digitalRead(Ad));
  Serial.print("|");
  Serial.print(digitalRead(Ae));
  Serial.print("|");
  Serial.print(digitalRead(Af));
  Serial.print("|");
  Serial.println(digitalRead(Ag));
  */
    
  switch(digitalRead(CA) |  digitalRead(CB)<<1 | digitalRead(CC)<<2) {
    case 7: {
      // Serial.print(anData);
      data[0] = Seg2Bin(anData);
      // Serial.println(data[0]);
      break;
    } 
    case 5: {
      // Serial.print(anData);
      data[1] = Seg2Bin(anData);
      // Serial.println(data[1]);
      break;
    }
    case 3: {
      // Serial.print(anData);
      data[2] = Seg2Bin(anData);
      // Serial.println(data[2]);
      break;
    }
    default: {
      // Serial.println(digitalRead(CA) |  digitalRead(CB)<<1 | digitalRead(CC)<<2);
      break;
    }
  }
  delay(1);
  
  
  if (data[2] != 0) {    // do not consider value '0'
    segmentC = data[2];
  }
  
  
  if (data[1] != 0) {    // do not consider value '0'
    segmentB = data[1];
  }
 
  if (count >= 100) { 
    // after 1000 counts, the values settle to what we observe on the display
    Serial.println(10*segmentB + segmentC);    // print the "O2 sat"
    count = 0;
  }
  count++;
}

int Seg2Bin(int in) {
  switch(in) {
    case 0b1110111: {
      return 0;
    }
    case 0b0100100: {
      return 1;
    }
    case 0b1011101: {
      return 2;
    }
    case 0b1101101: {
      return 3;
    }
    case 0b0101110: {
      return 4;
    }
    case 0b1101011: {
      return 5;
    }
    case 0b1111011: {
      return 6;
    }
    case 0b0100101: {
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
