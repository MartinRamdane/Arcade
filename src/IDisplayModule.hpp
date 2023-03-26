/*
** EPITECH PROJECT, 2023
** IDisplayModule.hpp
** File description:
** IDisplayModule
*/

#ifndef DISPLAY_MODULE_I
    #define DISPLAY_MODULE_I

#include <string>
#include "IGameModule.hpp"

class IDisplayModule {
    public:
        virtual ~IDisplayModule () = default ;

        /**
        ** @brief Must be called before any other method to initialize the display
        ** @param entites The entities to display
        **/
        virtual void init(std::map<std::string, IGameModule::Entity> &entites) = 0;

        /**
        ** @brief Must be called to stop the display and free all resources
        **/
        virtual void stop() = 0;

        /**
        ** @brief Must be called to update the display, this method must be called before draw
        ** @param entites The entities to display
        **/
        virtual void update(std::map<std::string, IGameModule::Entity> &entities) = 0;

        /**
        ** @brief Must be called to draw the display, this method must be called after update
        **/
        virtual void draw() = 0;

        /**
        ** @brief Must be called to get the event from the display
        ** @return The event as a string
        **/
        virtual std::string getEvent() = 0;

        /**
        ** @brief Must be called to get the name of the library used
        ** @return The name of the library
        **/
        virtual const std::string &getName() const = 0;
};

#endif /* !DISPLAY_MODULE_I */
