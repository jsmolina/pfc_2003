#ifndef CFilterDI_H
#define CFilterDI_H
#include "Event.h"

extern Event event_historical;

class CFilterDI {
	private:
		int m_dead_zone; // zona morta: on el event no tindrà valor (per dispositius sorollosos)
		unsigned long event_identifier; // identificador únic d'events
		int last_dominant;
	public:
		CFilterDI(int deadzone); // construeix el objecte i assigna la zona morta dels dispositius
		bool IsEnqueueable(int dispDI,int nBotons, jsmstatus * st, HWND &output);
	//	bool IsEnqueueable(int dispDI, Event *event, HWND &output); // retorna si el event val la pena guardar-lo per les finestres
		void  MapToConfiguration(); // modifica el STATUS_current per tal de poder correspondre amb la configuració actual
		int CompareGenerateAndSend(); // a partir de STATUS_current, generarà un event més compatible amb l'aplicació SpaceWare i l'enviarà cap a l'aplicació
		void JsmstatusToStatus(jsmstatus * st, int neixos, int nbotons, int dispDI); // agafa el status donat, i l'assigna a la variable global current_status
		void FilterDeadZone(); // filtra perquè els moviments inferiors a la zona morta es converteixin en zero
	protected:
		bool DIAxisAssignat(int eixSP, int dispDI); // està assignat el eix a un dispositiu DirectInput
		bool DIButtonAssignat(int dispDI, int nBotons); // està assignat el boto a un dispositiu DirectInput
		void MapAxis(int eixDI, int * output, jsmstatus *st);		
};

#endif // CFilterDI_H
/*
	Classe CFilter
	--------------- NORMES DELS FILTRES -------------------------
	1- Un filtre pot tenir una 'zona morta'
	2- Només ens interessen aquells eixos que seràn mapejats
	3- Igualment, només interessen els botons que seràn mapejats
	4- Al filtre es podrien aplicar les configuracions escollides
	   dintre de la GUI (sensibilitat, ...)
	5- Quan estigui filtrat, ja només caldrà guardar-ho a la cua
	   d'events
	6- Retornar el HWND de la aplicació ACTIVA de les que tinguem
	   a la llista.
	*/