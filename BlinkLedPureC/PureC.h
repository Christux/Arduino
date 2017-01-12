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

#ifndef PureC_h
#define PureC_h

/*
 * Translation table for arduino UNO pins to dirs, ports and bits
 */
#define DIR_PIN_8 DDRB
#define DIR_PIN_9 DDRB
#define DIR_PIN_10 DDRB
#define DIR_PIN_11 DDRB
#define DIR_PIN_12 DDRB
#define DIR_PIN_13 DDRB

#define OUT_PIN_8 PORTB
#define OUT_PIN_9 PORTB
#define OUT_PIN_10 PORTB
#define OUT_PIN_11 PORTB
#define OUT_PIN_12 PORTB
#define OUT_PIN_13 PORTB

#define IN_PIN_8 PINB
#define IN_PIN_9 PINB
#define IN_PIN_10 PINB
#define IN_PIN_11 PINB
#define IN_PIN_12 PINB
#define IN_PIN_13 PINB

#define BIT_PIN_8 (1<<0)
#define BIT_PIN_9 (1<<1)
#define BIT_PIN_10 (1<<2)
#define BIT_PIN_11 (1<<3)
#define BIT_PIN_12 (1<<4)
#define BIT_PIN_13 (1<<5)


/*
 * Write functions on pins
 */
#define JOIN(x,y) x##y
#define PIN_TO_DIR(x) JOIN(DIR_PIN_,x)
#define PIN_TO_OUT(x) JOIN(OUT_PIN_, x)
#define PIN_TO_IN(x) JOIN(IN_PIN_, x)
#define PIN_TO_BIT(x) JOIN(BIT_PIN_, x)

#define DIGIWRITE_H(prt, pn) prt |= pn
#define DIGIWRITE_L(prt, pn) prt &= ~pn
#define DIGIWRITE_T(prt, pn) prt ^= pn
#define DIGIREAD(prt, pn) prt & pn

#define SET_MODE_OUTPUT(pin) DIGIWRITE_H( PIN_TO_DIR(pin), PIN_TO_BIT(pin) )
#define SET_MODE_INPUT(pin) DIGIWRITE_L( PIN_TO_DIR(pin), PIN_TO_BIT(pin) );
#define SET_MODE_INPUT_PULLUP(pin) DIGIWRITE_L( PIN_TO_DIR(pin), PIN_TO_BIT(pin) ); WRITE_PIN_ON(pin)

#define WRITE_HIGH(pin) DIGIWRITE_H( PIN_TO_OUT(pin), PIN_TO_BIT(pin) )
#define WRITE_LOW(pin) DIGIWRITE_L( PIN_TO_OUT(pin), PIN_TO_BIT(pin) )
#define WRITE_TOOGLE(pin) DIGIWRITE_T( PIN_TO_OUT(pin), PIN_TO_BIT(pin) )

#define READ_PIN(pin) DIGIREAD( PIN_TO_IN(pin), PIN_TO_BIT(pin) )

#endif
