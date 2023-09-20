#include <M5StickCPlus.h>
#include <buffer.h>
#define MIN_WIDTH (0.3)
#define WIDTH_UPDATE (100)

int step = 0;
float total = 0;
int count = 0;
float avg = 1.1;
float width = avg / 10;
boolean state = false;
boolean old_state = false;
Buffer buffer(100);

void setup()
{
  M5.begin();

  // Improve battery life.
  // M5.Axp.ScreenBreath(8);
  setCpuFrequencyMhz(10);

  // Display setting
  M5.Lcd.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(5);
  M5.Lcd.setTextColor(WHITE, BLACK);

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Step:\n");
  M5.Lcd.printf("0\n");
  // M5.Lcd.println("platform.io");

  // IMU & LED
  M5.IMU.Init();
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1);
  }
}

// Variables for step counter

void loop()
{
  // Accelerometer value for x,y,z axis.
  float accX = 0;
  float accY = 0;
  float accZ = 0;

  // Get accel.
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  float accel = sqrt(accX * accX + accY * accY + accZ * accZ);
  Serial.printf(">step:%d\n", step);
  Serial.printf(">avg:%f\n", avg);
  Serial.printf(">width:%f\n", width);
  Serial.printf(">total:%f\n", total);
  Serial.printf(">accel:%f\n", accel);
  Serial.printf(">accX:%f\n", accX);
  Serial.printf(">accY:%f\n", accY);
  Serial.printf(">accZ:%f\n", accZ);
  Serial.printf(">avg+width:%f\n", avg + width);

  // Calibration for average acceleration.
  buffer.push(accel);
  avg = buffer.average();
  count += 1;
  if (count >= WIDTH_UPDATE)
  {
    width = avg / 10;
    // width = width < MIN_WIDTH ? MIN_WIDTH : width;
    count = 0;
  }

  // When current accel. is ...
  if (accel > avg + width && accel > avg + (width * 2))
  {
    state = true;
  }
  else if (accel < avg - width && accel < avg - (width * 2))
  {
    state = false;
  }

  // Count up step.
  if (!old_state && state)
  {
    step += 1;
    digitalWrite(M5_LED, LOW); // led on

    // Display step
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Step:\n");
    M5.Lcd.printf("%5d\n", step);
  }
  else
  {
    digitalWrite(M5_LED, HIGH); // led off
  }
  old_state = state;

  delay(100);
}
