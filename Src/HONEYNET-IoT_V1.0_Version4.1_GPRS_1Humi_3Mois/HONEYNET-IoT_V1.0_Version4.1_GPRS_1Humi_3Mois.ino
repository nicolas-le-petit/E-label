#include "App_config.h"
#include "App_Untils.h"

void reset_arduino()
{
  asm volatile ( "jmp 0");
}

void get_mac_address()
{
  // start system timer here
  timeout_init(timer_reset_arduino);
  Serial.println(F("AT+GSN"));
  while (!Serial.find("OK\r\n"))
  {
    delay(100);
    Serial.println(F("AT+GSN"));
    if (timeout_check(&timer_reset_arduino, 10000))
    {
      reset_arduino();
    }
  }

  delay(100);
  Flush_Serial();
  Serial.println(F("AT+GSN"));
  String read_data = Serial.readStringUntil("OK");
  read_data = read_data.substring(read_data.lastIndexOf('OK') - 20, read_data.lastIndexOf('OK') - 5);
  IMEI = read_data;
  read_data = read_data.substring(3);

  if (read_data.length() == 12)
  {
    String IMEI = read_data;
    String _mac;
    for (int i = 0; i < IMEI.length(); i++)
    {
      _mac = _mac + IMEI[i];
      if (((i + 1) % 2) == 0)
      {
        _mac = _mac + ':';
      }
    }
    _mac.remove(_mac.length() - 1);
    MAC = _mac;
  }
  else
  {
    reset_arduino();
  }
}

void get_ssn()
{
  // start system timer here
  timeout_init(timer_reset_arduino);
  Serial.println(F("AT+CCID"));
  while (!Serial.find("OK\r\n"))
  {
    delay(100);
    Serial.println(F("AT+CCID"));
    if (timeout_check(&timer_reset_arduino, 10000))
    {
      reset_arduino();
    }
  }

  delay(100);
  Flush_Serial();
  Serial.println(F("AT+CCID"));
  String read_ssn = Serial.readStringUntil("OK");
  read_ssn = read_ssn.substring(read_ssn.lastIndexOf('OK') - 25, read_ssn.lastIndexOf('OK') - 5);

  if (read_ssn.length() == 20)
  {
    SSN = read_ssn;
  }
  else
  {
    reset_arduino();
  }
}

void RestartSIM() {
#ifdef _DEBUG_
  mySerial.println(F("Restart SIM"));
#endif

  // Dam bao SIM da tat
  TurnOffSIM();

  // Bat dau khoi dong lai SIM
  digitalWrite(NRESET, HIGH);
  delay(1000);

  digitalWrite(PWRKEY, HIGH);
  delay(1000);
  digitalWrite(PWRKEY, LOW);

  // start system timer here
  timeout_init(timer_reset_arduino);
  // Cho de SIM khoi dong GPRS xong
  Serial.println("AT+CGATT?");
  while (!Serial.find("+CGATT: 1\r\n"))
  {
    delay(100);
    Serial.println("AT+CGATT?");
    if (timeout_check(&timer_reset_arduino, 60000))
    {
      reset_arduino();
    }
  }

  get_mac_address();
  delay(100);
  get_ssn();
}

void set_mode_gpio() {
  for (byte i = 0; i < sizeof(LIST_PIN_GPIO) / sizeof(byte); i++)
  {
    pinMode(LIST_PIN_GPIO[i], OUTPUT);
  }
}

boolean user_task_send_data()
{
  float humi = dht.readHumidity();
  delay(100);
  float temp = dht.readTemperature();
  delay(100);

  // Doc gia tri Sensor
  int value_adc2 = analogRead(ADC2);
  delay(100);
  int value_adc3 = analogRead(ADC3);
  delay(100);
  int value_adc4 = analogRead(ADC4);
  delay(100);
  float f_value_adc2 =  100 - (value_adc2 / 1023.0) * 100;
  float f_value_adc3 =  100 - (value_adc3 / 1023.0) * 100;
  float f_value_adc4 =  100 - (value_adc4 / 1023.0) * 100;

  if (isnan(humi) == 0 && isnan(temp) == 0)
  {
    String s_data = "\"humi1\":\"" + (String)humi + "\",\"temp1\":\"" + (String)temp + "\",\"mois1\":\"" + (String)f_value_adc2 + "\",\"mois2\":\"" + (String)f_value_adc3 + "\",\"mois3\":\"" + (String)f_value_adc4 + "\"";
    return send_data_to_cloud(s_data);
  }
  else
  {
    String s_data = "\"mois1\":\"" + (String)f_value_adc2 + "\",\"mois2\":\"" + (String)f_value_adc3 + "\",\"mois3\":\"" + (String)f_value_adc4 + "\"";
    return send_data_to_cloud(s_data);
  }

  blink_led();
}

