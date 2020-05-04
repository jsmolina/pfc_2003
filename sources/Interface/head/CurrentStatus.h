// CurentStatus.h: interface for the CCurrentStatus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURENTSTATUS_H__3D1B179B_9243_4471_BC4A_127F78931D54__INCLUDED_)
#define AFX_CURENTSTATUS_H__3D1B179B_9243_4471_BC4A_127F78931D54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCurrentStatus  
{
public:
	CCurrentStatus();
	void SetNumberButtons(int nbuttons);
	int  GetNumberButtons();
	virtual ~CCurrentStatus();
		void operator =  ( const CCurrentStatus &cur )   
		{ 
			tx = cur.tx; ty = cur.ty; tz = cur.tz; rx=cur.tx; ry=cur.ry; rz=cur.rz;  
			nbuttons=cur.nbuttons;  changed=cur.changed; bpr_array = new int[nbuttons]; 
			for (register int i; i < nbuttons; i++) bpr_array[i]=cur.bpr_array[i];
		}



	int tx, ty, tz; // eixos de translacions que generen el event
	int rx, ry, rz; // eixos de rotacions que generen el event
	
	int * bpr_array; // array que necessita ser dimensionat
	int * bpr_interchange;
	bool changed;
protected:
	int nbuttons;
};

#endif // !defined(AFX_CURENTSTATUS_H__3D1B179B_9243_4471_BC4A_127F78931D54__INCLUDED_)
