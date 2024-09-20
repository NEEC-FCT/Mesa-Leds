#include <FastLED.h>

#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontP16x16.h>


#define LED_PIN        53
#define COLOR_ORDER    RGB
#define CHIPSET        WS2812B

#define MATRIX_WIDTH   -32
#define MATRIX_HEIGHT  18
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

cLEDText ScrollingMsg;

const unsigned char TxtDemo[] = { "     Bem Vindos Caloiros"};


void logo_NEEC(){
  //Logo feito com quadrados e espelhado na horizontal
  leds.DrawFilledRectangle(0, 0, leds.Width() ,leds.Height(), CRGB(255, 255, 140));
  leds.DrawFilledRectangle(-1 + leds.Width() - 1, 4, -1 + leds.Width() - 2 , 14  , CRGB(10, 255, 26));
  leds.DrawFilledRectangle(-1 + leds.Width() - 2, 3, -1 + leds.Width() - 4 , 4   , CRGB(10, 255, 26));
  leds.DrawFilledRectangle(-1 + leds.Width() - 4, 4, -1 + leds.Width() - 5 , 13  , CRGB(10, 255, 26));
  leds.DrawFilledRectangle(-1 + leds.Width() - 5, 13,-1 + leds.Width() - 7 , 14  , CRGB(10, 255, 26));
  leds.DrawFilledRectangle(-1 + leds.Width() - 7, 3, -1 + leds.Width() - 8 , 13  , CRGB(10, 255, 26));
  
  leds.DrawFilledRectangle(-1 + leds.Width() - 11, 3,-1 + leds.Width() - 15 , 4  , CRGB(0, 9, 255));
  leds.DrawFilledRectangle(-1 + leds.Width() - 10, 5,-1 + leds.Width() - 11 , 7  , CRGB(0, 9, 255));
  leds.DrawFilledRectangle(-1 + leds.Width() - 11, 8,-1 + leds.Width() - 15 , 9  , CRGB(0, 9, 255));
  leds.DrawFilledRectangle(-1 + leds.Width() - 10, 10,-1 + leds.Width() -  11 , 12  , CRGB(0, 9, 255));
  leds.DrawFilledRectangle(-1 + leds.Width() - 11, 13,-1 + leds.Width() -  15 , 14  , CRGB(0, 9, 255));

  leds.DrawFilledRectangle(-1 + leds.Width() - 18, 3,-1 + leds.Width() - 22 , 4  , CRGB(0, 9, 255));
  leds.DrawFilledRectangle(-1 + leds.Width() - 17, 5,-1 + leds.Width() - 18 , 7  , CRGB(0, 9, 255));
  leds.DrawFilledRectangle(-1 + leds.Width() - 18, 8,-1 + leds.Width() - 22 , 9  , CRGB(0, 9, 255));
  leds.DrawFilledRectangle(-1 + leds.Width() - 17, 10,-1 + leds.Width() -  18 , 12  , CRGB(0, 9, 255));
  leds.DrawFilledRectangle(-1 + leds.Width() - 18, 13,-1 + leds.Width() -  22 , 14  , CRGB(0, 9, 255));

  leds.DrawFilledRectangle(-1 + leds.Width() - 25, 3,-1 + leds.Width() - 30 , 4  , CRGB(0, 164, 202));
  leds.DrawFilledRectangle(-1 + leds.Width() - 24, 5,-1 + leds.Width() - 25 , 12  , CRGB(0, 164, 202));
  leds.DrawFilledRectangle(-1 + leds.Width() - 25, 13,-1 + leds.Width() -  30 , 14  , CRGB(0, 164, 202));

  //leds.DrawFilledRectangle(0, 0, 31, 31, CRGB(0, 164, 202));
  FastLED.show();
}

void setup()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.addLeds<CHIPSET, LED_PIN, GRB>(leds[0], 13);

  FastLED.setBrightness(200);
  FastLED.clear(true);
  
  ScrollingMsg.SetFont(FontP16x16Data);
  ScrollingMsg.Init(&leds, leds.Width(), leds.Height(), 0, 2);
  ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xFF, 0xFF, 0xFF);
  ScrollingMsg.SetFrameRate(0.2);
  ScrollingMsg.SetTextDirection(CHAR_DOWN);
  ScrollingMsg.SetScrollDirection(SCROLL_RIGHT);
}

void loop()
{
  if (ScrollingMsg.UpdateText() == -1){
    ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
    logo_NEEC();
    delay(5000);
    FastLED.clear(true);


  }
  else
    FastLED.show();
  delay(10);
  
}