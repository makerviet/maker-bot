#include <Arduino.h>
#include <DNSServer.h>
#include <ESPUI.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define Servo_1 7
#define Servo_2 6
#define Servo_3 5
#define Servo_4 4
#define Servo_5 3
#define Servo_6 2

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
#include <WiFi.h>

const char *ssid = "Makerbot BANHMI";
const char *password = "";

const char *hostname = "Makerbot.io";

// uint16_t status;

void setPWM(int chan1, int chan2, bool state, uint16_t val)
{
  Serial.println(val);
  if (state)
  {
    pwm.setPWM(chan1, 0, val);
    pwm.setPWM(chan2, 0, 0);
    //    pwm.setPWM(chan1,  val,0 );
    //    pwm.setPWM(chan2, 0, 4096 );
  }
  else
  {
    pwm.setPWM(chan2, 0, val);
    pwm.setPWM(chan1, 0, 0);
    //pwm.setPWM(chan2,  val,0 );
    //    pwm.setPWM(chan1, 0, 4096 );
  }
}

void DC_slider(Control *sender, int type)
{
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");

  int16_t val;
  if (sender->value)
    val = (sender->value).toInt() * 4095 / 100;
  else
    val = 0;

  bool dir = 0x8000 & val;
  val = abs(val);
  switch(sender->id){
  case 2:
  {
    setPWM(8, 9,dir ,  val);
    break;
  }
  case 5:
  {
    setPWM(10, 11,dir, val);
    break;
  }
  case 8 :
  {
       setPWM(12, 13, dir,  val);
    break;
  }
  case 11:
  {
      setPWM(14, 15, dir,  val);
    break;
  }
  }
  Serial.println(val);

}

void Servo_slider(Control *sender, int type)
{
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");

  uint16_t val;
  if (sender->value)
    val = (sender->value).toInt()/5;
  else
    val = 0;
  Serial.println(val);
  switch(sender->id){
  case 15:
  {
        pwm.setPWM(Servo_1, 0, val);
    break;
  }
  case 18:
  {
            pwm.setPWM(Servo_2, 0, val);
    break;
  }
  case 21 :
  {
        pwm.setPWM(Servo_3, 0, val);
    break;
  }
  case 24:
  {
        pwm.setPWM(Servo_4, 0, val);
    break;
  }
  case 27:
  {
        pwm.setPWM(Servo_5, 0, val);
    break;
  }
    case 30:
  {
        pwm.setPWM(Servo_6, 0, val);
    break;
  }
  }
}
void setup(void)
{
  pinMode(13,OUTPUT);
  digitalWrite(13,1);
  ESPUI.setVerbosity(Verbosity::VerboseJSON);
  Serial.begin(115200);
  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(60);
//  Wire.setClock(400000);

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

  uint16_t tab1 = ESPUI.addControl(ControlType::Tab, "", "DC Motor");
//  ESPUI.addControl(ControlType::Switcher, "Switch two", "", ControlColor::None, tab1, &otherSwitchExample1);
  uint16_t  slider_1 = ESPUI.addControl(ControlType::Slider, "DC Motor 1", "0", ControlColor::Turquoise, tab1, &DC_slider);
  ESPUI.addControl(Min, "", "-100", None, slider_1);
  ESPUI.addControl(Max, "", "100", None, slider_1);
  
  uint16_t slider_2 = ESPUI.addControl(ControlType::Slider, "DC motor 2", "0", ControlColor::Emerald, tab1, &DC_slider);
  ESPUI.addControl(Min, "", "-100", None, slider_2);
  ESPUI.addControl(Max, "", "100", None, slider_2);
  
  uint16_t slider_3 = ESPUI.addControl(ControlType::Slider, "DC motor 3", "0", ControlColor::Peterriver, tab1, &DC_slider);
  ESPUI.addControl(Min, "", "-100", None, slider_3);
  ESPUI.addControl(Max, "", "100", None, slider_3);
  
  uint16_t slider_4 = ESPUI.addControl(ControlType::Slider, "DC motor 4", "0", ControlColor::Wetasphalt, tab1, &DC_slider);
  ESPUI.addControl(Min, "", "-100", None, slider_4);
  ESPUI.addControl(Max, "", "100", None, slider_4);

  uint16_t tab2 = ESPUI.addControl(ControlType::Tab, "", "Servos");
  
  uint16_t  slider_5 = ESPUI.addControl(ControlType::Slider, "Servo 1", "0", ControlColor::Turquoise, tab2, &Servo_slider);
   ESPUI.addControl(Min, "", "400", None, slider_5);
  ESPUI.addControl(Max, "", "2200", None, slider_5);
    
  uint16_t  slider_6 = ESPUI.addControl(ControlType::Slider, "Servo 2", "0", ControlColor::Carrot, tab2, &Servo_slider);
   ESPUI.addControl(Min, "", "400", None, slider_6);
  ESPUI.addControl(Max, "", "2200", None, slider_6);  
  
  uint16_t  slider_7 = ESPUI.addControl(ControlType::Slider, "Servo 3", "0", ControlColor::Alizarin, tab2, &Servo_slider);
   ESPUI.addControl(Min, "", "400", None, slider_7);
  ESPUI.addControl(Max, "", "2200", None, slider_7);

    
  uint16_t  slider_8 = ESPUI.addControl(ControlType::Slider, "Servo 4", "0", ControlColor::Peterriver, tab2, &Servo_slider);
   ESPUI.addControl(Min, "", "400", None, slider_8);
  ESPUI.addControl(Max, "", "2200", None, slider_8);
    
  uint16_t  slider_9 = ESPUI.addControl(ControlType::Slider, "Servo 6", "0", ControlColor::Wetasphalt, tab2, &Servo_slider);
   ESPUI.addControl(Min, "", "400", None, slider_9);
  ESPUI.addControl(Max, "", "2200", None, slider_9);  
  uint16_t  slider_10 = ESPUI.addControl(ControlType::Slider, "Servo 6", "0", ControlColor::Emerald, tab2, &Servo_slider);
   ESPUI.addControl(Min, "", "400", None, slider_10);
  ESPUI.addControl(Max, "", "2200", None, slider_10);
  
  /*
     .begin loads and serves all files from PROGMEM directly.
     If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
     (.prepareFileSystem has to be run in an empty sketch before)
  */

  // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
  ESPUI.sliderContinuous = true;

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