void check_input_digital()
{
  int flag_input_changed = 0;
  int LIST_VALUES_INPUT_LAST[] = {0, 0, 0, 0};
  for (byte i = 0; i < sizeof(LIST_VALUES_INPUT) / sizeof(int); i++)
  {
    if (LIST_VALUES_INPUT[i] != digitalRead(LIST_PIN_INPUT[i]))
    {
      flag_input_changed = 1;
    }
    LIST_VALUES_INPUT_LAST[i] = digitalRead(LIST_PIN_INPUT[i]);
  }

  if (flag_input_changed == 1)
  {
    if (user_task_update_info("\"in_val\":[" + (String)LIST_VALUES_INPUT_LAST[0] + "," + (String)LIST_VALUES_INPUT_LAST[1] + "," + (String)LIST_VALUES_INPUT_LAST[2] + "," + (String)LIST_VALUES_INPUT_LAST[3] + "]"))
    {
      for (byte i = 0; i < sizeof(LIST_VALUES_INPUT) / sizeof(int); i++)
      {
        LIST_VALUES_INPUT[i] = LIST_VALUES_INPUT_LAST[i];
      }
    }
  }
}

void setup()
{
#ifdef _DEBUG_
  mySerial.begin(115200);
  mySerial.println(F("setup init"));
#endif

  // Input Sensor analog
  pinMode(ADC2, INPUT);
  pinMode(ADC3, INPUT);
  pinMode(ADC4, INPUT);

  // Set mode Input digital
  for (byte i = 0; i < sizeof(LIST_PIN_INPUT) / sizeof(byte); i++)
  {
    pinMode(LIST_PIN_INPUT[i], INPUT_PULLUP);
  }

  // LED bao trang thai
  pinMode(RS2, OUTPUT);
  digitalWrite(RS2, HIGH);
  delay(3000);
  digitalWrite(RS2, LOW);

  Serial.begin(9600);
  // Serial.setTimeout(5000);

  // Dieu khien SIM
  pinMode(NRESET, OUTPUT);
  pinMode(PWRKEY, OUTPUT);

  set_mode_gpio();
}

void blink_led()
{
  delay(50);
  digitalWrite(RS2, LOW);
  delay(50);
  digitalWrite(RS2, HIGH);
  delay(50);
  digitalWrite(RS2, LOW);
  delay(50);
  digitalWrite(RS2, HIGH);
  delay(50);
  digitalWrite(RS2, LOW);
  delay(50);
  digitalWrite(RS2, HIGH);
}

void run_gpio(byte pin_gpio, byte status_gpio) {
  digitalWrite(pin_gpio, status_gpio);
}

boolean user_task_update_info(String str_data)
{
  Flush_Serial();

  Serial.println("AT+CIPCLOSE");
  Serial.find("ERROR\r\n");

  Serial.println(F("AT+CIPSTART=\"TCP\",\"ais.honeynet.vn\",\"5100\""));//start up the connection
  if (!Serial_Wait_For_Resp("CONNECT OK\r\n", CMD, DEFAULT_TIMEOUT, DEFAULT_INTERCHAR_TIMEOUT))
  {
    return false;
  }

  String s_data = MAC + "[]UpdateInfo-{" + str_data + "}";
  // String s_data = MAC + "[]UpdateInfo-{\"ssn\":\"" + SSN + "\",\"imei\":\"" + IMEI + "\"}";
  delay(100);
  Flush_Serial();
  Serial.println("AT+CIPSEND");
  Serial.find("> ");

  Serial.print(s_data);
  Serial.print("");
  Serial.println((char)26);
  if (!Serial_Wait_For_Resp("SEND OK", CMD, DEFAULT_TIMEOUT, DEFAULT_INTERCHAR_TIMEOUT))
  {
    return false;
  }

#ifdef _DEBUG_
  mySerial.println(s_data);
#endif

  Serial.println("AT+CIPCLOSE");
  Serial.find("CLOSE OK\r\n");

  blink_led();
  return true;
}

