#ifndef AHT10_SENSOR_H
#define AHT10_SENSOR_H

#include "interfaces/AHT10-I2C-HAL.h"
#include "interfaces/AHT10-Delay-HAL.h"

namespace AHT10
{
    enum SensorWorkingMode
    {
        WORKING_MODE_NOR,
        WORKING_MODE_CYC,
        WORKING_MODE_CMD,
        WORKING_MODE_UNKNOWN,
    };

    class SensorStatus
    {
    public:
        SensorStatus(uint8_t statusByte);

        bool isBusy();

        SensorWorkingMode getWorkingMode();

        bool isCalibrationEnabled();
    private:
        uint8_t statusByte_;
    };
    namespace Measurement
    {
        enum Status
        {
            MEASUREMENT_OK,
            MEASUREMENT_ERROR,
        };

        struct Result
        {
            double temperature;
            double humidity;
            Status status;
            SensorStatus sensorStatus;

            bool isOk()
            {
                return status == MEASUREMENT_OK;
            }
        };
    } // namespace Measurement

    class Sensor
    {
    public:
        Sensor(AHT10::I2C::HAL *i2cHAL, AHT10::Platform::DelayFunction delayFn);
        virtual ~Sensor() {}

        void initialize();
        void reset();
        Measurement::Result measure();

    private:
        AHT10::I2C::HAL *i2c_;
        AHT10::Platform::DelayFunction delay_;
    };
} // namespace AHT10

#endif