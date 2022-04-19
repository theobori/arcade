/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** dl loader
*/

#ifndef __DLLoader_HPP__
    #define __DLLoader_HPP__

    #include <iostream>
    #include <dlfcn.h>
    #include <memory>
    #include <vector>

    #include "Errors.hpp"

namespace Arcade {
    class DLLoader {

        public:
            DLLoader()
            {

            };
        
            ~DLLoader()
            {
                for (std::size_t i = 0; i < this->_handles.size() - 1; i++) {
                    dlclose(this->_handles[i]);
                }
            };

            template <typename T>
            std::shared_ptr<T> getPtrFromObject(std::string fileName, std::string symbolName)
            {
                void *handle = dlopen(fileName.c_str(), RTLD_LAZY);
                char *dlsym_error = NULL;
                void *symbol = NULL;
                std::shared_ptr<T> (*call)();

                if (handle == NULL)
                    throw (DLError("Cannot open library, error: " + std::string(dlerror()), "Invalid lib"));
                dlerror();

                symbol = dlsym(handle, symbolName.c_str());
                call = reinterpret_cast<std::shared_ptr<T> (*)()>(symbol);

                dlsym_error = dlerror();
                if (dlsym_error) {
                    throw (DLError("Cannot load symbol: " + symbolName, "Invalid symbol"));
                }
                this->_handles.push_back(handle);
                return (call());
            }

        private:
            std::vector<void *> _handles;
    };
}

#endif /* !__DDLoader_HPP__ */
