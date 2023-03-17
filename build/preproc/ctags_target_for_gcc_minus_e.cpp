# 1 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
# 2 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 2
# 3 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 2
# 4 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 2
# 5 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 2




// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...


Adafruit_SSD1306 display(128 /* OLED display width, in pixels*/, 64 /* OLED display height, in pixels*/, &Wire, -1 /* Reset pin # (or -1 if sharing Arduino reset pin)*/);





static const unsigned char 
# 22 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                          __attribute__((__progmem__)) 
# 22 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                                  logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(0x02 /*|< Gen. display voltage from 3.3V*/, 0x3C /*|< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32*/)) {
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 45 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 45 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                  "SSD1306 allocation failed"
# 45 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                  ); &__c[0];}))
# 45 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                  )));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, 1 /*|< Draw 'on' pixels*/);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  testdrawline(); // Draw many lines

  testdrawrect(); // Draw rectangles (outlines)

  testfillrect(); // Draw rectangles (filled)

  testdrawcircle(); // Draw circles (outlines)

  testfillcircle(); // Draw circles (filled)

  testdrawroundrect(); // Draw rounded rectangles (outlines)

  testfillroundrect(); // Draw rounded rectangles (filled)

  testdrawtriangle(); // Draw triangles (outlines)

  testfilltriangle(); // Draw triangles (filled)

  testdrawchar(); // Draw characters of the default font

  testdrawstyles(); // Draw 'stylized' characters

  testscrolltext(); // Draw scrolling text

  testdrawbitmap(); // Draw a small bitmap image

  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  testanimate(logo_bmp, 16, 16); // Animate bitmaps
}

void loop() {
}

void testdrawline() {
  int16_t i;

  display.clearDisplay(); // Clear display buffer

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, 1 /*|< Draw 'on' pixels*/);
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for(i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }

  delay(2000); // Pause for 2 seconds
}

void testdrawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, 1 /*|< Draw 'on' pixels*/);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testfillrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=3) {
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, 2 /*|< Invert pixels*/);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testdrawcircle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<((display.width())>(display.height())?(display.width()):(display.height()))/2; i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillcircle(void) {
  display.clearDisplay();

  for(int16_t i=((display.width())>(display.height())?(display.width()):(display.height()))/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    display.fillCircle(display.width() / 2, display.height() / 2, i, 2 /*|< Invert pixels*/);
    display.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(2000);
}

void testdrawroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, 2 /*|< Invert pixels*/);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawtriangle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<((display.width())>(display.height())?(display.width()):(display.height()))/2; i+=5) {
    display.drawTriangle(
      display.width()/2 , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, 1 /*|< Draw 'on' pixels*/);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfilltriangle(void) {
  display.clearDisplay();

  for(int16_t i=((display.width())>(display.height())?(display.width()):(display.height()))/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    display.fillTriangle(
      display.width()/2 , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, 2 /*|< Invert pixels*/);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1); // Normal 1:1 pixel scale
  display.setTextColor(1 /*|< Draw 'on' pixels*/); // Draw white text
  display.setCursor(0, 0); // Start at top-left corner
  display.cp437(true); // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else display.write(i);
  }

  display.display();
  delay(2000);
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1); // Normal 1:1 pixel scale
  display.setTextColor(1 /*|< Draw 'on' pixels*/); // Draw white text
  display.setCursor(0,0); // Start at top-left corner
  display.println((reinterpret_cast<const __FlashStringHelper *>(
# 301 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 301 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                 "Hello, world!"
# 301 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                 ); &__c[0];}))
# 301 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                 )));

  display.setTextColor(0 /*|< Draw 'off' pixels*/, 1 /*|< Draw 'on' pixels*/); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(1 /*|< Draw 'on' pixels*/);
  display.print((reinterpret_cast<const __FlashStringHelper *>(
# 308 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 308 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
               "0x"
# 308 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
               ); &__c[0];}))
# 308 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
               ))); display.println(0xDEADBEEF, 16);

  display.display();
  delay(2000);
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(1 /*|< Draw 'on' pixels*/);
  display.setCursor(10, 0);
  display.println((reinterpret_cast<const __FlashStringHelper *>(
# 320 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 320 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                 "scroll"
# 320 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                 ); &__c[0];}))
# 320 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                 )));
  display.display(); // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width() - 16 ) / 2,
    (display.height() - 16) / 2,
    logo_bmp, 16, 16, 1);
  display.display();
  delay(1000);
}





void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[10 /* Number of snowflakes in the animation example*/][3];

  // Initialize 'snowflake' positions
  for(f=0; f< 10 /* Number of snowflakes in the animation example*/; f++) {
    icons[f][0 /* Indexes into the 'icons' array in function below*/] = random(1 - 16, display.width());
    icons[f][1] = -16;
    icons[f][2] = random(1, 6);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 364 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 364 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                "x: "
# 364 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                ); &__c[0];}))
# 364 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                )));
    Serial.print(icons[f][0 /* Indexes into the 'icons' array in function below*/], 10);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 366 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 366 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                " y: "
# 366 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                ); &__c[0];}))
# 366 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                )));
    Serial.print(icons[f][1], 10);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 368 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 368 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                " dy: "
# 368 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino" 3
                ); &__c[0];}))
# 368 "c:\\Users\\taine\\Documents\\Code\\13ELE-BattleBot\\test.ino"
                )));
    Serial.println(icons[f][2], 10);
  }

  for(;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< 10 /* Number of snowflakes in the animation example*/; f++) {
      display.drawBitmap(icons[f][0 /* Indexes into the 'icons' array in function below*/], icons[f][1], bitmap, w, h, 1 /*|< Draw 'on' pixels*/);
    }

    display.display(); // Show the display buffer on the screen
    delay(200); // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< 10 /* Number of snowflakes in the animation example*/; f++) {
      icons[f][1] += icons[f][2];
      // If snowflake is off the bottom of the screen...
      if (icons[f][1] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][0 /* Indexes into the 'icons' array in function below*/] = random(1 - 16, display.width());
        icons[f][1] = -16;
        icons[f][2] = random(1, 6);
      }
    }
  }
}
