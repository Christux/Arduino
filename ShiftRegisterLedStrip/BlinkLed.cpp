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

#include "BlinkLed.h"

/*
 * Constructor
 */
BlinkLed::BlinkLed(unsigned int ledPin, unsigned int delay) :
  _ledPin(ledPin),
  _delay(delay),
  _nextFlicker(0),
  _state(false)
{}

/*
 * Setup led pin
 */
void BlinkLed::setup() const {
  pinMode(_ledPin, OUTPUT);
  digitalWrite(_ledPin,_state);
}

/*
 * Reverses led state
 */
void BlinkLed::update() {

  unsigned long curr_time = millis();

  if (curr_time >= _nextFlicker) {
    _nextFlicker = curr_time + _delay;
    _state=!_state;
    digitalWrite(_ledPin, _state);
  }
}