boolean user_task_control_gpio() {
  Flush_Serial();
  check_input_digital();

  Serial.println("AT+CIPCLOSE");
  Serial.find("ERROR\r\n");

  Serial.println(F("AT+CIPSTART=\"TCP\",\"ais.honeynet.vn\",\"5100\""));//start up the connection
  if (!Serial_Wait_For_Resp("CONNECT OK\r\n", CMD, DEFAULT_TIMEOUT, DEFAULT_INTERCHAR_TIMEOUT))
  {
    return false;
  }

  String s_data = MAC + "[]CtrlGPIO";

  //  delay(100);
  Flush_Serial();
  Serial.println("AT+CIPSEND");
  Serial.find("> ");
  // delay(1000);

  Serial.print(s_data);
  Serial.print("");
  Serial.println((char)26);
  String read_data = Serial.readStringUntil('}');
  String _json_control = read_data.substring(read_data.indexOf('{'), read_data.lastIndexOf(']') + 1);
  _json_control += '}';


#ifdef _DEBUG_
  mySerial.print(F("_json_control:"));
  mySerial.println(_json_control);
#endif

  Serial.println("AT+CIPCLOSE");
  Serial.find("CLOSE OK\r\n");

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(_json_control);
  if (!root.success()) {
#ifdef _DEBUG_
    mySerial.println(F("parseObject() failed)"));
#endif
    // by pass
    return true;
  }
  uint32_t _interval = root["interval"];
  INTERVAL = _interval * 1000;

  int element_gpio = root["gpio"].size();
  if (element_gpio > 0)
  {
#ifdef _DEBUG_
    mySerial.print(F("element_gpio:"));
    mySerial.println(String(element_gpio));
#endif

    for (byte i = 0; i < element_gpio; i++)
    {
      // Kiểm tra để tránh trường hợp số lượng GPIO truyền vào không đúng số lượng GPIO của thiết bị
      if (i < sizeof(LIST_PIN_GPIO) / sizeof(byte))
      {
        run_gpio(LIST_PIN_GPIO[i], root["gpio"][i]);
      }
    }
  }

  blink_led();
  return true;
}

void TurnOffSIM() {
  digitalWrite(NRESET, LOW);
  digitalWrite(PWRKEY, HIGH);
  delay(1500);
}

void Flush_Serial()
{
  while (Serial.available()) {
    Serial.read();
  }
}

