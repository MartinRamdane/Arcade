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
    public:
        class Error : public std::exception {
            public:
                Error(std::string const &message) : _message(message) {}
                const char *what() const noexcept override { return _message.c_str(); }
            private:
                std::string _message;
        };
    public :
        DLLoader(std::string libName) {
            handle = dlopen(libName.c_str(), RTLD_LAZY);
            if (!handle) {
                throw Error("Error on loading library, library doesn't exist or is not a valid library");
            }
            instance = ((T*(*)())dlsym(handle, "create"))();
            char *error;
            if ((error = dlerror()) != NULL)  {
               throw Error("Error on creating library instance");
            }
            dlerror();
        };
        ~DLLoader() {
            ((void(*)(T*))dlsym(handle, "destroy"))(instance);
            dlclose(handle);
        };
        T *getInstance() {return instance;};
    private:
        T *instance;
        void *handle = nullptr;
};

#endif /* !DLLOADER_HEADER */
