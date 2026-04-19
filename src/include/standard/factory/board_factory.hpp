#ifndef STANDARD_BOARD_FACTORY_HPP
#define STANDARD_BOARD_FACTORY_HPP

#include <core/factory/board_factory.hpp>

namespace hal::standard
{
    class board_factory final : public core::board_factory
    {
      public:
        std::unique_ptr<core::board> make(const char *rom_path) override;
    };
}

#endif
