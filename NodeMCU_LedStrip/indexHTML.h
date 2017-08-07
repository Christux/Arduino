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

PROGMEM const char INDEX_HTML[] = R"=====(

<!doctype html>
<html>
  <head>
    <title>Led Strip Remote by Christux</title>
    <meta charset="utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="Remote application for NodeMCU LedStrip"/>
    <meta name="keywords" content="Remote,LedStrip"/>
    <meta name="author" content="Christophe Rubeck"/>
    <meta name="copyright" content="Christophe Rubeck 2017"/>
    <script type="text/javascript" src="./js/ledStrip.js"></script>
    <link type="text/css" rel="stylesheet" href="./css/ledStrip.css"/>
    <link href="./favicon.ico" rel="icon" type="image/x-icon" />
  </head> 
  
  <body>
    <div id="remote">
      <div class="button unactive">Led 1</div>
      <div class="button unactive">Led 2</div>
      <div class="button unactive">Led 3</div>
      <div class="button unactive">Led 4</div>
    </div>
  </body>
</html>

)=====";
