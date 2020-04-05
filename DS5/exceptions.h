#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H
#include <iostream>
#include <string>
using namespace std;

class MessageExeption{
public:
	MessageExeption():message("Exception"){}
	MessageExeption(string theMessage){message = theMessage;}
	void outputMessage(){cout << message << endl;}
protected:
	string message;
};


class IllegalParameterValue : public MessageExeption{
public:
	IllegalParameterValue():MessageExeption("Illegal parameter value"){}
	IllegalParameterValue(string theMessage):MessageExeption(theMessage){}
};

class IllegalIndex : public MessageExeption{
public:
	IllegalIndex():MessageExeption("Illegal index value"){}
	IllegalIndex(string theMessage):MessageExeption(theMessage){}
};

class OutOfBounds {
public:
	OutOfBounds() {}
};

class NoMem {
public:
	NoMem() {}
};

class NoPrev {
public:
	NoPrev() {}
};

class NoNext {
public:
	NoNext() {}
};

#endif