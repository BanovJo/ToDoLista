
// ToDoListaApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
//#include "afxdb.h"


// CToDoListaAppApp:
// See ToDoListaApp.cpp for the implementation of this class
//

class CToDoListaAppApp : public CWinApp
{
public:
	CToDoListaAppApp();

	
// Overrides
public:
	virtual BOOL InitInstance();
	static CDatabase* Connect();
	static void Disconnect(CDatabase*);
	
// Implementation
	DECLARE_MESSAGE_MAP()
};

extern CToDoListaAppApp theApp;
