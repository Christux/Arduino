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

#include "Animator.h"

Animator::Animator()
{}

void Animator::add(Animation *animation)
{
  _animations[_nAnim++]=animation;
}

uint8_t Animator::getAnimNumber() const
{
  return _nAnim;
}

void Animator::nextAnimation()
{
  _currentAnim = _currentAnim < _nAnim - 1 ? _currentAnim + 1 : 0;
  _animations[_currentAnim]->reset();
}

void Animator::handle() const
{
  _animations[_currentAnim]->update();
}

void Animator::play(uint8_t id)
{
  _currentAnim = id;
  _animations[_currentAnim]->reset();
}


