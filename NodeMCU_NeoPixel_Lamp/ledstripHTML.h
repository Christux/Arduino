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

PROGMEM const char INDEX_HTML[] = R"=====(

<!doctype html>
<html>

<head>
  <title>RGB Led Strip by Christux</title>
  <meta charset="utf-8"/>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <script type="text/javascript" src="./js/RGBledStrip.js"></script>
  <link type="text/css" rel="stylesheet" href="./css/RGBledStrip.css"/>
  <link href="./image/favicon.ico" rel="icon" type="image/x-icon" />
</head> 

<body>

  <header>
    <nav>
      <div class="button unactive">
        <a href="#animation">Mode</a>
      </div>
      <div class="button active">
        <a href="#color">Color</a>
      </div>
      <div class="button unactive">
        <a href="#about">About</a>
      </div>
    </nav>
  </header>
  
  <div id="content">
    <section class="category animation">
      <div id="animation"></div>
    </section>
    <section class="category color">
      <div id="brightness"></div>
      <div id="color"></div>
    </section>
    <section class="category about">
      <h1>Led Strip Control</h1>
      <p>Copyright Christux 2017</p>
      <p>All rights reserved</p>
      <div id="info">
        <div class="button">Get more info</div>
      </div>
    </section>
  </div>

</body>

)=====";
