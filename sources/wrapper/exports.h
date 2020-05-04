#ifndef EXPORTS_H
#define EXPORTS_H

// Defineix la informació sobre les longituds (estàtiques)
#define LONG_QUEUE 10001
#define LONG_STRING 255
#define WRAPPER_EVENTID 949689

typedef struct {
	long id; // identificador del event
	int tx, ty, tz; // eixos de translacions que generen el event
	int rx, ry, rz; // eixos de rotacions que generen el event
	int boto;   // boto SpaceWare que va generar el event
	unsigned long butwise;
	short motion; // -1->no_inicialitzat 1->moviment 2->botó 3->boto+moviment 4->release event
	HWND  hwnd; // aplicació de les registrades que estava focalitzada quan es va crear el event	
}Event;

typedef struct {
	char bios [LONG_STRING];
	char model_str[LONG_STRING];
	int dll_major;
	int dll_minor;
	int model;
	int eixos;
	int botons;
	int major;
	int minor;
	bool can_beep;
}Devinfo;

typedef struct {
	char registered_exe[LONG_STRING]; // amb això sabem més precisament la aplicació
	HWND registered_hwnd;

}App_Register;

#endif