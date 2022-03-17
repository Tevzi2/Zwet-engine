#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>
#include <scene.h>
#include <attributeLayout.h>
#include <drawer.h>

// renderer klasa povezuje vse ostale kalse v render sistemu, da se na zaslo izrise celotna slika

namespace ZWET
{
    using EntityMap = tsl::hopscotch_map<int, SharedPtr<Entity>>;

    class Renderer
    {
        public:
            Renderer(Scene& scene, unsigned int fpsCap, GLFWwindow* window, double& delta);

            ~Renderer();

            void init();

            void viewport(size_t x, size_t y, size_t width, size_t height);

            void setFpsCap(unsigned int fpsCap);

            void setBackground(rgb color) { backgroundColor = color; };

            static UniquePtr<Renderer> create(Scene& scene, unsigned int fpsCap, GLFWwindow* window, double& delta);

            void frame();

        private:
            GLFWwindow* window;
            Scene& scene;
            EntityMap& entities;
            SharedPtr<Camera> camera;
            double& delta;
            rgb backgroundColor;

            void create();
    };
}