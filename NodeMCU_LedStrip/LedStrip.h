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

#ifndef LedStrip_h
#define LedStrip_h


#include "Arduino.h"

class LedStrip
{
  protected:
    const uint8_t _nLeds;
    uint8_t *_leds;
    uint8_t *_ledPins;
    
  public:
    LedStrip(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
    ~LedStrip();
    void setup() const;
    void show() const;
    void all();
    void set(uint8_t i, uint8_t val);
    uint8_t get(uint8_t i) const;
    void reset();
};


#endif
