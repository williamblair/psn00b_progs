/*
 * Texture.h
 */

#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <sys/types.h>
#include <stdio.h>	
#include <string.h>
#include <psxetc.h>	
#include <psxgte.h>	
#include <psxgpu.h>	

/*
===============================================================================
Texture

    PSX Vram Texture Page ID and CLUT ID (if applicable)
===============================================================================
*/

class Texture
{

public:

// These need to be scaled by the actual width and height of the texture
typedef struct {
    unsigned int v0;
    unsigned int v1;
} TEXCOORD;

enum BitDepth {
    FOUR_BIT,
    EIGHT_BIT,
    SIXTEEN_BIT
};

typedef struct {
    
    unsigned int *textureData;
    unsigned int *clutData;
    
    short textureVramX, textureVramY;
    short textureVramWidth, textureVramHeight;

    short clutVramX, clutVramY;
    

    BitDepth bitDepth;

} Properties;
    
    Texture();
    ~Texture();

    // call this before drawing a model
    // x = VRAM x
    // y = VRAM y
    static void LoadDefault(const int x, const int y);

    void Load(Texture::Properties *textureProperties);

/*    int getWidth(void) const
    {
        return properties.textureVramWidth;
    } 
    int getHeight(void) const
    {
        return properties.textureVramHeight;
    }*/
    void applyToPrimitive(POLY_FT3 *prim, TEXCOORD *coord0, TEXCOORD *coord1, TEXCOORD *coord2)
    {
        int texWidth  = properties.textureVramWidth;
        int texHeight = properties.textureVramHeight;
        setUV3(
            prim,
            coord0->v0*texWidth, coord0->v1*texHeight,       // U0, V0 (top left)
            coord1->v0*texWidth, coord1->v1*texHeight,       // U1, V1 (top right)
            coord2->v0*texWidth, coord2->v1*texHeight       // U2, V2 (bottom left)
        );  
    
        // set texturepage
        setTPage(
            prim,
            (int)properties.bitDepth, // texture page mode, 0 - 4bit, 1 - 8bit, 2 - 16bit
            0, // semitransparency rate
            properties.textureVramX, properties.textureVramY  // X, Y in VRAM
        );

        // set clut
        setClut(prim, properties.clutVramX, properties.clutVramY);
    }

private:

    Properties properties;

    static unsigned short defaultTexture[64*64]; // 64bit width, 64bit height
};

#endif // end ifndef TEXTURE_H_INCLUDED

