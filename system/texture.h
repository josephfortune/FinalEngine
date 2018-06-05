#include <stdint.h>
#include <stdlib.h>

#define L_ENDIAN // <===== Change for architecture!!!!!!!!!!!!!


//================================ baseTexture ================================

class baseTexture
{
	public:
	baseTexture( int height, int width );
	int getHeight( void );
	int getWidth( void );
	int getSize( void );

	protected:
	int height;
	int width;
	
};

//================================ Texture24 ================================

#ifdef L_ENDIAN		// little-endian pixel
struct Pixel24
{
	uint8_t b;
	uint8_t g;
	uint8_t r;
};
#else
struct Pixel24		// Big endian pixel
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};
#endif

class Texture24 : public baseTexture
{
	public:
	Texture24( void );
	Texture24( int height, int width );
	void setPixel( int row, int column, int r, int g, int b );
	struct Pixel24 getPixel( int row, int column );
	static Texture24 getNullTexture( void );

	protected:
	struct Pixel24* pixels;
	
};
