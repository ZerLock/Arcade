/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-arcade-thomas.mazaud
** File description:
** Events
*/

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include "types/Global.hpp"

namespace arcade {

    /**
     * @brief Raw key, key returned by the pollEvent of graphical libraries
     *
     */
    enum RawKey {
        K_A,
        K_B,
        K_C,
        K_D,
        K_E,
        K_F,
        K_G,
        K_H,
        K_I,
        K_J,
        K_K,
        K_L,
        K_M,
        K_N,
        K_O,
        K_P,
        K_Q,
        K_R,
        K_S,
        K_T,
        K_U,
        K_V,
        K_W,
        K_X,
        K_Y,
        K_Z,
        K_0,
        K_1,
        K_2,
        K_3,
        K_4,
        K_5,
        K_6,
        K_7,
        K_8,
        K_9,
        K_SPACE,
        K_ESCAPE,
        K_ENTER,
        K_BACKSPACE,
        K_UP,
        K_DOWN,
        K_LEFT,
        K_RIGHT,
        MOUSE_LEFT,
        MOUSE_RIGHT,
    };

    /**
     * @brief Action to execute according to the mapping (RawKey -> Keymaps)
     *
     */
    enum Keymaps {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        PAUSE,
        PREV_GAME,
        NEXT_GAME,
        PREV_GRAPH,
        NEXT_GRAPH,
        RESTART,
        MENU,
        QUIT,
        ENTER,
        SUBMENU1,
        SUBMENU2,
        ACTIONA,
        ACTIONB
    };

    /**
     * @brief Event structure, that contain RawKey returned by the graphical library and mouse position
     *
     */
    struct Event {
        RawKey key;
        Coords pos;
    };

    /**
     * @brief KeyInput that use to formalize the Event (RawKey + mouse position) and Keymaps
     *
     */
    struct KeyInput {
        Event keyEvent;
        Keymaps mapping;
    };
}

#endif /* !EVENTS_HPP_ */
