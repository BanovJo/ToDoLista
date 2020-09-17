
// ToDoListaDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ToDoListaApp.h"
#include "ToDoListaDlg.h"
#include "EditDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CToDoListaDlg dialog



CToDoListaDlg::CToDoListaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TODOLISTA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToDoListaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListControl);
	DDX_Control(pDX, IDC_CHECK_FILTER, m_FilterOffOn);

	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE_FILTER, m_FilterFromDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TIME_FILTER, m_FilterFromTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE_FILTER_TO, m_FilterToDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TIME_FILTER_TO, m_FilterToTime);

	DDX_Control(pDX, IDC_EDIT_PRIO, m_FilterPrio);

}

BEGIN_MESSAGE_MAP(CToDoListaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_FILTER, &CToDoListaDlg::OnBnClickedCheckFilter)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DATE_FILTER, &CToDoListaDlg::OnDtnDatetimechangeDatetimepickerDateFilter)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_TIME_FILTER, &CToDoListaDlg::OnDtnDatetimechangeDatetimepickerTimeFilter)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DATE_FILTER_TO, &CToDoListaDlg::OnDtnDatetimechangeDatetimepickerDateFilterTo)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_TIME_FILTER_TO, &CToDoListaDlg::OnDtnDatetimechangeDatetimepickerTimeFilterTo)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CToDoListaDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CToDoListaDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CToDoListaDlg::OnBnClickedButtonDelete)
	ON_EN_CHANGE(IDC_EDIT_PRIO, &CToDoListaDlg::OnEnChangeEditPrio)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblClickYourListCtrl)
END_MESSAGE_MAP()


// CToDoListaDlg message handlers

BOOL CToDoListaDlg::OnInitDialog()
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

	//Init controls

	m_FilterFromDate.SetTime(COleDateTime::GetCurrentTime());
	m_FilterFromTime.SetTime(COleDateTime::GetCurrentTime());
	m_FilterToDate.SetTime(COleDateTime::GetCurrentTime());
	m_FilterToTime.SetTime(COleDateTime::GetCurrentTime());
	m_FilterPrio.Clear();

	ListView_SetExtendedListViewStyle(m_ListControl, LVS_EX_GRIDLINES | LVS_SHOWSELALWAYS | LVS_NOSORTHEADER | LVS_EX_FULLROWSELECT);

	m_ListControl.InsertColumn(0, L"Vrijeme", LVCFMT_CENTER, -1, 0);
	m_ListControl.InsertColumn(1, L"Prioritet", LVCFMT_CENTER, -1, 0);
	m_ListControl.InsertColumn(2, L"Opis Zadatka", LVCFMT_CENTER, -1, 0);

	m_ListControl.SetColumnWidth(0, 120);
	m_ListControl.SetColumnWidth(1, 50);
	m_ListControl.SetColumnWidth(2, 280);

	Fill();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CToDoListaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CToDoListaDlg::OnPaint()
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
HCURSOR CToDoListaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CToDoListaDlg::ClearList()
{
	int count = m_ListControl.GetItemCount();
	m_ListControl.DeleteAllItems();
}

