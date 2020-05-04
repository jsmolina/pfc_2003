#ifndef CHandle_H
#define CHandle_H
#include <windows.h>

class CHandle  
{
public:
	CHandle();
	CHandle(HWND h, char e[50], int id);
	~CHandle();
	// variables
	HWND hwnd; // el handle de la finestra
	char exe[50]; // el nom del executable
	int  id;
};

#endif
