#ifndef AHT10_I2C_HAL_INTERFACE_H
#define AHT10_I2C_HAL_INTERFACE_H

#include <cstdint>
#include <cstdlib>
#include <vector>

namespace AHT10
{
    namespace I2C
    {
        using ByteVec = std::vector<uint8_t>;

        enum WriteStatus
        {
            WRITE_OK,
            WRITE_FAILURE,
            WRITE_TIMEOUT,
            WRITE_ERROR_UNKNOWN,
        };

        enum ReadStatus
        {
            READ_OK,
            READ_INSUFFICIENT_DATA,
            READ_ERROR_UNKNOWN,
        };

        struct ReadResult
        {
            ByteVec data;
            ReadStatus status;
        };

        class HAL
        {
        public:
            HAL() {}
            virtual ~HAL() {}

            virtual ReadResult read(size_t size) = 0;
            virtual WriteStatus write(ByteVec data) = 0;
            virtual WriteStatus write(const uint8_t *data, size_t length) = 0;
        };
    }
}

#endif
