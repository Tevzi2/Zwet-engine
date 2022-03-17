#pragma once

#include <core.h>
#include <utils.h>

// klasa, drawer se uporablja kadar so vse stvari za risanje nastavljene in je potrebno sliko narisat na okno

namespace ZWET
{
    class Drawer
    {
        public:
            Drawer(unsigned int type, int first, size_t amount);

            ~Drawer();

            void setPolyCount(size_t newAmount) { amount = newAmount; };

            void setDrawType(unsigned int newType);

            void setFirst(int newFirst);

            static void draw(unsigned int type, int first, size_t amount);
            void draw();

            static SharedPtr<Drawer> create(unsigned int type, int first, size_t amount);

        private:
            // tip risanja, ki se bo izvedel
            unsigned int type;
            // prvi atribut za risanje
            int first;
            // kolicina trikotnikov, ki se bodo narisali na okno
            size_t amount;
    };
}