void CToDoListaDlg::Fill()
{
	CDatabase database;
	if (theApp.Connect(database) == FALSE) return;

	CString SqlString;
	CString sID, sVrijemeDO, sOpis, sPrio;

	CRecordset recset(&database);

	if (m_FilterOffOn.GetCheck() == BST_UNCHECKED)
	{
		SqlString = L"SELECT ID, VrijemeDO, OpisZadatka, Prioritet FROM Zadatci order by Prioritet desc, VrijemeDO desc";
	}
	else
	{
		COleDateTime dateFrom;
		COleDateTime timeFrom;
		COleDateTime dateTo;
		COleDateTime timeTo;

		m_FilterFromDate.GetTime(dateFrom);
		m_FilterFromTime.GetTime(timeFrom);
		m_FilterToDate.GetTime(dateTo);
		m_FilterToTime.GetTime(timeTo);

		dateFrom = COleDateTime::COleDateTime(dateFrom.GetYear(), dateFrom.GetMonth(), dateFrom.GetDay(),
			timeFrom.GetHour(), timeFrom.GetMinute(), timeFrom.GetSecond()
		);
		dateTo = COleDateTime::COleDateTime(dateTo.GetYear(), dateTo.GetMonth(), dateTo.GetDay(),
			timeTo.GetHour(), timeTo.GetMinute(), timeTo.GetSecond()
		);

		SqlString = L"SELECT ID, VrijemeDO, OpisZadatka, Prioritet FROM Zadatci";
		SqlString += L" where VrijemeDO>=#";
		CString a = dateFrom.Format(L"%D %T");
		SqlString += a;
		SqlString += "# and VrijemeDO<=#";
		CString b = dateTo.Format(L"%D %T");
		SqlString += b;
		SqlString += L"#";
		CString c = L"";
		m_FilterPrio.GetWindowText(c);
		if (c != "")
		{
			SqlString += " and Prioritet=";
			SqlString += c;
		}
		SqlString += L"  order by Prioritet desc, VrijemeDO desc";
	}

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

	ClearList();

	while (!recset.IsEOF())
	{
		CDBVariant vID;
		recset.GetFieldValue(L"ID", vID);
		CDBVariant dt;
		recset.GetFieldValue(L"VrijemeDO", dt);
		recset.GetFieldValue(L"OpisZadatka", sOpis);
		recset.GetFieldValue(L"Prioritet", sPrio);

		COleDateTime oledt = COleDateTime::COleDateTime(dt.m_pdate->year, dt.m_pdate->month, dt.m_pdate->day, dt.m_pdate->hour, dt.m_pdate->minute, dt.m_pdate->second);

		sVrijemeDO = oledt.Format(L"%e.%m.%Y. %X");
		sVrijemeDO.Replace(L".0", L".");
		sOpis.Replace(L"\r", L" ");
		m_ListControl.InsertItem(0, sVrijemeDO, 0);
		m_ListControl.SetItemText(0, 1, sPrio);
		m_ListControl.SetItemText(0, 2, sOpis);
		m_ListControl.SetItemData(0, vID.m_lVal);

		recset.MoveNext();
	}
}


void CToDoListaDlg::OnBnClickedCheckFilter()
{
	Fill();
}


void CToDoListaDlg::OnDtnDatetimechangeDatetimepickerDateFilter(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_FilterOffOn.GetCheck() == BST_CHECKED) Fill();
}


void CToDoListaDlg::OnDtnDatetimechangeDatetimepickerTimeFilter(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_FilterOffOn.GetCheck() == BST_CHECKED) Fill();
}


void CToDoListaDlg::OnDtnDatetimechangeDatetimepickerDateFilterTo(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_FilterOffOn.GetCheck() == BST_CHECKED) Fill();
}


void CToDoListaDlg::OnDtnDatetimechangeDatetimepickerTimeFilterTo(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_FilterOffOn.GetCheck() == BST_CHECKED) Fill();
}


void CToDoListaDlg::OnBnClickedButtonAdd()
{
	EditDlg editDlg;
	editDlg.DoModal();

	Fill();
}


void CToDoListaDlg::OnBnClickedButtonEdit()
{
	int row = m_ListControl.GetSelectionMark();
	if (row < 0) return;

	POSITION pos = m_ListControl.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int row = m_ListControl.GetNextSelectedItem(pos);
		DWORD_PTR id = m_ListControl.GetItemData(row);
		CString strID;
		strID.Format(L"%d", id);
		EditDlg editDlg;
		editDlg.ID = strID;
		editDlg.DoModal();
	}

	Fill();
}


void CToDoListaDlg::OnBnClickedButtonDelete()
{
	int row = m_ListControl.GetSelectionMark();
	if (row < 0) return;

	CDatabase database;
	if (theApp.Connect(database) == FALSE) return;

	CString SqlString;

	CString sID, sDatumUpisa, sVrijemDO, sOpis, sPrio;


	POSITION pos = m_ListControl.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		while (pos)
		{
			int row = m_ListControl.GetNextSelectedItem(pos);
			DWORD_PTR id = m_ListControl.GetItemData(row);
			CString strID;
			strID.Format(L"%d", id);
			SqlString = "DELETE FROM Zadatci where ID=";
			SqlString += strID;
			database.ExecuteSQL(SqlString);
		}
	}

	//must close...if not...Fill() will give wrong output
	database.Close();

	Fill();
}


void CToDoListaDlg::OnEnChangeEditPrio()
{
	if (m_FilterOffOn.GetCheck() == BST_CHECKED) Fill();
}

void CToDoListaDlg::OnDblClickYourListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnBnClickedButtonEdit();
}