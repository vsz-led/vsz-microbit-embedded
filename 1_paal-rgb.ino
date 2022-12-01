const int halleffect1 = 0; //hall effect sensor is connected to input pin 0
const int led1red = 3; //led1 rood is connected to output pin 3
const int led1green = 4; //led1 groen is connected to output pin 3

//initialize state and time
int state = 0;
int time = 0;

void setup() {
  //configure hall effect pin as input
  pinMode(halleffect1, INPUT);
  //configure led pins as output
  pinMode(led1red, OUTPUT);
  pinMode(led1green, OUTPUT);
  //start serial for debugging hall effect sensor state
  Serial.begin(9600);
  Serial.println("amogus");
}

void loop() {
  //turn off green led if it was on
  digitalWrite(led1green, LOW);

  //fetch hall effect sensor state
  state = digitalRead(halleffect1);
  if (state == LOW) {
    //input detected, red led will turn on
    digitalWrite(led1red, HIGH);
  } else {
    //input not detected, red led can turn off and time can increase for idle led
    digitalWrite(led1red, LOW);
    time++;
    
    //check if time limit to blink has been reached
    if (time >= 500) {
      //reset time limit
      time = 0;
      //turn on green led
      digitalWrite(led1green, HIGH);
      //wait
      delay(100);
    }
  }

  //debug print hall effect sensor state
  Serial.println(state);

  //delay to keep counter static
  delay(10);
}
