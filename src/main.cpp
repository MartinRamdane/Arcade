#include "IDisplayModule.hpp"
#include "DLLoader.hpp"
#include "Core.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: ./arcade ./lib/lib.so" << std::endl;
        return 84;
    }
    try {
        Core core(av[1]);
        core.init();
        core.mainloop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
