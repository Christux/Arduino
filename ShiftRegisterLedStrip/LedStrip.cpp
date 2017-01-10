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

#include "LedStrip.h"

/*
 * Construtor
 */
LedStrip::LedStrip(const uint8_t nLeds, uint8_t clockPin, uint8_t latchPin, uint8_t dataPin) :
  _N(nLeds),
  _T((uint8_t*)malloc(_N)),
  _clockPin(clockPin),
  _latchPin(latchPin),
  _dataPin(dataPin)
{
  reset();
}

LedStrip::~LedStrip() {
  free(_T);
}

/*
 * Setup transmission pins
 */
void LedStrip::setup() const {
  pinMode(_latchPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_dataPin, OUTPUT);
}

/*
 * Turns off all leds
 */
void LedStrip::reset() {
  for (int i = 0; i < _N; i++) _T[i] = 0;
}

/*
 * Sets value of the i-th led
 */
void LedStrip::set(uint8_t i, uint8_t val) {
  _T[i] = val;
}

/*
 * Gets value of the i-th led
 */
uint8_t LedStrip::get(uint8_t i) const {
  return _T[i];
}

/*
 * Commits led states to the physical led strip
 */
void LedStrip::show() const {
  for (int i = 0; i < _N; i++) {
    digitalWrite(_dataPin, _T[_N - i - 1]);
    clock();
  }
  latch();
}

/*
 * Transmission methods, see data sheet of your shiftregister
 */
inline void LedStrip::putch() const {
  delayMicroseconds(CLOCK_TEMP);
}

inline void LedStrip::clock() const {
  digitalWrite(_clockPin, HIGH);
  putch();
  digitalWrite(_clockPin, LOW);
  putch();
}

inline void LedStrip::latch() const {
  digitalWrite(_latchPin, HIGH);
  putch();
  digitalWrite(_latchPin, LOW);
  putch();
}

