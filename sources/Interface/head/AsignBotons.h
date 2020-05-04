#ifndef AsignBotons_H
#define AsignBotons_H
#include <list>
#include "Boto.h"



		class AsignBotons {
			private:
//				Boto * pLlistabotons;	
				std::list<Boto *> Llista;				
			public:
				int count;
				AsignBotons(); // constructor
				~AsignBotons(); // destructor
				void Reset();
				void Add(int BotoDI, int BotoSP, int DispDI); // add element
				void Add(Boto *b); // add element
				//void Remove(); // remove element
				Boto *Get(int num, int dispDI, bool DI);	// si DI FALSE, busca per SP
				int GetCount();	// retorna el número d'elements en la llista
				void SetList(std::list<Boto *> &Llistanew, int co);
				std::list<Boto *> GetList(); // get pointer to first element
		};

#endif 