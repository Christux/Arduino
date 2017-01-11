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

/*
 * Constructor
 */
Button::Button(unsigned int buttonPin, buttonActionFunction callbackFunction) :
  _buttonPin(buttonPin),
  _callbackFunction(callbackFunction),
  _buttonState(HIGH),
  _lastButtonState(HIGH),
  _pushTime(0)
{}

/*
 * Setup
 */
void Button::setup() const {
  pinMode(_buttonPin, INPUT_PULLUP);
}

/*
 * Listen to button push and call _callbackFunction
 */
void Button::handle() {

  unsigned long currTime = millis();
  _buttonState = digitalRead(_buttonPin);
  
  if (_buttonState == LOW) {
    if (_lastButtonState == HIGH && currTime > _pushTime) {
      _callbackFunction();
    }
    _pushTime = currTime + _pushDelay;
  }
  _lastButtonState = _buttonState;
}

