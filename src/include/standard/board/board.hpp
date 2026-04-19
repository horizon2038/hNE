#ifndef STANDARD_BOARD_BOARD_HPP
#define STANDARD_BOARD_BOARD_HPP

#include <core/board/board.hpp>
#include <core/cpu/cpu.hpp>

#include <memory>

namespace hal::standard
{
    class board final : public core::board
    {
      public:
        explicit board(std::unique_ptr<core::cpu> init_cpu);
        ~board() override;

        void run() override;

      private:
        std::unique_ptr<core::cpu> cpu;
    };
}

#endif
