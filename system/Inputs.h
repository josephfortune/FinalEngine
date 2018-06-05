#ifndef INPUTS_H
#define INPUTS_H

class Inputs
{
	public:
	Inputs(void);
	
	void setMovFwd();
	void setMovBack();
	void setTurnLeft();
	void setTurnRight();

	void unSetMovFwd();
	void unSetMovBack();
	void unSetTurnLeft();
	void unSetTurnRight();

	bool isSetMovFwd();
	bool isSetMovBack();
	bool isSetTurnLeft();
	bool isSetTurnRight();

	void reset();

	private:	
	bool movFwd, movBack, turnLeft, turnRight;
};

#endif
