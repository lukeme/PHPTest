// phpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "php.h"
#include "phpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhpDlg dialog

CPhpDlg::CPhpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPhpDlg)
	m_input = _T("");
	m_output = _T("");
	m_phpdir = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CPhpDlg)
	DDX_Control(pDX, IDC_OUTPUT, m_outputCtl);
	DDX_Control(pDX, IDC_INPUT, m_inputCtl);
	DDX_Text(pDX, IDC_INPUT, m_input);
	DDX_Text(pDX, IDC_OUTPUT, m_output);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPhpDlg, CDialog)
	//{{AFX_MSG_MAP(CPhpDlg)
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_CLEAR, OnMenuClear)
	ON_COMMAND(ID_MENU_EXEC, OnMenuExec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhpDlg message handlers

BOOL CPhpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	::RegisterHotKey(m_hWnd,199,MOD_ALT,'X');

	CFileFind ff;
	int IsFile=ff.FindFile(".\\config.ini");
	if(!IsFile){
		AfxMessageBox("请在config.ini中设定php-cgi.exe的位置");
		::WritePrivateProfileString("php","dir", "D:wamp\\php\\php-cgi.exe",".\\config.ini");
	}

	// 从配置文件中读取php-cgi.exe的路径
	::GetPrivateProfileString("php","dir","default", m_phpdir.GetBuffer(_MAX_PATH), _MAX_PATH,".\\config.ini");

	//	若不存在test.php，则创建之
	if(!ff.FindFile(".\\test.php")){
		CFile file;
		CString str = "<?php\n\tprint_r(range(1,10)); \n?>";
		file.Open("test.php",CFile::modeCreate|CFile::modeWrite);
		file.Write(str,str.GetLength());
		file.Close();
	}

	// 拼接得到当前目录下的php文件路径
	CFile myFile;
	if(myFile.Open(".\\test.php",CFile::modeReadWrite))
	{
		CString str;
		myFile.Read(str.GetBuffer(myFile.GetLength()),myFile.GetLength());
		GetDlgItem(IDC_INPUT)->SetWindowText(str);
	}
	
	myFile.Close();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPhpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPhpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPhpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPhpDlg::OnHotKey(WPARAM wp,LPARAM lp)//热键
{
	if(wp==199)
	{
		if(IsWindowVisible())
			ShowWindow(SW_HIDE);
		else
			ShowWindow(SW_SHOWNORMAL);
	}
}

void CPhpDlg::OnOK() 
{
	m_inputCtl.GetWindowText(m_input);

	// 拼接得到当前目录下的php文件路径
	char chPath[301];
	::GetCurrentDirectory(300,(LPTSTR)chPath);//得到当前目录
	char path[10]= "\\test.php";
	strcat(chPath, path);

	CFile myFile;
	try{
		if(myFile.Open(".\\test.php",CFile::modeCreate|CFile::modeReadWrite))
		{
			myFile.SeekToBegin();
			myFile.Write((unsigned char *)(m_input.GetBuffer(0)),m_input.GetLength());
			myFile.Flush();
			myFile.Close();
		}
		else
		{
			AfxMessageBox("test.php写入失败");
		}

	}catch(CFileException *e){
		CString str;
		str.Format("写入失败的原因是:%d",e->m_cause);
		MessageBox("str");
		myFile.Abort();
		e->Delete();
	}
	

	//命名管道的创建：
	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES)};
	sa.bInheritHandle = 1;
	sa.lpSecurityDescriptor = NULL;
	
	HANDLE hStdoutR, hStdoutW, hStdinR, hStdinW;
	CreatePipe(&hStdoutR, &hStdoutW, &sa, 0);
	SetHandleInformation(hStdoutR,HANDLE_FLAG_INHERIT, 0);
	CreatePipe(&hStdinR, &hStdinW, &sa, 0);
	SetHandleInformation(hStdinW, HANDLE_FLAG_INHERIT, 0);
	

	//启动php-cgi进程:
	STARTUPINFO si = {sizeof(STARTUPINFO)};
	PROCESS_INFORMATION pi;
	si.hStdOutput = hStdoutW;
	si.hStdInput = hStdinR;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;

	// 拼接php-cgi 和 php文件
	char phppath[MAX_PATH];
	strncpy(phppath, (LPCTSTR)m_phpdir, sizeof(phppath));
	char blankchar[2] = " ";
	strcat(phppath, blankchar);
	strcat(phppath, chPath);
	char env[255] = "CONTENT_TYPE=application/x-www-form-urlencoded\0SCRIPT_FILENAME=";
	strcat(env, chPath);
	
	if(!CreateProcess(NULL, (LPTSTR)phppath, 
		NULL, NULL, 1, NORMAL_PRIORITY_CLASS, env, NULL, &si, &pi)){
		AfxMessageBox("解释test.php出错");
	}
	
		
	CloseHandle(hStdoutW);
	CloseHandle(hStdinR);
	CloseHandle(hStdinW);

	//读取返回数据：
	char buf[1000] = {0};
	DWORD dwRead = 0;
	while(ReadFile(hStdoutR, buf, sizeof(buf), &dwRead, NULL) && dwRead != 0){
		GetDlgItem(IDC_OUTPUT)->SetWindowText(buf);
	}
	
	CloseHandle(hStdoutR);

}

BOOL CPhpDlg::DestroyWindow() 
{
	//释放注册的热键
	::UnregisterHotKey(m_hWnd,199);
	return CDialog::DestroyWindow();
}


void CPhpDlg::OnMenuClear() 
{
	m_outputCtl.SetWindowText("");
}

void CPhpDlg::OnMenuExec() 
{
	CPhpDlg::OnOK();
}

BOOL CPhpDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ( (pMsg-> message == WM_KEYDOWN)) 
	{ 
		if(pMsg-> wParam == VK_F5){
			CPhpDlg::OnOK();
		}else if(pMsg-> wParam == VK_F4){
			CPhpDlg::OnMenuClear();
		}

	}

	
	return CDialog::PreTranslateMessage(pMsg);
}
