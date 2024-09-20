#include <FastLED.h>
#include "frames.h"
#include <LEDMatrix.h>

// Change the next 6 defines to match your matrix type and size

#define LED_PIN        53
#define COLOR_ORDER    RGB
#define CHIPSET        WS2812B

#define MATRIX_WIDTH   32  // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_HEIGHT  18  // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX  // See top of LEDMatrix.h for matrix wiring types

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

uint8_t angle = 0;

void Draw(/*const CRGB matrix[MATRIX_WIDTH][MATRIX_HEIGHT]*/) {

  for ( int x = 0; x < MATRIX_WIDTH; ++x ) {
    for ( int y = 0; y < MATRIX_HEIGHT; ++y ) {
      leds(x, y) = BadApple[x][y];
    }
  }
  FastLED.show();
  delay(100);
}

void play() {

  uint32_t value,aux;

  for( int n = 0; n < NFRAMES;++n ){
    for( int y = 0; y < MATRIX_HEIGHT; ++y ) {
      
      value = BadApple[n][y]; 

      for( int x = 0; x < MATRIX_WIDTH ; ++x ) {
        aux = 1;
        aux = aux << x;
        aux = aux & value;

        if( aux ){
          leds(x,y) = CRGB( 255,255,255 ) ;

        }else{
          leds(x,y) = 0;
        
        }
      }
    }
    
    FastLED.show();
    delay(200);
  }
}


void setup()
{

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], 576);
  FastLED.addLeds<CHIPSET, LED_PIN, GRB>(leds[0], 13);
  
  FastLED.setBrightness(127);
  FastLED.clear(true);
  delay(500);
}

void loop() {

  play();
}
