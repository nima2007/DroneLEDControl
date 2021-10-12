
//#include <Servo.h> 
#include <PWMServo.h>


#define NOP3 "nop\n\t""nop\n\t""nop\n\t"
#define NOP4 "nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP6 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"


#define signalpin 3
#define oscpin 11
#define servopin 10

unsigned char test = 0;
unsigned char res = 0;
PWMServo myservo;
bool is_open = false;

enum DroneColor
{
  grey = 194,
  orange = 80, 
  yellow = 122,
  lime = 254,
  green = 204,
  cyan = 70,
  blue = 192,
  purple = 180,
  violet = 146
};

void setup() {
  // put your setup code here, to run once:
  pinMode(signalpin, INPUT);
  pinMode(oscpin, OUTPUT);
  digitalWrite(oscpin, LOW);
  delayMicroseconds(1000);
  myservo.attach(servopin);
  motor_close(true);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(2000);
  res = get_color();
  if(res == DroneColor::orange)
  {
    //digitalWrite(oscpin, HIGH);
    motor_open();
    delay(1000);
  }
  else if(res == DroneColor::purple)
  {
    motor_close();
    delay(1000);
  }
  
  
}

unsigned char get_color(void)
{
  unsigned char first = read_packet();
  delay(100);
  unsigned char sec = read_packet();

  if(first == sec)
  {
    return first;
  }
  else
  {
    return get_color();
  }
  
}

unsigned char read_packet(void)
{
  noInterrupts()
  unsigned char timer = 20;
  unsigned char escape = 120;
  while(timer)
  {
    if(digitalReadFast(signalpin))
    {
      timer = 20;
    }
    delayMicroseconds(250);
    timer--;
    if(--escape == 0)
    {
      interrupts()
      return 0;
    }
  }

  while(digitalReadFast(signalpin) == LOW){} // Start of data

  for(int i = 0;i<8;i++) // Read 8 bits
  {
    __asm(NOP6); // offset from start of high to measauring point
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    digitalWriteFast(oscpin, HIGH);
    bitWrite(test, i, digitalReadFast(signalpin) == HIGH);
    digitalWriteFast(oscpin, LOW);
    while(digitalReadFast(signalpin) == HIGH){} // wait for high to stop
    while(digitalReadFast(signalpin) == LOW){} // wait for new high

  }

  interrupts()
  bitWrite(test, 0, 0); // ignore first captured bit since timing is bad
  return test;
  
}

void motor_open()
{
  if(is_open)
  {
    return;
  }
  myservo.write(130);
  is_open = true;
}

void motor_close(bool force)
{
  if(!is_open && !force)
  {
    return;
  }
  myservo.write(170);
  is_open = false;
  
}

void motor_close()
{
  return motor_close(false);
  
}
