#ifndef RAM_HPP
#define RAM_HPP

#include "core/common/common.hpp"
#include <core/io/io.hpp>

#include <stdint.h>

namespace core
{
    class working_ram final : public io
    {
      public:
        uint8_t read(address target_address) override;
        void    write(address target_address, uint8_t data) override;

      private:
        uint8_t _ram[0x800];
    };
}

#endif
