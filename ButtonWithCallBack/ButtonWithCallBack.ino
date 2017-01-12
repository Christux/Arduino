/* 
 * Copyright (c) 2017 Christophe Rubeck.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU Lesser General Public License as   
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * Lesser General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Button.h"

#define BUTTON_PIN 7
#define LED_PIN LED_BUILTIN

/*
 * CallBack function
 */
void changeLedState() {
  digitalWrite(LED_PIN,!digitalRead(LED_PIN));
}

/* 
 *  Defines button
 */
Button b = Button(BUTTON_PIN,changeLedState);

/*
 * Setup
 */
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN,HIGH);
  b.setup();
}

/*
 * Main loop
 */
void loop() {
  b.handle();
}
