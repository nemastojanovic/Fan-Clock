
int verde = 2 ;

void setup() {
  // put your setup code here, to run once:
  pinMode(verde, INPUT);
  Serial.begin(9600);
  //La costante RISING fa in modo che l'interrup legga il valore 
  // quando il pin passa dal basso verso l'alto.
  attachInterrupt(digitalPinToInterrupt(verde), m, RISING);
}

void loop(){
  delay(500);
}

void m(){
  //scrivo il vaore sul monitor seriale
  Serial.println(digitalRead(verde));
}


