#include <Arduino.h>
#include "slconfig.h"
#include "command.h"
#include "device.h"

#define PARSE_COMMAND 0
#define PARSE_ARGS    1
#define PARSE_STRING  2
#define PARSE_ERROR   3
#define PARSE_END     4

command::command(){
	byteOffset = 0;
	parseState = PARSE_END;
};


/*********************************
 *
 ********************************/
 
bool command::getCommand() {
	
	while(SLSERIAL.available()) {
		
		byte c = SLSERIAL.read();
		
		if(c == -16)
			continue;
		
		if(byteOffset >= 32) {
			SLSERIAL.println(F("log(\"read error command\")"));
            byteOffset = 0;
			parseState = PARSE_ERROR;
		}
		if(PARSE_COMMAND == parseState) {
			
			if(c != '(')
				parseMethod[byteOffset++]=c;
			else {
				parseMethod[byteOffset++]=0;
				byteOffset = 0;
				args = 0;
				parseState = PARSE_ARGS;
			}
			
		}else if(PARSE_ARGS == parseState) {
			
			if(c == ',') {
				argv[args][byteOffset++] = 0;
				byteOffset = 0;
				args++;		
				if(args > MAX_COMMAND_COUNT) {
					parseState = PARSE_ERROR;
					SLSERIAL.println(F("log(\"command to long\")"));
				}
			}else if(c == ')') {
				argv[args][byteOffset++] = 0;
				args++;
				if( argv[0][0] == 0)
					args = 0;
				parseState = PARSE_END;
				return true;
			}else if(c == '\"') {
				parseState = PARSE_STRING;
			}else if(c != ' '&&c != '\t') {
				argv[args][byteOffset++] = c;
			}
				
			
		}else if(PARSE_STRING == parseState) {
			
			if( c != '\"' ) 
				argv[args][byteOffset++] = c;
			else
				parseState = PARSE_ARGS;
			
		}else if(PARSE_ERROR == parseState) {
			
			if( c == ')') {
				args = 0;
				*parseMethod = 0;
				parseState = PARSE_END;
				return false;
			}
		}else {
			if(c != ' '&&c != '\t'&&c != '\r'&&c != '\n') {
				parseState = PARSE_COMMAND;
				byteOffset = 0;
				parseMethod[byteOffset++]=c;
			}
		}
	}
	return false;
}

void command::dispatch() {
	device* dev = NULL;
	
	dev = DeviceManager::findDevice(parseMethod);
	if(dev != NULL)
		dev->e_func(args,argv);
	
}


void command::debug() {
	SLSERIAL.print(F("log(\"methed name:"));
	SLSERIAL.print(parseMethod);
	SLSERIAL.println(F("\")"));
	SLSERIAL.print(F("log(\"argument count:"));
	SLSERIAL.print(args);
	SLSERIAL.println(F("\")"));
	
	for(int i = 0 ; i < args;i++) {
		SLSERIAL.print(F("log(\"argument "));
		SLSERIAL.print(i);
		SLSERIAL.print(":");
		SLSERIAL.print(&argv[i][0]);
		SLSERIAL.println(F("\")"));
	}
	
}

