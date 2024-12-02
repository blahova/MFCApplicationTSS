
// MFCApplicationTSSDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationTSS.h"
#include "MFCApplicationTSSDlg.h"
#include "afxdialogex.h"
#include "Library.h"


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

public:
//	afx_msg void OnHistogramR();
//	afx_msg void OnHistogramG();
//	afx_msg void OnHistogramB();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_HISTOGRAM_R, &CAboutDlg::OnHistogramR)
//	ON_COMMAND(ID_HISTOGRAM_G, &CAboutDlg::OnHistogramG)
//	ON_COMMAND(ID_HISTOGRAM_B, &CAboutDlg::OnHistogramB)
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
	ON_MESSAGE(WM_HISTOGRAM_CALCULATED, OnHistogramCalculated)
	ON_MESSAGE(WM_SEPIA_DONE, OnSepiaDone)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILE_LIST, &CMFCApplicationTSSDlg::OnLvnItemchangedFileList)
	ON_COMMAND(ID_HISTOGRAM_B, &CMFCApplicationTSSDlg::OnHistogramB)
	ON_COMMAND(ID_HISTOGRAM_G, &CMFCApplicationTSSDlg::OnHistogramG)
	ON_COMMAND(ID_HISTOGRAM_R, &CMFCApplicationTSSDlg::OnHistogramR)
	ON_COMMAND(ID_IMAGE_SEPIA1, &CMFCApplicationTSSDlg::OnImageSepia1)
	ON_COMMAND(ID_IMAGE_SEPIA2, &CMFCApplicationTSSDlg::OnImageSepia2)
	ON_COMMAND(ID_IMAGE_SEPIA3, &CMFCApplicationTSSDlg::OnImageSepia3)
	ON_COMMAND(ID_IMAGE_ORIGINAL, &CMFCApplicationTSSDlg::OnImageOriginal)
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




void CMFCApplicationTSSDlg::CheckHistogram(Img& image)
{
	if (image.bCalculated || image.bStarted || !image.m_image || image.m_image->GetLastStatus() != Gdiplus::Ok)
	{
		return;
	}

	Img img = image;
	Gdiplus::Image* imgCopy = img.m_image->Clone();

	Gdiplus::Bitmap* bitmap = static_cast<Gdiplus::Bitmap*>(imgCopy);
	UINT width = bitmap->GetWidth();
	UINT height = bitmap->GetHeight();
	Gdiplus::Rect rect(0, 0, width, height);
	Gdiplus::BitmapData bitmapData;

	if (bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppRGB, &bitmapData) == Gdiplus::Ok)
	{
		const BYTE* pixels = static_cast<BYTE*>(bitmapData.Scan0);
		int stride = bitmapData.Stride;

		img.bStarted = true;
		std::thread([this, &image, img, pixels, width, height, stride]() mutable {
			//Sleep(5000);
			CalculateHistogramFromPixels(pixels, width, height, stride, img.m_red, img.m_green, img.m_blue);

			bool bNotify = false;
			{
				std::mutex l;
				if (img.m_name == image.m_name)
				{
					image.m_red = img.m_red;
					image.m_green = img.m_green;
					image.m_blue=img.m_blue;
					image.bCalculated = true;
					image.bStarted = false;
					bNotify = true;
				}
				else
				{
					//ASSERT(NULL);
				}
			}

			if (bNotify)
			{
				PostMessage(WM_HISTOGRAM_CALCULATED);
			}
			}).detach();

			bitmap->UnlockBits(&bitmapData);
	}
}

void CMFCApplicationTSSDlg::CheckSepia(int index)
{
	if (m_images[index].bSepiaInProgress || !m_images[index].m_image)
	{
		return;
	}
	
	
	if (bSepia1 && m_images[index].m_sepia[0] == nullptr) SepiaThread(m_images[index],1);
	else if (bSepia2 && m_images[index].m_sepia[1] == nullptr) SepiaThread(m_images[index],2);
	else if (bSepia3 && m_images[index].m_sepia[2] == nullptr) SepiaThread(m_images[index],3);
	else return;
}

