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

#include "LedStrip.h"

/*
   Construtor
*/
LedStrip::LedStrip(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) :
 _nLeds(4),
 _leds((uint8_t*)malloc(_nLeds)),
 _ledPins((uint8_t*)malloc(_nLeds))
{
  _ledPins[0] = pin1;
  _ledPins[1] = pin2;
  _ledPins[2] = pin3;
  _ledPins[3] = pin4;
}

LedStrip::~LedStrip() {
  free(_leds);
  free(_ledPins);
}

/*
   Setup transmission pins
*/
void LedStrip::setup() const {

  for (int i = 0; i < _nLeds; i++) {
    pinMode(_ledPins[i], OUTPUT);
  }
}

/*
   Turns off all leds
*/
void LedStrip::reset() {
  for (int i = 0; i < _nLeds; i++) _leds[i] = LOW;
}

/*
 * Turns all leds on
 */
void LedStrip::all() {
  for (int i = 0; i < _nLeds; i++) _leds[i] = HIGH;
}

/*
   Sets value of the i-th led
*/
void LedStrip::show() const {
  for (int i = 0; i < _nLeds; i++) digitalWrite(_ledPins[i], _leds[i]);
}

/*
   Sets value of the i-th led
*/
void LedStrip::set(uint8_t i, uint8_t val) {
  _leds[i] = val;
}

/*
   Gets value of the i-th led
*/
uint8_t LedStrip::get(uint8_t i) const {
  return _leds[i];
}

