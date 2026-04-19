#ifndef IO_HPP
#define IO_HPP

#include <stdint.h>
#include <core/common/common.hpp>

namespace core
{
    class io
    {
      public:
        virtual ~io() {};
        virtual uint8_t read(address target_address) = 0;
        virtual void write(address target_address, uint8_t data) = 0;
        virtual void tick()
        {
        }
        virtual bool poll_nmi()
        {
            return false;
        }
    };

}

#endif
