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

#include <Arduino.h>
#include <PgmSpace.h>

PROGMEM const char FAVICON[] = {
  0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x10, 0x10, 0x00, 0x01, 0x00,
  0x04, 0x00, 0x28, 0x01, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00,
  0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
  0x11, 0x10, 0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x01, 0x11,
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
  0x00, 0x11, 0x11, 0x00, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00, 0x00, 0x01,
  0x11, 0x11, 0x11, 0x00, 0x11, 0x00, 0x00, 0x11, 0x00, 0x11, 0x11, 0x00,
  0x01, 0x11, 0x11, 0x10, 0x00, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00,
  0x11, 0x11, 0x00, 0x01, 0x10, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00,
  0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x10, 0x00, 0x00, 0x11, 0x11, 0x00,
  0x00, 0x01, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x11, 0x11,
  0x10, 0x00, 0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
  0x11, 0x11, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfe, 0x7f,
  0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xf3, 0xcf,
  0x00, 0x00, 0xf8, 0x1f, 0x00, 0x00, 0xcc, 0x33, 0x00, 0x00, 0xc7, 0xe3,
  0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x0f, 0xf0,
  0x00, 0x00, 0x83, 0xc1, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xf8, 0x1f,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00
};
