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

#ifndef BlinkLed_h
#define BlinkLed_h

#include "Arduino.h"

class BlinkLed
{
  protected:
    unsigned int _ledPin;
    unsigned int _delay;
    unsigned long _nextFlicker;
    bool _state;
    
  public:
    BlinkLed(unsigned int ledPin, unsigned int delay);
    void setup() const;
    void update();
};

#endif
