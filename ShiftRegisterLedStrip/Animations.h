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

#ifndef Animations_h
#define Animations_h

#include "Arduino.h"
#include "LedStrip.h"

/*
 * Interface for animation classes
 */
class Animation
{
  public:
    virtual ~Animation() {};
    virtual void reset() = 0;
    virtual void update() = 0;
};

/*
 * Abstract class for animation classes
 */
class AAnimation : public Animation
{
  protected:
    const uint8_t _N;
    LedStrip& _ledstrip;
    const unsigned int _delay = 100;
    unsigned long _nextFlicker;
    unsigned int _step;
    const unsigned int _numStep;
    virtual void run() = 0;

  public:
    AAnimation(uint8_t nLeds, LedStrip& ledstrip, unsigned int numStep);
    virtual ~AAnimation() {};
    void update();
    void reset();
};

/*
 * Animation classes
 */
class Right : public AAnimation
{
  public:
    Right(uint8_t nLeds, LedStrip& ledstrip): AAnimation(nLeds, ledstrip, nLeds) {};
    ~Right() {};
  protected:
    void run();
};

class Left : public AAnimation
{
  public:
    Left(uint8_t nLeds, LedStrip& ledstrip): AAnimation(nLeds, ledstrip, nLeds) {};
    ~Left() {};
  protected:
    void run();
};

class Center: public AAnimation
{
  public:
    Center(uint8_t nLeds, LedStrip& ledstrip): AAnimation(nLeds, ledstrip, nLeds/2) {};
    ~Center() {};
  protected:
    void run();
};

class Bounce : public AAnimation
{
  public:
    Bounce(uint8_t nLeds, LedStrip& ledstrip): AAnimation(nLeds, ledstrip, 2 * nLeds) {};
    ~Bounce() {};
  protected:
    void run();
};

class KnightRider : public AAnimation
{
  public:
    KnightRider(uint8_t nLeds, LedStrip& ledstrip): AAnimation(nLeds, ledstrip, 4 * nLeds) {};
    ~KnightRider() {};
  protected:
    void run();
};

class Random : public AAnimation
{
  public:
    Random(uint8_t nLeds, LedStrip& ledstrip): AAnimation(nLeds, ledstrip, 1) {};
    ~Random() {};
  protected:
    void run();
};

#endif
