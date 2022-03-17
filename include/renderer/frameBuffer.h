#pragma once

#include <core.h>
#include <utils.h>

// frame buffer lahko drzi sliko, ki se je narisala na njega namesto okna in jo lahko spreminja
// klasa skrbi da se vse nastavitve za frame buffer nastavijo preden se slika narise na njega

namespace ZWET 
{
    struct FrameBufferSettings
    {
        unsigned int target = GL_TEXTURE_2D;
        int internalFormatTexture = GL_RGB;
        size_t width = 800;
        size_t height = 600;
        unsigned int textureType = GL_UNSIGNED_BYTE;
        void* pixels = NULL;
        int minInterpolation = GL_LINEAR;
        int maxInterpolation = GL_LINEAR;
        unsigned int internalFormatRenderBuffer = GL_DEPTH24_STENCIL8;
    };

    class FrameBuffer
    {
        public:
            FrameBuffer(FrameBufferSettings* settings);

            ~FrameBuffer();

            void bind();

            void unbind();

            void attachTexture();

            static SharedPtr<FrameBuffer> create(FrameBufferSettings*);

        private:
            FrameBufferSettings* settings;
            unsigned int frameBuffer;
            unsigned int frameBufferTexture;
            unsigned int frameBufferObject;

            void genFrameBuffer(size_t amount, unsigned int buffer);

            void genFrameBufferTex(unsigned int buffer);

            void genFrameBufferObject(unsigned int buffer);
            
            void attachToRenderBuffer(unsigned int frameBuffer, unsigned int renderBuffer, unsigned int textureBuffer);
    };
}