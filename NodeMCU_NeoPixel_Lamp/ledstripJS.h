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

PROGMEM const char JS[] = R"=====(

/*
 * Led Strip Remote
 *
 * Author : Christux
 * Version : 4.0
 * Date : 20 aout 2017
 */
'use strict';

var remote = (function (self) {

    /*
     * Initialize all sub-object
     */

    var init = execStep(self,"init");
    var build = execStep(self,"build");
    var onload = execStep(self,"onload");

    /*
     * Waits until all modules are loaded before to init
     */
    window.addEventListener(
            "load",
            (function () {
                return function () {
                    init();
                    build();
                    onload();
                };
            })(),
            false);

    function execStep(ctx,step) {
        return function () {
            for (var name in ctx) {
                if (ctx[name].hasOwnProperty(step)) {
                    if (typeof (ctx[name][step]) === 'function') {
                        ctx[name][step]();
                    }
                    if (Array.isArray(ctx[name][step])) {
                        resolve(ctx[name][step]);
                    }
                }
            }
        };
    }

    // For dependency injection
    function resolve(array) {

        var modules = [];
        var func = array[array.length-1];
        var deps = array.slice(0,array.length-1);
        
        deps.forEach(function (dep) {

            if (self.hasOwnProperty(dep)) {
                modules.push(self[dep]);
            } else {
                throw new Error('Dependency module ' + dep + ' not found !');
            }
        });

        return func.apply(this, modules);
    }

    return self;

})(remote || {});

/*
 * Pattern module
 */
var remote = (function (self) {

    self.pattern = (function() {

        return this;

    }).call({
        init: function() {

        },
        build: function() {

        },
        onload: function() {

        },
        onchange: function() {

        }
    });

    return self;
    
})(remote || {});

/*
 * Navigation module
 */
var remote = (function (self) {

    /*
     * Navigates between pages by handling section visibility and navbar
     */
    var buttonList = [];
    var categoryList = [];
    var resetScroll;

    /*
    * Gets selected page
    */
    var getSelectedAnchor = function () {
        return window.location.hash.split('#')[1] || 'animation';
    };

    /*
    * Sets current page on navbar
    */
    var disactivate = function (button) {
        button.className = "button active";
    };

    /*
    * Sets other pages on navbar
    */
    var activate = function (button) {
        button.className = "button unactive";
    };

    /*
    * Displays selected page and update navbar
    */
    var displaySelectedCategory = function () {

        var selectedAnchor = getSelectedAnchor();
        var showedCategory = window.document.getElementsByClassName(selectedAnchor)[0];

        for (var i in categoryList) {
            if (categoryList[i].style) {

                if (categoryList[i] === showedCategory) {
                    categoryList[i].style.display = "block";
                    if (buttonList[i]) {
                        disactivate(buttonList[i]);
                    }
                } else {
                    categoryList[i].style.display = "none";
                    if (buttonList[i]) {
                        activate(buttonList[i]);
                    }
                }
            }
        }

        // Goes on the top of the page
        resetScroll();
    };

    self.navigate = (function(){

        /*
        * Listen to change anchor event
        */
        window.addEventListener(
                "hashchange",
                (function () {
                    return function () {
                        displaySelectedCategory();
                    };
                })(),
                false);

        return this;

    }).call(
    {
        init: ['scroll',function (scroll) {
            resetScroll = scroll.init;

            buttonList = window.document.getElementsByTagName("header")[0].getElementsByClassName("button");
            categoryList = window.document.getElementById("content").getElementsByClassName("category");

            displaySelectedCategory();
        }]
    });

    return self;
    
})(remote || {});


/*
 * Scroll module
 */
var remote = (function (self) {

    var set = function (position) {
        window.document.body.scrollTop = position;
        window.document.documentElement.scrollTop = position;
    };

    self.scroll = (function () {

        return this;
    }).call({
        set: function (position) {
            set(position);
        },
        init: function () {
            set(0);
        }
    });

    return self;

})(remote || {});


/*
 * Observer module (GoF design pattern)
 */
var remote = (function (self) {

    var actionHandlers = [];

    self.observer = (function() {

        return this;
    
    }).call({
        notifyAll: function () {

            var args = arguments;

            actionHandlers.forEach(function (ah) {
                if (typeof ah === 'function') {
                    ah.apply(this, args);
                }
            });
        },

        registerHandler: function (handler) {
            
            if (typeof handler === 'function') {
                actionHandlers.push(handler);
            }
        }
  });

    return self;
    
})(remote || {});


/*
 * HTTP module, build httprequest
 */
