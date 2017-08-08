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

#ifndef Animator_h
#define Animator_h

#include "Animations.h"

/*
 * Interface for animation classes
 */
class Animator
{
  protected:
    uint8_t _nAnim = 0;
    uint8_t _currentAnim = 0;
    Animation * _animations[20];
  
  public:
    Animator();
    void add(Animation*);
    uint8_t getAnimNumber() const;
    void handle() const;
    void nextAnimation();
    void play(uint8_t id);
};

#endif
