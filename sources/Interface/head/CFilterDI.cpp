#define WRAPPER_EVENTID 949689
#define WM_SPACEBALL 49674

#include "CFilterDI.h" // class header file
#include "CBDades.h"
#define OS_WIN32
#include <si.h>
#include "..\exports.h"
#include "CurrentStatus.h"

//bool last_pressed = false;
extern  CBDades  dbase;
extern CCurrentStatus STATUS_current;
extern CCurrentStatus STATUS_last;
extern HWND hwndj;
extern char buffer_fore[255];
extern HWND	handle_darrera;
extern int SPW_MESSAGE;
//unsigned long bitwise[16]={2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

//////////////////////////////////////////////////////////////////
CFilterDI::CFilterDI(int deadzone) 
{
	m_dead_zone = deadzone;
	event_identifier=0;	
	last_dominant=-1;			
}
//////////////////////////////////////////////////////////////////
bool CFilterDI::DIAxisAssignat(int eixSP, int dispDI)
{
	CConfiguration * c = dbase.GetDevConfig();
	AsignEixos * ae = &(c->theAsignEixos);
	Eix * eix;

	eix = ae->Get(eixSP,  false);
	if (eix!=NULL)
	{
		if (eix->dispDI!=dispDI) return false; // no assignat a aquest dispositiu
		else return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////
bool CFilterDI::DIButtonAssignat(int dispDI, int nBotons)
{
	CConfiguration * c = dbase.GetDevConfig();
	AsignBotons * ab = &(c->theAsignBotons);
	bool retorn = false;

	register int i=0;
	Boto * b;
	
	for (i = 0; i < nBotons; i++)
	{
		b = ab->Get(i, dispDI, true);		

		if (b!= NULL) 
		{			
			retorn=true;			
		}
	}
	return retorn;
}
//////////////////////////////////////////////////////////////////
bool CFilterDI::IsEnqueueable(int dispDI, int nBotons, jsmstatus * st, HWND &output)
{
	bool enqueueable=false;

	
	CConfiguration * c = dbase.GetDevConfig();
	bool enqueuable=false;

	if (c->hTraslacions) // si té habilitades les traslacions
	{
		if(DIAxisAssignat(SI_TX, dispDI)) enqueuable=true;
		if(DIAxisAssignat(SI_TY, dispDI)) enqueuable=true;
		if(DIAxisAssignat(SI_TZ, dispDI)) enqueuable=true;	
	}
	if (c->hRotacions) // si té habilitades les traslacions
	{
		if(DIAxisAssignat(SI_RX, dispDI)) enqueuable=true;
		if(DIAxisAssignat(SI_RY, dispDI)) enqueuable=true;
		if(DIAxisAssignat(SI_RZ, dispDI)) enqueuable=true;
	}
//	if(DIButtonAssignat(dispDI, nBotons)) 
		enqueuable=true;
	///////////////////////////////////////////////////////
	return enqueuable;
}
//////////////////////////////////////////////////////////////////
void  CFilterDI::MapToConfiguration()
{
	// canviar event per satisfer configuracions
	CConfiguration * cc=dbase.GetDevConfig();
	/* ****** SENSIBILITAT GLOBAL  **************** */	
		if (cc->tx==true)
		{
			STATUS_current.tx=STATUS_current.tx*((double)cc->sensibilitat/100);			
			STATUS_current.tx*=((double)cc->panoramitzar/100);
		}
		else 
			STATUS_current.tx=0;

		if (cc->ty==true)
		{
			STATUS_current.ty=STATUS_current.ty*((double)cc->sensibilitat/100)*(-1);
			STATUS_current.ty*=((double)cc->panoramitzar/100);
		}
		else
			STATUS_current.ty=0;

		if (cc->tz==true)
		{
			STATUS_current.tz=STATUS_current.tz*((double)cc->sensibilitat/100)*(-1);
			STATUS_current.tz*=((double)cc->zooming/100);
		}
		else 
			STATUS_current.tz=0;

		if (cc->rx==true)
		{
			STATUS_current.rx=STATUS_current.rx*((double)cc->sensibilitat/100);
			STATUS_current.rx*=((double)cc->rotacions/100);
		}
		else
			STATUS_current.rx=0;

		if (cc->ry==true)
		{
			STATUS_current.ry=STATUS_current.ry*((double)cc->sensibilitat/100);
			STATUS_current.ry*=((double)cc->rotacions/100);
		}
		else
			STATUS_current.ry=0;
		if (cc->rx==true)
		{
			STATUS_current.rz=STATUS_current.rz*((double)cc->sensibilitat/100);
			STATUS_current.rz*=((double)cc->rotacions/100);
		}
		else
			STATUS_current.rz=0;
	
		
		if(cc->hFilt_eixdominant==true)
		{
			// TODO: Mirar quin és el major, i fer tots els altres a zero
			register int i;
			int MAX = 0;
			int ID_MAX=0;
			
			
			if (last_dominant==-1)
			{
				for (i = 0; i < 6; i++)
				{
					switch(i)
					{
					case 0:
						if (abs(STATUS_current.tx)>MAX)
						{
							ID_MAX=SI_TX;
							MAX=abs(STATUS_current.tx);
						}
					break;
					case 1:
						if (abs(STATUS_current.ty)>MAX)
						{
							ID_MAX=SI_TY;
							MAX=abs(STATUS_current.tx);
						}
					break;
					case 2:
						if (abs(STATUS_current.tz)>MAX)
						{
							ID_MAX=SI_TZ;
							MAX=abs(STATUS_current.tx);
						}
					break;
					case 3:
						if (abs(STATUS_current.rx)>MAX)
						{
							ID_MAX=SI_RX;
							MAX=abs(STATUS_current.tx);
						}
					break;
					case 4:
						if (abs(STATUS_current.ry)>MAX)
						{
							ID_MAX=SI_RY;
							MAX=abs(STATUS_current.tx);
						}
					break;
					case 5:
						if (abs(STATUS_current.rz)>MAX)
						{
							ID_MAX=SI_RZ;
							MAX=abs(STATUS_current.tx);
						}
					break;
					} // fi del switch
				} // fi del for
				last_dominant = ID_MAX;
			} // fi de si no tenim un dominant
			else
			{
				ID_MAX = last_dominant;
			}

			switch(ID_MAX)
			{
			case SI_TX:
				STATUS_current.ty=0;
				STATUS_current.tz=0;
				STATUS_current.rx=0;
				STATUS_current.ry=0;
				STATUS_current.rz=0;
				break;
			case SI_TY:
				STATUS_current.tx=0;
				STATUS_current.tz=0;
				STATUS_current.rx=0;
				STATUS_current.ry=0;
				STATUS_current.rz=0;
				break;
			case SI_TZ:
				STATUS_current.tx=0;
				STATUS_current.ty=0;
				STATUS_current.rx=0;
				STATUS_current.ry=0;
				STATUS_current.rz=0;
				break;
			case SI_RX:
				STATUS_current.tx=0;
				STATUS_current.ty=0;
				STATUS_current.tz=0;				
				STATUS_current.ry=0;
				STATUS_current.rz=0;
				break;
			case SI_RY:
				STATUS_current.tx=0;
				STATUS_current.ty=0;
				STATUS_current.tz=0;				
				STATUS_current.rx=0;
				STATUS_current.rz=0;
				break;
			case SI_RZ:
				STATUS_current.tx=0;
				STATUS_current.ty=0;
				STATUS_current.tz=0;				
				STATUS_current.rx=0;
				STATUS_current.ry=0;
				break;
			} // fi del switch(MAX_ID)
				
		} // fi filtre d'eix dominant

		if (cc->y_z_int==true)
		{
			int ty = STATUS_current.ty;
			STATUS_current.ty=STATUS_current.tz;
			STATUS_current.tz=ty;
		}
		AsignEspecials * aesp = &(cc->theAsignEspecials);
		Asignacio * ae;
		int v_intermig = 0;		

		if (aesp->count > 0)
		{
			// TODO: Canviar els eixos segons la configuració interna
			for (register int i = 0; i < STATUS_current.GetNumberButtons(); i++)
			{
				ae = aesp->Get(i);				
				if (STATUS_current.bpr_interchange[ae->boto_modificador]==1)
				{
					switch(ae->eixSP_inicial)
					{
					case SI_TX:
					{
						switch(ae->eixSP_final)
						{						
						case SI_TY:							
							STATUS_current.ty = STATUS_current.tx;							
							STATUS_current.tx = 0;
							STATUS_last.tx =0;
							STATUS_last.ty = 0;							
							return;
						break;
						case SI_TZ:
							//v_intermig = STATUS_current.tz;
							STATUS_current.tz = STATUS_current.tx;							
							STATUS_current.tx = 0;
							STATUS_last.tx =0;
							STATUS_last.tz = 0;														
							return;
						break;
						case SI_RX:
							//v_intermig = STATUS_current.rx;
							STATUS_current.rx = STATUS_current.tx;
							STATUS_current.tx = 0;
							STATUS_last.tx =0;
							STATUS_last.rx = 0;
							return;
						break;
						case SI_RY:
							//v_intermig = STATUS_current.ry;
							STATUS_current.ry = STATUS_current.tx;
							STATUS_current.tx = 0;
							STATUS_last.tx =0;
							STATUS_last.ry = 0;
							return;
						break;
						case SI_RZ:
							//v_intermig = STATUS_current.rz;
							STATUS_current.rz = STATUS_current.tx;
							STATUS_current.tx = 0;
							STATUS_last.tx =0;
							STATUS_last.rz = 0;
							return;
						break;
						}
					
					break;
					}

					case SI_TY:
					{
						switch(ae->eixSP_final)
						{						
						case SI_TX:
							//v_intermig = STATUS_current.tx;
							STATUS_current.tx = STATUS_current.ty;
							STATUS_current.ty = 0;
							STATUS_last.ty =0;
							STATUS_last.tx = 0;
							return;
						break;
						case SI_TZ:
							//v_intermig = STATUS_current.tz;
							STATUS_current.tz = STATUS_current.ty;
							STATUS_current.ty = 0;
							STATUS_last.ty =0;
							STATUS_last.tz = 0;
							return;
						break;
						case SI_RX:
							//v_intermig = STATUS_current.rx;
							STATUS_current.rx = STATUS_current.ty;
							STATUS_current.ty = 0;
							STATUS_last.ty =0;
							STATUS_last.rx = 0;							
							return;
						break;
						case SI_RY:
							//v_intermig = STATUS_current.ry;
							STATUS_current.ry = STATUS_current.ty;
							STATUS_current.ty = 0;
							STATUS_last.ty =0;
							STATUS_last.ry = 0;
							return;
						break;
						case SI_RZ:
							//v_intermig = STATUS_current.rz;
							STATUS_current.rz = STATUS_current.ty;
							STATUS_current.ty = 0;
							STATUS_last.ty =0;
							STATUS_last.rz = 0;
							return;
						break;
						}
					break;
					}

					case SI_TZ:
					{
						switch(ae->eixSP_final)
						{												
						case SI_TX:
							//v_intermig = STATUS_current.tx;
							STATUS_current.tx = STATUS_current.tz;
							STATUS_current.tz = 0;
							STATUS_last.tz =0;
							STATUS_last.tx = 0;
							return;
						break;
						case SI_TY:
							//v_intermig = STATUS_current.ty;
							STATUS_current.ty = STATUS_current.tz;
							STATUS_current.tz = 0;
							STATUS_last.tz =0;
							STATUS_last.ty = 0;
							return;
						break;
						case SI_RX:
							//v_intermig = STATUS_current.rx;
							STATUS_current.rx = STATUS_current.tz;
							STATUS_current.tz = 0;
							STATUS_last.tz =0;
							STATUS_last.rx = 0;
							return;
						break;
						case SI_RY:
							//v_intermig = STATUS_current.ry;
							STATUS_current.ry = STATUS_current.tz;
							STATUS_current.tz = 0;
							STATUS_last.tz =0;
							STATUS_last.ry = 0;
							return;
						break;
						case SI_RZ:
							//v_intermig = STATUS_current.rz;
							STATUS_current.rz = STATUS_current.tz;
							STATUS_current.tz = 0;
							STATUS_last.tz =0;
							STATUS_last.rz = 0;
							return;
						break;
						}
					break;
					}

					case SI_RX:
					{
						switch(ae->eixSP_final)
						{												
						case SI_TX:
							//v_intermig = STATUS_current.tx;
							STATUS_current.tx = STATUS_current.rx;
							STATUS_current.rx = 0;
							STATUS_last.rx =0;
							STATUS_last.tx = 0;
							return;
						break;
						case SI_TY:
							//v_intermig = STATUS_current.ty;
							STATUS_current.ty = STATUS_current.rx;
							STATUS_current.rx = 0;
							STATUS_last.rx =0;
							STATUS_last.ty = 0;
							return;
						break;
						case SI_TZ:
							//v_intermig = STATUS_current.tz;
							STATUS_current.tz = STATUS_current.rx;
							STATUS_current.rx = 0;
							STATUS_last.rx =0;
							STATUS_last.tz = 0;
							return;
						break;
						case SI_RY:
							//v_intermig = STATUS_current.ry;
							STATUS_current.ry = STATUS_current.rx;
							STATUS_current.rx = 0;
							STATUS_last.rx =0;
							STATUS_last.ry = 0;
							return;
						break;
						case SI_RZ:
							//v_intermig = STATUS_current.rz;
							STATUS_current.rz = STATUS_current.rx;
							STATUS_current.rx = 0;
							STATUS_last.rx =0;
							STATUS_last.rz = 0;
							return;
						break;
						}
					break;
					}

					case SI_RY:
					{
						switch(ae->eixSP_final)
						{												
						case SI_TX:
							//v_intermig = STATUS_current.tx;
							STATUS_current.tx = STATUS_current.ry;
							STATUS_current.ry = 0;
							STATUS_last.ry =0;
							STATUS_last.tx = 0;
							return;
						break;
						case SI_TY:
							//v_intermig = STATUS_current.ty;
							STATUS_current.ty = STATUS_current.ry;
							STATUS_current.ry = 0;
							STATUS_last.ry =0;
							STATUS_last.ty = 0;
							return;
						break;
						case SI_TZ:
							//v_intermig = STATUS_current.tz;
							STATUS_current.tz = STATUS_current.ry;
							STATUS_current.ry = 0;
							STATUS_last.ry =0;
							STATUS_last.tz = 0;
							return;
						break;
						case SI_RX:
							//v_intermig = STATUS_current.rx;
							STATUS_current.rx = STATUS_current.ry;
							STATUS_current.ry = 0;
							STATUS_last.ry =0;
							STATUS_last.rx = 0;
							return;
						break;						
						case SI_RZ:
							//intermig = STATUS_current.rz;
							STATUS_current.rz = STATUS_current.ry;
							STATUS_current.ry = 0;
							STATUS_last.ry =0;
							STATUS_last.rz = 0;
							return;
						break;
						}
					break;
					}

					case SI_RZ:
					{
						switch(ae->eixSP_final)
						{												
						case SI_TX:
							//intermig = STATUS_current.tx;
							STATUS_current.tx = STATUS_current.rz;
							STATUS_current.rz = 0;
							STATUS_last.rz =0;
							STATUS_last.tx = 0;
							return;
						break;
						case SI_TY:
							//intermig = STATUS_current.ty;
							STATUS_current.ty = STATUS_current.rz;
							STATUS_current.rz = 0;
							STATUS_last.rz =0;
							STATUS_last.ty = 0;
							return;
						break;
						case SI_TZ:
							//intermig = STATUS_current.tz;
							STATUS_current.tz = STATUS_current.rz;
							STATUS_current.rz = 0;
							STATUS_last.rz =0;
							STATUS_last.tz = 0;
							return;
						break;
						case SI_RX:
							//intermig = STATUS_current.rx;
							STATUS_current.rx = STATUS_current.rz;
							STATUS_current.rz = 0;
							STATUS_last.rz =0;
							STATUS_last.rx = 0;
							return;
						break;						
						case SI_RY:
							//intermig = STATUS_current.ry;
							STATUS_current.ry = STATUS_current.rz;
							STATUS_current.rz = 0;
							STATUS_last.rz =0;
							STATUS_last.ry = 0;
							return;
						break;
						}
					break;
					} // fi del case RZ
					} // fi del switch general
				} // fi del if button=1
			} // fi del FOR d'intercanvi d'eixos
		} // fi del 'if hi ha alguna asignació especial'
		
	return;
}
//////////////////////////////////////////////////////////////////
void CFilterDI::JsmstatusToStatus(jsmstatus * st, int neixos, int nbotons, int dispDI)
{
	CConfiguration * c = dbase.GetDevConfig();
	AsignEixos * ae = &(c->theAsignEixos);
	Eix * eix;
	register int i=0;
	
 i=0;
	if (c->hTraslacions) // si té habilitades les traslacions
	{
		if (ae==NULL) MessageBox(NULL, "AE is null in JsmstatusToEvent", "Error", MB_OK);
		
		// comprovo per la TX
		eix = ae->Get(SI_TX, false);
		//st->nDevice
		if(eix!=NULL) {
			// i si ho és, està amb el dispositiu actual?
			if (eix->dispDI==dispDI) {				
				MapAxis(eix->eixDI, &(STATUS_current.tx), st);
			}
		}	
		// comprovo per la TY
		eix = ae->Get(SI_TY, false);
		
		if(eix!=NULL) {
			// i si ho és, està amb el dispositiu actual?
			if (eix->dispDI==dispDI) {				
				MapAxis(eix->eixDI, &(STATUS_current.ty), st);
			}
		}	
		// comprovo per la TZ
		eix = ae->Get(SI_TZ, false);
		
		if(eix!=NULL) {
			// i si ho és, està amb el dispositiu actual?
			if (eix->dispDI==dispDI) {				
				MapAxis(eix->eixDI, &(STATUS_current.tz), st);
			}
		}
	}
	if (c->hRotacions) // si té habilitades les traslacions
	{
		// comprovo per la RX
		eix = ae->Get(SI_RX, false);
		
		if(eix!=NULL) {
			// i si ho és, està amb el dispositiu actual?
			if (eix->dispDI==dispDI) {				
				MapAxis(eix->eixDI, &(STATUS_current.rx), st);
			}
		}
		// comprovo per la RY
		eix = ae->Get(SI_RY, false);		
		if(eix!=NULL) {
			// i si ho és, està amb el dispositiu actual?
			if (eix->dispDI==dispDI) {				
				MapAxis(eix->eixDI, &(STATUS_current.ry), st);
			}
		}
		// comprovo per la RZ
		eix = ae->Get(SI_RZ, false);		
		if(eix!=NULL) {
			// i si ho és, està amb el dispositiu actual?
			if (eix->dispDI==dispDI) {				
				MapAxis(eix->eixDI, &(STATUS_current.rz), st);
			}
		}
	}
	// ara pels botons
	AsignBotons * ab = &(c->theAsignBotons);

	Boto * b;
	for (i = 0; i < nbotons; i++)
	{
		// per a cada dispositiu, miro que algun dels seus botons
		// estiguin assignats a AssignBotons
		// el fallo es que los botones tienen el mismo nombre en todos!!
		b=NULL;
		b = ab->Get(i, dispDI, true);		
			// Com que guarda el botó inferior pitjat, aquest guardo
			// això es pot canviar a la classe Event
			if (b!= NULL) 
			{
				if (st->b[b->botoDI]!=0)
				{		
					if (b->dispDI==dispDI)
					{
						STATUS_current.bpr_array[b->botoSP]=st->b[b->botoDI];						
						sprintf(buffer_fore, "Push-dispDI=%d\r\n botoSP=%d\r\n botoDI=%d\r\n", b->dispDI, b->botoSP, b->botoDI);
					}
				}	
				
			}		
	}
}
//////////////////////////////////////////////////////////////////
void CFilterDI::MapAxis(int eixDI, int * output, jsmstatus *st)
{
	switch(eixDI)
	{
		case 0: // assignat per la X
			(*output)=st->x;
			return;
		break;
		case 1: // assignat per la Y
			(*output)=st->y;
			return;
		break;
		case 2: // assignat per la Z
			(*output)=st->z;
			return;
		break;
		case 3: //rx
			(*output)=st->raxis[0];
		break;
		case 4://ry
			(*output)=st->raxis[1];
		break;
		case 5://rz
			(*output)=st->raxis[2];
		break;
		case 6://pov1
			(*output)=st->eixpov[0];
		break;
		case 7://pov2
			(*output)=st->eixpov[1];
		break;
		case 8://pov3
			(*output)=st->eixpov[2];
		break;
		case 9://pov4
			(*output)=st->eixpov[3];
		break;
		case 10://slider1
			(*output)=st->eixslider[0];
		break;
		case 11://slider2
			(*output)=st->eixslider[1];
		break;
		// TODO: Encara es podrien mapejar més eixos, però això
		//       encara no ho faré <RETURN HERE>
	}
}
//////////////////////////////////////////////////////////////////
void CFilterDI::FilterDeadZone()
{
	if (m_dead_zone>abs(STATUS_current.rx)) STATUS_current.rx = 0;	
	if (m_dead_zone>abs(STATUS_current.ry)) STATUS_current.ry = 0;
	if (m_dead_zone>abs(STATUS_current.rz)) STATUS_current.rz = 0;
	if (m_dead_zone>abs(STATUS_current.tx)) STATUS_current.tx = 0;
	if (m_dead_zone>abs(STATUS_current.ty)) STATUS_current.ty = 0;
	if (m_dead_zone>abs(STATUS_current.tz)) STATUS_current.tz = 0;
}
//////////////////////////////////////////////////////////////////
int CFilterDI::CompareGenerateAndSend()
{
	Event *			e=NULL;
	int				len = 0;
	HWND			hWnd=NULL;
	HWND			hwnd_real=NULL;
	HWND			output=NULL;
	int				tipus_enviat = 0;
	register int	i=0;
	bool			boto_activat=false;
	bool			event_moviment=false;
	Window_Handles* wh = dbase.GetWindowHandles();

	hWnd	= GetForegroundWindow();
	hwnd_real=hWnd;

	if(GetTopWindow(hWnd)!=NULL)
	{		
		hWnd=GetTopWindow(hWnd);
	}
	// la finestra no era bona?	
	CHandle * handle;
	handle=wh->Get(hWnd);
	
	if (handle==NULL) {
	//	sprintf(buffer_fore, "No window is detected ");
		if (handle_darrera!=NULL) output=handle_darrera;
		else return -1; // cap event enviat
	}
	else {	
		output = handle->hwnd;
		//output = hwnd_real;
	}
	
	if(hwnd_real!=NULL) hWnd =hwnd_real;
	//if(!wh->IfExists(hwnd_real, output)) return -1; // cap event enviat
	handle_darrera=output;
		//output
	sprintf(buffer_fore, " hwnd_getfore=%x\r\nhwnd donat=%x\r\n", hWnd, output);
	// enviarem un event de moviment?
	if ((STATUS_current.tx!=0) || (STATUS_current.ty!=0) ||(STATUS_current.tz!=0) || (STATUS_current.rx!=0) ||(STATUS_current.ry!=0) || (STATUS_current.rz!=0))
	{
		if (STATUS_current.tx != STATUS_last.tx) {
			tipus_enviat=1;
			STATUS_last.tx = STATUS_current.tx;
			// generar i enviar event de moviment en TX
			event_moviment=true;
		}
		if (STATUS_current.ty != STATUS_last.ty) {
			tipus_enviat=1;
			STATUS_last.ty = STATUS_current.ty;
			// generar i enviar event de moviment en TY
			event_moviment=true;
		}
		if (STATUS_current.tz != STATUS_last.tz) {
			tipus_enviat=1;
			STATUS_last.tz = STATUS_current.tz;
			// generar i enviar event de moviment en TZ
			event_moviment=true;
		}
		if (STATUS_current.rx != STATUS_last.rx) {
			tipus_enviat=1;
			STATUS_last.rx = STATUS_current.rx;
			// generar i enviar event de moviment en RX
			event_moviment=true;
		}
		if (STATUS_current.ry != STATUS_last.ry) {
			tipus_enviat=1;
			STATUS_last.ry = STATUS_current.ry;
			// generar i enviar event de moviment en TZ
			event_moviment=true;
		}
		if (STATUS_current.rz != STATUS_last.rz) {
			tipus_enviat=1;
			STATUS_last.rz = STATUS_current.rz;
			// generar i enviar event de moviment en RX
			event_moviment=true;
		}
		/// TEMPORAL: Experiment d'usabilitat
		
		tipus_enviat=1;
		event_moviment=true;
		////////////////////////////////////////
		////////////////////////////////////////////////////////////
		//----- SI HEM DETECTAT MOVIMENT --------------------------//
		/////////////////////////////////////////////////////////////
		if (event_moviment==true)
		{
			e		= new Event();			
			// identificador (i posició) del event
			if (event_identifier >= 10000) event_identifier=-1;
			event_identifier++;
			e->motion=1; e->boto=-1; e->butwise=0;
			e->hwnd=hWnd; e->id=event_identifier;
			e->rx=STATUS_current.rx; e->ry=STATUS_current.ry;
			e->rz=STATUS_current.rz;
			e->tx=STATUS_current.tx; e->ty=STATUS_current.ty;
			e->tz=STATUS_current.tz;
			PushEvent(e);
			//::PostMessage(output, WM_PAINT, WRAPPER_EVENTID, e->id);	
			::PostMessage(output, WM_SPACEBALL, WRAPPER_EVENTID, e->id);				
		}
	}
	else 
	{
		if ((STATUS_current.tx ==0) && (STATUS_last.tx!=0)) {
			tipus_enviat=2;
			STATUS_last.tx = 0;
			// enviar event de tipus zero
			//::PostMessage(output, WM_PAINT, WRAPPER_EVENTID,SI_ZERO_EVENT);
			::PostMessage(output, WM_SPACEBALL, WRAPPER_EVENTID, SI_ZERO_EVENT);	
			last_dominant=-1;
		}
		if ((STATUS_current.ty ==0) && (STATUS_last.ty!=0)) {
			tipus_enviat=2;
			STATUS_last.ty = 0;
			// enviar event de tipus zero
			//::PostMessage(output, WM_PAINT, WRAPPER_EVENTID,SI_ZERO_EVENT);
			::PostMessage(output, WM_SPACEBALL, WRAPPER_EVENTID, SI_ZERO_EVENT);	
			last_dominant=-1;
		}
		if ((STATUS_current.tz ==0) && (STATUS_last.tz!=0)) {
			tipus_enviat=2;
			STATUS_last.tz = 0;
			// enviar event de tipus zero
			//::PostMessage(output, WM_PAINT, WRAPPER_EVENTID,SI_ZERO_EVENT);			
			::PostMessage(output, WM_SPACEBALL, WRAPPER_EVENTID, SI_ZERO_EVENT);	
			last_dominant=-1;
		}
		if ((STATUS_current.rx ==0) && (STATUS_last.rx!=0)) {
			tipus_enviat=2;
			STATUS_last.rx = 0;
			// enviar event de tipus zero
			//::PostMessage(output, WM_PAINT, WRAPPER_EVENTID,SI_ZERO_EVENT);			
			::PostMessage(output, WM_SPACEBALL, WRAPPER_EVENTID, SI_ZERO_EVENT);	
			last_dominant=-1;
		}
		if ((STATUS_current.ry ==0) && (STATUS_last.ry!=0)) {
			tipus_enviat=2;
			STATUS_last.ry = 0;
			// enviar event de tipus zero
			//::PostMessage(output, WM_PAINT, WRAPPER_EVENTID,SI_ZERO_EVENT);
			::PostMessage(output, WM_SPACEBALL, WRAPPER_EVENTID, SI_ZERO_EVENT);	
			last_dominant=-1;
		}
		if ((STATUS_current.rz ==0) && (STATUS_last.rz!=0)) {
			tipus_enviat=2;
			STATUS_last.rz = 0;
			// enviar event de tipus zero
			//::PostMessage(output, WM_PAINT, WRAPPER_EVENTID,SI_ZERO_EVENT);
			::PostMessage(output, WM_SPACEBALL, WRAPPER_EVENTID, SI_ZERO_EVENT);	
			last_dominant=-1;
		}
	}
	// enviarem un event de botó?
	for (i = 0; i < STATUS_current.GetNumberButtons(); i++)
	{
		if(STATUS_current.bpr_array[i]==1) 
		{
			boto_activat=true;
			// mirar si en last no va estar activat
			if (STATUS_last.bpr_array[i]!=1) // primera activació
			{
				tipus_enviat=3; // push
				STATUS_last.bpr_array[i]=1;
				// ENVIAR PUSH
				// pels intercanvis d'eixos	
				STATUS_current.bpr_interchange[i]=1;
					e		= new Event();			
					// identificador (i posició) del event
					if (event_identifier >= 10000) event_identifier=-1;
					event_identifier++;
					// si yo reservo para dos posiciones, ni puedo llenar 
					// la posición 5, ni puedo 
					e->motion=2; e->boto=i+1;
					e->hwnd=hWnd; e->id=event_identifier;
					e->rx=0; e->ry=0; e->rz=0;e->tx=0; e->ty=0;
					e->tz=0;
					PushEvent(e);
					//::PostMessage(output, WM_PAINT, WRAPPER_EVENTID,e->id);
					::PostMessage(output, WM_SPACEBALL, WRAPPER_EVENTID, e->id);	
					
			}
		}
		else if (STATUS_current.bpr_array[i]==0)
		{
			if (STATUS_last.bpr_array[i]==1)
			{
				tipus_enviat=4; // release
				STATUS_last.bpr_array[i]=0;
				// ENVIAR RELEASE
				// pels intercanvis d'eixos
				STATUS_current.bpr_interchange[i]=0;
					e		= new Event();			
					// identificador (i posició) del event
					if (event_identifier >= 10000) event_identifier=-1;
					event_identifier++;
					
					e->motion=3; e->boto=i+1;
					e->hwnd=hWnd; e->id=event_identifier;
					e->rx=0; e->ry=0; e->rz=0;e->tx=0; e->ty=0;
					e->tz=0;
					PushEvent(e);
					//::PostMessage(output, WM_PAINT, WRAPPER_EVENTID,e->id);
					::PostMessage(output, WM_SPACEBALL, WRAPPER_EVENTID, e->id);	
			}
		}
	}
	if (e!=NULL) delete e;		

	return tipus_enviat;
}