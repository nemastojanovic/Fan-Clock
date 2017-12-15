long s = 0;
long interval = 0;
int verde = 2 ;

void setup() {
  pinMode(verde, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(verde), t, RISING);
}

void loop(){
}

void t(){
  interval = millis()-s;
  Serial.println(interval);
  s = millis();
  interval = 0;
}


