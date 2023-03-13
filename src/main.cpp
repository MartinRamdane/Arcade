#include "IDisplayModule.hpp"
#include "DLLoader.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: ./arcade ./lib/lib.so" << std::endl;
        return 84;
    }
    DLLoader<IDisplayModule> *loader = new DLLoader<IDisplayModule>(av[1]);
    IDisplayModule *instance = loader->getInstance();
    instance->init();
    instance->stop();
    std::cout << (instance->getName()) << std::endl;
    delete loader;
    return 0;
}
