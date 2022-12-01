static int halleffect1 = 0;
const int led1rood = 3;
const int led1groen = 4;

int state = 0;
int tijd = 0;

void setup() {
  pinMode(halleffect1, INPUT);
  pinMode(led1rood, OUTPUT);
  pinMode(led1groen, OUTPUT);
  Serial.begin(9600);
  Serial.println("amogus");
}

void loop() {
  digitalWrite(led1groen, LOW);

  state = digitalRead(halleffect1);
  if (state == LOW) {
    digitalWrite(led1rood, HIGH);
  } else {
    digitalWrite(led1rood, LOW);
    tijd++;
  }
  Serial.println(digitalRead(halleffect1));

  if (state == HIGH && tijd >= 500) {
    tijd = 0;
    digitalWrite(led1groen, HIGH);
    delay(100);
  }
  delay(10);
}