void CMFCApplicationTSSDlg::CalculateSepia1(Gdiplus::Bitmap* pix)
{
	UINT width = pix->GetWidth();
	UINT height = pix->GetHeight();

	Gdiplus::Rect rect(0, 0, width, height);
	Gdiplus::BitmapData bitmapData;

	if (pix->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bitmapData) == Gdiplus::Ok)
	{
		BYTE* pixels = static_cast<BYTE*>(bitmapData.Scan0);
		int stride = bitmapData.Stride;

		for (UINT y = 0; y < height; ++y)
		{
			for (UINT x = 0; x < width; ++x)
			{
				BYTE B = pixels[y * stride + x * 4];
				BYTE G = pixels[y * stride + x * 4 + 1];
				BYTE R = pixels[y * stride + x * 4 + 2];

				BYTE* pixel = pixels + (y * stride) + (x * 4);

				int sepiaR = static_cast<int>((R * 0.393) + (G * 0.769) + (B * 0.189));
				int sepiaG = static_cast<int>((R * 0.349) + (G * 0.686) + (B * 0.168));
				int sepiaB = static_cast<int>((R * 0.272) + (G * 0.534) + (B * 0.131));

				pixel[2] = static_cast<BYTE>((sepiaR < 255) ? sepiaR : 255);
				pixel[1] = static_cast<BYTE>((sepiaG < 255) ? sepiaG : 255);
				pixel[0] = static_cast<BYTE>((sepiaB < 255) ? sepiaB : 255);
			}
		}
		pix->UnlockBits(&bitmapData);
	}
}

void CMFCApplicationTSSDlg::CalculateSepia2(Gdiplus::Bitmap* pix)
{
	UINT width = pix->GetWidth();
	UINT height = pix->GetHeight();

	Gdiplus::Rect rect(0, 0, width, height);
	Gdiplus::BitmapData bitmapData;

	if (pix->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bitmapData) == Gdiplus::Ok)
	{
		BYTE* pixels = static_cast<BYTE*>(bitmapData.Scan0);
		int stride = bitmapData.Stride;

		for (UINT y = 0; y < height; ++y)
		{
			for (UINT x = 0; x < width; ++x)
			{
				BYTE B = pixels[y * stride + x * 4];
				BYTE G = pixels[y * stride + x * 4 + 1];
				BYTE R = pixels[y * stride + x * 4 + 2];

				double luma = (0.3 * R + 0.59 * G + 0.11 * B) / 255;

				BYTE* pixel = pixels + (y * stride) + (x * 4);

				int sepiaR = static_cast<int>((R * 0.393) + (G * 0.769) + (B * 0.189))*luma;
				int sepiaG = static_cast<int>((R * 0.349) + (G * 0.686) + (B * 0.168)) * luma;
				int sepiaB = static_cast<int>((R * 0.272) + (G * 0.534) + (B * 0.131)) * luma;

				pixel[2] = static_cast<BYTE>((sepiaR < 255) ? sepiaR : 255);
				pixel[1] = static_cast<BYTE>((sepiaG < 255) ? sepiaG : 255);
				pixel[0] = static_cast<BYTE>((sepiaB < 255) ? sepiaB : 255);
			}
		}
		pix->UnlockBits(&bitmapData);
	}
}

void CMFCApplicationTSSDlg::CalculateSepia3(Gdiplus::Bitmap* pix)
{
	UINT width = pix->GetWidth();
	UINT height = pix->GetHeight();

	Gdiplus::Rect rect(0, 0, width, height);
	Gdiplus::BitmapData bitmapData;

	if (pix->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bitmapData) == Gdiplus::Ok)
	{
		BYTE* pixels = static_cast<BYTE*>(bitmapData.Scan0);
		int stride = bitmapData.Stride;

		for (UINT y = 0; y < height; ++y)
		{
			for (UINT x = 0; x < width; ++x)
			{
				BYTE B = pixels[y * stride + x * 4];
				BYTE G = pixels[y * stride + x * 4 + 1];
				BYTE R = pixels[y * stride + x * 4 + 2];

				BYTE brownR = 112;
				BYTE brownG = 66;
				BYTE brownB = 20;

				double intensity = 0.4;

				double grey = 0.3 * R + 0.59 * G + 0.11 * B;

				BYTE* pixel = pixels + (y * stride) + (x * 4);

				int sepiaR = static_cast<int>(grey + (brownR - grey) * intensity) ;
				int sepiaG = static_cast<int>(grey + (brownG - grey) * intensity);
				int sepiaB = static_cast<int>(grey + (brownB - grey) * intensity);

				pixel[2] = static_cast<BYTE>((sepiaR < 255) ? sepiaR : 255);
				pixel[1] = static_cast<BYTE>((sepiaG < 255) ? sepiaG : 255);
				pixel[0] = static_cast<BYTE>((sepiaB < 255) ? sepiaB : 255);
			}
		}
		pix->UnlockBits(&bitmapData);
	}
}

