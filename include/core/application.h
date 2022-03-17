#pragma once

#include <core.h>
#include <scene.h>
#include <renderer.h>
#include <window.h>
#include <utils.h>
#include <log.h>

/*
	TODO:
		- Port the old physics engine and improve it,
		- port the font library
		- do better mesh optimisations for newer OpenGL versions (instanced rendering),
		- rebrand the game engine to Bolt engine (We have a whole logo now goddamn it)
*/

namespace ZWET
{
    class Application {
    	public:
    		Application();

			void setFpsCap(float fpsCap);

			void setWindowDims(size_t width, size_t height);

			void setBackgroundColor(rgb color) { renderer->setBackground(color); };

    		void run();
    
    		void setScene(Scene& scene);

    	private:
			// renderer pripisan k aplikaciji shranjen v unique smart pointerju
    		UniquePtr<Renderer> renderer;

			// okno na katerega se riše
    		GLFWwindow* engineWindow;
			// najvecje stevilo risb, ki se jih lahko narise v eni sekundi
    		unsigned int fpsCap;
			// racunanje pretecenega casa od trenutne narisane slike do prejsnje
    		double currentTime, lastTime, deltaTime;
			double old = 0;

			// funkcija za omejevanje slik, ki se lahko narisejo v eni sekundi
			void blockFramerate(float fpsCap);

			// izracunaj cas med trenutno narisano sliko in prejsno
			void calculateDelta();
    };
}