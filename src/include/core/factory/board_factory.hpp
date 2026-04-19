#ifndef CORE_FACTORY_BOARD_FACTORY_HPP
#define CORE_FACTORY_BOARD_FACTORY_HPP

#include <core/board/board.hpp>

#include <memory>

namespace core
{
    class board_factory
    {
      public:
        virtual ~board_factory() {};
        virtual std::unique_ptr<board> make(const char *rom_path) = 0;
    };
}

#endif
