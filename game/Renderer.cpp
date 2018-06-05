#ifndef Renderer_H
#define Renderer_H
#include "Renderer.h"

#include <math.h>
//#include <SDL2/SDL.h>

#include <iostream>          ///////////////////////////////////////////////////////////////////// debug
using namespace std;

//extern SDL_Window* window; // for the slow frame by fame render effect

/*********************************************************************************************/

Renderer::Renderer( int hght, int wdth, World* world ) : height( hght ), width( wdth ), world( world)
{		
	// This section pre-builds directional vectors which are later used
	// for finding intersections.	
	float fov_rads = FIELD_OF_VIEW * PI / 180; // Field of view in radians
	float angle = ( PI - fov_rads ) / 2;	// starting angle (rightmost angle in FOV)
	float angle_diff = fov_rads / H_PIXELS; // Find the difference in angle between pixels

	// Populate the vector array
	for ( int i = H_PIXELS -1 ; i >= 0; i-- ) // Load them in reverse as we scan pixels from right to left
	{
		vectors[i].x = cos( angle );
		vectors[i].y = sin( angle );
		angle += angle_diff;
	}

	/* To lower the resolution to give the renderer a retro feel, we actually use several real pixels inside
	/  a single pixel within the game. This determines how many actual pixels there are in a rendered pixel. */
	truePxls = width / H_PIXELS;

	// Height in retro-Pixels
	retHeight = V_PIXELS;

	// Width in retro-Pixels
	retWidth = H_PIXELS;

	// Calculate center of screen in retro-Pixels
	vtRetCenter = retHeight / 2;

	// Scale factor
	scaleFactor = retHeight * 10;

	// Queue for additional scenes as sectors found
	additionalScenes = Queue<Scene>(1024);

	// TODO this is just for testing currently ====================================================================
	Wad myWad("textures/tropical.wad");

	texture = myWad.getTexture24(6);

	// ============================================================================================================
}

/*********************************************************************************************/

void Renderer::setPixelBuffer( uint32_t *pixelBuffer )
{
	pixels = pixelBuffer;
}

/*********************************************************************************************/

void Renderer::setColor( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	RGB.r = red;
	RGB.g = green;
	RGB.b = blue;
	RGB.alpha = alpha;
}

/*********************************************************************************************/

void Renderer::putPixel( int x, int y )
{
	// Make sure pixels are within bounds
	if ( (x > 0 && x < width ) && (y > 0 && y < height) )
	{	
		uint32_t* pixel = pixels + y * width + x;
		*pixel = RGB.color;
	}
}

/*********************************************************************************************/

void Renderer::putRetPxl( int x, int y )
{
	int trueX = (x * truePxls);
	int trueY = (y * truePxls);

	// Make sure pixels are within bounds
	if ( (trueX > 0 && trueX < width ) && (trueY > 0 && trueY < height) )
	{	
		

		for (int xPxl = 0; xPxl < truePxls; xPxl++)
		{
			for (int yPxl = 0; yPxl < truePxls; yPxl++)
			{
				uint32_t* pixel = pixels + (trueY + yPxl) * width + (trueX + xPxl);
				*pixel = RGB.color;
			}
		}
		
	}
}

/*********************************************************************************************/

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
    #define sign(x) ((x) > 0 ? 1: ((x) == 0 ? 0: (-1)))

    int dx, dy, dxabs, dyabs, i, px, py, sdx, sdy, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    sdx = sign(dx);
    sdy = sign(dy);
    dxabs = abs(dx);
    dyabs = abs(dy);
    x = 0;
    y = 0;
    px = x1;
    py = y1;

    if (dxabs >= dyabs)
    {
        for (i = 0; i <= dxabs; i++)
        {
            y += dyabs;
            if ( y >= dxabs)
            {
                y -= dxabs;
                py += sdy;
            }
            putPixel(px, py);
            px += sdx;
        }
    }
    else
    {
        for (i = 0; i <= dyabs; i++)
        {
            x += dxabs;
            if (x >= dyabs)
            {
                x -= dyabs;
                px += sdx;
            }
            putPixel(px, py);
            py += sdy;
        }
    }
}

