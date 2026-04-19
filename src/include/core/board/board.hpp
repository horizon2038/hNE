#ifndef CORE_BOARD_BOARD_HPP
#define CORE_BOARD_BOARD_HPP

namespace core
{
    class board
    {
      public:
        virtual ~board() {};
        virtual void run() = 0;
    };
}

#endif
