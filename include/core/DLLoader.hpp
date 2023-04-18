/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include <iostream>
#include <memory>
#include "Error.hpp"

namespace core {

    class DLLoader {
        public:
            DLLoader(const std::string &path, int mode = RTLD_NOW);

            /**
             * @brief Get the Instance object
             *
             * @tparam T
             * @return T*
             */
            template <class T>
            T *getInstance() const
            {
                T *(*ctor)() = (T *(*)()) dlsym((_handle.get()), "entryPoint");
                if (!ctor) {
                    throw core::Error(dlerror());
                }
                return ctor();
            }

            /**
             * @brief call an extern "C" function from the library
             *
             * @tparam T
             * @param fctName
             * @return T
             */
            template <class T>
            T call(const std::string &fctName)
            {
                T (*fct)() = (T (*)()) dlsym((_handle).get(), fctName.c_str());
                if (!fct) {
                    throw core::Error(dlerror());
                }
                return fct();
            }

            /**
             * @brief Get the library path
             *
             * @return std::string
             */
            std::string getPath() const;

        protected:
        private:
            std::string _path;
            std::shared_ptr<void> _handle;
    };
}

#endif /* !DLLOADER_HPP_ */
