
/*
TODO:
 setCursor(col, row) for all 4 rows
 clear() and home()
 display() / noDisplay()
 cursor() / noCursor()
 blink() / noBlink()
 createChar(slot, rows) (move the Tamil data out of the driver into a sketch)
 */

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

/*initialisation by instruction=>
1. function set 3 times
2. 4th time function set with mode type
3. display off
4. display clear
5. display entry mode set
6. display on
*/ 

  pininit();

  delay(50);

  lcdWrite(0b00110000,false);
  delay(5); // functionset by instruction

  lcdWrite(0b00110000,false);
  delayMicroseconds(150);

  lcdWrite(0b00110000,false);
  delayMicroseconds(150);

  lcdWrite(0b00111000,false);
  delayMicroseconds(100);

  lcdWrite(0b00001000,false); // display off
  delayMicroseconds(100);

  lcdWrite(0b00000001,false); // didsplay clear
  delay(2);

  lcdWrite(0b00000110,false); // entrymode : incre by 1
  delayMicroseconds(100);

  lcdWrite(0b00001100,false); //display on
  delayMicroseconds(100);
}

void loadTamilchar()
{
  // Custom 8 char using glyph code
  // fill ur required glyph code for custom char
const uint8_t glyph[8][8] = {
  {0x0f, 0x0a, 0x1f, 0x13, 0x1f, 0x03, 0x04, 0x08},  
  {0x07, 0x04, 0x17, 0x15, 0x15, 0x1f, 0x00, 0x00},  
  {0x04, 0x17, 0x15, 0x15, 0x1f, 0x04, 0x12, 0x0c},  
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
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
  }

}
void setup() 
{
  lcdinit();
  //const char message[] = " vaada mapula vala pazhaa thopula...vaada mapula vala pazhaa thopula";
 // writedata(message);
/*
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
*/

}

void loop() 
{

}
