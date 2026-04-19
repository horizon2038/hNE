#include <standard/board/board.hpp>

#include <unistd.h>

namespace hal::standard
{
    board::board(std::unique_ptr<core::cpu> init_cpu) : cpu(std::move(init_cpu))
    {
    }

    board::~board() = default;

    void board::run()
    {
        if (!cpu)
        {
            return;
        }

        cpu->reset();
        for (;;)
        {
            cpu->clock();
            // usleep(5);
        }
    }
}
