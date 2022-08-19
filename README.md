# AHT10 Temperature & Humidity Sensor C++ Library

## Stability

This library is still in early stage. Expect breaking changes until further notice.


## Usage

Arduino

```c++
#include <Arduino.h>
#include <Wire.h>
#include <AHT10.h>
#include <AHT10-Arduino-I2C-HAL.h>

static constexpr auto SENSOR_ADDR = 0x38;

AHT10::I2C::Arduino i2cHAL(&Wire, SENSOR_ADDR);
AHT10::Sensor sensor(&i2cHAL, delay);

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    delay(3000);

    sensor.initialize();
    delay(100);
}

void loop()
{
    auto res = sensor.measure();
    if (res.isOk())
    {
        if (res.sensorStatus.isBusy())
        {
            Serial.println("Sensor is busy!");
        }

        Serial.print("Temperature: ");
        Serial.print(res.temperature);
        Serial.print(", Humidity: ");
        Serial.println(res.humidity);
    }
    delay(1000);
}
```