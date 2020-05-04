#include "AsignEspecials.h" // class header file
//#include "Asignacio.h"
#include <stdlib.h>
#include <windows.h>

/////////////////////////////////////////////////////////////////
AsignEspecials::AsignEspecials()
{
	Llista.clear();
	count =0;	
}
/////////////////////////////////////////////////////////////////
AsignEspecials::~AsignEspecials()
{
	Asignacio * bnext;

	std::list<Asignacio*>::iterator it;
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
void AsignEspecials::Add(int boto_modificador, int eixSP_final, int eixSP_inicial)
{
	Asignacio * a = new Asignacio();
	
	a->boto_modificador=boto_modificador;
	a->eixSP_final=eixSP_final;
	a->eixSP_inicial=eixSP_inicial;

	Llista.push_back(a);
	count++;	
}
/////////////////////////////////////////////////////////////////
void AsignEspecials::Add(Asignacio * a)
{	
	Llista.push_back(a);
	count++;
}
/////////////////////////////////////////////////////////////////
Asignacio *AsignEspecials::Get(int boto_modificador)
{
	Asignacio *aaux;	
	if (Llista.empty()) return NULL;
		std::list<Asignacio*>::iterator it;
		for (it = Llista.begin(); it != Llista.end(); it++)
		{
			aaux=(*it);
			if (aaux->boto_modificador==boto_modificador) return aaux;
		}
	return aaux;
}
//////////////////////////////////////////////////////////////////////
std::list<Asignacio *> AsignEspecials::GetList()
{	
	return Llista;
}
//////////////////////////////////////////////////////////////////////
void AsignEspecials::SetList(std::list<Asignacio *> &Llistanew, int co)
{	
	Llista = Llistanew;
	count = co;
}
//////////////////////////////////////////////////////////////////////
int AsignEspecials::GetCount()
{
	return count;
}
/////////////////////////////////////////////////////////////////////
void AsignEspecials::Reset()
{
	Asignacio * bnext;

	std::list<Asignacio*>::iterator it;
	for (it = Llista.begin(); it != Llista.end(); it++)
	{		
		bnext=(*it);
		if (bnext!=NULL)
			delete bnext; // part perillosa, però que cal alliberar memòria
	}
	count=0;
	Llista.clear();
}