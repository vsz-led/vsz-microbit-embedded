const int halleffect1 = 0; //hall effect sensor 1 is connected to input pin 0
const int halleffect2 = 1; //hall effect sensor 2 is connected to input pin 1
const int halleffect3 = 2; //hall effect sensor 3 is connected to input pin 2

const int ledgreen = 3; //the green leds are connected to pin 3

const int led1 = 4; //led1 (red) is connected to output pin 4
const int led2 = 6; //led2 (red) is connected to output pin 6
const int led3 = 7; //led3 (red) is connected to output pin 7
const int led4 = 16; //led4 (red) is connected to output pin 16

//initialize sensor states and time
int zuid = 0;
int west = 0;
int oost = 0;
int time = 0;

void setup() {
  //configure hall effect pin as input
  pinMode(halleffect1, INPUT);
  pinMode(halleffect2, INPUT);
  pinMode(halleffect3, INPUT);
  //configure led pins as output
  pinMode(ledgreen, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  //start serial for debugging hall effect sensor state
  Serial.begin(9600);
  Serial.println("amogus");
}

void loop() {
  //turn off green led if it was on
  digitalWrite(ledgreen, LOW);
  
  //fetch hall effect sensor state
  oost = digitalRead(halleffect1);
  zuid = digitalRead(halleffect2);
  west = digitalRead(halleffect3);


  if (oost == LOW | zuid == LOW | west == LOW) {
    //input detected
    if (zuid == LOW) {
      digitalWrite(led2, HIGH);
      digitalWrite(led4, HIGH);
    }
    if (oost == LOW) {
      digitalWrite(led1, HIGH);
    }
    if (west == LOW) {
      digitalWrite(led3, HIGH);
    }
  } else {
    //input not detected, red led can turn off and time can increase for idle led
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    time++;
    
    //check if time limit to blink has been reached
    if (time >= 500) {
      //reset time limit
      time = 0;
      //turn on green led
      digitalWrite(ledgreen, HIGH);
      //wait
      delay(100);
    }
  }

  //delay to keep counter static
  delay(10);
}

void testleds() {
  digitalWrite(ledgreen, HIGH);
  delay(100);
  digitalWrite(ledgreen, LOW);
  delay(100);
  digitalWrite(led1, HIGH);
  delay(100);
  digitalWrite(led1, LOW);
  delay(100);
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led2, LOW);
  delay(100);
  digitalWrite(led3, HIGH);
  delay(100);
  digitalWrite(led3, LOW);
  delay(100);
  digitalWrite(led4, HIGH);
  delay(100);
  digitalWrite(led4, LOW);
  delay(100);
}

void testsensors() {
  Serial.print("sensor 1: ");
  Serial.println(digitalRead(halleffect1));
  Serial.print("sensor 2: ");
  Serial.println(digitalRead(halleffect2));
  Serial.print("sensor 3: ");
  Serial.println(digitalRead(halleffect3));
}
