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

#include "Button.h"

/*
 * Constructor
 */
Button::Button(unsigned int buttonPin, buttonActionFunction callbackFunction) :
  _buttonPin(buttonPin),
  _callbackFunction(callbackFunction),
  _buttonState(HIGH),
  _lastButtonState(HIGH)
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

  _buttonState = digitalRead(_buttonPin);
  if (_buttonState == LOW) {
    if (_buttonState != _lastButtonState) {
      _callbackFunction();
    }
  }
  _lastButtonState = _buttonState;
}

