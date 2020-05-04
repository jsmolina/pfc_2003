// CurentStatus.cpp: implementation of the CCurrentStatus class.
//
//////////////////////////////////////////////////////////////////////

#include "CurrentStatus.h"
#include <stdlib.h>
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurrentStatus::CCurrentStatus()
{
	tx =0;
	ty =0;
	tz =0;
	rx =0;
	ry =0;
	rz =0;
	bpr_array =NULL; 
	changed=false;
	nbuttons=0;
}

CCurrentStatus::~CCurrentStatus()
{
	register int i;
	for (i = 0; i < nbuttons;i++)
	{
		if (bpr_array[i]!=NULL) delete bpr_array;
	}
}

void CCurrentStatus::SetNumberButtons(int nbuttons)
{
	this->nbuttons=nbuttons;
	bpr_array=new int[nbuttons];
	bpr_interchange=new int[nbuttons];

	for (register int i=0; i < nbuttons;i++)
	{
		this->bpr_array[i]=0;		
		this->bpr_interchange[i]=0;		
	}
	this->tx =0;
	this->ty =0;
	this->tz =0;	
	this->rx =0;
	this->ry =0;
	this->rz =0;
}

int  CCurrentStatus::GetNumberButtons()
{
	return nbuttons;
}