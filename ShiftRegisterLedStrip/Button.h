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

#ifndef Button_h
#define Button_h

#include "Arduino.h"

/*
 * Defines pointer to function type
 */
typedef void (*buttonActionFunction) ();

class Button
{  
  protected:
    unsigned int _buttonPin;
    buttonActionFunction _callbackFunction;
    int _buttonState;
    int _lastButtonState;
    
  public:
    Button(unsigned int ledPin, buttonActionFunction callbackFunction);
    void setup() const;
    void handle();
};

#endif
