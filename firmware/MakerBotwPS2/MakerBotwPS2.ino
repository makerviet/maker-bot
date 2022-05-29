/*
 * A better version of MakerBotwPS2 example used with makerbot BANHMI hardware platform
 * This version simplify the joystick driving method, where the functionality stay the same.
 * Added new controling menthod, switch driving mode by pressing SELECT button
 * Added nitro like speed booster when holding L2
 * 
 * Writen by Tu Dang - Makerviet
 */

#include "motors.h"
#include "PS2_controller.h"

void setup()
{

  Serial.begin(115200);
  initMotors();
  setupPS2controller();
  Serial.println("Done setup!");
}

void loop()
{
  ps2x.read_gamepad(0, 0);
  PS2control();

  delay(50);

}
