#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>

// klasa namenjena za dobivanje uporabnikovih vnosov na tipkovnici

namespace ZWET
{
    class KeyboardInput
    {
        public: 
            KeyboardInput(GLFWwindow* window);

            ~KeyboardInput();

            bool isKeyHeld(int key);

		    bool isKeyToggled(int key);

            static SharedPtr<KeyboardInput> create(GLFWwindow* window);

        private:
            GLFWwindow* window;
    };
}