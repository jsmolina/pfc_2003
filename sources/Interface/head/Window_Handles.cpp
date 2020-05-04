#include "Window_Handles.h" // class header file
#include "..\exports.h"

Window_Handles::Window_Handles()
{
//	Llista.clear();
	count =0;
}
//////////////////////////////////////////////////////////////////////
Window_Handles::~Window_Handles()
{
	CHandle * bnext;

	std::list<CHandle *>::iterator it;
	for (it = Llista.begin(); it != Llista.end(); it++)
	{
		bnext=(*it);
		delete bnext; // part perillosa, però que cal alliberar memòria
	}
	Llista.clear();
	count =0;
}
//////////////////////////////////////////////////////////////////////
void Window_Handles::Add(HWND h)
{
	CHandle * c = new CHandle(h, NULL, count);
	
	Llista.push_back(c);
	count++;
	if (Llista.empty()) MessageBox(NULL, "Empty??", "Error", MB_OK);

}
//////////////////////////////////////////////////////////////////////
void Window_Handles::Add(HWND h, char exe[50])
{
	CHandle * c = new CHandle(h, exe, count);
	
	Llista.push_back(c);
	if (Llista.empty()) MessageBox(NULL, "Empty??", "Error", MB_OK);
	count++;
}
//////////////////////////////////////////////////////////////////////
CHandle * Window_Handles::Get(HWND h)
{
	CHandle * ret = NULL;
	if (Llista.empty()) return NULL;

	std::list<CHandle *>::iterator it;

	for (it = Llista.begin(); it != Llista.end(); it++)
	{
		ret=(*it);
		if (ret->hwnd==h) return ret;
	}

	return (NULL);
}
//////////////////////////////////////////////////////////////////////
bool Window_Handles::IfExists(HWND h)
{
	CHandle * ret = NULL;
	if (h==NULL) return false;
/*	if (count==0) {
		MessageBeep(MB_ICONHAND);		
		return false;
	}*/
	std::list<CHandle *>::iterator it;
	for (it = Llista.begin(); it != Llista.end(); it++)
	{
		ret=(*it);

		if (ret->hwnd==h) { 
			MessageBox(NULL, "Handle Coincide con uno", "COINCIDE", MB_OK);
			return true;
		}
	}
	return (false);
}
//////////////////////////////////////////////////////////////////////
bool Window_Handles::IfExists(char exe[50], HWND &houtput)
{
	CHandle * ret = NULL;
	if (exe==NULL) return false;
	houtput=NULL;
/*	if (count==0) {
		MessageBeep(MB_ICONHAND);		
		return false;
	}*/
	std::list<CHandle *>::iterator it;
	for (it = Llista.begin(); it != Llista.end(); it++)
	{
		ret=(*it);

		if (strcmp(ret->exe, exe)==0) {
			houtput=ret->hwnd;
			return true;
		}
	}
	return (false);
}
//////////////////////////////////////////////////////////////////////
bool Window_Handles::Remove(HWND h)
{
	CHandle * ret = NULL;
	
	if (Llista.empty()) return false;
	
	std::list<CHandle *>::iterator it;

	for (it = Llista.begin(); it != Llista.end(); it++)
	{
		ret=(*it);
		if (ret->hwnd==h) {
			Llista.erase(it);
			count--;
			return true;
		}
	}
	return (false);
}
//////////////////////////////////////////////////////////////////////
