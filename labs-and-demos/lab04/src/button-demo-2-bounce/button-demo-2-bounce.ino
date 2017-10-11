// 实验: 按一下键，数字加 1

// 8 个控制 LED 的 pin
const int ledPins[] = {2, 3 ,4, 5, 6, 7, 8, 9};

const int buttonPin1 = A0; // 这个实验只用一个键
const int buttonPin2 = 12;
const int buttonPin3 = 11;
const int buttonPin4 = 10;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);

  for(int i = 0; i < 8; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
}

void write_leds(uint8_t data)
{
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(ledPins[i], _BV(i) & data);
  }
}

uint8_t in_val;    // 用来存键值
uint8_t count = 0;

void loop() {

  // 如果键没有被按下，则程序一直停在此处，处于等待状态，不往下走
  while ( digitalRead(buttonPin1) == HIGH ) ; // <1>

  count++;  // 有键按下了, count 自增 1
  if (count > 15) count = 0;  // 做越界处理，超过 15 了回到 0，因为我们只用 4 个 LED

  // 如果键被按下但未松开，则程序一直停在此处，不往下走
  while ( digitalRead(buttonPin1) == LOW) ;

  write_leds(count); // 松开按键后更新显示
  Serial.println(in_val, HEX);
}

