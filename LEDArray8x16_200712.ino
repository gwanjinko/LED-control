#include <LedControl.h>

/* 설정 */
int intensity = 0; // LED 밝기 0~15
int animationSpeed = 10; // 애니메이션 속도 0~15
int animationRestartTimeInterval = 1000; // 애니메이션 완료 후 재시작 시간 (단위: ms)
bool ledAllOn = true; // 1. 모든 LED 켜기
bool isAnimation = false; // 2. 애니메이션 모드
int snapshotNumber = 0; // 3. (1,2가 false일 때) 애니메이션 내에서 고정할 이미지 선택 (0~26) "  KU-KIST  PLCL  123456789  "

/* 폰트 */
const byte FONTS[][8] = {
{
  B00000000,
  B11100100,
  B10010100,
  B11100100,
  B10000100,
  B10000100,
  B10000111,
  B00000000
},{
  B00000000,
  B01100100,
  B10010100,
  B10000100,
  B10000100,
  B10010100,
  B01100111,
  B00000000
},{
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00001100,
  B00110000,
  B01100000,
  B01111110
},{
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00011100,
  B00000110,
  B01100110,
  B00111100
},{
  B00000000,
  B00001100,
  B00011100,
  B00101100,
  B01001100,
  B01111110,
  B00001100,
  B00001100
},{
  B00000000,
  B01111110,
  B01100000,
  B01111100,
  B00000110,
  B00000110,
  B01100110,
  B00111100
},{
  B00000000,
  B00111100,
  B01100110,
  B01100000,
  B01111100,
  B01100110,
  B01100110,
  B00111100
},{
  B00000000,
  B01111110,
  B01100110,
  B00001100,
  B00001100,
  B00011000,
  B00011000,
  B00011000
},{
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B00111100,
  B01100110,
  B01100110,
  B00111100
},{
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B00111110,
  B00000110,
  B01100110,
  B00111100
},{
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B01111110,
  B01100110,
  B01100110,
  B01100110
},{
  B00000000,
  B01111100,
  B01100110,
  B01100110,
  B01111100,
  B01100110,
  B01100110,
  B01111100
},{
  B00000000,
  B00111100,
  B01100110,
  B01100000,
  B01100000,
  B01100000,
  B01100110,
  B00111100
},{
  B00000000,
  B01111100,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01111100
},{
  B00000000,
  B01111110,
  B01100000,
  B01100000,
  B01111100,
  B01100000,
  B01100000,
  B01111110
},{
  B00000000,
  B01111110,
  B01100000,
  B01100000,
  B01111100,
  B01100000,
  B01100000,
  B01100000
},{
  B00000000,
  B00111100,
  B01100110,
  B01100000,
  B01100000,
  B01101110,
  B01100110,
  B00111100
},{
  B00000000,
  B01100110,
  B01100110,
  B01100110,
  B01111110,
  B01100110,
  B01100110,
  B01100110
},{
  B00000000,
  B00111100,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00111100
},{
  B00000000,
  B00011110,
  B00001100,
  B00001100,
  B00001100,
  B01101100,
  B01101100,
  B00111000
},{
  B00000000,
  B01100110,
  B01101100,
  B01111000,
  B01110000,
  B01111000,
  B01101100,
  B01100110
},{
  B00000000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01111111,
  B01111111
},{
  B00000000,
  B01100011,
  B01110111,
  B01111111,
  B01101011,
  B01100011,
  B01100011,
  B01100011
},{
  B00000000,
  B01100011,
  B01110011,
  B01111011,
  B01101111,
  B01100111,
  B01100011,
  B01100011
},{
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B00111100
},{
  B00000000,
  B01111100,
  B01100110,
  B01100110,
  B01100110,
  B01111100,
  B01100000,
  B01100000
},{
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B01100110,
  B01101110,
  B00111100,
  B00000110
},{
  B00000000,
  B01111100,
  B01100110,
  B01100110,
  B01111100,
  B01111000,
  B01101100,
  B01100110
},{
  B00000000,
  B00111100,
  B01100110,
  B01100000,
  B00111100,
  B00000110,
  B01100110,
  B00111100
},{
  B00000000,
  B01111110,
  B01011010,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000
},{
  B00000000,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B00111100
},{
  B00000000,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B00111100,
  B00011000
},{
  B00000000,
  B01100011,
  B01100011,
  B01100011,
  B01101011,
  B01111111,
  B01110111,
  B01100011
},{
  B00000000,
  B01100011,
  B01100011,
  B00110110,
  B00011100,
  B00110110,
  B01100011,
  B01100011
},{
  B00000000,
  B01100110,
  B01100110,
  B01100110,
  B00111100,
  B00011000,
  B00011000,
  B00011000
},{
  B00000000,
  B01111110,
  B00000110,
  B00001100,
  B00011000,
  B00110000,
  B01100000,
  B01111110
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000
},{
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111
}};

