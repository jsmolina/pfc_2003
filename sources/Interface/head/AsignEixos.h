#ifndef AsignEixos_H
#define AsignEixos_H
#include "Eix.h"
#include <list>


		class AsignEixos {
			private:
				int count;
				std::list<Eix *> Llista;
			public:
				AsignEixos(); // constructor
				~AsignEixos(); // destructor
				void Add(int dispDI, int eixDI, int eixSP); // add element
				void Add(Eix *e); // add element				
				Eix *Get(int eix, bool DI);	// si DI FALSE, busca per SPaceware
				bool IfExists(int eix, bool DI);	// si DI FALSE, busca per SP i retorna true si està a la llista
				int GetCount();	// retorna el número d'elements en la llista
				void AsignEixos::SetList(std::list<Eix *> &Llistanew, int co);
				std::list<Eix *> GetList(); // get pointer to first element
				void Reset(); // resetejar la llista sencera
		};

#endif // AsignEixos_H
