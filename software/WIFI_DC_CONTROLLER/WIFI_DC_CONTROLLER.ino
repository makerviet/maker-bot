#include <DNSServer.h>
#include <ESPUI.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

const char *ssid = "ESPUI";
const char *password = "espui";
const char *hostname = "espui";

bool dir1 = 0, dir2 = 0, dir3 = 0, dir4 = 0, dir5 = 0;
uint16_t status;
uint16_t button1;
uint16_t millisLabelId;
uint16_t switchOne;

void setPWM(int chan1, int chan2, bool state, uint16_t val)
{
  Serial.println(val);
  if (state)
  {
    pwm.setPWM(chan1, 0, val);
    pwm.setPWM(chan2, 4096, 0);
  }
  else
  {
    pwm.setPWM(chan2, 0, val);
    pwm.setPWM(chan1, 4096, 0);
  }
}

void slider1(Control *sender, int type)
{
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  uint16_t val;
  if (sender->value)
    val = (sender->value).toInt() * 40 + 95;
  else
    val = 0;
  Serial.println(val);
  setPWM(8, 9, dir1, 4095 - val);
}

void slider2(Control *sender, int type)
{
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  uint16_t val;
  if (sender->value)
    val = (sender->value).toInt() * 40 + 95;
  else
    val = 0;
  Serial.println(val);
  setPWM(10, 11, dir2, 4095 - val);
}

void slider3(Control *sender, int type)
{
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  uint16_t val;
  if (sender->value)
    val = (sender->value).toInt() * 40 + 95;
  else
    val = 0;
  Serial.println(val);
  setPWM(12, 13, dir3, 4095 - val);
}

void slider4(Control *sender, int type)
{
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  //u  Serial.println(sender->value);
  uint16_t val;
  if (sender->value)
    val = (sender->value).toInt() * 40 + 95;
  else
    val = 0;
  Serial.println(val);
  setPWM(14, 15, dir4, 4095 - val);
}

void otherSwitchExample1(Control *sender, int value)
{
  switch (value)
  {
  case S_ACTIVE:
    Serial.print("Active:");
    dir1 = 1;
    break;

  case S_INACTIVE:
    Serial.print("Inactive");
    dir1 = 0;
    break;
  }

  Serial.print(" ");
  Serial.println(sender->id);
}
void otherSwitchExample2(Control *sender, int value)
{
  switch (value)
  {
  case S_ACTIVE:
    Serial.print("Active:");
    dir2 = 1;
    break;

  case S_INACTIVE:
    Serial.print("Inactive");
    dir2 = 0;
    break;
  }

  Serial.print(" ");
  Serial.println(sender->id);
}
void otherSwitchExample3(Control *sender, int value)
{
  switch (value)
  {
  case S_ACTIVE:
    Serial.print("Active:");
    dir3 = 1;
    break;

  case S_INACTIVE:
    Serial.print("Inactive");
    dir3 = 0;
    break;
  }

  Serial.print(" ");
  Serial.println(sender->id);
}
void otherSwitchExample4(Control *sender, int value)
{
  switch (value)
  {
  case S_ACTIVE:
    Serial.print("Active:");
    dir4 = 1;
    break;

  case S_INACTIVE:
    Serial.print("Inactive");
    dir4 = 0;
    break;
  }

  Serial.print(" ");
  Serial.println(sender->id);
}

void setup(void)
{
  ESPUI.setVerbosity(Verbosity::VerboseJSON);
  Serial.begin(115200);
  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1000);
  Wire.setClock(400000);

  WiFi.setHostname(hostname);

  // try to connect to existing network
  WiFi.begin(ssid, password);
  Serial.print("\n\nTry to connect to existing network");

  {
    uint8_t timeout = 10;

    // Wait for connection, 5s timeout
    do
    {
      delay(500);
      Serial.print(".");
      timeout--;
    } while (timeout && WiFi.status() != WL_CONNECTED);

    // not connected -> create hotspot
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.print("\n\nCreating hotspot");

      WiFi.mode(WIFI_AP);
      WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
      WiFi.softAP(ssid);

      timeout = 5;

      do
      {
        delay(500);
        Serial.print(".");
        timeout--;
      } while (timeout);
    }
  }

  dnsServer.start(DNS_PORT, "*", apIP);

  Serial.println("\n\nWiFi parameters:");
  Serial.print("Mode: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? "Station" : "Client");
  Serial.print("IP address: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());

  ESPUI.addControl(ControlType::Switcher, "Switch two", "", ControlColor::None, Control::noParent, &otherSwitchExample1);
  ESPUI.addControl(ControlType::Slider, "motor one", "0", ControlColor::Alizarin, Control::noParent, &slider1);
  ESPUI.addControl(ControlType::Switcher, "Switch two", "", ControlColor::None, Control::noParent, &otherSwitchExample2);
  ESPUI.addControl(ControlType::Slider, "motor two", "0", ControlColor::Alizarin, Control::noParent, &slider2);
  ESPUI.addControl(ControlType::Switcher, "Switch two", "", ControlColor::None, Control::noParent, &otherSwitchExample3);
  ESPUI.addControl(ControlType::Slider, "motor three", "0", ControlColor::Alizarin, Control::noParent, &slider3);
  ESPUI.addControl(ControlType::Switcher, "Switch two", "", ControlColor::None, Control::noParent, &otherSwitchExample4);
  ESPUI.addControl(ControlType::Slider, "motor four", "0", ControlColor::Alizarin, Control::noParent, &slider4);

  /*
     .begin loads and serves all files from PROGMEM directly.
     If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
     (.prepareFileSystem has to be run in an empty sketch before)
  */

  // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
  // ESPUI.sliderContinuous = true;

  /*
     Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
     SECURE way of limiting access.
     Anyone who is able to sniff traffic will be able to intercept your password
     since it is transmitted in cleartext. Just add a string as username and
     password, for example begin("ESPUI Control", "username", "password")
  */
  //  motorSlider a(18, 19, "acnv");
  ESPUI.begin("ESPUI Control");
}

void loop(void)
{
  dnsServer.processNextRequest();
}
