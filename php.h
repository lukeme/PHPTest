// php.h : main header file for the PHP application
//

#if !defined(AFX_PHP_H__861815F4_2DAE_4F7F_B3A3_9885D77A7FE8__INCLUDED_)
#define AFX_PHP_H__861815F4_2DAE_4F7F_B3A3_9885D77A7FE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPhpApp:
// See php.cpp for the implementation of this class
//

class CPhpApp : public CWinApp
{
public:
	CPhpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPhpApp)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHP_H__861815F4_2DAE_4F7F_B3A3_9885D77A7FE8__INCLUDED_)
