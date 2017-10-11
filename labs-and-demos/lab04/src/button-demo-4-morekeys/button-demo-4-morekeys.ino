// 用延时的方法去除抖动

const int button1Pin = A0;
const int button2Pin = A1;

// 8 个控制 LED 的 pin
const int ledPins[] = {2, 3 ,4, 5, 6, 7, 8, 9};

void setup()
{
  Serial.begin(9600);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

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

byte in_val;
byte in_val2;
int buttonState; // 用来保存按键状态的变量
byte count = 0;

void loop() {

  in_val = digitalRead(button1Pin) + (digitalRead(button2Pin) << 1); // 2 个键的读取值组合到一个字节中 <1>
  delay(10); // 延时 10 ms, 跳过抖动区
  in_val2 = digitalRead(button1Pin) + (digitalRead(button2Pin) << 1);

  if (in_val == in_val2) // 相隔 10ms, 两次读到的值是一样的！
  {
    if (in_val != buttonState) // 按键的状态发生了变化(和上次不一样)
    {

      if (in_val == 0b00000010) // 最低一位是 0, 说明 button1 被按下了
      {
        count++;  // 有键按下了, count 自增 1
        if (count >= 15) count = 15;  // 不超过 15
      }

      if (in_val == 0b00000001) // 第 2 位是 0, 说明 button2 被按下了
      {
        if (count > 0) count--; // 大于 0 才自减 1，否则会溢出
      }

    }

    buttonState = in_val2; // 把按键新的状态保存起来，下个循环要用到
  }

  write_leds(count); // 显示

  //Serial.println(in_val, HEX); // 可以打印到串口观察数值
}

