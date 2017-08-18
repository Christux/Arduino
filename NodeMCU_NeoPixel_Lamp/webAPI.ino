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

void getConfig()
{
  sendConfig();
}

void setConfig()
{
  // Init Json buffer
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(server.arg("plain"));

  if (root.success())
  {
    JsonVariant animation = root["animation"];
    if (animation.success()) 
    {
      int anim = root["animation"].as<int>();

      if (anim >= 0 && anim < animator.animCount()) {
        config.saveAnim(anim);
        animator.setAnimation(anim);
      }
    }

    JsonVariant color = root["color"];
    if (color.success())
    {
      RgbColor rgb(0,0,0);

      JsonVariant red = color["red"];
      if(red.success())
      {
        rgb.R = red.as<char>();
      }

      JsonVariant green = color["green"];
      if(green.success())
      {
        rgb.G = green.as<char>();
      }

      JsonVariant blue = color["blue"];
      if(blue.success())
      {
        rgb.B = blue.as<char>();
      }
      
      config.saveColor(rgb);
      animator.setColor(rgb);
    }
  }
  
  sendConfig();
}

void sendConfig()
{
  int animation = animator.getAnimation();
  RgbColor rgb = animator.getColor();
  
  // Init Json buffer
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& color = root.createNestedObject("color");

  root["animation"] = animation;
  color["red"] = rgb.R;
  color["green"] = rgb.G;
  color["blue"] = rgb.B;

  // Prints Json object to string buffer
  char buffer[256];
  root.printTo(buffer, sizeof(buffer));

  // Sends the Json to requester
  server.send(200, "application/json", buffer);
}

void getInfo()
{
 // Init Json buffer
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["vendor"] = "Christux";
  root["model"] = "LedStrip01";
  root["version"] = 1;
  root["serial"] = "PROTO01";
  root["firmware_build_date"] = __DATE__ " " __TIME__;
  root["ip_adress"] = WiFi.localIP().toString();
  root["mac_adress"] = WiFi.macAddress();
  root["Free_Heap"] = ESP.getFreeHeap();
  root["Chip_Id"] = ESP.getChipId();
  root["Flash_Chip_Size"] = ESP.getFlashChipSize();
  root["Flash_Chip_Frequency"] = ESP.getFlashChipSpeed();

   // Prints Json object to string buffer
  char buffer[300];
  root.printTo(buffer, sizeof(buffer));

  // Sends the Json to requester
  server.send(200, "application/json", buffer);
}


