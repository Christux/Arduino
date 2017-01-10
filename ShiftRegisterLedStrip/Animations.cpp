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
 
#include "Animations.h"

/*
 * Abstract class for animation classes
 */
AAnimation::AAnimation(uint8_t nLeds, LedStrip& ledstrip, unsigned int numStep) :
  _N(nLeds),
  _ledstrip(ledstrip),
  _nextFlicker(0),
  _step(0),
  _numStep(numStep)
{}

void AAnimation::reset() {
  _step = 0;
  _ledstrip.reset();
}

void AAnimation::update() {
  unsigned long curr_time = millis();
  if (curr_time >= _nextFlicker) {
    run();
    _step = _step < _numStep - 1 ? _step + 1 : 0;
    _nextFlicker = curr_time + _delay;
  }
}

/*
 * Run methods for all animations
 */
void Right::run() {
  int i = _step;
  _ledstrip.set(i, 1);
  _ledstrip.show();
  _ledstrip.set(i, 0);
}

void Left::run() {
  int i = _step;
  _ledstrip.set(_N - i - 1, 1);
  _ledstrip.show();
  _ledstrip.set(_N - i - 1, 0);
}

void Center::run() {
  int i = _step;
  _ledstrip.set(i, 1);
  _ledstrip.set(_N - i - 1, 1);
  _ledstrip.show();
  _ledstrip.set(i, 0);
  _ledstrip.set(_N - i - 1, 0);
}

void Bounce::run() {

  if (_step < _N) {
    int i = _step;
    _ledstrip.set(i, 1);
    _ledstrip.show();
    _ledstrip.set(i, 0);
  }

  if (_step >= _N) {
    int i = _step - _N;
    _ledstrip.set(_N - i - 1, 1);
    _ledstrip.show();
    _ledstrip.set(_N - i - 1, 0);
  }
}

void KnightRider::run() {

  if (_step < _N) {
    int i = _step;
    _ledstrip.set(i, 1);
    _ledstrip.show();
  }

  if (_step >= _N && _step < 2 * _N) {
    int i = _step - _N;
    _ledstrip.set(i, 0);
    _ledstrip.show();
  }

  if (_step >= 2 * _N && _step < 3 * _N) {
    int i = _step - 2 * _N;
    _ledstrip.set(_N - i - 1, 1);
    _ledstrip.show();
  }

  if (_step >= 3 * _N && _step < 4 * _N) {
    int i = _step - 3 * _N;
    _ledstrip.set(_N - i - 1, 0);
    _ledstrip.show();
  }
}

void Random::run() {

  for (int i = 0; i < _N; i++) {
    _ledstrip.set(i, random(2));
  }
  _ledstrip.show();
}
