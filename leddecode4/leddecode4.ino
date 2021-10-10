

#define NOP3 "nop\n\t""nop\n\t""nop\n\t"
#define NOP4 "nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP6 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"


#define signalpin 3
#define oscpin 11

unsigned char test = 0;
unsigned char res = 0;

enum color
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
  
}

void loop() {
  // put your main code here, to run repeatedly:

  res = get_color();
  if(res == 80)
  {
    digitalWrite(oscpin, HIGH);
  }
  delay(2000);
  
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
  //__asm(NOP6);

  for(int i = 0;i<8;i++) // Read 8 bits
  {
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    digitalWriteFast(oscpin, HIGH);
    //__asm(NOP6);
    bitWrite(test, i, digitalReadFast(signalpin) == HIGH);
    digitalWriteFast(oscpin, LOW);
    /*__asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP6);
    __asm(NOP4);*/
    while(digitalReadFast(signalpin) == HIGH){}
    while(digitalReadFast(signalpin) == LOW){}

  }

  /*digitalWriteFast(oscpin, HIGH);
  //__asm(NOP6);
  bitWrite(test, 1, digitalReadFast(oscpin));
  //__asm( "nop" );
  digitalWriteFast(oscpin, LOW);
  __asm(NOP6);

  /*__asm( "nop" );
  __asm( "nop" );
  __asm( "nop" );
  __asm( "nop" );
  __asm( "nop" );
  __asm( "nop" );
  __asm( "nop" );
  __asm( "nop" );
  __asm( "nop" );
  __asm( "nop" );*/
 /*
  digitalWriteFast(oscpin, LOW);
  test = digitalReadFast(signalpin);

  if(test == 0)
  {
    __asm(NOP6);
    digitalWriteFast(oscpin, HIGH);
    __asm(NOP6);
    digitalWriteFast(oscpin, LOW);
  }
  */
  /*for (int j = 0;j < test; j++)
  {
    digitalWriteFast(oscpin, HIGH);
    __asm(NOP6);
    digitalWriteFast(oscpin, LOW);
    __asm(NOP6);
    
  }*/
  interrupts()
  bitWrite(test, 0, 0); // ignore first captured bit since timing is bad
  return test;
  
}
