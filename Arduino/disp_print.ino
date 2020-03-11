// Подключение библиотек
#include <UTFT.h>
#include <URTouch.h>

// Определение максимальных и минимальных координат по осям X и Y
#define X_MIN 0
#define X_MAX 319
#define Y_MIN 0
#define Y_MAX 239

// Определение цвета фона
#define BC_R 0
#define BC_G 0
#define BC_B 0

// Определение цвета текста и кнопок
#define FC_R 255
#define FC_G 255
#define FC_B 0

// Создание объектов библиотечных классов
UTFT disp(TFT01_24SP,  9, 8, 12, 11, 10);
URTouch ts( 6, 5, 4, 3, 2);

// Используемый шрифт
extern uint8_t BigFont[];  

// Инициализация дисплея
void setup()
{
  Serial.begin(9600);
  
  disp.InitLCD(LANDSCAPE);
  disp.setFont(BigFont);
  disp.setBackColor(BC_R, BC_G, BC_B);
  disp.setColor(BC_R, BC_G, BC_B);
  disp.fillRect(X_MIN, Y_MIN, X_MAX, Y_MAX);
  
  ts.InitTouch(LANDSCAPE);
  ts.setPrecision(PREC_HI); 
}

void loop()
{
  printIC(FC_R, FC_G, FC_B);
  delay(2000);
  printIC(BC_R, BC_G, BC_B);
  delay(2000);

  printWFR(FC_R, FC_G, FC_B);
  delay(2000);
  printWFR(BC_R, BC_G, BC_B);
  delay(2000);

  printAG(FC_R, FC_G, FC_B);
  delay(2000);
  printAG(BC_R, BC_G, BC_B);
  delay(2000);

  printAD(FC_R, FC_G, FC_B);
  delay(2000);
  printAD(BC_R, BC_G, BC_B);
  delay(2000);

  printTRQ(FC_R, FC_G, FC_B);
  delay(2000);
  printTRQ(BC_R, BC_G, BC_B);
  delay(2000);

  printCBQ(FC_R, FC_G, FC_B, -1);
  delay(2000);
  printCBQ(BC_R, BC_G, BC_B, -1);
  delay(2000);
  printCBQ(FC_R, FC_G, FC_B, 0);
  delay(2000);
  printCBQ(BC_R, BC_G, BC_B, 0);
  delay(2000);

  printISM(FC_R, FC_G, FC_B);
  delay(2000);
  printISM(BC_R, BC_G, BC_B);
  delay(2000);

  printSSM(FC_R, FC_G, FC_B);
  delay(2000);
  printSSM(BC_R, BC_G, BC_B);
  delay(2000);

  printNCE(FC_R, FC_G, FC_B);
  delay(2000);
  printNCE(BC_R, BC_G, BC_B);
  delay(2000);

  printSCE(FC_R, FC_G, FC_B);
  delay(2000);
  printSCE(BC_R, BC_G, BC_B);
  delay(2000);

  printTRC(FC_R, FC_G, FC_B);
  delay(2000);
  printTRC(BC_R, BC_G, BC_B);
  delay(2000);
}

void printWFR(int r, int g, int b)
{
  disp.setColor(r, g, b);
  disp.print("WAITING", 103, 24);
  disp.print("FOR", 135, 84);
  disp.print("RFID", 127, 144);
}

void printAG(int r, int g, int b)
{
  disp.setColor(r, g, b);
  disp.print("ACCESS GRANTED", 47, 204);
}

void printAD(int r, int g, int b)
{
  disp.setColor(r, g, b);
  disp.print("ACCESS DENIED", 55, 204);
}

void printTRQ(int r, int g, int b)
{
  disp.setColor(r, g, b);
  
  disp.print("CHOOSE ACTION", 55, 7);
  
  disp.drawRoundRect(50, 40, 270, 90);
  disp.print("TAKE", 127, 57);

  disp.drawRoundRect(50, 110, 270, 160);
  disp.print("RETURN", 111, 127);

  disp.drawRoundRect(50, 180, 270, 230);
  disp.print("QUIT", 127, 197);
}

void printCBQ(int r, int g, int b, int superuser)
{
  disp.setColor(r, g, b);

  disp.print("CHOOSE CELL", 71, 7);

  disp.drawRoundRect(10, 40, 70, 100);
  disp.print("1", 32, 62);

  disp.drawRoundRect(90, 40, 150, 100);
  disp.print("2", 112, 62);

  disp.drawRoundRect(170, 40, 230, 100);
  disp.print("3", 192, 62);

  disp.drawRoundRect(250, 40, 310, 100);
  disp.print("4", 272, 62);

  disp.drawRoundRect(10, 120, 70, 180);
  disp.print("5", 32, 142);

  disp.drawRoundRect(90, 120, 150, 180);
  disp.print("6", 112, 142);

  disp.drawRoundRect(170, 120, 230, 180);
  disp.print("7", 192, 142);

  if (superuser >= 0)
  {
    disp.drawRoundRect(250, 120, 310, 180);
    disp.print("8", 272, 142);
  }

  disp.drawRoundRect(40, 200, 120, 230);
  disp.print("BACK", 48, 207);
  
  disp.drawRoundRect(200, 200, 280, 230);
  disp.print("QUIT", 208, 207);
}

void printIC(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("INITIALIZING", 63, 52);
  disp.print("COMPONENTS", 79, 172);
}

void printISM(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("IN", 143, 22);
  disp.print("SUPERUSER", 87, 82);
  disp.print("MODE", 127, 142);

  disp.drawRoundRect(100, 190, 220, 230);
  disp.print("QUIT", 127, 202);
}

void printNCE(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("NET", 135, 22);
  disp.print("CONNECTION", 79, 82);
  disp.print("ERROR", 119, 142);

  disp.drawRoundRect(10, 190, 310, 230);
  disp.print("LOGIN AS SUPERUSER", 15, 202);
}

void printSCE(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("SERVER", 111, 22);
  disp.print("CONNECTION", 79, 82);
  disp.print("ERROR", 119, 142);

  disp.drawRoundRect(10, 190, 310, 230);
  disp.print("LOGIN AS SUPERUSER", 15, 202);
}

void printSSM(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("SWITCH TO", 87, 22);
  disp.print("SUPERUSER", 87, 82);
  disp.print("MODE?", 119, 142);

  disp.drawRoundRect(50, 190, 150, 230);
  disp.print("YES", 76, 202);

  disp.drawRoundRect(170, 190, 270, 230);
  disp.print("NO", 204, 202);
}

void printTRC(int r, int g, int b)
{
  disp.setColor(r, g, b);

  disp.print("OPEN SELECTED CELL", 7, 15);
  disp.print("TAKE OR RETURN VALUE", 0, 60);
  disp.print("CLOSE CELL", 79, 105);
  disp.print("AND COMFIRM ACTION", 15, 150);

  disp.drawRoundRect(10, 190, 130, 230);
  disp.print("CONFIRM", 14, 202);

  disp.drawRoundRect(150, 190, 220, 230);
  disp.print("BACK", 153, 202);

  disp.drawRoundRect(240, 190, 310, 230);
  disp.print("QUIT", 243, 202);
}
