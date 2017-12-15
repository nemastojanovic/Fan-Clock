#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>


//pin da cui comando i led 
#define PIN 6

long s = 0;
long interval = 0;
int verde = 2 ;

//la variabile toogle indica se i led dovrano essere spenti (true) o accessi (false)
bool toogle = true;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(verde, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(verde), t, RISING);
  //richiamo begin per poter preparare i pin dei led
  strip.begin();
    
  //setto la luminosità dei led
  strip.setBrightness(100);
}

void loop(){
}

void t(){
    //alterno l'accesione e lo spengimento dei led
    toogle = !toogle;
    
    //passo tutti i led uno a uno
    for(int j = 0; j < strip.numPixels(); j++){
      if(toogle){
        //se toggle è true spengo tutti i led
        strip.setPixelColor(j, 0, 0, 0);
      }
      else{
        //altrimenti accendo tutti i led
        strip.setPixelColor(j, 255, 255, 255);
      }
    }
    
    //applico i dati alla striscia
    strip.show();
}


