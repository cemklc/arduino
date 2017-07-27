#include "FastLED.h"

#define NUM_LEDS 15  // Toplam LED sayısı
#define DATA_PIN 11 // LEDlerin data inputunun bağlı olduğu arduino pini
#define CLOCK_PIN 12  // LEDlerin clock inputunun bağlı olduğu arduino pini
#define dtime 10 // Yanıp sönme hızı
#define ftime 2 // Yanıp sönme hızı
#define fftime 2 // Yanıp sönme hızı
#define sdtime 80 // Kayma hızı
#define ttime 2 // Sinyal hızı
#define LEFT_HEADER_START 2 // Sol header ledinin başladığı numara
#define LEFT_HEADER_END 4 // Sol header ledinin bittiği numara
#define RIGHT_HEADER_START 10
#define RIGHT_HEADER_END 12
#define HEADER_COUNT 3 // Tek bir taraftaki header led sayısı
#define TOTAL_HEADERS 6 // Toplam header led sayısı

// Define the array of leds
CRGB leds[NUM_LEDS];

uint8_t coll = 0;
uint8_t color = 0;
uint8_t patt = 0;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {

  if (Serial.available() > 0) {
    coll = Serial.parseInt();
    patt = Serial.parseInt();
  }
  switch (coll) {
    case 1:
      color = 0;    //BLUE
      break;
    case 2:
      color = 160;   //RED
      break;
    case 3:
      color = 100;  //GREEN
      break;
    case 4:
      color = 80;  //TURKUAZ
      break;
    case 5:
      color = 90;  //YOSUN YESILI
      break;
    case 6:
      color = 140;  //SARI
      break;
    case 7:
      color = 151;  //TURUNCU
      break;
    case 8:
      color = 185;  //PEMBE
      break;
    case 9:
      color = 120;  //YESIL-SARI
      break;
    case 10:
      color = 230;  //EFLATUN
      break;
    case 11:
      color = 63;  //ACIK MAVI
      break;
    default:
      idle();
      break;
  }

  switch (patt) {
    case 1:       //FADE
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        fade();
      }
      break;
    case 2:       //SLIDE
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        slide();
      }
      break;
    case 3:       //LEFT SIGNAL
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        turnleft();
      }
      break;
    case 4:       //RIGHT SIGNAL
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        turnright();
      }
      break;
    case 5:       //FULL FADE
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        fullfade();
      }
      break;
    case 6:       //BACK SLIDE
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        backslide();
      }
      break;
    case 7:       //SOLID
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        solid();
      }
      break;
    default:
      clearleds();
      idle();
      while (1) {
        if (Serial.available() > 0)
          break;
      }
      break;
  }
}

//FADE
void fade() {
  for (uint8_t val = 0; val < 255; val++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CHSV(color, 255 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(ftime);
  }
  for (uint8_t val = 255; val > 0; val--) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CHSV(color, 255 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(ftime);
  }
}

//SLIDE
void slide() {
  uint8_t cc = 0;
  while (cc <= (NUM_LEDS ) / 2 ) {
    if (NUM_LEDS / 2 - cc <= LEFT_HEADER_END && NUM_LEDS / 2 - cc >= LEFT_HEADER_START ) {
      cc++;
      continue;
    }
    leds[NUM_LEDS / 2 - cc] = CHSV(color, 255 , 200 );
    leds[NUM_LEDS / 2 + cc] = CHSV(color, 255 , 200 );
    FastLED.show();
    delay(sdtime);
    leds[NUM_LEDS / 2 - cc] = CHSV(color, 255 , 0 );
    leds[NUM_LEDS / 2 + cc] = CHSV(color, 255 , 0 );

    cc++;
  }
}

//BACK-SLIDE
void backslide() {
  uint8_t cc = 0;
  while (cc <= (NUM_LEDS ) / 2 ) {
    if (cc <= LEFT_HEADER_END && cc >= LEFT_HEADER_START ) {
      cc++;
      continue;
    }
    leds[cc] = CHSV(color, 255 , 200 );
    leds[NUM_LEDS - cc - 1] = CHSV(color, 255 , 200 );
    FastLED.show();
    delay(sdtime);
    leds[cc] = CHSV(color, 255 , 0 );
    leds[NUM_LEDS - cc - 1] = CHSV(color, 255 , 0 );

    cc++;
  }
}

//SETS HEARDER LEDS WHITE
void headlight() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if (i >= LEFT_HEADER_START && i <= LEFT_HEADER_END || i >= RIGHT_HEADER_START && i <= RIGHT_HEADER_END ) {
      leds[i] = CRGB(100, 100 , 100 );
    }
  }
  FastLED.show();
}

//IDLE
void idle() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if (i >= LEFT_HEADER_START + 1 && i <= LEFT_HEADER_END || i >= RIGHT_HEADER_START + 1 && i <= RIGHT_HEADER_END ) {
      leds[i] = CRGB(100, 100 , 100 );
    }
  }
  FastLED.show();
}

//CLEAR ALL LEDS
void clearleds() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0 , 0 );
  }
  FastLED.show();
  delay(dtime);
}

// LEFT SIGNAL - HALF FADE
void turnleft() {
  for (uint8_t val = 0; val < 255; val++) {
    for (uint8_t i = 0; i < NUM_LEDS / 2 + 1; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      leds[i] = CHSV(color, 255 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(ttime);
  }
  for (uint8_t val = 255; val > 0; val--) {
    for (uint8_t i = 0; i < NUM_LEDS / 2 + 1; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      leds[i] = CHSV(color, 255 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(ttime);
  }
}

// RIGHT SIGNAL - HALF FADE
void turnright() {
  for (uint8_t val = 0; val < 255; val++) {
    for (uint8_t i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
      if (i == RIGHT_HEADER_START )
        i = i + HEADER_COUNT;
      leds[i] = CHSV(color, 255 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(ttime);
  }
  for (uint8_t val = 255; val > 0; val--) {
    for (uint8_t i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
      if (i == RIGHT_HEADER_START )
        i = i + HEADER_COUNT;
      leds[i] = CHSV(color, 255 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(ttime);
  }
}

//FULL FADE
void fullfade() {
  for (uint8_t val = 0; val < 255; val++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(color, 255 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(fftime);
  }
  for (uint8_t val = 255; val > 0; val--) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(color, 255 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(fftime);
  }
}

//SABIT
void solid() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(color, 255 , 200 );
  }
  FastLED.show();
  delay(dtime);
}
