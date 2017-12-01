//librerie utili per poter comandare il led
#include <Adafruit_GFX.h> 
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

//pin da cui comando i led 
#define PIN 6

//la variabile toogle indica se i led dovrano essere spenti (true) o accessi (false)
bool toogle = true;

//Creo l'oggetto che mi permette di potere controllare la striscia di led
// Parametro 1 = numero di led della striscia 
// Parametro 2 = pin con cui commandare la striscia
// Parametro 3 = tipo di led 
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs) 
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers) 
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products) 
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    //richiamo begin per poter preparare i pin dei led
    strip.begin();
    
    //setto la luminosità dei led
    strip.setBrightness(40);

    //show serve a mandare i dati settati alla striscia
    strip.show();
}

void loop() {
  
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
    
    //aspetto 10 millisecondi 
    delay(10);
}
