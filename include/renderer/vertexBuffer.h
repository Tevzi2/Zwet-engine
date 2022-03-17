#pragma once

#include <core.h>
#include <utils.h>

// vertex buffer klasa skrbi, da se 3d modeli, pozicije, barve, normalni vektorji, shranijo v spomin graficne kartice,
// za risanje na okno.

namespace ZWET
{
    class VertexBuffer
    {
        public:
            VertexBuffer(size_t amount, std::vector<float>* positions);

            ~VertexBuffer();

            static SharedPtr<VertexBuffer> create(size_t amount, std::vector<float>* positions);

            void bind();

            static void unbind();

            void setData(std::vector<float>* positions);

            size_t& getPolyCount();

            unsigned int& getBuffer() { return buffer; };

        private: 
            unsigned int buffer;
            size_t polyCount;
    };
}