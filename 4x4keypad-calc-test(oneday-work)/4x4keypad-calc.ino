#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_Keypad.h"
#include "U8glib.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int num1 = 0;
int num2 = 0;
int action = 0;
bool result = false;
int Number = 0;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '='},
  {'*', '0', '/', '^'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
 // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //isplay.clearDisplay();
  //display.display();
  customKeypad.begin();
}

void loop() {
  customKeypad.tick();

  while (customKeypad.available()) {
    keypadEvent e = customKeypad.read();
    char key = (char)e.bit.KEY;

    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      Serial.print(key);
      Serial.println(" pressed");

      if (key >= '0' && key <= '9') {
        if (num1 == 0)
          num1 = key - '0';
        else
          num1 = (num1 * 10) + (key - '0'); //Pressed twice
      }
     

      
      if (key == '+') {
        action = '+';
        num2 = num1;
        num1 = 0;
      }
      else if (key == '-') {
        action = '-';
        num2 = num1;
        num1 = 0;
      }
      else if (key == '*') {
        action = '*';
        num2 = num1;
        num1 = 0;
      }
      else if (key == '/') {
        action = '/';
        num2 = num1;
        num1 = 0;
      }
      else if (key == '=') {
        result = true;
      }
    }
    else if (e.bit.EVENT == KEY_JUST_RELEASED) {
      Serial.print(key);
      Serial.println(" released");
    }
  }

  if (num1 != 0 && num2 != 0 && result == true) {
    if (action == '+')
      Number = num1 + num2;
    else if (action == '-')
      Number = num1 - num2;
    else if (action == '*')
      Number = num1 * num2;
    else if (action == '/')
      Number = num1 / num2;

    else if (action == '^')
      Number = num1 ^ num2;
    else if (action == 'C')
      Number = num1 = num2;

      do {
      draw();
    } while (oled.nextPage());

   
    num1 = 0;
    num2 = 0;
    action = 0;
    result = false;
   
  }

  delay(10);
}


void draw() {
  oled.setFont(u8g_font_helvB10);
  // Print strings
  oled.drawStr(0, 10, "num1");
  oled.drawStr(0, 20, "action");
  oled.drawStr(0, 30, "num2 ;)");

    if (result == true) {
     oled.drawStr(1, 40, String(result).c_str()) ;
   }
}
 
