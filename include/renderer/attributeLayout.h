#pragma once

#include <core.h>
#include <utils.h>

namespace ZWET
{
    // struktura, ki drzi porazporeditev attributa v bufferju
    struct Layout
    {
        unsigned int& program;
        unsigned int& buffer;
        std::string nameOfAttribute; 
        int size; 
        unsigned int type; 
        unsigned int normalise;
        int totalSizeInBytes; 
        ptrdiff_t offset;
    };

    // klasa za nastavljanje raporeditve atributov v bufferjih
    class AttributeLayout
    {
        public:
            AttributeLayout(unsigned int& program, unsigned int& buffer);

            ~AttributeLayout();

            static void setLayout(Layout attribLayout);

        private:
            // shader program in vertex buffer
            unsigned int& program;
            unsigned int& buffer;
    };
}