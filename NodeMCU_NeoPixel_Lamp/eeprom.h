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
#include <EEPROM.h>

/*
 * Save data in eeprom
 * byte 0: mode
 * byte 1: r
 * byte 2: g
 * byte 3: b
 */

struct Config {

  void saveColor(RgbColor col) {
    EEPROM.begin(4);
    EEPROM.write(1, col.R);
    EEPROM.write(2, col.G);
    EEPROM.write(3, col.B);
    EEPROM.commit();
    EEPROM.end();
  }

  void saveAnim(int anim)
  {
    EEPROM.begin(4);
    EEPROM.write(0, anim);
    EEPROM.commit();
    EEPROM.end();
  }

  int readAnim() {
    EEPROM.begin(4);
    int anim = EEPROM.read(0);
    EEPROM.end();
    return anim;
  }

  RgbColor readColor() {
    EEPROM.begin(4);
    RgbColor color(EEPROM.read(1),
                    EEPROM.read(2),
                    EEPROM.read(3));
    EEPROM.end();
    return color;
  }
  
};

