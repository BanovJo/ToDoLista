
// ToDoListaDlg.h : header file
//

#pragma once


// CToDoListaDlg dialog
class CToDoListaDlg : public CDialogEx
{
// Construction
public:
	CToDoListaDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TODOLISTA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CListCtrl m_ListControl;
	CButton m_FilterOffOn;
	CDateTimeCtrl m_FilterFromDate;
	CDateTimeCtrl m_FilterFromTime;
	CDateTimeCtrl m_FilterToDate;
	CDateTimeCtrl m_FilterToTime;
	CEdit m_FilterPrio;
	
	void ClearList();
	void Fill();

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblClickYourListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckFilter();
	afx_msg void OnDtnDatetimechangeDatetimepickerDateFilter(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerTimeFilter(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerDateFilterTo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerTimeFilterTo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnEnChangeEditPrio();
};
