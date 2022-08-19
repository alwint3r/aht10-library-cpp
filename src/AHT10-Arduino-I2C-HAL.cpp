#include "AHT10-Arduino-I2C-HAL.h"

#if defined(ARDUINO)

namespace AHT10
{
    namespace I2C
    {
        Arduino::Arduino(TwoWire *wire, uint8_t addr) : wire_(wire), addr_(addr) {}

        ReadResult Arduino::read(size_t size)
        {
            ReadResult result{ByteVec{}, READ_OK};
            auto received = wire_->requestFrom(addr_, size);

            if (received < size)
            {
                result.status = READ_INSUFFICIENT_DATA;
                return result;
            }

            result.data.reserve(received);

            for (auto i = 0; i < received; i++)
            {
                result.data.push_back(wire_->read());
            }

            return result;
        }

        WriteStatus Arduino::write(ByteVec data)
        {
            wire_->beginTransmission(addr_);
            wire_->write(data.data(), data.size());
            auto res = wire_->endTransmission();

            return translateWriteStatus(res);
        }

        WriteStatus Arduino::write(const uint8_t *data, size_t length)
        {
            Wire.beginTransmission(addr_);
            Wire.write(data, length);
            auto res = Wire.endTransmission();

            return translateWriteStatus(res);
        }

        WriteStatus Arduino::translateWriteStatus(int writeStatus)
        {
            if (writeStatus == 0)
            {
                return WRITE_OK;
            }

            if (writeStatus == 2)
            {
                return WRITE_FAILURE;
            }

            if (writeStatus == 5)
            {
                return WRITE_TIMEOUT;
            }

            return WRITE_ERROR_UNKNOWN;
        }
    }
}

#endif
