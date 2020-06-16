// Testing a debug console thingy

#include <stdio.h>
#include <sys/types.h>
#include <psxetc.h>
#include <psxgte.h>
#include <psxgpu.h>

#include "Texture.h"
#include "sfont.h"

#define ever ;;

// Define display/draw environments for double buffering
DISPENV disp[2];
DRAWENV draw[2];
int db;


// Init function
void init(void)
{
	// This not only resets the GPU but it also installs the library's
	// ISR subsystem to the kernel
	ResetGraph(0);
	
	// Define display environments, first on top and second on bottom
	SetDefDispEnv(&disp[0], 0, 0, 320, 240);
	SetDefDispEnv(&disp[1], 0, 240, 320, 240);
	
	// Define drawing environments, first on bottom and second on top
	SetDefDrawEnv(&draw[0], 0, 240, 320, 240);
	SetDefDrawEnv(&draw[1], 0, 0, 320, 240);
	
	// Set and enable clear color
	setRGB0(&draw[0], 0, 96, 0);
	setRGB0(&draw[1], 0, 96, 0);
	draw[0].isbg = 1;
	draw[1].isbg = 1;
	
	// Clear double buffer counter
	db = 0;
	
	// Apply the GPU environments
	PutDispEnv(&disp[db]);
	PutDrawEnv(&draw[db]);
	
	// Load test font
	FntLoad(960, 0);
	
	// Open up a test font text stream of 100 characters
	FntOpen(0, 8, 320, 224, 0, 100);
}

int main(void)
{
    Texture fontTex;
    
    init();

    // 320,0 = VRAM pos
    Texture::LoadDefault(320, 0);

    Texture::Properties fontTexProp;// = {
    fontTexProp.textureData = (unsigned int*)sfont;
    fontTexProp.clutData = NULL;
    fontTexProp.textureVramX = 384;
    fontTexProp.textureVramY = 0;
    fontTexProp.textureVramWidth = 128;
    fontTexProp.textureVramHeight = 116;
    fontTexProp.clutVramX = 0;
    fontTexProp.clutVramY = 0;
    fontTexProp.bitDepth = Texture::SIXTEEN_BIT;
    fontTex.Load(&fontTexProp);
    
    for (ever)
    {}

    return 0;
}

