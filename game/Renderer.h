#include <stdint.h>
#include "../maths/Vector2.h"
#include "Scene.h"
#include "World.h"
#include "../data_structures/Queue.h"

// TESTING
#include "../system/wad.h"

#define H_PIXELS 480 // 240 virtual horizontal pixels
#define V_PIXELS 320 // 160 virtual vertical pixels
#define FIELD_OF_VIEW 60.0f // 60 degree field of view
#define MAX_ADDITIONAL_SCENES 1024

// Constants
#define TWO_PI 6.28318530718
#define PI 3.14159265359
#define PI_OVER_2 0.15915494309
#define ONE_OVER_PI 0.31830988618
#define PI_OVER_3 1.0471975512
#define TWO_PI_OVER_3 2.09439510239

union Color
{
	struct
	{
		uint8_t b;
		uint8_t g;
		uint8_t r;
		uint8_t alpha;
	};
	
	uint32_t color;
};

// The Renderer class is intended to be a gateway class, the only class that is coupled
// with the underlaying architecture's graphics implementation
class Renderer
{
	public:
	Renderer( int hght, int wdth, World* world );

	// Sets the pixel buffer
	void setPixelBuffer( uint32_t *pixelBuffer );

	// Sets current drawing color
	void setColor( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

	// Puts a pixel on the screen
	void putPixel(int x, int y);

	// Puts a retro-Pixel on the screen
	void putRetPxl(int x, int y);

	// Draws a line
	void drawLine(int x1, int y1, int x2, int y2);

	// Draws a retro-Pixel line
	void drawRetLine(int x1, int y1, int x2, int y2);

	// get Width
	int getWidth( void );

	// get Height
	int getHeight( void );

	// Render a scene object
	void renderScene( Scene scene );

	protected:
	uint32_t *pixels;	// Pixel buffer
	Vector2 vectors[H_PIXELS];	// Directional vectors
	union Color RGB;	// Current drawing color
	int height;			// Screen height in actual pixels
	int width;			// Screen width in actual pixels
	int retHeight;		// Screen height in retro-Pixels
	int retWidth;		// Screen width in retro-Pixels
	int truePxls;		// How many actual pixels are inside of a rendered pixel (retro-Pixels)
	int vtRetCenter;	// Vertical center of screen in retro-Pixels
	int hzPadding;		// Padding for uneven virtual pixel to screen ratios
	int vtPadding;		// ...
	int scaleFactor; 	// For determining perspective wall height
	Texture24 texture; // TESTING==================================================================================
	World *world;
	Queue<Scene> additionalScenes; // Additional scenes to render as portals are found

	void renderWalls( Scene scene );
	
};
