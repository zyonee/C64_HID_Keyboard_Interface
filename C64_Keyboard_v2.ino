int inChar=0;
int keyPos=0;
int digitalread=0;
int keyDown[65];
long lastDebounceTime[65];
int shifted[65];
int debounceDelay=50;
int ckey=127;
int RESTORE=127;
int shift=0;
int outPin=2;
int i;
int windowsShift;

char keyMap[192]={
49,178,128,177,32,135,113,50, //   1 BS CTRL RS SPC C= Q 2
51,119,97,129,122,115,101,52,//  3 W A LSHFT Z S E 4
53,114,100,120,99,102,116,54,  // 5 R D X C F T 6
55,121,103,118,98,104,117,56,  // 7 Y G V B H U 8
57,105,106,110,109,107,111,48,  // 9 I J N M K O 0
43,112,108,44,46,58,34,45,  // + P L , . : @ -
35,42,59,47,133,61,211,210,//£ * ; / RSHFT = Pi Home
212,176,215,217,194,196,198,200, // Del Return LR UD F1 F3 F5 F7

33,178,128,177,32,135,81,64, //   ! BS CTRL RS SPC C= Q "
92,87,65,129,90,83,69,36,//  # W A LSHFT Z S E $
37,82,68,88,67,70,84,38,  // % R D X C F T &
39,89,71,86,66,72,85,40,  // ' Y G V B H U (
41,73,74,78,77,75,79,48,  // ) I J N M K O 0
43,80,76,60,62,91,96,95,  // + P L < > : @ -
35,42,93,63,133,61,214,210,//£ * ; ? RSHFT = Pi Home
209,176,216,218,195,197,199,201, // Del Return LR UD F2 F4 F6 F8

49,223,9,177,32,128,113,50, //   1 BS CTRL RS SPC C= Q 2
51,119,97,129,122,115,101,52,//  3 W A LSHFT Z S E 4
53,114,100,120,99,102,116,54,  // 5 R D X C F T 6
55,121,103,118,98,104,117,56,  // 7 Y G V B H U 8
57,105,106,110,109,107,111,48,  // 9 I J N M K O 0
45,112,108,44,46,59,91,61,  // + P L , . : @ -
209,93,39,47,133,92,212,210,//£ * ; / RSHFT = Pi Home
178,176,215,217,194,196,198,200, // Del Return LR UD F1 F3 F5 F7
};

void setup() {
  // open the serial port:
   Serial.begin(9600);
  // initialize control over the keyboard:
  Keyboard.begin();

  for (i=0; i<64; i++) keyDown[i]=0;


  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

  pinMode(0,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(16,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);
  pinMode(14,INPUT_PULLUP);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);

  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);

  if (!digitalRead(10)) windowsShift=1; else windowsShift=0;
}

void loop() {

  for (outPin=2;outPin<10; outPin++)
    {
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    pinMode(4,INPUT);
    pinMode(5,INPUT);
    pinMode(6,INPUT);
    pinMode(7,INPUT);
    pinMode(8,INPUT);
    pinMode(9,INPUT);

    pinMode(outPin,OUTPUT);
    digitalWrite(outPin,LOW);
    for (i=0; i<8; i++)
      {
      keyPos=i+((outPin-2)*8);
      if (!windowsShift) inChar=keyMap[keyPos+shift];
       else inChar=keyMap[keyPos+128];
      if (i==0) digitalread=1-digitalRead(10);
      if (i==1) digitalread=1-digitalRead(16);
      if (i==2) digitalread=1-digitalRead(14);
      if (i==3) digitalread=1-digitalRead(15);
      if (i==4) digitalread=1-digitalRead(A0);
      if (i==5) digitalread=1-digitalRead(A1);
      if (i==6) digitalread=1-digitalRead(A2);
      if (i==7) digitalread=1-digitalRead(A3);


   if ((millis()-lastDebounceTime[keyPos])>debounceDelay)
   {
      if (digitalread==1 && keyDown[keyPos]==0)
        {
        keyDown[keyPos]=inChar;
        if ((keyPos!=11&&keyPos!=52)||windowsShift==1)
          {
          lastDebounceTime[keyPos] = millis();
          Keyboard.press(keyDown[keyPos]);
          }
          else { lastDebounceTime[keyPos]=millis(); shift=64; }
        }
      if (digitalread==0 && keyDown[keyPos]!=0)
        {
        if ((keyPos!=11&&keyPos!=52)||windowsShift==1)
          {
          lastDebounceTime[keyPos] = millis();
          Keyboard.release(keyDown[keyPos]);
          }
          else { lastDebounceTime[keyPos]=millis(); shift=0; }
        keyDown[keyPos]=0;
        }
     }
    }
    digitalWrite(outPin,HIGH);
    }
  if (digitalRead(0)==0&&keyDown[65]==0)
    {
    Keyboard.press(RESTORE);
    keyDown[65]=RESTORE;
    }
  if (digitalRead(0)==1&&keyDown[65]==RESTORE)
    {
    keyDown[65]=0;
    Keyboard.release(RESTORE);
    }
}
