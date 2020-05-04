#include "AsignEixos.h" // class header file
#include <stdio.h>
#include "windows.h"


/////////////////////////////////////////////////////////////////
AsignEixos::AsignEixos()
{
	Llista.clear();
	count =0;	
}
/////////////////////////////////////////////////////////////////
AsignEixos::~AsignEixos()
{
	Eix * bnext;

	std::list<Eix*>::iterator it;
	for (it = Llista.begin(); it != Llista.end(); it++)
	{
		bnext=(*it);
		if (bnext!=NULL)
			delete bnext; // part perillosa, però que cal alliberar memòria
	}
	Llista.clear();
	count =0;
}
/////////////////////////////////////////////////////////////////
void AsignEixos::Add(int dispDI, int eixDI, int eixSP)
{
	Eix * e = new Eix();
	
	e->eixDI=eixDI;
	e->eixSP=eixSP;
	e->dispDI=dispDI;
	Llista.push_back(e);


	count++;
}
/////////////////////////////////////////////////////////////////
void AsignEixos::Add(Eix * e)
{	
	Llista.push_back(e);


	count++;
}
/////////////////////////////////////////////////////////////////
Eix *AsignEixos::Get(int eix, bool DI)
{
	Eix *eaux;
	
	if (Llista.empty()) return NULL;
	if (DI) 
	{
		std::list<Eix*>::iterator it;
		for (it = Llista.begin(); it != Llista.end(); it++)
		{
			eaux=(*it);
			if (eaux->eixDI==eix) return eaux;
		}

	}
	else {
		// retorna el botó a partir de siapp
		std::list<Eix*>::iterator it;
		for (it = Llista.begin(); it != Llista.end(); it++)
		{
			eaux=(*it);
			if (eaux->eixSP==eix) return eaux;
		}
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////
bool AsignEixos::IfExists(int eix, bool DI)
{
	
	Eix * eaux =NULL;
	
	if (Llista.empty()) return false;
	if (count <=0) {		
		PostQuitMessage(0);		
		return false;
	}
	
	if (DI) 
	{
		std::list<Eix*>::iterator it;
		for (it = Llista.begin(); it != Llista.end(); it++)
		{
			eaux=(*it);
			if (eaux->eixDI==eix) return true;
		}
	}
	else {
		std::list<Eix*>::iterator it;
		for (it = Llista.begin(); it != Llista.end(); it++)
		{
			eaux=(*it);
			if (eaux->eixSP==eix) return true;
		}	
	}	
return(false);
}

//////////////////////////////////////////////////////////////////////
std::list<Eix *> AsignEixos::GetList()
{	
	return Llista;
}
//////////////////////////////////////////////////////////////////////
void AsignEixos::SetList(std::list<Eix *> &Llistanew, int co)
{	
//	copy(Llistanew.begin(), Llistanew.end(), Llista.begin());
	Llista = Llistanew;
	count = co;
}
//////////////////////////////////////////////////////////////////////
int AsignEixos::GetCount()
{
	return count;
}

//////////////////////////////////////////////////////////////////
void AsignEixos::Reset()
{
	Eix * bnext;

	std::list<Eix*>::iterator it;
	for (it = Llista.begin(); it != Llista.end(); it++)
	{
		bnext=(*it);
		if (bnext!=NULL)
			delete bnext; // part perillosa, però que cal alliberar memòria
	}
	count=0;
	Llista.clear();
}