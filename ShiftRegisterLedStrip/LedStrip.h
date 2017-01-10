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

#ifndef LedStrip_h
#define LedStrip_h

#include "Arduino.h"

class LedStrip
{
  protected:
    uint8_t _N;
    uint8_t *_T;
    uint8_t _clockPin;
    uint8_t _latchPin;
    uint8_t _dataPin;
    const uint8_t CLOCK_TEMP = 50; // u-seconds
    
  public:
    LedStrip(uint8_t nLeds, uint8_t clockPin, uint8_t latchPin, uint8_t dataPin);
    ~LedStrip();
    void setup() const;
    void show() const;
    void set(uint8_t i, uint8_t val);
    uint8_t get(uint8_t i) const;
    void reset();
    
  private:
    inline void putch() const;
    inline void clock() const;
    inline void latch() const;
};

#endif
