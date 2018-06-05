#ifndef FILE_H
#define FILE_H
#include "file.h"
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#ifndef TEXTURE_H
#define TEXTURE_H
#include "texture.h"
#endif

#define MAXTEXTURENAME 16
#define MIPLEVELS 3

class Wad : public File
{
	public:
	Wad(std::string filePath);
	~Wad();
	Texture24 getTexture24( int index );
	
	
	protected:
	
	// ----------------------------- Data Structures -----------------------------------
	struct WADHEADER
	{
		char szMagic[4];    // should be WAD2/WAD3
		int32_t nDir;       // number of directory entries
		int32_t nDirOffset; // offset into directory
	};

	struct WADDIRENTRY
	{
		int32_t nFilePos;            // offset in WAD
		int32_t nDiskSize;           // size in file
		int32_t nSize;               // uncompressed size
		int8_t nType;                // type of entry
		int8_t bCompression;           // 0 if none
		int16_t nDummy;              // not used
		char szName[MAXTEXTURENAME]; // must be null terminated
	};

	struct BSPMIPTEX
	{
		char szName[MAXTEXTURENAME];  // Name of texture
		uint32_t nWidth, nHeight;     // Extends of the texture
		uint32_t nOffsets[MIPLEVELS]; // Offsets to texture mipmaps from BSPMIPTEX;
	};
	// ---------------------------------------------------------------------------------
	
	struct WADDIRENTRY *entry;
	struct WADHEADER *header;
	
};
