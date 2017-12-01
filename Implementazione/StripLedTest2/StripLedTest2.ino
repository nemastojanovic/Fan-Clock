//librerie utili per poter comandare il led
#include <Adafruit_GFX.h> 
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

//pin da cui comando i led 
#define PIN 6

//led serve a selezionare un singolo led alla volta
int led = 0;

//dir è la direzione in cui andrà il accensione e lo spegnimento dei led
bool dir = true;

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
    strip.setBrightness(255);

    //show serve a mandare i dati settati alla striscia
    strip.show();
}

void loop() {
    //quando arrivo ai limiti inverto direzione
    if(led == strip.numPixels()-1){
      dir = false;
    }
    else if(led == 0){
      dir = true;
    }

    //se la dir è true passo al led dopo se è false passo al prima
    if(dir){
      led++;
    }
    else{
      led--;
    }

    //setto il colore dei led con colori diversi
    if(led%2 == 0){
      strip.setPixelColor(led, 255, 0, 0);
    }
    else if(led%3 == 0){
      strip.setPixelColor(led, 0, 255, 0);    
    }
    else{
      strip.setPixelColor(led, 0, 0, 255); 
    }
    
    //applico i dati alla striscia
    strip.show();

    //spengo il led in modo che nel prossimo giro quando accendo il prossimo led questo si spegnerà
    strip.setPixelColor(led, 0, 0, 0);

    //aspetto 10 millisecondi
    delay(10);
}