boolean Serial_Wait_For_Resp(const char* resp, int type, unsigned int timeout, unsigned int chartimeout)
{
  int len = strlen(resp);
  int sum = 0;
  unsigned long timerStart, prevChar;    //prevChar is the time when the previous Char has been read.
  timerStart = millis();
  prevChar = 0;
  while (1) {
    delay(1);
    if (Serial.available()) {
      char c = Serial.read();
      prevChar = millis();
      sum = (c == resp[sum]) ? sum + 1 : 0;
      if (sum == len)break;
    }
    // Thời gian timeout để hàm này chạy
    if ((unsigned long) (millis() - timerStart) > timeout * 1000UL) {
      //          mySerial.print("Ham da chay het thoi gian:");
      //          Print_Char(resp);
      // delay(3000);
      return false;
    }
    // If interchar Timeout => return FALSE. So we can return sooner from this function.
    // Thoi gian timeout giua
    if (((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)) {
      //          mySerial.print("Het thoi gian cho nhan giua 2 ky tu:");
      //          Print_Char(resp);
      // delay(3000);
      return false;
    }
  }
  //If is a CMD, we will finish to read buffer.
  if (type == CMD) Flush_Serial();
  //    mySerial.print("Da tim ra chuoi:");
  //    Print_Char(resp);
  // delay(3000);
  return true;
}

//    "humi1":"54.49","temp1":"55.55","mois1":"345"
boolean send_data_to_cloud(String sensor_data)
{
  Flush_Serial();

  Serial.println("AT+CIPCLOSE");
  Serial.find("ERROR\r\n");

  Serial.println(F("AT+CIPSTART=\"TCP\",\"ais.honeynet.vn\",\"5100\""));//start up the connection
  if (!Serial_Wait_For_Resp("CONNECT OK\r\n", CMD, DEFAULT_TIMEOUT, DEFAULT_INTERCHAR_TIMEOUT))
  {
    return false;
  }


  String s_data = MAC + "[]Insertsensor-{\"sensor\":{" + sensor_data + "}}";
  delay(100);
  Flush_Serial();
  Serial.println("AT+CIPSEND");
  Serial.find("> ");
  // delay(1000);

  Serial.print(s_data);
  Serial.print("");
  Serial.println((char)26);
  if (!Serial_Wait_For_Resp("SEND OK", CMD, DEFAULT_TIMEOUT, DEFAULT_INTERCHAR_TIMEOUT))
  {
    return false;
  }

#ifdef _DEBUG_
  mySerial.println(s_data);
#endif

  Serial.println("AT+CIPCLOSE");
  Serial.find("CLOSE OK\r\n");

  return true;
}

String getSerialData()
{
  String input;
  while (Serial.available())
  {
    input = Serial.readString();
  }
  return input;
}

// Lưu chuỗi vào EEPROM từ ô nhớ from đến ô nhớ to: Chiều dài chuỗi = from - to + 1
// Ví dụ: Lưu chuỗi 123456789, chuỗi có 9 ký tự.
// Nếu chọn ô nhớ 0 là vị trí bắt đầu thì vị trí ô nhớ kết thúc sẽ là 8
// Nếu chọn ô nhớ 1 là vị trí bắt đầu thì vị trí ô nhớ kết thúc sẽ là 9
void save_to_EEPROM(String s, byte from, byte to) {
  // Khai báo mảng byte buf với size = chiều dài + 1(chứa thêm ký tự \0 khi dùng hàm getBytes)
  byte buf[to - from + 2];
  s.getBytes(buf, to - from + 2);
  for (byte i = from; i <= to; i++) {
    delay(5);
    EEPROM.update(i, buf[i - from]);
  }
}

// Đọc giá trị từ ô nhớ from đến ô nhớ to trong EEPROM, sau đó trả về một chuỗi
String read_from_EEPROM(byte from, byte to)
{
  String tmp;
  for (byte i = from; i <= to; i++) {
    delay(5);
    tmp += (char) EEPROM.read(i);
  }
  return tmp;
}

void loop()
{
  // Bat dau khoi dong lai SIM
  RestartSIM();

  // On LED
  digitalWrite(RS2, HIGH);

#ifdef _DEBUG_
  mySerial.println(F("BAT DAU VONG LAP"));
  mySerial.print(F("IMEI:")); mySerial.println(IMEI);
  mySerial.print(F("MAC:")); mySerial.println(MAC);
  mySerial.print(F("SSN:")); mySerial.println(SSN);
#endif

  // start system timer here
  timeout_init(timer_control_gpio);
  timeout_init(timer_update_info);
  timeout_init(timer_send_data);
#ifdef _DEBUG_
  mySerial.println(F("System timer init!"));
#endif

  // Control & Send data on start
  user_task_update_info("\"ssn\":\"" + SSN + "\",\"imei\":\"" + IMEI + "\"");
  user_task_control_gpio();
  user_task_send_data();

  while (1)
  {
    // Every 1000ms
    if (timeout_check(&timer_control_gpio, 1000))
    {
#ifdef _DEBUG_
      mySerial.print(F("INTERVAL:"));
      mySerial.println((String)INTERVAL);
#endif
      if (!user_task_control_gpio())
      {
        break;
      }
    }

    // Every INTERVAL * 2
    if (timeout_check(&timer_update_info, INTERVAL * 2))
    {
      if (!user_task_update_info("\"ssn\":\"" + SSN + "\",\"imei\":\"" + IMEI + "\""))
      {
        break;
      }
    }

    // interval_send_data giay
    if (timeout_check(&timer_send_data, INTERVAL))
    {
      if (!user_task_send_data())
      {
        break;
      }
    }
  }
}
