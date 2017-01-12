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
#include "PureC.h"

#define LedPin LED_BUILTIN

/*
 * Defines some functions
 */
#define SetLedOutput SET_MODE_OUTPUT(LedPin)
#define LedOn WRITE_HIGH(LedPin)
#define LedOff WRITE_LOW(LedPin)
#define LedToogle WRITE_TOOGLE(LedPin)

#define Tdelay 500
#define Wait _delay_ms(Tdelay)

/*
 * Setup
 */
void setup() {
  SetLedOutput;
}

/*
 * Main loop
 */
void loop() {
  
  LedOn;
  Wait;
  LedOff;
  Wait;
  
  LedToogle;
  Wait;
  LedToogle;
  Wait;
}
