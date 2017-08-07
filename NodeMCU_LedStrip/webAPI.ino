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

void getLeds() {

  Serial.println("");
  Serial.print("Get request from ");
  Serial.println(server.client().remoteIP().toString());

  sendLeds();
}

void setLeds() {

  Serial.println("");
  Serial.print("Post request from ");
  Serial.println(server.client().remoteIP().toString());

  // Init Json buffer
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));

  Serial.println(server.arg("plain"));

  if (root.success())
  {
    // Init the 4th keys
    const char *key[] = {"led1", "led2", "led3", "led4"};

    // Look for Json properties on all keys
    for (int i = 0; i < 4; i++)
    {
      if (root.containsKey(key[i]))
      {
        char value = root[key[i]].as<bool>();
        ledstrip.set(i, value);
        Serial.print("Change state of ");
        Serial.println(key[i]);
      }
    }

    // Look for 'all' property
    if (root.containsKey("all"))
      {
        if(root["all"].as<bool>())
        {
          ledstrip.all();
        }
        else {
          ledstrip.reset();
        }
      }

    // Commit led states
    ledstrip.show();
  }

  // Return current led state
  sendLeds();
}

void sendLeds() {

  // Init Json buffer
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  // Init the 4th keys
  const char *key[] = {"led1", "led2", "led3", "led4"};

  // Set Json object with key values
  for (int i = 0; i < 4; i++)
  {
    root[key[i]] = ledstrip.get(i) == 0 ? false : true;
  }

  // Prints Json object to string buffer
  char buffer[256];
  root.printTo(buffer, sizeof(buffer));

  // Sends the Json to requester
  server.send(200, "application/json", buffer);
  Serial.println(buffer);
}

