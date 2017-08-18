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

PROGMEM const char CSS[] = R"=====(

body{
    width:100%;
    height:auto;
    min-height:60em;
    background-color:Silver;
    margin:0;
    padding:0;
    margin-left:auto; 
    margin-right:auto;
}

header{
    position:fixed;
    width: 100%;
    height: 6em;
    margin-bottom: 1em;
    background-color: DimGray;
}

nav{
    display:table;
    width:100%;
    margin-left:auto; 
    margin-right:auto;
    padding-top: 0.6em;
    border-spacing: 0.8em;
}

nav .button{
    width:20%;
    display:table-cell;
    text-align:center;
    vertical-align:middle;
    border-radius: 0.8em;
}

nav .button a {
    display:block;
    width:100%;
    line-height:3.4em;
    font-weight:bold;
    text-decoration: none;
    color: LightCyan ;
}

nav .unactive {
    background-color: grey;
    cursor: Pointer;
}

nav .active, nav .button:hover{
    background-color: darkgrey;
}

#content{
    padding-top:7em;
    padding-bottom:1em;
    margin-left:auto; 
    margin-right:auto;
    text-align:center;
}

#animation .button{
    display:block;
    padding-top:1em;
    padding-bottom:1em;
    margin:1.4em;
    width:60%;
    max-width: 20em;
    line-height:2em;
    text-align:center;
    vertical-align:middle;
    font-weight:bold;
    color: whiteSmoke;
    margin-left:auto; 
    margin-right:auto;
    border-radius: 0.8em;
}

#animation .unactive {
    background-color:slategrey;
    cursor: Pointer;
}

#animation .active, #animation .button:hover{
    background-color:gray ;
}

#brightness, #color{
    display: table;
    width: 95%;
    max-width: 24em;
    margin-top:1em;
    margin-left:auto; 
    margin-right:auto;
    border-spacing: 0.8em;
}

#brightness .divTableBody, #color .divTableBody {
    display: table-row-group;
}

#brightness .divTableRow, #color .divTableRow {
    display: table-row;
}

#brightness .divTableCell, #color .divTableCell {
    display: table-cell;
    width:7em;
    height:7em;
    border-radius: 0.8em;
    vertical-align:middle;
    cursor: Pointer;
}

#info .button{
    display:block;
    padding-top:1em;
    padding-bottom:1em;
    margin:1.4em;
    width:40%;
    max-width: 20em;
    line-height:1.2em;
    text-align:center;
    vertical-align:middle;
    font-weight:bold;
    color: whiteSmoke;
    margin-left:auto; 
    margin-right:auto;
    border-radius: 0.4em;
    background-color:gray;
    cursor: Pointer;
}

#info .info {
    width: 80%;
    text-align:left;
    margin-top: 2em;
    margin-left: auto;
    margin-right: auto;
}

#info .info .key {
    color: olive;
}

#info .info .value {
    color: grey;
}

/*
 * Responsive design for desktop, default for mobile device
 */
@media only screen and (min-width : 800px) {
    html{
        background-color: #e6e6e6;
    }
    body {
        width:26em;
        border-radius:2em;
        margin-top:2em;
        margin-bottom:2em;
    }
    header{
        height: 8em;
        width:100%;
        position:relative;
        border-radius: 2em 2em 0em 0em;
    }
    #content{
        padding-top:1em;
    }
    nav{
        padding-top: 2em;
    }
}

)=====";
