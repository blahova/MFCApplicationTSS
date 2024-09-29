
// MFCApplicationTSSDlg.h : header file
//

#pragma once


// CMFCApplicationTSSDlg dialog
class CMFCApplicationTSSDlg : public CDialogEx
{
// Construction
public:
	CMFCApplicationTSSDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONTSS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_fileList;
	CRect m_rect;
	CRect m_rectFileList;
	CStatic m_staticHistogram;
	CRect m_rectHistogram;
	CRect m_rectImage;
	CStatic m_staticImage;
	afx_msg void OnFileOpen32771();
	afx_msg void OnFileClose32772();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	afx_msg LRESULT WM_DRAW_IMAGE(WPARAM wParam, LPARAM lParam);
};
