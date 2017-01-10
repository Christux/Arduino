/*
    Copyright Christux 2017
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Arduino.h"
#include "LedStrip.h"
#include "Animations.h"
#include "BlinkLed.h"

#define BUTTON_PIN 7
#define LATCH_PIN 9
#define CLOCK_PIN 8
#define DATA_PIN 10
#define N_LEDS 8

// Init ledstrip
LedStrip ledstrip(N_LEDS, CLOCK_PIN, LATCH_PIN, DATA_PIN);

// Init animations in a table
const int nAnim = 6;
Animation * animations[nAnim] = {
  new Right(N_LEDS, ledstrip),
  new Left(N_LEDS, ledstrip),
  new Bounce(N_LEDS, ledstrip),
  new Center(N_LEDS, ledstrip),
  new KnightRider(N_LEDS, ledstrip),
  new Random(N_LEDS, ledstrip)
};

// Init button
int currentAnim = 4;
int buttonState = HIGH;         // current state of the button
int lastButtonState = HIGH;

// Init blinking led
BlinkLed bl = BlinkLed(LED_BUILTIN,1000);

/*
 * Setup
 */
void setup() {
  ledstrip.setup();
  bl.setup();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

/*
 * Main loop
 */
void loop() {

  /* 
   * Blinks built-in led, shows if program is alive
   */
  bl.update();

  /*
   * Listen on button push and go to next animation
   */
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW) {
    if (buttonState != lastButtonState) {
      currentAnim = currentAnim < nAnim - 1 ? currentAnim + 1 : 0;
      animations[currentAnim]->reset();
    }
  }
  lastButtonState = buttonState;

  /*
   * Listen on serial communication
   */
  if (Serial.available() > 0) {
    char c = Serial.read() - 49;
    if (c >= 0 && c < nAnim) {
      currentAnim = c;
      animations[currentAnim]->reset();
      Serial.println(currentAnim+1,DEC);
    }
    else {
      Serial.print("Error: enter a number between 1 and ");
      Serial.print(nAnim,DEC);
      Serial.print("\n");
    }
  }

  /*
   * Play animation
   */
  animations[currentAnim]->update();

  delay(20);
}