/*********************************************************************************************/

void Renderer::drawRetLine(int x1, int y1, int x2, int y2)
{
    #define sign(x) ((x) > 0 ? 1: ((x) == 0 ? 0: (-1)))

    int dx, dy, dxabs, dyabs, i, px, py, sdx, sdy, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    sdx = sign(dx);
    sdy = sign(dy);
    dxabs = abs(dx);
    dyabs = abs(dy);
    x = 0;
    y = 0;
    px = x1;
    py = y1;

    if (dxabs >= dyabs)
    {
        for (i = 0; i <= dxabs; i++)
        {
            y += dyabs;
            if ( y >= dxabs)
            {
                y -= dxabs;
                py += sdy;
            }
            putRetPxl(px, py);
            px += sdx;
        }
    }
    else
    {
        for (i = 0; i <= dyabs; i++)
        {
            x += dxabs;
            if (x >= dyabs)
            {
                x -= dyabs;
                px += sdx;
            }
            putRetPxl(px, py);
            py += sdy;
        }
    }
}

/*********************************************************************************************/

int Renderer::getWidth( void )
{
	return width;
}

/*********************************************************************************************/

int Renderer::getHeight( void )
{
	return height;
}

/*********************************************************************************************/

void Renderer::renderScene( Scene scene )
{
	additionalScenes.add(scene); // The starting scene. Others will get added as portals are found.

	while (!additionalScenes.empty())
	{
		renderWalls(additionalScenes.remove());
		// Other stuff will go here, ligthing, sprites...
	}
	
}

/*********************************************************************************************/

