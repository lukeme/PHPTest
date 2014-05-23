// phpDlg.h : header file
//

#if !defined(AFX_PHPDLG_H__E3675C83_0000_4F64_8B41_537C3434504D__INCLUDED_)
#define AFX_PHPDLG_H__E3675C83_0000_4F64_8B41_537C3434504D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPhpDlg dialog

class CPhpDlg : public CDialog
{
// Construction
public:
	CPhpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPhpDlg)
	enum { IDD = IDD_PHP_DIALOG };
	CEdit	m_outputCtl;
	CEdit	m_inputCtl;
	CString	m_input;
	CString	m_output;
	CString m_phpdir;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhpDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPhpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHotKey(WPARAM wp,LPARAM lp);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnMenuClear();
	afx_msg void OnMenuExec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHPDLG_H__E3675C83_0000_4F64_8B41_537C3434504D__INCLUDED_)
