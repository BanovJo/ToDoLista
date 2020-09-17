
// ToDoListaApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
//#include "afxdb.h"


// CToDoListaApp:
// See ToDoListaApp.cpp for the implementation of this class
//

class CToDoListaApp : public CWinApp
{
public:
	CToDoListaApp();


	// Overrides
public:
	virtual BOOL InitInstance();
	BOOL Connect(CDatabase& database);

	// Implementation
	DECLARE_MESSAGE_MAP()
};

extern CToDoListaApp theApp;
