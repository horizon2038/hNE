#include <standard/factory/board_factory.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 1;
    }

    hal::standard::board_factory factory;
    auto                        board = factory.make(argv[1]);
    if (!board)
    {
        return 1;
    }

    board->run();
    return 0;
}