var remote = (function (self) {

    self.HTTP = (function() {
      
      return this;

    }).call({
      get: function (url) {
        return createXhrBuilder('GET', url, null);
      },
      post: function (url, obj) {
        return createXhrBuilder('POST', url, obj);
      }
        });
        
    function createXhrBuilder(verb, url, obj) {

    var xhr = new XMLHttpRequest();
    var success, error, timeout;
    var obj = obj || null;

    xhr.onreadystatechange = function () {

      if (xhr.readyState === xhr.DONE) {
        if (xhr.status === 200) {
          if (success) {
            if (typeof (success) === 'function') {
              success(xhr.responseText);
            }
          }
        } else {
          if (error) {
            if (typeof (error) === 'function') {
              error(xhr.status + " " + xhr.statusText);
            }
          }
        }
      }
    };

    xhr.onerror = function (e) {
      if (error) {
        if (typeof (error) === 'function') {
          error(e.error);
        }
      }
    };

    xhr.ontimeout = function (e) {
      if(timeout) {
        if(typeof(timeout)==='function') {
          timeout(e);
        }
      }
    };

    return (function() {
      
      return this;

    }).call({
      success: function (callback) {
        success = callback;
        return this;
      },
      error: function (callback) {
        error = callback;
        return this;
      },
      timeout: function(callback) {
        timeout = callback;
        return this;
      },
      setTimeout: function(delay) {
        xhr.timeout = delay;
        return this;
      },
      send: function () {
        xhr.open(verb, url, true);
        xhr.send(obj);
      }
        });
    }

    return self;
    
})(remote || {});


/*
 * Data model module
 */
var remote = (function (self) {

    var observer, http;
    var url;
    var previous = "";

    function get() {

        http.get(url)
            .setTimeout(10000)
            .success(function(resp){
                // Little optimization, notifies only if changes
                if(resp !== previous) {
                    previous = resp;
                    observer.notifyAll(JSON.parse(resp));
                }
            })
            .error(function(resp){
                console.log(resp);
            })
            .timeout(function(resp){
                console.log(resp);
            })
            .send();
    }
    
    function set(obj) {

        http.post(url,JSON.stringify(obj))
            .setTimeout(10000)
            .success(function(resp){
                var data = JSON.parse(resp);
                observer.notifyAll(data);
            })
            .error(function(resp){
                console.log(resp);
            })
            .timeout(function(resp){
                console.log(resp);
            })
            .send();
    }

    self.model = (function() {

        setInterval(function(){
            get();
        },6000);

        return this;

    }).call({
        init: ['observer','HTTP',function(obs,HTTP) {
            observer = obs;
            http = HTTP;
            url = '/api';
        }],
        onload: function() {
            get();
        },
        update: function() {
            get();
        },
        send: function(data) {
            set(data);
        }
    });

    return self;
    
})(remote || {});


/*
 * Animation module
 */
var remote = (function (self) {

    var node;
    var buttonList = [];

    var availableModes = [
        "Static color", "Rainbow lamp", "Rainbow lamp rand",
        "Rainbow", "Comet", "Breathing", "Fire", "Theater",
        "Knight Rider", "Flag", "Sunrise","Off"];
    
    function build(model) {

        for (var i = 0, len = availableModes.length; i < len; i++) {

            var button = document.createElement('div');
            button.innerHTML = availableModes[i];
            button.className = "button unactive";
            button.onclick = (function (I) {
                return function () {
                    changeMode(model,I);
                };
            })(i);
            
            node.appendChild(button);
            buttonList.push(button);
        }
    }

    function changeMode(model,newMode) {

        var obj = {
            animation: newMode
        };
        model.send(obj);
    }

    function update(anim) {

        for (var i = 0, len = buttonList.length; i < len; i++) {
            if(anim === i) {
                buttonList[i].className = "button active";
            }
            else {
                buttonList[i].className = "button unactive";
            }
        }
    }

    self.animation = (function() {

        return this;

    }).call({
        init: ['observer',function(observer) {
            node = document.getElementById("animation");
            
            observer.registerHandler(function(data){
                update(data.animation);
            });
        }],
        build: ['model',function(model) {
            build(model);
        }]
    });

    return self;
    
})(remote || {});


/*
 * Brightness module
 */
var remote = (function (self) {

    var node;
    var buttonList = [];
    var bColors = [];

    function build(model) {

        var tablebody = document.createElement('div');
        tablebody.className = 'divTableBody';
        node.appendChild(tablebody);

        var tablerow = document.createElement('div');
        tablerow.className = 'divTableRow';
        tablebody.appendChild(tablerow);

        for (var i = 0; i < 6; i++) {

            var button = document.createElement('div');
            button.className = "divTableCell";
            button.style.backgroundColor = "black";
            button.onclick = (function (I) {
                return function () {
                    changeColor(model,I);
                };
            })(i);
            
            tablerow.appendChild(button);
            buttonList.push(button);
        }
    }

    function computeColors(color) {

        var r = color.red, g=color.green, b=color.blue;

        var brightness = Math.max(r, g, b, 1); // Avoid dividing by zero
        var brightIdx = Math.max(0, Math.round(6 - brightness / (255 / 6)));
        for (var i = 0; i < 6; i++) {
            var newR = Math.round(r * (1 - 1 / 6 * i) * 255 / brightness);
            var newG = Math.round(g * (1 - 1 / 6 * i) * 255 / brightness);
            var newB = Math.round(b * (1 - 1 / 6 * i) * 255 / brightness);
            bColors[i] = "rgb(" + newR.toString() + "," + newG.toString() + "," + newB.toString() + ")";
        }

        return brightIdx;
    }

    function update(color) {

        var idx = computeColors(color);

        for (var i = 0; i < 6; i++) {

            var style = buttonList[i].style;

            style.backgroundColor =  bColors[i];

            if (i === idx) {
                style.borderStyle = "solid";
                style.borderWidth = "0.5em";
                style.borderColor = "white";
            }
            else {
                style.border = "none";
            }
        }
    }

    function changeColor(model,idx) {

        var rgb = bColors[idx].split(/rgb\(+(.+?)\,+(.+?)\,+(.+?)\)/);
        var color = {
            color: {
                red: parseInt(rgb[1]),
                green: parseInt(rgb[2]),
                blue : parseInt(rgb[3])
            }
        };

        model.send(color);
    }

    self.brightness = (function() {

        return this;

    }).call({
        init: ['observer',function(observer) {
            node = document.getElementById("brightness");
            
            observer.registerHandler(function(data){
                update(data.color);
            });
        }],
        build: ['model',function(model) {
            build(model);
        }]
    });

    return self;
    
})(remote || {});


