/*
 * Texture.cpp
 */


#include "Texture.h"

Texture::Texture()
{
    memset(&properties, 0, sizeof(properties));

    // set defaults
    properties.textureData = (unsigned int *)defaultTexture;
    properties.clutData = NULL;

    properties.textureVramX = 320;
    properties.textureVramY = 0;
    properties.textureVramWidth  = 64;
    properties.textureVramHeight = 64;

    properties.bitDepth = SIXTEEN_BIT;
}

Texture::~Texture()
{
}

void Texture::LoadDefault(const int x, const int y)
{
    unsigned short colors[] = {
        0b1000000000011111, // red
        0b1111111111111111  // white
    };

    // checkerboard pattern
    size_t color_index = 0;
    for (size_t row = 0; row < 64; ++row)
    {
        for (size_t col = 0; col < 64; ++col)
        {
            if ((col+1) % 16 == 0) {
                color_index = !color_index;
            }

            defaultTexture[row*64+col] = colors[color_index];
        }

        if ((row+1) % 16 == 0) {
            color_index = !color_index;
        }
    }

    RECT texRect = {x, y, 64, 64}; // x,y,w,h
    LoadImage(&texRect, (unsigned int *)defaultTexture);
}

void Texture::Load(Texture::Properties *textureProperties)
{
    memcpy(&properties, textureProperties, sizeof(Properties));

    // Load the texture data
    short actualWidth = properties.textureVramWidth >> 
        (2 - (short)properties.bitDepth);
    RECT textureRect = { 
        properties.textureVramX, properties.textureVramY, 
        actualWidth, properties.textureVramHeight 
    };
    LoadImage(&textureRect, properties.textureData);

    // load the clut data
    if (properties.clutData != NULL && properties.bitDepth != SIXTEEN_BIT)
    {
        RECT clutRect = {
            properties.clutVramX, properties.clutVramY,
            256, 1 // width and height
        };
        LoadImage(&clutRect, properties.clutData);
    }
}

unsigned short Texture::defaultTexture[64*64];