enum e_font_index {
    FONT_0,
    FONT_1,
    FONT_2,
    FONT_3,
    FONT_4,
    FONT_5,
    FONT_6,
    FONT_7,
    FONT_8,
    FONT_9,
    FONT_A,
    FONT_B,
    FONT_C,
    FONT_D,
    FONT_E,
    FONT_F,
    FONT_G,
    FONT_H,
    FONT_I,
    FONT_J,
    FONT_K,
    FONT_L,
    FONT_M,
    FONT_N,
    FONT_O,
    FONT_P,
    FONT_Q,
    FONT_R,
    FONT_S,
    FONT_T,
    FONT_U,
    FONT_V,
    FONT_W,
    FONT_X,
    FONT_Y,
    FONT_Z,
    FONT_MINUS,
    FONT_BLANK,
    FONT_HEART,
    FONT_ALL,
};

/* 회로 */
const int DIN_PIN = 7;
const int CS_PIN = 6;
const int CLK_PIN = 5;

/* 상수 */
const int numOfDevices = 2;
const int addressRight8x8 = 0;
const int addressLeft8x8 = 1;

/* 애니메이션 순서 */
int animationMessage[] = {
  FONT_BLANK,
  FONT_BLANK,
  FONT_K,
  FONT_U,
  FONT_MINUS,
  FONT_K,
  FONT_I,
  FONT_S,
  FONT_T,
  FONT_BLANK,
  FONT_BLANK,
  FONT_P,
  FONT_L,
  FONT_C,
  FONT_L,
  FONT_BLANK,
  FONT_BLANK,
  FONT_1,
  FONT_2,
  FONT_3,
  FONT_4,
  FONT_5,
  FONT_6,
  FONT_7,
  FONT_8,
  FONT_9,
  FONT_BLANK,
  FONT_BLANK,
};

const int ANIMATION_LEN = sizeof(animationMessage)/sizeof(enum e_font_index);

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, numOfDevices);

void setup() 
{
 if(intensity <0)
 {
  intensity = 0; 
 } else if(intensity > 15)
 {
  intensity = 15;
 }
 
 if(animationSpeed <0)
 {
  animationSpeed = 0; 
 } else if(intensity > 15)
 {
  animationSpeed = 15;
 }
 
 for(int num = 0; num < numOfDevices; num++)
  {
   lc.shutdown(num,false);
   lc.setIntensity(num,intensity);
   lc.clearDisplay(num);
  }
}
 
void loop() 
{
  byte buffer1[numOfDevices+1][8];
  if(ledAllOn)
  {
    /* 1. LED 전체 켜기 모드 */
    for (int i = 0; i < 8; i++) 
    {
      lc.setRow(addressLeft8x8, i, FONTS[FONT_ALL][i]);
      lc.setRow(addressRight8x8, i, FONTS[FONT_ALL][i]);
    }
  }
  else if(isAnimation)
  {
    /* 2. 이미지 스크롤 모드 */
    for (int i = 0; i < numOfDevices; i++)
    {
      for (int j = 0; j < 8; j++) 
      {
        buffer1[i][j] = B00000000;
      }
    }
    for (int i = 0; i < ANIMATION_LEN; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        buffer1[numOfDevices][j] = FONTS[animationMessage[i]][j];
      }
      for (int j = 0; j < 8; j++)
      {
        for (int k = 0; k < 8; k++)
        {
          buffer1[0][k] = (buffer1[0][k] << 1) | (buffer1[1][k] >> 7);
          buffer1[1][k] = (buffer1[1][k] << 1) | (buffer1[2][k] >> 7);
          buffer1[2][k] = (buffer1[2][k] << 1);
        }
        for (int i = 0; i < 8; i++) 
        {
          lc.setRow(addressLeft8x8, i, buffer1[0][i]);
          lc.setRow(addressRight8x8, i, buffer1[1][i]);
        }
        delay(300 - 19 * animationSpeed);
      }
    }
    delay(animationRestartTimeInterval);
  }
  else
  {
    /* 3. 정지 이미지 출력 모드 */
    if(snapshotNumber < 0)
      snapshotNumber = 0;
    else if(snapshotNumber > ANIMATION_LEN - 2)
      snapshotNumber = ANIMATION_LEN - 2;

    for (int i = 0; i < 8; i++) 
    {
      lc.setRow(addressLeft8x8, i, FONTS[snapshotNumber][i]);
      lc.setRow(addressRight8x8, i, FONTS[snapshotNumber + 1][i]);
    }
  }
}