/*
 * Color picker module
 */
var remote = (function (self) {

    var node;
    var buttonList = [];
    var gColors = [];

    var colorTab = [// Colors, 5x3 grid
        "rgb(255,0,0)", "rgb(255,128,0)", "rgb(255,215,0)",
        "rgb(255,255,0)", "rgb(128,255,128)", "rgb(0,255,0)",
        "rgb(0,255,128)", "rgb(0,255,255)", "rgb(0,128,255)",
        "rgb(0,0,255)", "rgb(128,0,255)", "rgb(255,0,255)",
        "rgb(255,128,128)", "rgb(255,0,128)", "rgb(255,255,255)"];

    function build(model) {

        var tablebody = document.createElement('div');
        tablebody.className = 'divTableBody';
        node.appendChild(tablebody);

        // Add buttons to panel
        for (var i = 0; i < 5; i++) {

            var tablerow = document.createElement('div');
            tablerow.className = 'divTableRow';
            tablebody.appendChild(tablerow);
            
            for (var j = 0; j < 3; j++) {

                var button = document.createElement('div');
                button.className = "divTableCell";
                button.style.backgroundColor = colorTab[i * 3 + j];
                button.onclick = (function (I) {
                    return function () {
                        changeColor(model,I);
                    };
                })(i * 3 + j);

                tablerow.appendChild(button);
            }
        }
    }

    function update(color) {

        var r = color.red, g=color.green, b=color.blue;
        var brightness = Math.max(r, g, b, 1); // Avoid dividing by zero

        // Adjust color table to brightness
        for (var i = 0, len = colorTab.length; i < len; i++) {
            var rgb = colorTab[i].split(/rgb\(+(.+?)\,+(.+?)\,+(.+?)\)/);
            var r = parseInt(rgb[1]);
            var g = parseInt(rgb[2]);
            var b = parseInt(rgb[3]);
            var newR = Math.round(r * brightness / 255);
            var newG = Math.round(g * brightness / 255);
            var newB = Math.round(b * brightness / 255);
            gColors[i] = "rgb(" + newR.toString() + "," + newG.toString() + "," + newB.toString() + ")";
        }
    }

    function changeColor(model,idx) {

        var rgb = gColors[idx].split(/rgb\(+(.+?)\,+(.+?)\,+(.+?)\)/);
        var color = {
            color: {
                red: parseInt(rgb[1]),
                green: parseInt(rgb[2]),
                blue : parseInt(rgb[3])
            }
        };

        model.send(color);
    }

    self.picker = (function() {

        return this;

    }).call({
        init: ['observer',function(observer) {
            node = document.getElementById("color");
            
            observer.registerHandler(function(data){
                update(data.color);
            });
        }],
        build: ['model',function(model) {
            build(model);
        }]
    });

    return self;
    
})(remote || {});


/*
 * Info module
 */
var remote = (function (self) {

    var node;

    function build(http) {

        var button = node.getElementsByClassName("button")[0];
        button.onclick = function() {
            
            http.get("/info")
            .setTimeout(10000)
            .success(function(resp){
                display(JSON.parse(resp));
            })
            .error(function(resp){
                console.log(resp);
            })
            .timeout(function(resp){
                console.log(resp);
            })
            .send();
        };
    }

    function display(info) {

        node.innerHTML = "";

        var table = document.createElement('table');
        table.className = "info";
        node.appendChild(table);

        for (var field in info) {
            if (info.hasOwnProperty(field)) {
            
                var row = document.createElement('tr');
                table.appendChild(row);

                var key = document.createElement('td');
                var value = document.createElement('td');
                row.appendChild(key);
                row.appendChild(value);

                key.innerHTML = field;
                key.className = "key";
                value.innerHTML = info[field];
                value.className = "value";
            }
        }
    }

    self.info = (function() {

        return this;

    }).call({
        init: function() {
            node = document.getElementById("info");
        },
        build: ['HTTP',function(http) {
            build(http);
        }]
    });

    return self;
    
})(remote || {});

)=====";
