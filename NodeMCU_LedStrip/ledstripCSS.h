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

#include <PgmSpace.h>

PROGMEM const char CSS[] = R"=====(

/*
 * Led Strip Remote
 *
 * Author : Christux
 * Version : 1.0
 * Date : 20 juil 2017
 */

body{
  width:100%;
  height:auto;
  background-color:Silver;
  margin:0;
  padding:0;
  margin-left:auto; 
  margin-right:auto;
}

.button{
  display:block;
  padding-top:1em;
  padding-bottom:1em;
  margin:1.4em;
  width:60%;
  max-width: 20em;
  line-height:2em;
  text-align:center;
  font-weight:bold;
  color: whiteSmoke;
  margin-left:auto; 
  margin-right:auto;
  border-radius: 0.8em;
  cursor: Pointer;
}

.active {
  background-color:purple;
}

.unactive {
  background-color:slategrey;
}


)=====";
