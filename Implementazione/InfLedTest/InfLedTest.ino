//dichiaro il pin da cui leggero il valore della fotoresistenza
int pc = A0;

void setup() {
  //pinMode(infLed, INPUT_PULLUP);
  Serial.begin(9600);
  //attachInterrupt(digitalPinToInterrupt(infLed), printHigh, RISING);
}

void loop() {
  
  //leggo il valore della fotoresistenza
  int photocell = analogRead(pc);

  Serial.println(photocell);
  delay(1);
}
void printHigh(){
  Serial.println(analogRead(pc));
}
