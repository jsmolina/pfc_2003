#ifndef Event_H
#define Event_H
#include <stdlib.h>
#include "DirectInput/dinput_f.h"



// Estructura de dades per guardar events
typedef struct {
	long id; // identificador del event
	int tx, ty, tz; // eixos de translacions que generen el event
	int rx, ry, rz; // eixos de rotacions que generen el event
	int boto;   // boto SpaceWare que va generar el event
	unsigned long butwise;
	short motion; // -1->no_inicialitzat 1->moviment 2->botó 3->boto+moviment 4->release event
	HWND  hwnd; // aplicació de les registrades que estava focalitzada quan es va crear el event	
}Event;


#endif // Event_H
