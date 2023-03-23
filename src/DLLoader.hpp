/*
** EPITECH PROJECT, 2023
** DLLoader.hpp
** File description:
** DLLoader
*/

#ifndef DLLOADER_HEADER
    #define DLLOADER_HEADER

#include <iostream>
#include <dlfcn.h>
#include <memory>

template <typename T>
class DLLoader {
    public :
        DLLoader(std::string libName) {
            handle = dlopen(libName.c_str(), RTLD_LAZY);
            if (!handle) {
                std::cerr << "Error: " << dlerror() << std::endl;
                exit(84);
            }
            instance = ((std::shared_ptr<T> (*)())dlsym(handle, "create"))();
            char *error;
            if ((error = dlerror()) != NULL)  {
                fprintf(stderr, "%s\n", error);
                exit(EXIT_FAILURE);
            }
            dlerror();
        };
        ~DLLoader() {
            dlclose(handle);
        };
        std::shared_ptr<T> getInstance() {return instance;};
    private:
        std::shared_ptr<T> instance;
        void *handle = nullptr;
};

#endif /* !DLLOADER_HEADER */
