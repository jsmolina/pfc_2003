#ifndef CConfiguration_H
#define CConfiguration_H
#include "AsignBotons.h"
#include "AsignEixos.h"
#include "AsignEspecials.h"

#ifdef WRAPPER_EXPORTS
#define WRAPPER_API __declspec(dllexport)
#else
#define WRAPPER_API __declspec(dllimport)
#endif

		class CConfiguration {
			public:
				int sensibilitat;
				bool hFilt_eixdominant;
				bool y_z_int;
				bool hTraslacions;
				bool tx;
				bool ty;
				bool tz;
				bool hRotacions;
				bool rx;
				bool ry;
				bool rz;
				bool beep_act;
				int panoramitzar;
				int rotacions;
				int zooming;			
				AsignBotons theAsignBotons;
				AsignEixos theAsignEixos;
				AsignEspecials theAsignEspecials;
		};

#endif // CConfiguration_H
