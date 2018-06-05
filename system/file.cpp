#ifndef FILE_H
#define FILE_H
#include "file.h"
#endif

//================================ Constructor ================================

File::File(std::string filePath, std::string mode)
{
	active = false;
	fileName = "Null_File";
	
	open(filePath, mode);
}

//================================ Destructor ================================

File::~File()
{
	if (active)
		close();
}


//================================ open ================================

bool File::open(std::string filePath, std::string mode)
{
	file = fopen( filePath.c_str(), mode.c_str() );

	if (file == NULL)
		return false;

	active = true;
	fileName = filePath;
	return true;
}

//================================ close ================================

void File::close(void)
{
	if (!active)
		return;

	fclose(file);
	active = false;
	fileName = "Null_File";
}

//================================ rewind ================================

bool File::rewind(void)
{
	if (!active)
		return false;

	std::rewind(file);
	return true;
}

//================================ getPos ================================

int File::getPos(void)
{
	if (!active)
		return -1;
	
	return ftell(file);
}

//================================ setPos ================================

bool File::setPos(int pos)
{

	if (!active)
		return false;

	if ( fseek(file, pos, SEEK_SET) )
		return false;

	return true;
}

//================================ getFileName ================================

std::string File::name(void)
{
	return fileName;
}

//================================ read ================================

int File::read(void* buffer, int numBytes, int num)
{
	if (!active)
		return 0;

	return fread(buffer, numBytes, num, file);
}
//======================================================================
