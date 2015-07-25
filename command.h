#ifndef _SL_COMMAND_
#define _SL_COMMAND_
#include "slconfig.h"

class command {
public:
	command();
	virtual ~command(){}
	
	bool getCommand();
	void dispatch();
	
	void debug();
private:
	int args;
	char argv[MAX_COMMAND_COUNT][MAX_ARGUMENT_LENGTH];
	char parseMethod[MAX_ARGUMENT_LENGTH];
	byte byteOffset;
	byte parseState;
};


#endif

