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

int segmentB = 0, segmentC = 0;
int ci = 1, bi = 1;                // counters for how many values have been added to the segmentB and C vriables respectively

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
    
  switch(digitalRead(CA) |  digitalRead(CB)<<1 | digitalRead(CC)<<2) {
    case 1: {
      data[0] = Seg2Bin(anData);
      break;
    } 
    case 2: {
      data[1] = Seg2Bin(anData);
      break;
    }
    case 4: {
      data[2] = Seg2Bin(anData);
      break;
    }
    default: {
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
  
  Serial.println(10*segmentB + segmentC);    // print the "O2 sat"
    
  /**/
  
  /*
  Serial.print("A: ");
  Serial.println(data[0]);
  
  Serial.print("B: ");
  Serial.print(data[1]);
  Serial.print('\t');
  Serial.print("C: ");
  Serial.println(data[2]);/**/
  
  // Serial.println(10*data[2]+data[1]);
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
