#include "FastLED.h"

#define NUM_LEDS 15  // Toplam LED sayısı
#define DATA_PIN 11 // LEDlerin data inputunun bağlı olduğu arduino pini
#define CLOCK_PIN 12  // LEDlerin clock inputunun bağlı olduğu arduino pini
#define dtime 10 // Yanıp sönme hızı
#define sdtime 80 // Kayma hızı
#define LEFT_HEADER_START 2 // Sol header ledinin başladığı numara
#define LEFT_HEADER_END 4 // Sol header ledinin bittiği numara
#define RIGHT_HEADER_START 10
#define RIGHT_HEADER_END 12
#define HEADER_COUNT 3 // Tek bir taraftaki header led sayısı
#define TOTAL_HEADERS 6 // Toplam header led sayısı

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

//HEADLIGHT

void headlight() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if (i >= LEFT_HEADER_START && i <= LEFT_HEADER_END || i >= RIGHT_HEADER_START && i <= RIGHT_HEADER_END ) {
      leds[i] = CRGB(100, 100 , 100 );
    }
  }
  FastLED.show();
}

//GREEN PULSE

void processing() {
  for (uint8_t val = 0; val < 200; val++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(0, val , 0 );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
  for (uint8_t val = 200; val > 0; val--) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(0, val , 0 );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
}

//GREEN SLIDE

void moving() {
  uint8_t cc = 0;
  while (cc <= (NUM_LEDS ) / 2 ) {
    if (NUM_LEDS / 2 - cc <= LEFT_HEADER_END && NUM_LEDS / 2 - cc >= LEFT_HEADER_START ) {
      cc++;
      continue;
    }
    leds[NUM_LEDS / 2 - cc] = CRGB(0, 100 , 0 );
    leds[NUM_LEDS / 2 + cc] = CRGB(0, 100 , 0 );
    FastLED.show();
    delay(sdtime);
    leds[NUM_LEDS / 2 - cc] = CRGB(0, 0 , 0 );
    leds[NUM_LEDS / 2 + cc] = CRGB(0, 0 , 0 );

    cc++;
  }
}


//YELLOW SLIDE
void approaching() {
  uint8_t cc = 0;
  while (cc <= (NUM_LEDS ) / 2 ) {
    if (NUM_LEDS / 2 - cc <= LEFT_HEADER_END && NUM_LEDS / 2 - cc >= LEFT_HEADER_START ) {
      cc++;
      continue;
    }
    leds[NUM_LEDS / 2 - cc] = CRGB(0, 100 , 100 );
    leds[NUM_LEDS / 2 + cc] = CRGB(0, 100 , 100 );
    FastLED.show();
    delay(sdtime);
    leds[NUM_LEDS / 2 - cc] = CRGB(0, 0 , 0 );
    leds[NUM_LEDS / 2 + cc] = CRGB(0, 0 , 0 );

    cc++;
  }
}


//LOADING - BLUE PULSE

void load() {
  for (uint8_t val = 0; val < 200; val++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(val, 0 , 0 );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
  for (uint8_t val = 200; val > 0; val--) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(val, 0 , 0 );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
}

//ESTOP - RED PULSE

void estop() {
  for (uint8_t val = 0; val < 200; val++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(0, 0 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
  for (uint8_t val = 200; val > 0; val--) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(0, 0 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
}

//CLEAR LEDS

void clearleds() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0 , 0 );
  }
  FastLED.show();
  delay(dtime);
}

//FAULT - ALL RED
void fault() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0 , 200 );
  }
  FastLED.show();
  delay(dtime);
}

// LEFT SIGNAL - HALF YELLOW PULSE
void turnleft() {
  for (uint8_t val = 0; val < 200; val++) {
    for (uint8_t i = 0; i < NUM_LEDS / 2 + 1; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      leds[i] = CRGB(0, val , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
  for (uint8_t val = 200; val > 0; val--) {
    for (uint8_t i = 0; i < NUM_LEDS / 2 + 1; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      leds[i] = CRGB(0, val , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
}
// RIGHT SIGNAL - HALF YELLOW PULSE

void turnright() {
  for (uint8_t val = 0; val < 200; val++) {
    for (uint8_t i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
      if (i == RIGHT_HEADER_START )
        i = i + HEADER_COUNT;
      leds[i] = CRGB(0, val , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
  for (uint8_t val = 200; val > 0; val--) {
    for (uint8_t i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
      if (i == RIGHT_HEADER_START )
        i = i + HEADER_COUNT;
      leds[i] = CRGB(0, val , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
}

// PATH BLOCKED - PURPLE PULSE
void pathblocked() {
  for (uint8_t val = 0; val < 200; val++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(val, 0 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
  for (uint8_t val = 200; val > 0; val--) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(val, 0 , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
}

// MANUEL CONTROL - WHITE PULSE
void manuelcontrol() {
  for (uint8_t val = 0; val < 200; val++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(val, val , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
  for (uint8_t val = 200; val > 0; val--) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (i == LEFT_HEADER_START )
        i = i + HEADER_COUNT;
      if (i == RIGHT_HEADER_START)
        i = i + HEADER_COUNT;
      leds[i] = CRGB(val, val , val );
    }
    if (Serial.available() > 0)
      break;
    FastLED.show();
    delay(dtime / 5);
  }
}

void loop() {
  int inByte = Serial.read();
  switch (inByte) {
    case 'p':
      Serial.print("Processing\n");
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        processing();
      }
      break;

    case 'm':
      Serial.print("Moving\n");
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        moving();
      }
      break;

    case 'a':
      Serial.print("Approaching\n");
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        approaching();
      }
      break;

    case 'l':
      Serial.print("Loading/Unloading\n");
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        load();
      }
      break;

    case 'e':
      Serial.print("Emergency Stop\n");
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        estop();
      }
      break;

    case 'f':
      Serial.print("Fault\n");
      clearleds();
      while (1) {
        if (Serial.available() > 0)
          break;
        fault();
      }
      break;

    case 'r':
      Serial.print("Right Turn\n");
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        turnright();
      }
      break;

    case 't':
      Serial.print("Left Turn\n");
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        turnleft();
      }
      break;

    case 'b':
      Serial.print("Path Blocked\n");
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        pathblocked();
      }
      break;

    case 'c':
      Serial.print("Manuel Control\n");
      clearleds();
      headlight();
      while (1) {
        if (Serial.available() > 0)
          break;
        manuelcontrol();
      }
      break;

    default:
      if (Serial.available() > 0)
        break;
      for (uint8_t i = 0; i < NUM_LEDS; i++) {
        if (i >= LEFT_HEADER_START + 1 && i <= LEFT_HEADER_END || i >= RIGHT_HEADER_START && i <= RIGHT_HEADER_END - 1 ) {
          leds[i] = CRGB(100, 100 , 100 );
        }
        else
          leds[i] = CRGB(0, 0 , 0 );
      }
      FastLED.show();
      break;
  }
}