void Renderer::renderWalls( Scene scene )
{
	int numWalls = scene.getNumWalls();
	Wall *currWall; // The wall being rendered
	Vector2 V, W, VW;
	float distAlongWall;

	// Vectors
	Vector2 zeroVector(0, 0);
	Vector2 rightBound(0.5, 0.86602540378); // < 1/2, sqrt(3)/2> Right FOV
	Vector2 leftBound(-0.5, 0.86602540378); // <-1/2, sqrt(3)/2> Left FOV
	Vector2 rightPerp(-0.86602540378, 0.5); // Vector normal (inboard) to Right FOV
	Vector2 leftPerp(0.86602540378, 0.5); // Vector normal (inboard) to Left FOV

	// Draw boundaries on map
	setColor(255, 0, 0, 255);
	drawLine(rightBound.x/4 + width/4, rightBound.y/4 + height/4, (rightBound * 1000).x/4 + width/4, (rightBound * -1000).y/4 + height/4);
	drawLine(leftBound.x/4 + width/4, leftBound.y/4 + height/4, (leftBound * 1000).x/4 + width/4, (leftBound * -1000).y/4 + height/4);
	setColor(0, 0, 255, 255);

	// Draw all walls before chopping in blue on map
	for ( int wallNum = 0; wallNum < numWalls; wallNum++ )
	{	
		currWall = scene.wallAt( wallNum ); // This will be changed to pop walls of the stack in order of closests to furthest
			
		//Wall's Vectors
		V = currWall->v1;
		W = currWall->v2;
	
		drawLine(V.x/4 + width/4, height/4 - V.y/4, W.x/4 + width/4, height/4 - W.y/4);
	}

	// Draw walls after chopped in green on map
	setColor(0, 255, 0, 255);
	for ( int wallNum = 0; wallNum < numWalls; wallNum++ )
	{	
		currWall = scene.wallAt( wallNum ); // This will be changed to pop walls of the stack in order of closests to furthest

		// If wall behind player, skip
		//if (Vector2(1, 0) * currWall->normal < 0)
		//	continue;

		// TEMPORARY !!!!!! for the solid wall fade effect
		float fadeFactor = (currWall->v1.length() + currWall->v2.length()) / 4;
			
		// Wall's Vectors
		V = currWall->v1;
		W = currWall->v2;

		// Cast 2 rays along the FOV boundaries to see if they intersect with the wall
		Vector2 leftRay = Vector2::rayIntersect(zeroVector, leftBound, V, W-V);
		Vector2 rightRay = Vector2::rayIntersect(zeroVector, rightBound, V, W-V);

		// Stays true if there is no intersection with the rays above
		int noIntersection = 1;


		// If the leftRay's intersection is within the wall
		distAlongWall = (leftRay - V).length();
		if (leftRay.y > 0 && (leftRay-V) * (W-V) > 0 && distAlongWall < (W-V).length())
		{
			// Update the wall's leftmost vertex to where the intersection was.
			// (chopping the wall where is no longer visible) 
			V = leftRay;
			noIntersection = 0;
		}
		
		// If the rightRay's intersection is within the wall
		distAlongWall = (rightRay - V).length();
		if ((rightRay-V) * (W-V) > 0 && distAlongWall < (W-V).length())
		{
			// Update the wall's rightmost vertex to where the intersection was.
			// (chopping the wall where is no longer visible) 
			W = rightRay;
			noIntersection = 0;
		}


		/* leftPerp and rightPerp are vectors that are pointing inwards from the 2 vectors that 
		/  describe the FOV boundaries. If the wall didn't intersect with either of the FOV vectors,
		/  then either the entire wall is within the FOV, or outside the FOV. If it is inside the
		/  FOV, then then both Vertices will give a positive result when dot-producted with the
		/  perp vectors. Otherwise, the wall is completely outside the FOV and so we skip it. */
		if (noIntersection)
		{
			if ( (leftPerp * V < 0) || (leftPerp * W < 0) || (rightPerp * V < 0) || (rightPerp * W < 0))
				continue;	
		}

		/* Ok well that leaves a little issue. We think of FOV as a V-shape extending forward. 
		/  However, mathematically it is actually treated more like an X, where the FOV is not
		/  only a v-shape on top, but the reverse V-shape on the bottom, which would be like
		/  the player having eye's in the back of their head, which they don't. But because this
		/  is how those perp Vectors work, we have to be sure and reject and walls that "appear"
		/  to be within the FOV, but are actually behind us. 
		/  (Should be irrelevant once the walls are presorted and behind walls are eliminated 
        /   before the scene is passed ) */
		if ( V.y < 0 || W.y < 0)
				continue;
	
		// Draw on map
		drawLine(V.x/4 + width/4, height/4 - V.y/4, W.x/4 + width/4, height/4 - W.y/4);

		/* This must be done after walls facing away from player have been eliminated, otherwise 2 adjacent sectors will recursively keep
		 * adding each other to the queue */		
		if (currWall->isPortal)
		{
				additionalScenes.add(world->getScene(currWall->nextSector));
				continue;
		}

		// ********** 3D(ish) Rendering **********
		float scrSpcX1, scrSpcX2, coeff;
		int startCol, endCol;	
		
		// Get the angles (right side is angle 0)
		float angleV = PI - atan2(V.y, V.x);
		float angleW = PI - atan2(W.y, W.x);

		scrSpcX1 = retWidth * (3 * angleV * ONE_OVER_PI - 1);
		scrSpcX2 = retWidth * (3 * angleW * ONE_OVER_PI - 1);

		coeff = scaleFactor*(V.y-W.y)/(V.y*W.y*(W.x-V.x));

		startCol = scrSpcX1;
		endCol = scrSpcX2;

		float height1 = scaleFactor/V.y;
		float height2 = scaleFactor/W.y;

		if (endCol - startCol == 0) continue; // dont divide by 0
		float slope = (height2 - height1) / (endCol - startCol);

		for (int col = startCol; col < endCol; col++)
		{
			int rowHeight = slope * (col - startCol) + height1;

			for (int row = 0; row < rowHeight; row++)
			{
				setColor(255 - fadeFactor, 255 - fadeFactor, 255 - fadeFactor, 0); // Gives further walls a darker look
				
				putRetPxl(col, vtRetCenter + row);
				putRetPxl(col, vtRetCenter - row);
				
				// For slow rendering
				//SDL_UpdateWindowSurface( window );
				//SDL_Delay(.5);
			}
		}
	}

	
}

/*********************************************************************************************/
#endif

