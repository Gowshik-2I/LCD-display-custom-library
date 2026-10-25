const uint8_t E = 11 ;
const uint8_t RS = 12 ;
int data[8] = {2,3,4,5,6,7,8,9};

void pininit()
{
  pinMode(E,OUTPUT);
  digitalWrite(E,LOW);
  pinMode(RS,OUTPUT);
  digitalWrite(RS,LOW);
  for(int i = 0;i<8;i++)
  {
    pinMode(data[i],OUTPUT);
    digitalWrite(data[i],LOW);
  }
}
void lcdinit()
{
  pininit();

  delay(50);

  digitalWrite(data[4],HIGH);
  digitalWrite(data[5],HIGH);
  pulseEnable();
  delay(5);

  digitalWrite(data[4],HIGH);
  digitalWrite(data[5],HIGH);
  pulseEnable();
  delayMicroseconds(150);

  digitalWrite(data[4],HIGH);
  digitalWrite(data[5],HIGH);
  pulseEnable();
  delayMicroseconds(150);

  digitalWrite(data[4],HIGH);
  digitalWrite(data[5],HIGH);
  digitalWrite(data[3],HIGH);
  pulseEnable();
  delayMicroseconds(100);

  pininit();

  digitalWrite(data[3],HIGH);
  pulseEnable();
  delayMicroseconds(100);

  pininit();

  digitalWrite(data[0],HIGH);
  pulseEnable();
  delay(2);

  pininit();

  digitalWrite(data[2],HIGH);
  digitalWrite(data[1],HIGH);
  pulseEnable();
  delayMicroseconds(100);

  digitalWrite(data[3],HIGH);
  digitalWrite(data[2],HIGH);
  pulseEnable();
  delayMicroseconds(100);
  pininit();
}

void loadTamilchar()
{
  // 5 glyphs x 8 rows. Only the lower 5 bits matter: bit 4 = leftmost pixel.
const uint8_t glyph[8][8] = {
  {0x0f, 0x0a, 0x1f, 0x13, 0x1f, 0x03, 0x04, 0x08},  // 0: ெ
  {0x07, 0x04, 0x17, 0x15, 0x15, 0x1f, 0x00, 0x00},  // 1: க
  {0x04, 0x17, 0x15, 0x15, 0x1f, 0x04, 0x12, 0x0c},  // 2: ௗ
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 3: சி
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
   
};

  lcdWrite(0b01000000,false);
  for(int i = 0 ; i<8 ; i++)
  {
    for(int j = 0 ; j < 8 ; j++)
    {
      lcdWrite(glyph[i][j],true);
    }
  }
  lcdWrite(0b10000000,false);
}

void putdata(uint8_t msg)
{
  for(int i = 0 ; i < 8 ; i++)
  {
    uint8_t shiftedmsg = msg>>i;
    if(shiftedmsg & 1)
    {
      digitalWrite(data[i],HIGH);
    }
    else
    {
      digitalWrite(data[i],LOW);
    }
  }
}

void pulseEnable()
{
  digitalWrite(E,HIGH);
  delayMicroseconds(1);
  digitalWrite(E,LOW);
}

void lcdWrite(uint8_t x,bool isdata)
{
  putdata(x);
  if(isdata)
  {
    digitalWrite(RS,HIGH);
  }
  else
  {
    digitalWrite(RS,LOW);
  }
  pulseEnable();
  delayMicroseconds(50);
}

void writedata(const char datatoprint[])
{
  int a = 0;
  while(datatoprint[a]!='\0')
  {
    lcdWrite(datatoprint[a],1);
    a++;
    delay(500);
  }

}
void setup() 
{
  lcdinit();
  //const char message[] = " vaada mapula vala pazhaa thopula...vaada mapula vala pazhaa thopula";
 // writedata(message);
 loadTamilchar();
  int a = ' ';
 lcdWrite(a,true);
 for(int i = 5 ; i < 8 ; i++)
 {
  lcdWrite(i,true);
  delay(500);
 }
 lcdWrite(a,true);

 lcdWrite(a,true);
 for(int i = 0 ; i < 3 ; i++)
 {
  lcdWrite(i,true);
  delay(500);
 }


}

void loop() 
{

}
