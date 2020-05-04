// Handle.cpp: implementation of the CHandle class.
//
//////////////////////////////////////////////////////////////////////
#include "Handle.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHandle::CHandle()
{
	hwnd=NULL;
	id=-1;
	sprintf(exe, "");	
}

CHandle::CHandle(HWND h, char e[50], int id)
{
	this->hwnd=h;
	this->id=id;	
	sprintf(exe, "%s", e);	

}

CHandle::~CHandle()
{

}
