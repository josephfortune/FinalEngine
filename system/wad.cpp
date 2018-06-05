#ifndef WAD_H
#define WAD_H
#include "wad.h"
#endif

//================================ Constructor ================================

Wad::Wad(std::string filePath) : File(filePath, "rb")
{
	

	// Pointer inits (Safety first!)
	header = NULL;	
	entry = NULL;

	// No need in validating if parent constructor passed a null file
	if (!active) return;

	// ********************** Read header
	header = (struct WADHEADER*)malloc( sizeof( struct WADHEADER ) );
	if ( header == NULL )
	{
		active = false;
		return;
	}
	if ( read(header, sizeof(struct WADHEADER), 1) < 1)
	{
		active = false;
		return;
	}

	// ********************** Verify WAD filetype
	if ( strncmp(header->szMagic, "WAD2", 4) && strncmp(header->szMagic, "WAD3", 4) )
	{
		active = false;
		return;
	}

	// ********************** Populate directory entries
	
	// Allocate space
	entry = (struct WADDIRENTRY*)calloc( header->nDir, sizeof( struct WADDIRENTRY ) );
	if (entry == NULL)
	{
		active = false;
		return;
	}

	// Read file entries/directories into structs
	setPos(header->nDirOffset);	
	if ( read(entry, sizeof( struct WADDIRENTRY ), header->nDir) < header->nDir)
	{
		active = false;
		return;
	}

	
}

//================================ Destructor ================================

Wad::~Wad()
{

	// ********************** Free allocated memory	
	
	// Free Header
	if (header != NULL) free(header);
	// Free WAD entries/directories
	if (entry != NULL) free(entry);
	
}

//================================ getTexture24 ================================

Texture24 Wad::getTexture24( int index )
{
	struct BSPMIPTEX *miptex;
	uint8_t *data, *pixels, *pallete;
	int matrixSize, height, width;

	// Load BSPMIPTEX + Raw data
	data = (uint8_t*)malloc( entry[index].nDiskSize );
	if ( data == NULL )
	{
		return Texture24::getNullTexture();
	}

	setPos( entry[index].nFilePos );
	if ( read( data, 1, entry[index].nDiskSize) < entry[index].nDiskSize )
	{
		return Texture24::getNullTexture();
	}

	miptex = (struct BSPMIPTEX*)data;
	pixels = data + miptex->nOffsets[0];

	height = miptex->nHeight;
	width = miptex->nWidth;
	matrixSize = height * width;

	pallete = data + miptex->nOffsets[3] + matrixSize/64 + 2; //miptex->nOffsets[3];	


	// Build texture
	Texture24 texture( miptex->nHeight, miptex->nWidth );
	for ( int i = 0; i < matrixSize; i++ )
	{
		int r, g, b;
		r = pallete [ 3 * pixels[i] ];
		g = pallete [ 3 * pixels[i] + 1 ];
		b = pallete [ 3 * pixels[i] + 2 ];

		texture.setPixel( i / width, i % width, r, g, b );
	}

	return texture;
	

}

//======================================================================
