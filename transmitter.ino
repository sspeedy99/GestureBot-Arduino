/* This is an arduino program for the nano which is fitted inside the wrist band to transmit the gesture to the reciever to the bot.
 *  Author: Shashi Prakash (https://github.com/sspeedy99)
 *  Date : 13 March 2018.
 */
#include <Wire.h>
#include <MPU6050.h>
#include <VirtualWire.h> 

MPU6050 mpu;

void setup()
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");
  vw_setup(2000); //Bits per second
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop()
{
  // Read normalized values
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;
  // Output
  if (pitch >= -10 && pitch <= 10 && roll >= -160 && roll <= -100) // Checking the Condition for front movement.
  {
    Serial.println("Forward");
    const char *msg0 = "aage";
    vw_send((uint8_t *)msg0, strlen(msg0)); // Sending the data to the reciever.
    vw_wait_tx();
  }
  else if (pitch >= -15 && pitch <= 10 && roll <= 160 && roll >= 100) // Checking the Condition for backward movement.
  {
    Serial.println("backward");
    const char *msg1 = "piche";
    vw_send((uint8_t *)msg1, strlen(msg1));
    vw_wait_tx();
  }
  else if (pitch > 10 && roll > 150) // Checking the Condition for left movement.
  {
    Serial.println("left");
    const char *msg2 = "baaye";
    vw_send((uint8_t *)msg2, strlen(msg2));
    vw_wait_tx();
  }
  else if (pitch < -10 && roll < -150) // Checking the Condition for Right movement.
  {
    Serial.println("right");
    const char *msg3 = "daaye";
    vw_send((uint8_t *)msg3, strlen(msg3));
    vw_wait_tx();
  }
  else if (pitch >= -10 && pitch <= 10 && (roll >= 160 || roll <= -160)) // Checking the Condition for static.
  {
    Serial.println("static");
    const char *msg4 = "static";
    vw_send((uint8_t *)msg4, strlen(msg4));
    vw_wait_tx();
  }
  else if (pitch >= -10 && pitch <= 10 && (roll >= -10 || roll <=30)) //The Pitch and Roll value of the gyro sensor is set on the ranges of -10 to +10(for pitch) and -10 to +10 (for Roll).
  {
    Serial.println("Hood");
    const char *msg4 = "Hood";
    vw_send((uint8_t *)msg4, strlen(msg4));
    vw_wait_tx();
  }
  Serial.print(" Y = ");
  Serial.print(pitch);
  Serial.print(" X = ");
  Serial.print(roll);

  Serial.println();

  delay(1000);
}


