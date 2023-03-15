#include "IDisplayModule.hpp"
#include "DLLoader.hpp"
#include "Core.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: ./arcade ./lib/lib.so" << std::endl;
        return 84;
    }
    Core core(av[1]);
    core.init();
    core.mainloop();
    return 0;
}
