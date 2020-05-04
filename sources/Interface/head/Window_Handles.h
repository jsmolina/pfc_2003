#ifndef Window_Handles_H
#define Window_Handles_H
#include <windows.h>
#include "Handle.h"
#include <list>

		class Window_Handles {
			public:
				Window_Handles();
				~Window_Handles();
				void Add(HWND h);
				void Add(HWND h, char exe[50]);
				bool Remove(HWND h);
				bool IfExists(HWND h);
				bool IfExists(char exe[50], HWND &houtput);
				CHandle * Get(HWND h);			
				int count;
			private:							
				std::list<CHandle *> Llista;				
		};

#endif // Window_Handles_H
