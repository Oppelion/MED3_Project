#ifndef NOTES_H
#define NOTES_H
#include <iostream>

extern int recvArray[3];

class Notes
{
private:
	
	const int maxSection = 13;
	float sections[13];
public:
	Notes();
	void section_Calculator();
	int noteAssigner();
};
#endif