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

PROGMEM const char JS[] = R"=====(

/*
 * Led Strip Remote
 *
 * Author : Christux
 * Version : 1.0
 * Date : 20 juil 2017
 */

(function(){
'use strict';

createRemote('/api');

function createRemote(urlFragment) {

    var buttons;

    window.addEventListener(
    "load",
    (function () {
        return function () {
        init();
        };
    })(),
    false);

    function init() {

        buttons = document.getElementsByClassName("button");

        getLeds();

        setInterval(function(){
            getLeds();
        },6000);
    }

    function updateButtons(leds) {

        for (var i = 0, l=buttons.length; i < l; i++) {
                
            var state = leds["led"+(i+1).toString()];
            
            buttons[i].className =  state ? "button active" : "button unactive";
            buttons[i].onclick = (function(I,newState) {
                return function() {
                    setLeds(I,newState);
                }
            })(i,!state);
        }
    }

    function setLeds(i,state) {

        var obj = {};
        obj["led"+(i+1).toString()]=state;

        httpRequest()
            .post(urlFragment,obj)
            .setTimeout(4000)
            .succes(function(data){
                updateButtons(data);
            })
            .error(function(resp){
                console.log(resp);
            })
            .timeout(function(resp){
                console.log(resp);
            })
            .send();
    }

    function getLeds() {
    
        httpRequest()
            .get(urlFragment)
            .setTimeout(4000)
            .succes(function(data){
                updateButtons(data);
            })
            .error(function(resp){
                console.log(resp);
            })
            .timeout(function(resp){
                console.log(resp);
            })
            .send();
    }
}

function httpRequest () {

    var xhr = new XMLHttpRequest();
    var succes,error,timeout;
    var obj=null;
    
    xhr.onreadystatechange = function () {

        if (xhr.readyState === xhr.DONE) {
            if (xhr.status === 200) {
                if(succes) {
                    if(typeof(succes)==='function') {
                        succes(JSON.parse(xhr.responseText));
                    }
                }
            } else {
                if(error) {
                    if(typeof(error)==='function') {
                        error(xhr.status+" "+xhr.statusText);
                    }
                }
            }
        }
    };
    
    xhr.onerror = function (e) {
        if(error) {
            if(typeof(error)==='function') {
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
        get: function(url) {
            xhr.open('GET', url, true);
            return this;
        },
        post: function(url,_obj) {
            xhr.open('POST', url, true);
            obj = _obj;
            return this;
        },
        succes: function(callback) {
            succes = callback;
            return this;
        },
        error: function(callback) {
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
        send: function() {
            xhr.send(JSON.stringify(obj));
        }
    });
}

})();

)=====";
