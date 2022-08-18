#include "AHT10.h"

namespace AHT10
{

    Sensor::Sensor(I2C::HAL *i2cHAL, Platform::DelayFunction delayFn) : i2c_(i2cHAL), delay_(delayFn)
    {
    }

    void Sensor::initialize()
    {
        I2C::ByteVec data{0b11100001};
        i2c_->write(data);
    }

    Measurement::Result Sensor::measure()
    {
        uint8_t command = 0b10101100;
        I2C::ByteVec data{command, 0b00110011, 0};
        Measurement::Result result{0.0, 0.0, Measurement::MEASUREMENT_OK};

        auto writeStatus = i2c_->write(data);
        if (writeStatus != I2C::WRITE_OK)
        {
            result.status = Measurement::MEASUREMENT_ERROR;
            return result;
        }

        delay_(80);

        auto expectedLength = 6;
        auto readResult = i2c_->read(expectedLength);

        if (readResult.status != I2C::READ_OK)
        {
            result.status = Measurement::MEASUREMENT_ERROR;
            return result;
        }

        uint32_t sHumidity = readResult.data[1] << 16 | readResult.data[2] << 8 | readResult.data[3];
        sHumidity >>= 4;

        uint32_t sTemperature = (readResult.data[3] & 0b00001111) << 16 | readResult.data[4] << 8 | readResult.data[5];

        result.temperature = (sTemperature / 1048576.0) * 200 - 50;
        result.humidity = (sHumidity / 1048576.0) * 100;

        return result;
    }

    SensorStatus::SensorStatus(uint8_t statusByte) : statusByte_(statusByte) {}

    SensorWorkingMode SensorStatus::getWorkingMode()
    {
        uint8_t mask = 0b01100000;
        if (statusByte_ & mask == 0)
        {
            return WORKING_MODE_NOR;
        }

        if (statusByte_ & mask == 0b00100000)
        {
            return WORKING_MODE_CYC;
        }

        if (statusByte_ & mask == 0b01000000 || statusByte_ & mask == 0b01100000)
        {
            return WORKING_MODE_CMD;
        }

        return WORKING_MODE_UNKNOWN;
    }

    bool SensorStatus::isBusy()
    {
        return statusByte_ & 128 == 128;
    }

    bool SensorStatus::isCalibrationEnabled()
    {
        return statusByte_ & 8 == 8;
    }
}