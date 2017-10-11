// 用 digitalRead() 函数测试 button 输入
const int buttonPin = A0;  // the button is connected to A0

// 8 个控制 LED 的 pin
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

uint8_t in_val;

void write_leds(uint8_t data)
{
  for(int i = 0; i < 8; i++)
    digitalWrite(ledPins[i], _BV(i) & data);
}

void setup() {
  //Serial.begin(9600);
  pinMode(buttonPin, INPUT);     // 连 button 的 pin 设置成输入模式
  digitalWrite(buttonPin, HIGH); // 使用内部上拉电阻

  for(int i = 0; i < 8; i++)
    pinMode(ledPins[i], OUTPUT); // 连 LED 的 pin 设置成输出模式

}

void loop() {
  in_val = digitalRead(buttonPin); // 读 A0 的状态，返回值: HIGH or LOW
  write_leds(in_val); // 输出到 LED 上
  //Serial.println(in_val, HEX); // 可以把 in_val 打印到串口查看
}
