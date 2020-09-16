#pragma once
#include "resource.h"

class EditDlg : public CDialogEx
{
	// Construction
public:
	EditDlg(CWnd* pParent = nullptr);	// standard constructor

	CString ID = L"";

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void Fill(CString ID);

// Implementation
protected:
	CDateTimeCtrl m_FromDate;
	CDateTimeCtrl m_FromTime;
	CEdit m_Prio;
	CEdit m_Task;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};

