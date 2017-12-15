long s = 0;
long interval = 0;
int verde = 2 ;

void setup() {
  pinMode(verde, INPUT_PULLUP);
  Serial.begin(9600);
  //La costante RISING fa in modo che l'interrupt legga il valore 
  // quando il pin passa dal basso verso l'alto.
  attachInterrupt(digitalPinToInterrupt(verde), t, RISING);
}

void loop(){
}

void t(){
  //Scrivo sul monitor seriale la velocità con cui fa un giro la ventola
  interval = millis()-s;
  Serial.println(interval);
  s = millis();
  interval = 0;
}


