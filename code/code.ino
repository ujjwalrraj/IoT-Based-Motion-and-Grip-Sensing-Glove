#define LED 4
#include<Wire.h>
#define SDA_1 32
#define SCL_1 33

float RateRoll,RatePitch,RateYaw;
float AccX,AccY,AccZ;
float AngleRoll,AnglePitch;
int16_t GyroX,GyroY,GyroZ;

float RateRoll_2,RatePitch_2,RateYaw_2;
float AccX_2,AccY_2,AccZ_2;
float AngleRoll_2,AnglePitch_2;
int16_t GyroX_2,GyroY_2,GyroZ_2;

float angle=0;
TwoWire I2C_1 = TwoWire(1);
void setup() {
  pinMode(LED,OUTPUT);
 Serial.begin(57600); // WIRE_ORIGINAL GPIO21,22
  //pinMode(21,OUTPUT);
 // Wire.setClock(400000);
  
 // Wire.begin();
 // delay(200);
  //Wire.beginTransmission(0x68);
  //Wire.write(0x6B);
  W//ire.write(0x00);
 // Wire.endTransmission();
  I2C_1.begin(SDA_1 , SCL_1 ,400000 );
  I2C_1.begin();
  delay(200);
  I2C_1.beginTransmission(0x68);
   I2C_1.write(0x6B);
  I2C_1.write(0x00);
  I2C_1.endTransmission();
}

void loop() {

 // gyro_signals();
  gyro2_signals();
//  Serial.println(AccX);
//  Serial.println(AccY);
//  Serial.println(AccZ);
//   Serial.println(GyroX);
//  Serial.println(GyroY);
//  Serial.println(GyroZ);
//Serial.print("1: ");
//Serial.println(AngleRoll);
//Serial.println(AnglePitch);
//Serial.print("2: ");
//Serial.println(AnglePitch);
angle=AngleRoll_2-AngleRoll;
Serial.print("FINAL: ");
Serial.println(angle);
  delay(10);
  
}
void gyro_signals()
{
Wire.beginTransmission(0x68);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(0x68,14,true);
int16_t AccXLSB=Wire.read()<<8|
Wire.read();
int16_t AccYLSB=Wire.read()<<8|
Wire.read();
int16_t AccZLSB=Wire.read()<<8|
Wire.read();

 RateRoll=GyroX/65.5;
 RatePitch=GyroY/65.5;
RateYaw=GyroZ/65.5;
AccX=(float)AccXLSB/4096;
AccY=(float)AccYLSB/4096;
AccZ=(float)AccZLSB/4096;
AngleRoll= RAD_TO_DEG * (atan2(-AccY, -AccZ)+PI);

AngleRoll=atan(AccY/sqrt(AccX*AccX+AccZ*AccZ))*1/(3.142/180);
AnglePitch=-atan(AccX/sqrt(AccY*AccY+AccZ*AccZ))*1/(3.142/180);
}
void gyro2_signals()
{
  I2C_1.beginTransmission(0x68);
I2C_1.write(0x3B);
I2C_1.endTransmission(false);
I2C_1.requestFrom(0x68,14,true);
int16_t AccXLSB_2=I2C_1.read()<<8|
I2C_1.read();
int16_t AccYLSB_2=I2C_1.read()<<8|
I2C_1.read();
int16_t AccZLSB_2=I2C_1.read()<<8|
I2C_1.read();
  
AccX_2=(float)AccXLSB_2/4096;
AccY_2=(float)AccYLSB_2/4096;
AccZ_2=(float)AccZLSB_2/4096;
AngleRoll_2=atan(AccY_2/sqrt(AccX_2*AccX_2+AccZ_2*AccZ_2))*1/(3.142/180);
AnglePitch_2=-atan(AccX_2/sqrt(AccY_2*AccY_2+AccZ_2*AccZ_2))*1/(3.142/180);
}