#ifndef AsignEspecials_H
#define AsignEspecials_H
#include "Asignacio.h"
#include <list>

		class AsignEspecials {
			private:
				std::list<Asignacio *> Llista;								
			public:
				AsignEspecials(); // constructor
				~AsignEspecials(); // destructor				
				void Add(int boto_modificador, int eixSP_final, int eixSP_inicial); // add element
				void Add(Asignacio *a); // add element				
				Asignacio *Get(int boto_modificador);
				int GetCount();	// retorna el número d'elements en la llista
				void SetList(std::list<Asignacio * > &Llistanew, int co);
				std::list<Asignacio *> GetList(); // get pointer to first element
				void Reset(); // reset the list
				// membres:
				int count;
		};

#endif // AsignEspecials_H
