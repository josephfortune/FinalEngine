#include <cstdio>
#include <string>
#include <stdint.h>

class File
{
	public:

	// Constructor/Destructor
	File(std::string filePath, std::string mode);
	~File();
	
	// Inits/Clean-up	
	bool open(std::string filePath, std::string mode);
	void close(void);

	// Access
	bool rewind(void);
	int getPos(void);
	bool setPos(int pos);	
	std::string name(void);
	int read(void* buffer, int numBytes, int num);
	
	protected:
	FILE* file;
	bool active;
	std::string fileName;

};
