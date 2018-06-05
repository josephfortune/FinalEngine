#include <SDL2/SDL.h>
#include <stdio.h>

//Mine
#include "game/Renderer.h"
#include "game/Character.h"
#include "system/Inputs.h"
#include "game/World.h"
#include "system/Controller.h"
#include "game/Sector.h"		

SDL_Window* window = NULL;

int main( int argc, char* args[] )
{
	// ================================================== Test Area Setup ==============================================
	
	Character player;
	Inputs input;
	World world;

	player.pos = Vector2(0, 80);
	player.angle = 60 * PI/180;

	world.setPlayer(&player);
	Controller controller(&input, &world);

	Wall walls[12];
	
	/* Old set
	walls[0] = Wall( 100, 100, 100, -100, NULL);
	walls[1] = Wall(100, -100, -100, -100, NULL);
	walls[2] = Wall(-100, -100, -100, 100, NULL);
	walls[3] = Wall(-100, 100, -25, 100, NULL);
	walls[4] = Wall(25, 100, 100, 100, NULL);
	walls[5] = Wall(-25, 100, -25, 105, NULL);
	walls[6] = Wall(-25, 105, -100, 105, NULL);
	walls[7] = Wall(-100, 105, -100, 155, NULL);
	walls[8] = Wall(-100, 155, 100, 155, NULL);
	walls[9] = Wall(100, 155, 100, 105, NULL);
	walls[10] = Wall(100, 105, 25, 105, NULL);
	walls[11] = Wall(25, 105, 25, 100, NULL); */
	


	Sector sectors[2];
	
	// Sector 0
	walls[0] = Wall(-50, -50, -50, 50, NULL);
	walls[1] = Wall(-50, 50, -25, 50, &sectors[1]);
	walls[2] = Wall(-25, 50, -25, 10, NULL);
	walls[3] = Wall(-25, 10, 50, 10, NULL);
	walls[4] = Wall(50, 10, 50, -50, NULL);
	walls[5] = Wall(50, -50, -50, -50, NULL);

	// Sector 1
	walls[6] = Wall(-50, -50, -50, 75, NULL);
	walls[7] = Wall(-50, 75, 50, 125, NULL);
	walls[8] = Wall(50, 125, 50, 50, NULL);
	walls[9] = Wall(50, 50, -25, 50, NULL);
	walls[10] = Wall(-25, 50, -50, 50, &sectors[0]);

	world.setWallsPtr(walls, 12);
	world.setSectorsPtr(sectors, 2);

	
	sectors[0].setWalls(walls, 6);
	sectors[1].setWalls(walls + 6, 5);

	player.setSector(&sectors[1]);
	

	// =================================================================================================================


	//The window we'll be rendering to
	SDL_Surface* screenSurface = NULL;

	// The Renderer object to handle the drawing
	Renderer renderer( 600, 1000, &world );

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "FINAL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, renderer.getWidth(), renderer.getHeight(), SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			// Set the pixel buffer in the renderer object
			renderer.setPixelBuffer( (uint32_t*)screenSurface->pixels);

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//User presses a key
					if( e.type == SDL_KEYDOWN )
					{
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							input.setMovFwd();
							break;

							case SDLK_DOWN:
							input.setMovBack();
							break;

							case SDLK_LEFT:
							input.setTurnLeft();
							break;

							case SDLK_RIGHT:
							input.setTurnRight();
							break;

						}
					}
					// User unpresses a key
					if( e.type == SDL_KEYUP )
					{
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							input.unSetMovFwd();
							break;

							case SDLK_DOWN:
							input.unSetMovBack();
							break;

							case SDLK_LEFT:
							input.unSetTurnLeft();
							break;

							case SDLK_RIGHT:
							input.unSetTurnRight();
							break;

						}
					}
				}		

				// ====================== TEST AREA ======================================
						


				//renderer.setColor(255, 255, 255, 255);
		
				
				//input.setTurnLeft();
				controller.processInputs();
				renderer.renderScene(world.getScene(player.sector));
				//renderer.drawRetLine(1,1, 120, 90);

				//printf("Direction: X: %f Y: %f\n", player.getDirection().x, player.getDirection().y);
				//printf("Pos: X: %f Y: %f\n", player.getPos().x, player.getPos().y);
				//printf("Angle: %f\n", player.getAngle() * 180/3.14);
				
				/*
				if (testSector.isInside(player.getPos()))
					printf("Inside\n");
				else printf("Outside\n");*/
				
				//Update the SDL surface
				SDL_UpdateWindowSurface( window );
				SDL_Delay(10);
				SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );

			}
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}