void CMFCApplicationTSSDlg::SepiaThread(Img& image, int which)
{
	std::thread([this, &image, which]() {
		image.bSepiaInProgress = true;
		//Sleep(5000);
		Img img = image;
		


		Gdiplus::Image* newImage = img.m_image->Clone();
		if (which == 1)
		{
			CalculateSepia1(static_cast<Gdiplus::Bitmap*>(newImage));
			img.m_sepia[0] = newImage;
		}
		else if (which == 2) 
		{
			CalculateSepia2(static_cast<Gdiplus::Bitmap*>(newImage));
			img.m_sepia[1] = newImage;
		}
		else
		{
			CalculateSepia3(static_cast<Gdiplus::Bitmap*>(newImage));
			img.m_sepia[2] = newImage;
		}
		bool bNotify = false;
		{
			std::mutex l;
			if (img.m_name == image.m_name)
			{
				if (which == 1) image.m_sepia[0] = img.m_sepia[0];
				else if (which == 2) image.m_sepia[1] = img.m_sepia[1];
				else image.m_sepia[2] = img.m_sepia[2];

				image.bSepiaInProgress = false;
				bNotify = true;
			}
			else
			{
				//ASSERT(NULL);
			}
		}
		if (bNotify)
		{
			PostMessage(WM_SEPIA_DONE);
		}

		}).detach();
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
		Img& image = m_images[selectedIndex];
		for (int i = 0; i < 3; ++i)
		{
			if (image.m_sepia[i] != nullptr)
			{
				delete image.m_sepia[i];
				image.m_sepia[i] = nullptr;
			}
		}
		m_images.erase(m_images.begin() + selectedIndex);

		DisplayFiles(); 
		OnImageOriginal();
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

	Gdiplus::Image* pImage; 

	if (bSepia1 || bSepia2 || bSepia3) CheckSepia(selected);

	if (bSepia1) pImage = m_images[selected].m_sepia[0];
	else if(bSepia2) pImage = m_images[selected].m_sepia[1];
	else if (bSepia3) pImage = m_images[selected].m_sepia[2];
	else pImage = m_images[selected].m_image;

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
		
		gr.DrawImage(pImage, xPos, yPos, newWidth, newHeight);
	}

	return S_OK;
}

LRESULT CMFCApplicationTSSDlg::OnDrawHist(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT st = (LPDRAWITEMSTRUCT)wParam;
	Gdiplus::Graphics gr(st->hDC);

	int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
	if (selected < 0 || selected >= m_images.size())
	{
		return S_OK;
	}

	Img& selectedImg = m_images[selected];
	if (!selectedImg.bCalculated || selectedImg.bStarted)
	{
		return S_OK;
	}

	CRect rect;
	m_staticHistogram.GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();

	//najdem maximalnu hodnotu v histograme, ci je R G alebo B, podla toho sa bude skalovat
	int maxValue = 0;
	for (int i = 0; i < 256; ++i)
	{
		maxValue = max(maxValue, selectedImg.m_red[i]);
		maxValue = max(maxValue, selectedImg.m_green[i]);
		maxValue = max(maxValue, selectedImg.m_blue[i]);
	}


	if (bRedChecked)
	{
		Gdiplus::Pen redPen(Gdiplus::Color::Red);
		int i;
		for ( i = 0; i < 256; ++i)
		{
			int lineHeight = (int)(((double)(selectedImg.m_red[i]) / maxValue) * height);
			gr.DrawLine(&redPen, i * width / 256, height, i * width / 256, height - lineHeight);
		}
	}

	if (bGreenChecked)
	{
		Gdiplus::Pen greenPen(Gdiplus::Color::Green);
		for (int i = 0; i < 256; ++i)
		{
			int lineHeight = (int)(((double)(selectedImg.m_green[i]) / maxValue) * height);
			gr.DrawLine(&greenPen, i * width / 256, height, i * width / 256, height - lineHeight);
		}
	}

	if (bBlueChecked)
	{
		Gdiplus::Pen bluePen(Gdiplus::Color::Blue);
		for (int i = 0; i < 256; ++i)
		{
			int lineHeight = (int)(((double)(selectedImg.m_blue[i]) / maxValue) * height);
			gr.DrawLine(&bluePen, i * width / 256, height, i * width / 256, height - lineHeight);
		}
	}

	return S_OK;
}



