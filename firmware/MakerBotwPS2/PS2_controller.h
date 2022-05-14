//#include "motors.h"
#include <PS2X_lib.h>

PS2X ps2x; // create PS2 Controller Class

#define PS2_DAT 12 //MISO  19
#define PS2_CMD 13 //MOSI  23
#define PS2_SEL 15 //SS     5
#define PS2_CLK 14 //SLK   18

//#define MIN_PWM 0
//#define MAX_PWM 4095
//bool RUN = 0;

void setupPS2controller()
{
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  ps2x.readType();
  //  ps2x.read_gamepad(false, 0); // disable vibration of the controller
}
bool PS2control()
{
  // Based on IgorF2's Arduino Bot:https://www.instructables.com/Arduino-Robot-With-PS2-Controller-PlayStation-2-Jo/

  int nJoyX = ps2x.Analog(PSS_RX); // read x-joystick
  int nJoyY = ps2x.Analog(PSS_RY); // read y-joystick

  nJoyX = map(nJoyX, 0, 255, -1023, 1023);
  nJoyY = map(nJoyY, 0, 255, 1023, -1023);

  // OUTPUTS
  int nMotMixL; // Motor (left) mixed output
  int nMotMixR; // Motor (right) mixed output

  // CONFIG
  // - fPivYLimt  : The threshold at which the pivot action starts
  //                This threshold is measured in units on the Y-axis
  //                away from the X-axis (Y=0). A greater value will assign
  //                more of the joystick's range to pivot actions.
  //                Allowable range: (0..+127)
  float fPivYLimit = 1023.0;

  // TEMP VARIABLES
  float nMotPremixL; // Motor (left) premixed output
  float nMotPremixR; // Motor (right) premixed output
  int nPivSpeed;     // Pivot Speed
  float fPivScale;   // Balance scale between drive and pivot

  // Calculate Drive Turn output due to Joystick X input
  if (nJoyY >= 0)
  {
    // Forward
    nMotPremixL = (nJoyX >= 0) ? 1023.0 : (1023.0 + nJoyX);
    nMotPremixR = (nJoyX >= 0) ? (1023.0 - nJoyX) : 1023.0;
  }
  else
  {
    // Reverse
    nMotPremixL = (nJoyX >= 0) ? (1023.0 - nJoyX) : 1023.0;
    nMotPremixR = (nJoyX >= 0) ? 1023.0 : (1023.0 + nJoyX);
  }

  // Scale Drive output due to Joystick Y input (throttle)
  nMotPremixL = nMotPremixL * nJoyY / 1023.0;
  nMotPremixR = nMotPremixR * nJoyY / 1023.0;

  // Now calculate pivot amount
  // - Strength of pivot (nPivSpeed) based on Joystick X input
  // - Blending of pivot vs drive (fPivScale) based on Joystick Y input
  nPivSpeed = nJoyX;
  fPivScale = (abs(nJoyY) > fPivYLimit) ? 0.0 : (1.0 - abs(nJoyY) / fPivYLimit);

  // Calculate final mix of Drive and Pivot
  nMotMixL = (1.0 - fPivScale) * nMotPremixL + fPivScale * (nPivSpeed);
  nMotMixR = (1.0 - fPivScale) * nMotPremixR + fPivScale * (-nPivSpeed);

  Serial.print(nMotMixL);
  Serial.print("\t");
  Serial.println(nMotMixR);
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

  if (nMotMixR > 50)
  {
    c3 = nMotMixR;
    // pwm.setPWM(PWM_CHANNEL1, motor_right_speed, MAX_PWM - motor_right_speed );
    // pwm.setPWM(PWM_CHANNEL2, 0, MAX_PWM );
  }

  else if (nMotMixR < -50)
  {
    // pwm.setPWM(PWM_CHANNEL2, motor_right_speed, MAX_PWM - motor_right_speed );
    // pwm.setPWM(PWM_CHANNEL1, 0, MAX_PWM );
    c4 = abs(nMotMixR);
  }

  if (nMotMixL > 50)
  {
    // pwm.setPWM(PWM_CHANNEL3, motor_left_speed, MAX_PWM - motor_left_speed );
    // pwm.setPWM(PWM_CHANNEL4, 0, MAX_PWM );
    c1 = nMotMixL;
  }
  else if (nMotMixL < -50)
  {
    // pwm.setPWM(PWM_CHANNEL4, motor_left_speed, MAX_PWM - motor_left_speed );
    // pwm.setPWM(PWM_CHANNEL3, 0, MAX_PWM );
    c2 = abs(nMotMixL);
  }
  setPWMMotors(c1, c2, c3, c4);
  delay(50);
  return 1;
}
