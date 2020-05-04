#ifndef EXPORTS_H
#define EXPORTS_H

#define OS_WIN32
#include <si.h>  // dades de tipus SpaceMouse
#include <Asignacio.h> // tipus simple (estructura)
#include <AsignBotons.h> // Asignacions de botons
#include <AsignEixos.h>  // Asignacions d'Eixos
#include <AsignEspecials.h>  // Asignacions de canvis en temps real
#include <Boto.h> // tipus simple (estructura)
#include <CConfiguration.h> // configuració del driver
//#include <CDevInfo.h> // informació del dispositiu
#include <CFilterDI.h> // filtratge de events
#include <Eix.h> // tipus simple(estructura)
#include <Event.h> // tipus simple (estructura)
#include <Handle.h> // tipus simple(estructura)
//#include <Queue.h>  // cua d'events per ser enviats
#include <Window_Handles.h> // llista de handles de finestres registrades
//#include <CSiappmfc.h> // comunicació d'aquesta aplicació amb wrapper.dll
#include <CBDades.h> // base de dades centralitzada


bool			IsInitialized(); // saber si el driver està carregat
void			Initialize();    // carregar el driver i les variables
void			Terminate();
void			ExeInit();
void			ChangeConfig(Devinfo * d);
bool			IsNewRegister();
bool			IsNewUnRegister();
void			PushEvent(Event *e);
HWND			GetApp();
HWND			GetUnApp();






#endif