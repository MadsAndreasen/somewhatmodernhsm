
#include "wizard.h"
#include <iostream>
#include <string>

std::string readCmd()
{
    std::string cmd;
    std::getline(std::cin, cmd);
    return cmd;
}

auto main() -> int
{
    WizardsWorld world;

    while(true) {
        std::string cmd = readCmd();
        if("quit" == cmd || "q" == cmd) {
            break;
        }
        else if("north" == cmd || "n" == cmd) {
            world.north();
        }
        else if("east" == cmd || "e" == cmd) {
            world.east();
        }
        else if("south" == cmd || "s" == cmd) {
            world.south();
        }
        else if("west" == cmd || "w" == cmd) {
            world.west();
        }
        else if("smell" == cmd) {
            world.smell();
        }
        else if("take" == cmd) {
            world.take();
        }
        else {
            std::cout << "I do not understand" << std::endl;
            std::cout << "Possible commands: north, east, south, west, quit" << std::endl;
        }
    }
}
