#ifndef TEXTURE_H
#define TEXTURE_H
#include "texture.h"
#endif


//================================ baseTexture ================================

baseTexture::baseTexture( int height = 1, int width = 1 )
{
	baseTexture::height = height;
	baseTexture::width = width;
	
}

int baseTexture::getHeight( void )
{
	return height;
}

int baseTexture::getWidth( void )
{
	return width;
}

int baseTexture::getSize( void )
{
	return (width * height);
}

//================================ Texture24 ================================

Texture24::Texture24( void ) : baseTexture( 0, 0 )
{

}

Texture24::Texture24( int height, int width ) : baseTexture( height, width )
{
	// Allocate space for pixel matrix
	pixels = (struct Pixel24*)malloc( sizeof( struct Pixel24 ) * height * width );
}

void Texture24::setPixel( int row, int column, int r, int g, int b )
{
	struct Pixel24 newpixel;
	newpixel.r = r;
	newpixel.g = g;
	newpixel.b = b;

	pixels[row * width + column] = newpixel;
}

struct Pixel24 Texture24::getPixel( int row, int column )
{
	struct Pixel24 pixel = pixels[ row * width + column ];
	return pixel;
}

Texture24 Texture24::getNullTexture( void )
{
	Texture24 nullTexture( 1, 1 );
	nullTexture.setPixel( 0, 0, 0, 0, 255 );
	return nullTexture;
}








