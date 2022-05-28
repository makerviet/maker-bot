#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PWM 0
#define MAX_PWM 4095

// PWM channels of pca9685 0-16
#define PWM_CHANNEL1 8
#define PWM_CHANNEL2 9
#define PWM_CHANNEL3 10
#define PWM_CHANNEL4 11

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setPWMMotors(int c1, int c2, int c3, int c4)
{
  char dbg_str[30];
  sprintf(dbg_str,"C1: %d\tC2: %d\tC3: %d\tC4: %d",c1,c2,c3,c4);
  Serial.println(dbg_str);

  pwm.setPWM(PWM_CHANNEL1, 0, c1);
  pwm.setPWM(PWM_CHANNEL2, 0, c2);
  pwm.setPWM(PWM_CHANNEL3, 0, c3);
  pwm.setPWM(PWM_CHANNEL4, 0, c4);
}

void initMotors()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);
  Wire.setClock(400000);

  setPWMMotors(0, 0, 0, 0);
}
