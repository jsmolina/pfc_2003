#include "AsignBotons.h" // class header file
#include <stdlib.h>
#include <windows.h>
/////////////////////////////////////////////////////////////////
AsignBotons::AsignBotons()
{
	Llista.clear();
	count =0;
}
/////////////////////////////////////////////////////////////////
AsignBotons::~AsignBotons()
{
	Boto * bnext;

	std::list<Boto*>::iterator it;
	for (it = Llista.begin(); it != Llista.end(); it++)
	{
		bnext=(*it);
		if (bnext != NULL)
			delete bnext; // part perillosa, però que cal alliberar memòria
	}
	Llista.clear();
	count =0;
}
/////////////////////////////////////////////////////////////////
void AsignBotons::Add(int BotoDI, int BotoSP, int DispDI)
{
	Boto * b = new Boto();

	b->botoDI=BotoDI;
	b->botoSP=BotoSP;
	b->dispDI=DispDI;

	Llista.push_back(b);
	count++;
	
}
/////////////////////////////////////////////////////////////////
void AsignBotons::Add(Boto * b)
{	
	Llista.push_back(b);
	count++;
}
/////////////////////////////////////////////////////////////////
Boto *AsignBotons::Get(int num, int dispDI,  bool DI)
{
	Boto *baux;
	if (Llista.empty()) return NULL;
	
	std::list<Boto*>::iterator it;
	if (DI) 
	{		
		for (it = Llista.begin(); it != Llista.end(); it++)
		{
			baux=(*it);
			if ((baux->botoDI==num)&&(baux->dispDI==dispDI)) return baux;
		}
	}
	else {
		// retorna el botó a partir de siapp
		
		for (it = Llista.begin(); it != Llista.end(); it++)
		{
			baux=(*it);
			if (baux->botoSP==num) return baux;
		}
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////
std::list<Boto *> AsignBotons::GetList()
{	
	return Llista;
}
//////////////////////////////////////////////////////////////////////
void AsignBotons::SetList(std::list<Boto *> &Llistanew, int co)
{	
//	copy(Llistanew.begin(), Llistanew.end(), Llista.begin());
	Llista = Llistanew;
	count = co;
}
//////////////////////////////////////////////////////////////////////
int AsignBotons::GetCount()
{
	return count;
}
///////////////////////////////////////////////////////////////////
void AsignBotons::Reset()
{
	Boto * bnext;

	std::list<Boto*>::iterator it;
	for (it = Llista.begin(); it != Llista.end(); it++)
	{
		bnext=(*it);
		if (bnext != NULL)
			delete bnext; // part perillosa, però que cal alliberar memòria
	}

	count=0;
	Llista.clear();
}