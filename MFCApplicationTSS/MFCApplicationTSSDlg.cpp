
// MFCApplicationTSSDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationTSS.h"
#include "MFCApplicationTSSDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



void CStaticImage::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage(WM_DRAW_IMAGE, (WPARAM)lpDrawItemStruct);
}

void CStaticHist::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage(WM_DRAW_HISTOGRAM, (WPARAM)lpDrawItemStruct);
}

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


// CMFCApplicationTSSDlg dialog



CMFCApplicationTSSDlg::CMFCApplicationTSSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONTSS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationTSSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_LIST, m_fileList);
	DDX_Control(pDX, IDC_STATIC_HISTOGRAM, m_staticHistogram);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_staticImage);
}

BEGIN_MESSAGE_MAP(CMFCApplicationTSSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN32771, &CMFCApplicationTSSDlg::OnFileOpen32771)
	ON_COMMAND(ID_FILE_CLOSE32772, &CMFCApplicationTSSDlg::OnFileClose32772)
	ON_WM_SIZE()
	ON_MESSAGE(WM_DRAW_IMAGE, OnDrawImage)
	ON_MESSAGE(WM_DRAW_HISTOGRAM, OnDrawHist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILE_LIST, &CMFCApplicationTSSDlg::OnLvnItemchangedFileList)
END_MESSAGE_MAP()


// CMFCApplicationTSSDlg message handlers

BOOL CMFCApplicationTSSDlg::OnInitDialog()
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

	// TODO: Add extra initialization here

	GetClientRect(&m_rect);
	m_fileList.GetWindowRect(&m_rectFileList);
	m_staticHistogram.GetWindowRect(&m_rectHistogram);
	ScreenToClient(&m_rectHistogram);
	m_staticImage.GetWindowRect(&m_rectImage);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplicationTSSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplicationTSSDlg::OnPaint()
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
HCURSOR CMFCApplicationTSSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicationTSSDlg::DisplayFiles()
{
	m_fileList.DeleteAllItems();

	for (int i = 0; i < m_images.size(); ++i)
	{
		m_fileList.InsertItem(i, m_images[i].m_name);
	}

	if (m_images.size() > 0)
	{
		m_fileList.SetItemState(0, LVIS_SELECTED , LVIS_SELECTED);

		m_staticImage.Invalidate(FALSE);

	}
}

bool CMFCApplicationTSSDlg::Duplicate(CString path)
{
	for (int i = 0; i < m_images.size(); i++)
	{
		if (m_images[i].m_path == path)
		{
			return false;
		}
	}
	return true;
}

void CMFCApplicationTSSDlg::OnFileOpen32771()
{
	TCHAR Filters[] = _T("Image Files (*.bmp;*.jpeg;*.jpg;*.png)|*.bmp;*.jpeg;*.jpg;*.png||");

	TCHAR InitialDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, InitialDir);

	CFileDialog dlg(TRUE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, Filters);
	dlg.m_ofn.lpstrInitialDir = InitialDir; 



	if (dlg.DoModal() == IDOK)
	{
		POSITION pos(dlg.GetStartPosition());
		while (pos)
		{
			CString filePath = dlg.GetNextPathName(pos);
			CString fileName;

			if (Duplicate(filePath))
            {
				Img im;
				im.m_path = filePath;

                int posOfBackslash = filePath.ReverseFind(_T('\\'));
                fileName = filePath.Right(filePath.GetLength() - posOfBackslash - 1);

				im.m_name = fileName;

				im.m_image = Gdiplus::Image::FromFile(filePath);

				if (im.m_image && im.m_image->GetLastStatus() == Gdiplus::Ok)
				{
					m_images.push_back(im); 
				}
				else
				{
					AfxMessageBox(_T("Failed to load the image."));
					delete im.m_image; 
				}
            }
			else
			{
				AfxMessageBox(_T("Duplicate file."));
			}
			
		}
		DisplayFiles();
	}
	else
	{
		return;
	}
}


void CMFCApplicationTSSDlg::OnFileClose32772()
{
	POSITION pos = m_fileList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("No file was selected."));
		return;
	}

	int selectedIndex = m_fileList.GetNextSelectedItem(pos);
	CString fileName = m_images[selectedIndex].m_name;
	int response = AfxMessageBox(_T("Do you want to delete file: ") + fileName + _T("?"), MB_YESNO | MB_ICONQUESTION);

	if (response == IDYES)
	{
		m_images.erase(m_images.begin() + selectedIndex);

		DisplayFiles(); 
		Invalidate(TRUE);
	}
}


void CMFCApplicationTSSDlg::OnSize(UINT nType, int cx, int cy)
{
	
	CDialogEx::OnSize(nType, cx, cy);
	int nDiffY =	cy - m_rect.Height();
	int nDiffX = cx - m_rect.Width();

	if(::IsWindow(m_fileList))
	{
		m_fileList.SetWindowPos(nullptr, 0, 0, m_rectFileList.Width(), m_rectFileList.Height() + nDiffY, SWP_NOMOVE);
		m_staticHistogram.SetWindowPos(nullptr, m_rectHistogram.left, m_rectHistogram.top + nDiffY, m_rectHistogram.Width(), m_rectHistogram.Height(), SWP_NOSIZE);
		m_staticImage.SetWindowPos(nullptr, m_rectImage.left, m_rectImage.left, m_rectImage.Width() + nDiffX, m_rectImage.Height() + nDiffY,SWP_NOMOVE);
	}
	Invalidate(TRUE);
	
}

LRESULT CMFCApplicationTSSDlg::OnDrawImage(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT st = (LPDRAWITEMSTRUCT)wParam;

	//CDC* pDC = CDC::FromHandle(st->hDC);
	Gdiplus::Graphics gr(st->hDC);

	int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
	if (selected == -1 || selected >= m_images.size())
	{
		return S_OK;
	}

	Gdiplus::Image* pImage = m_images[selected].m_image;

	if (pImage && pImage->GetLastStatus() == Gdiplus::Ok)
	{
		UINT imgWidth = pImage->GetWidth();
		UINT imgHeight = pImage->GetHeight();

		CRect rect;
		m_staticImage.GetClientRect(&rect);
		int areaW = rect.Width();
		int areaH = rect.Height();

		// zvacsenie a zmensenie
		double scaleX = (double)(areaW) / imgWidth;
		double scaleY = (double)(areaH) / imgHeight;
		double scale = min(scaleX, scaleY);  //podla toho ci je obrazok na vysku alebo sirku sa vybera

		
		int newWidth = (int)(imgWidth * scale);
		int newHeight = (int)(imgHeight * scale);

		
		int xPos = (areaW - newWidth) / 2;
		int yPos = (areaH - newHeight) / 2;


		gr.Clear(Gdiplus::Color::White);

		
		gr.DrawImage(pImage, xPos, yPos, newWidth, newHeight);
	}

	return S_OK;
}

LRESULT CMFCApplicationTSSDlg::OnDrawHist(WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}



void CMFCApplicationTSSDlg::OnLvnItemchangedFileList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	m_staticImage.Invalidate(FALSE);

	*pResult = 0;
}