void CMFCApplicationTSSDlg::OnLvnItemchangedFileList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (bBlueChecked || bRedChecked || bGreenChecked)
	{
		int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
		if (selected != -1 && selected < m_images.size())
		{
			CheckHistogram(m_images[selected]);
		}
	}
	Invalidate(TRUE);
	*pResult = 0;
}



void CMFCApplicationTSSDlg::OnHistogramB()
{
	bBlueChecked = !bBlueChecked;
	CMenu* pMenu = GetMenu();
	pMenu->CheckMenuItem(ID_HISTOGRAM_B, bBlueChecked ? MF_CHECKED : MF_UNCHECKED);

	int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
	if (selected != -1 && selected < m_images.size())
	{
		CheckHistogram(m_images[selected]);
	}
	Invalidate(TRUE);
}


void CMFCApplicationTSSDlg::OnHistogramG()
{
	bGreenChecked = !bGreenChecked;
	CMenu* pMenu = GetMenu();
	pMenu->CheckMenuItem(ID_HISTOGRAM_G, bGreenChecked ? MF_CHECKED : MF_UNCHECKED);
	int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
	if (selected != -1 && selected < m_images.size())
	{
		CheckHistogram(m_images[selected]);
	}
	Invalidate(TRUE);
}


void CMFCApplicationTSSDlg::OnHistogramR()
{
	bRedChecked = !bRedChecked;
	CMenu* pMenu = GetMenu();
	pMenu->CheckMenuItem(ID_HISTOGRAM_R, bRedChecked ? MF_CHECKED : MF_UNCHECKED);
	int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
	if (selected != -1 && selected < m_images.size())
	{
		CheckHistogram(m_images[selected]);
	}
	Invalidate(TRUE);
}

LRESULT CMFCApplicationTSSDlg::OnHistogramCalculated(WPARAM wParam, LPARAM lParam)
{
	m_staticHistogram.Invalidate(TRUE);
	return S_OK;
}

LRESULT CMFCApplicationTSSDlg::OnSepiaDone(WPARAM wParam, LPARAM lParam)
{
	m_staticImage.Invalidate(TRUE);
	return S_OK;
}


void CMFCApplicationTSSDlg::OnImageSepia1()
{
	if (bSepia1)return;
	CMenu* pMenu = GetMenu();
	bSepia1 = true;
	bSepia2 = false;
	bSepia3 = false;
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA1,MF_CHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA2, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA3, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_ORIGINAL, MF_UNCHECKED);

	int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
	if (selected != -1 && selected < m_images.size())
	{
		CheckSepia(selected);
	}
	m_staticImage.Invalidate(TRUE);
}


void CMFCApplicationTSSDlg::OnImageSepia2()
{
	if (bSepia2)return;
	CMenu* pMenu = GetMenu();
	bSepia1 = false;
	bSepia2 = true;
	bSepia3 = false;
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA2,MF_CHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA1, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA3, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_ORIGINAL, MF_UNCHECKED);

	int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
	if (selected != -1 && selected < m_images.size())
	{
		CheckSepia(selected);
	}
	m_staticImage.Invalidate(TRUE);
}


void CMFCApplicationTSSDlg::OnImageSepia3()
{
	if (bSepia3)return;
	CMenu* pMenu = GetMenu();
	bSepia1 = false;
	bSepia2 = false;
	bSepia3 = true;
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA3,  MF_CHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA2, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA1, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_ORIGINAL, MF_UNCHECKED);

	int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
	if (selected != -1 && selected < m_images.size())
	{
		CheckSepia(selected);
	}
	m_staticImage.Invalidate(TRUE);
}


void CMFCApplicationTSSDlg::OnImageOriginal()
{
	CMenu* pMenu = GetMenu();
	bSepia1 = false;
	bSepia2 = false;
	bSepia3 = false;
	pMenu->CheckMenuItem(ID_IMAGE_ORIGINAL, MF_CHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA1, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA3, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_IMAGE_SEPIA2, MF_UNCHECKED);
	
	int selected = m_fileList.GetNextItem(-1, LVNI_SELECTED);
	m_staticImage.Invalidate(TRUE);
}
