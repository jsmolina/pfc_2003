#ifndef Asignacio_H
#define Asignacio_H
#include <stdlib.h>

		class Asignacio {
			public:
				Asignacio() {
					boto_modificador=-1;
//					pNext=NULL;
				}
			//	Asignacio * pNext;
				int boto_modificador;
				int eixSP_inicial;
				int eixSP_final;				
		};

#endif // Asignacio_H
