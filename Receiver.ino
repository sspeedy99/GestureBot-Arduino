/* This is the program for arduino MEGA which is used in the chassis of the car by which it recives the data which is further used to control the motors and movement of the bot.
 *  Author : Shashi Prakash(https://github.com/sspeedy99)
 *  Date : 21 April 2018.
 */
#include <VirtualWire.h>
int in1 = 6;
int in2 = 5;
int in3 = 4;
int in4 = 3;
int en1 = 8;
int en2 = 2 ;
int en3 = 41; // The third enable pin is used for hood raising mechanism.
int in5 = 42; //motor driver L298 in1 will be in5 and in2 will be in6 of the motor which is used for hood part. 
int in6 = 43;
void setup()
{
  Serial.begin(9600); // Debugging only
  pinMode(13, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(en3, OUTPUT);


  //vw_set_ptt_inverted(true); // Required when using encoder/decoder
  vw_setup(2000);  // Bits per sec

  vw_rx_start();       // Start the receiver
}

void loop()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(en3, HIGH);

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    digitalWrite(13, HIGH); // Turn led 13 pin on



    if (char(buf[0]) == 'a') // Move forward.
    {
      Serial.println("Forward");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      delay(1000);
    }
    else if (char(buf[0]) == 's') // static value.
    {
      Serial.println("Static");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(1000);
    }
    else if (char(buf[0]) == 'b') // Move Left
    {
      Serial.println("Left");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(1000);
    }
    else if (char(buf[0]) == 'd') // Move Right.
    {
      Serial.println("Rght");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      delay(1000);
    }
    else if (char(buf[0]) == 'p') // Move backward
    {
      Serial.println("Backward");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      delay(1000);
    }
    else if (char(buf[0]) == 'H') // Raise the hood
    {
      
      //for Clockwise in1=HIGH, in2=LOW.
      //Clockwise for 20 secs.
      Serial.println("hood");
      
      digitalWrite(in5, HIGH);
      digitalWrite(in6, LOW);
      delay(20000);

      //for brake of 1 secs.
      digitalWrite(in5, HIGH);
      digitalWrite(in6, HIGH);
      delay(1000);

      //Anti clockwise for 20secs.
      digitalWrite(in5, LOW);
      digitalWrite(in6, HIGH);
      delay(20000);

      //for brake 1 sec.
      digitalWrite(in5, HIGH);
      digitalWrite(in6, HIGH);
      delay(1000);
    }
    Serial.println("");

  }
}
