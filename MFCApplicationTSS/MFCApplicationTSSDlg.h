
// MFCApplicationTSSDlg.h : header file
//
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#pragma once

enum
{
	WM_DRAW_IMAGE = WM_USER + 1,
	WM_DRAW_HISTOGRAM,
	WM_HISTOGRAM_CALCULATED
};

struct Img
{
	CString m_path;
	CString m_name;
	Gdiplus::Image* m_image;
	std::vector<int> m_red;
	std::vector<int> m_green;
	std::vector<int> m_blue;
	bool bCalculated = false;
	bool bStarted = false;
};


class CStaticImage : public CStatic
{
public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)override;
};
class CStaticHist :public CStatic
{
public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
};


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
	CStaticHist m_staticHistogram;
	CRect m_rectHistogram;
	CRect m_rectImage;
	CStaticImage m_staticImage;
	std::vector<Img> m_images;

	bool m_RedChecked = FALSE;
	bool m_GreenChecked = FALSE;
	bool m_BlueChecked = FALSE;

	void CheckHistogram(Img& image);

	void DisplayFiles();
	bool Duplicate(CString path);

	afx_msg void OnFileOpen32771();
	afx_msg void OnFileClose32772();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnDrawImage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrawHist(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHistogramCalculated(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLvnItemchangedFileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHistogramB();
	afx_msg void OnHistogramG();
	afx_msg void OnHistogramR();
};
