#ifndef AHT10_ARDUINO_I2C_HAL_H
#define AHT10_ARDUINO_i2C_HAL_H

#if defined(ARDUINO)

#include <Arduino.h>
#include <Wire.h>
#include "interfaces/AHT10-I2C-HAL.h"

namespace AHT10
{
    namespace I2C
    {
        class Arduino : public HAL {
        public:
            Arduino(TwoWire *wire, uint8_t address);
            virtual ~Arduino() {}

            virtual ReadResult read(size_t size);
            virtual WriteStatus write(ByteVec data);
            virtual WriteStatus write(const uint8_t *data, size_t length);
        private:
            WriteStatus translateWriteStatus(int writeStatus);
        private:
            TwoWire *wire_;
            uint8_t addr_;
        };
    } // namespace I2C

} // namespace AHT10

#endif

#endif
