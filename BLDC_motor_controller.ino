/*

 
 */

int A_sensor_pin = 4;    //define hall sensor pins
int B_sensor_pin = 3;
int C_sensor_pin = 2;

int A_high = 7; //define high and low coil pins
int B_high = 6;
int C_high = 5;
int A_low = 11;
int B_low = 10;
int C_low = 9;

int ledPin = 13;      // select the pin for the LED
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13
int A_sensor=0, B_sensor=0, C_sensor=0;  // variable to store the value coming from the sensor

int currentPhase = 0;
int prevPhase = 0;
int combine  = 0;
int ledPinState = 0;
int torqueLevel = 200;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
  pinMode(A_sensor_pin, INPUT); 
  pinMode(B_sensor_pin, INPUT); 
  pinMode(C_sensor_pin, INPUT); 


  pinMode(A_high, OUTPUT); 
  pinMode(B_high, OUTPUT); 
  pinMode(C_high, OUTPUT); 
//  pinMode(A_low, OUTPUT); 
//  pinMode(B_low, OUTPUT); 
//  pinMode(C_low, OUTPUT); 

  Serial.begin(115200);
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);  
  allOff();
  analogWrite(C_low, torqueLevel);
}

void loop() {
  // turn the ledPin on
  digitalWrite(ledPin, ledPinState);  

  // read the value from the hall sensors:
  A_sensor = digitalRead(B_sensor_pin);    
  B_sensor = digitalRead(C_sensor_pin);    
  C_sensor = digitalRead(A_sensor_pin);    
    
  currentPhase   = (A_sensor << 2) + (B_sensor << 1) + (C_sensor);
//
//  Serial.print(A_sensor);Serial.print(" ");   
//  Serial.print(B_sensor);Serial.print(" ");   
//  Serial.print(C_sensor);Serial.print(": ");   
//  Serial.print(currentPhase, BIN);
//  Serial.print("  Phase: ");
//  Serial.println(findPhase(currentPhase));
//  
//  if(currentPhase == 0)
//  {
//    Serial.print(currentPhase, BIN);
//    Serial.print("  Phase: ");
//    Serial.println(findPhase(currentPhase));
//  }

  if(currentPhase != prevPhase)
  {
    allOff();
    setPhase(findPhase(currentPhase));
    //Serial.print("Change in phase");
    if(ledPinState == 1)
    {
      ledPinState = 0;
    }
    else
    {
      ledPinState = 1;
    }
  }


  prevPhase = currentPhase;

  //delayMicroseconds(50);

}

int findPhase(int phaseSet)
{
  if(phaseSet == B00000001)
  {
    return(1);
  }
  else if(phaseSet == B00000101)
  {
    return(2);
  }
  else if(phaseSet == B00000100)
  {
    return(3);
  }
  else if(phaseSet == B00000110)
  {
    return(4);
  }
  else if(phaseSet == B00000010)
  {
    return(5);
  }
  else if(phaseSet == B00000011)
  {
  return(6);
  }  
  else{
    return(0);
  }
}


void setPhase(int phase){
  switch (phase){
    case 0:
      Serial.println("invlaid case:0");
      break;
    case 1:
      digitalWrite(B_high, HIGH);
      analogWrite(C_low, torqueLevel);
      break;
    case 2:
      digitalWrite(B_high, HIGH);
      analogWrite(A_low, torqueLevel);
      break;
    case 3:
      digitalWrite(C_high, HIGH);
      analogWrite(A_low, torqueLevel);
      break;
    case 4:
      digitalWrite(C_high, HIGH);
      analogWrite(B_low, torqueLevel);
      break;
    case 5:
      digitalWrite(A_high, HIGH);
      analogWrite(B_low, torqueLevel);
      break;
    case 6:
      digitalWrite(A_high, HIGH);
      analogWrite(C_low, torqueLevel);
      break;
    default:
      break;
  }
}

void allOff(){
  digitalWrite(A_high,LOW);
  digitalWrite(B_high,LOW);
  digitalWrite(C_high,LOW);

  analogWrite(A_low, 0);
  analogWrite(B_low, 0);
  analogWrite(C_low, 0);
}








