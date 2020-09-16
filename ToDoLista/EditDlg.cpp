#include "pch.h"
#include "EditDlg.h"


// ToDoListaDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ToDoListaApp.h"
#include "ToDoListaDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// EditDlg dialog



EditDlg::EditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EDIT, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void EditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATETIMEPICKER_EDIT_DATE_FILTER_TO, m_FromDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_EDIT_TIME_FILTER_TO, m_FromTime);

	DDX_Control(pDX, IDC_PRIO, m_Prio);
	DDX_Control(pDX, IDC_EDIT_TASK, m_Task);

}

BEGIN_MESSAGE_MAP(EditDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_OK, &EditDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &EditDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// EditDlg message handlers

BOOL EditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	m_Prio.SetWindowTextW(L"1");

	if (ID != "")
	{
		Fill(ID);
	}

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void EditDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void EditDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR EditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void EditDlg::OnBnClickedOk()
{
	CDatabase* pDatabase = CToDoListaAppApp::Connect();

	if (pDatabase == NULL) return;

	CString SqlString;

	if (ID != "")
	{
		//update
		SqlString = L"UPDATE Zadatci Set ";
		SqlString += " VrijemeDO=#";
		COleDateTime date, a, b;
		m_FromDate.GetTime(a);
		m_FromTime.GetTime(b);
		date.SetDateTime(a.GetYear(), a.GetMonth(), a.GetDay(),
			b.GetHour(), b.GetMinute(), b.GetSecond()
		);
		CString out = date.Format(L"%D %T");
		SqlString += out;
		SqlString += "#, OpisZadatka='";
		m_Task.GetWindowTextW(out);
		out.Replace(L"'", L"''");
		SqlString += out;
		SqlString += "', Prioritet='";
		m_Prio.GetWindowTextW(out);
		SqlString += out;
		SqlString += "' ";
		SqlString += " WHERE ID=";
		SqlString += ID;
		pDatabase->ExecuteSQL(SqlString);
	}
	else
	{
		//add
			
		SqlString = L"INSERT INTO Zadatci(VrijemeDO, OpisZadatka, Prioritet) VALUES(#";

		COleDateTime date, a, b;
		m_FromDate.GetTime(a);
		m_FromTime.GetTime(b);
		date.SetDateTime(a.GetYear(), a.GetMonth(), a.GetDay(),
			b.GetHour(), b.GetMinute(), b.GetSecond()
		);
		CString out = date.Format(L"%D %T");
		SqlString += out;
		SqlString += L"#, '";
		m_Task.GetWindowTextW(out);
		out.Replace(L"'", L"''");
		SqlString += out;
		SqlString += L"', '";
		m_Prio.GetWindowTextW(out);
		SqlString += out;
		SqlString += L"')";
		pDatabase->ExecuteSQL(SqlString);
	}

	CToDoListaAppApp::Disconnect(pDatabase);

	CDialogEx::OnOK();
}



void EditDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void EditDlg::Fill(CString ID)
{
	CDatabase* pDatabase = CToDoListaAppApp::Connect();

	if (pDatabase == NULL) return;

	CString SqlString;

	CString sID, sOpis, sPrio;

	CRecordset recset(pDatabase);

	SqlString = L"SELECT ID, VrijemeDO, OpisZadatka, Prioritet FROM Zadatci where ID=";
	SqlString += ID;

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	while (!recset.IsEOF())
	{
		//COleDateTime timeFrom;
		CDBVariant dt;
		recset.GetFieldValue(L"ID", sID);
		recset.GetFieldValue(L"VrijemeDO", dt, DEFAULT_FIELD_TYPE);

		COleDateTime timeFrom;
		timeFrom.SetDateTime(dt.m_pdate->year, dt.m_pdate->month, dt.m_pdate->day, dt.m_pdate->hour, dt.m_pdate->minute, dt.m_pdate->second);
		m_FromDate.SetTime(timeFrom);
		m_FromTime.SetTime(timeFrom);

		recset.GetFieldValue(L"OpisZadatka", sOpis);
		m_Task.SetWindowTextW(sOpis);
		recset.GetFieldValue(L"Prioritet", sPrio);
		m_Prio.SetWindowTextW(sPrio);

		break;
	}

	CToDoListaAppApp::Disconnect(pDatabase);
}
