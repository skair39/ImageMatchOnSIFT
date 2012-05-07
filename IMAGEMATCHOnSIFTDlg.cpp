// IMAGEMATCHOnSIFTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IMAGEMATCHOnSIFT.h"
#include "IMAGEMATCHOnSIFTDlg.h"
#include "ShowImgDlg.h"
#include "DlgMClose.h"

#include "sift\siftdll.h"

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
// CIMAGEMATCHOnSIFTDlg dialog

CIMAGEMATCHOnSIFTDlg::CIMAGEMATCHOnSIFTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIMAGEMATCHOnSIFTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIMAGEMATCHOnSIFTDlg)
	m_sltImg1 = _T("");
	m_sltImg2 = _T("");
	m_gws = -1;
	m_bd = -1;
	m_sdr = -1;
	m_mt = -1;
	m_is = _T("");
	m_cd = _T("");
	m_miniRes = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//
	/*��ʼ����Ա����ֵ*/
	m_imgdata1 = m_imgdata2 = NULL;		//���ͼ�����ݣ�����ͷ��Ϣ�ͽṹ��Ϣ��
	m_orgdata1 = m_orgdata2 = NULL;		//���RGB����
	//	m_newdata = NULL;
	m_img1path = "";
	m_img2path = "";
	m_graydata1 = NULL;
	m_graydata2 = NULL;
	matchedcos = NULL;
	featVect1 = NULL;
	featVect2 = NULL;
}

void CIMAGEMATCHOnSIFTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIMAGEMATCHOnSIFTDlg)
	DDX_Control(pDX, IDC_COMBOMINIRES, m_COMBOMiniRes);
	DDX_Control(pDX, IDC_EDITCD, m_EDITCD);
	DDX_Control(pDX, IDC_SLIDERCD, m_SLIDERCD);
	DDX_Control(pDX, IDC_EDITIS, m_EDITIS);
	DDX_Control(pDX, IDC_SLIDERIS, m_SLIDERIS);
	DDX_Control(pDX, IDC_EDITSELECTIMG2, m_EDITSLTIMG2);
	DDX_Control(pDX, IDC_EDITSELECTIMG1, m_EDITSLTIMG1);
	DDX_Control(pDX, IDC_COMBOMT, m_COMBOMT);
	DDX_Control(pDX, IDC_COMBOSDR, m_COMBOSDR);
	DDX_Control(pDX, IDC_COMBOBD, m_COMBOBD);
	DDX_Control(pDX, IDC_COMBOGWS, m_COMBOGWS);
	DDX_Text(pDX, IDC_EDITSELECTIMG1, m_sltImg1);
	DDX_Text(pDX, IDC_EDITSELECTIMG2, m_sltImg2);
	DDX_CBIndex(pDX, IDC_COMBOGWS, m_gws);
	DDX_CBIndex(pDX, IDC_COMBOBD, m_bd);
	DDX_CBIndex(pDX, IDC_COMBOSDR, m_sdr);
	DDX_CBIndex(pDX, IDC_COMBOMT, m_mt);
	DDX_Text(pDX, IDC_EDITIS, m_is);
	DDX_Text(pDX, IDC_EDITCD, m_cd);
	DDX_CBIndex(pDX, IDC_COMBOMINIRES, m_miniRes);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIMAGEMATCHOnSIFTDlg, CDialog)
	//{{AFX_MSG_MAP(CIMAGEMATCHOnSIFTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSELECTIMG1, OnButtonselectimg1)
	ON_BN_CLICKED(IDC_BUTTONSELECTIMG2, OnButtonselectimg2)
	ON_EN_MAXTEXT(IDC_EDITSELECTIMG1, OnMaxtextEditselectimg1)
	ON_EN_MAXTEXT(IDC_EDITSELECTIMG2, OnMaxtextEditselectimg2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERIS, OnCustomdrawSlideris)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERCD, OnCustomdrawSlidercd)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONSHOWIMG, static_cast<void>(OnButtonshowimg))
	ON_BN_CLICKED(IDC_BUTTONCLEAR, OnButtonclear)
	ON_BN_CLICKED(IDC_BUTTONFD, OnButtonfd)
	ON_CBN_SELCHANGE(IDC_COMBOGWS, OnSelchangeCombogws)
	ON_CBN_SELCHANGE(IDC_COMBOBD, OnSelchangeCombobd)
	ON_WM_MOVE()
	ON_CBN_DROPDOWN(IDC_COMBOGWS, OnDropdownCombogws)
	ON_BN_CLICKED(IDC_BUTTONMATCH, OnButtonmatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIMAGEMATCHOnSIFTDlg message handlers

BOOL CIMAGEMATCHOnSIFTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

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
	//���öԻ�����Ļλ��
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 20, 20, 0, 0,SWP_SHOWWINDOW|SWP_NOSIZE);
	/*gaussƽ���˴��ڴ�С�����б�*/
	CString gausswidsize;
	gausswidsize = "1.5";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "1.75";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "2.0";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "2.25";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "2.5";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "2.75";
	m_COMBOGWS.AddString(gausswidsize);
	gausswidsize = "3.0";
	m_COMBOGWS.AddString(gausswidsize);
	m_COMBOGWS.SetCurSel(2);
	
	/*�߽����ѡ��������Ϊ��λ������С��gaussƽ������*/
	CString bd;
	bd = "3";
	m_COMBOBD.AddString(bd);
	bd = "4";
	m_COMBOBD.AddString(bd);
	bd = "5";
	m_COMBOBD.AddString(bd);
	bd = "6";
	m_COMBOBD.AddString(bd);
	bd = "7";
	m_COMBOBD.AddString(bd);
	m_COMBOBD.SetCurSel(2);

	/*ƥ��������*/
	CString distratio;
	distratio = "0.90";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.85";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.80";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.78";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.75";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.72";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.70";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.68";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.65";
	m_COMBOSDR.AddString(distratio);
	distratio = "0.60";
	m_COMBOSDR.AddString(distratio);
	m_COMBOSDR.SetCurSel(3);

	/*�ݶ���ֵ*/
	CString mt;
	mt = "0.2";
	m_COMBOMT.AddString(mt);
	m_COMBOMT.SetCurSel(0);

	/*�����ı��༭����������*/
	m_EDITSLTIMG1.SetLimitText(100);
	m_EDITSLTIMG2.SetLimitText(100);

	/*���û�����������Χ����ʼλ��*/
	m_SLIDERIS.SetRange(0, 60);		//0.8-2.0,space��0.02
	m_SLIDERIS.SetPos(40);
	m_SLIDERCD.SetRange(0, 18);		//0.03-0.12 space:0.005
	m_SLIDERCD.SetPos(2);

	/*����initial scale�༭���ʼ����*/
	char	buf[10];
	CString edit;
	int		pos = m_SLIDERIS.GetPos();
	float	scale = pos*0.02+0.8;
	sprintf(buf, "%lf", scale);
	edit.Format("%s", buf);
	SetDlgItemText(IDC_EDITIS, edit);
	m_EDITIS.SetLimitText(4);

	/*����contrast threshhold �༭���ʼ����*/
	pos = m_SLIDERCD.GetPos();
	scale = pos*0.005 + 0.03;
	sprintf(buf, "%lf", scale);
	edit.Format("%s", buf);
	SetDlgItemText(IDC_EDITCD, edit);
	m_EDITCD.SetLimitText(4);

	/*check box�� ѡ���Ƿ�double������ͼ��,Ĭ�ϲ�ѡ��*/
	((CButton *)GetDlgItem(IDC_CHECKDBLBASEIMG))->SetCheck(false);

	/*�������һ��octave�ķֱ��ʴ�С*/
	CString miniRes;
	miniRes = "4";
	m_COMBOMiniRes.AddString(miniRes);
	miniRes = "8";
	m_COMBOMiniRes.AddString(miniRes);
	miniRes = "16";
	m_COMBOMiniRes.AddString(miniRes);
	miniRes = "32";
	m_COMBOMiniRes.AddString(miniRes);
	m_COMBOMiniRes.SetCurSel(1);

	/*���༭����Ͽ�ȵ����ݸ��µ�������*/
	UpdateData(true);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIMAGEMATCHOnSIFTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIMAGEMATCHOnSIFTDlg::OnPaint() 
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
HCURSOR CIMAGEMATCHOnSIFTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIMAGEMATCHOnSIFTDlg::OnButtonselectimg1() 
{
	// TODO: Add your control notification handler code here
	//select an image
	if (dspDlg.m_hWnd)
	{
		MessageBox("ͼ���Ѿ��򿪣����ȹر�ͼ��!");	
		return;
	}
	CFileDialog selectDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, NULL, NULL);
	selectDlg.m_ofn.lpstrTitle = TEXT("Select image 1") ;
	selectDlg.m_ofn.lpstrFilter="BMP Files (*.bmp, *.BMP)\0*.bmp\0\0";
	int retVal = selectDlg.DoModal();
	CString fext = selectDlg.GetFileExt();
	while((fext != "bmp")&&(fext != "BMP")&&(retVal!=IDCANCEL))
	{
		MessageBox("invalid image file!");
		retVal = selectDlg.DoModal();
		fext = selectDlg.GetFileExt();
	}
	if (retVal == IDCANCEL)
		return;	
	
	//get image path name
	SetDlgItemText(IDC_EDITSELECTIMG1, selectDlg.GetPathName());
}

void CIMAGEMATCHOnSIFTDlg::OnButtonselectimg2() 
{
	// TODO: Add your control notification handler code here
	if (dspDlg.m_hWnd)
	{
		MessageBox("ͼ���Ѿ��򿪣����ȹر�ͼ��!");	
		return;
	}
	CFileDialog selectDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, NULL, NULL);
	selectDlg.m_ofn.lpstrTitle = TEXT("Select image 2") ;
	selectDlg.m_ofn.lpstrFilter="BMP Files (*.bmp, *.BMP)\0*.bmp\0\0";
	int retVal = selectDlg.DoModal();
	CString fext = selectDlg.GetFileExt();
	while((fext != "bmp")&&(fext != "BMP")&&(retVal!=IDCANCEL))
	{
		MessageBox("invalid image file!");
		retVal = selectDlg.DoModal();
		fext = selectDlg.GetFileExt();
	}
	if (retVal == IDCANCEL)
		return;	
	
	//get image path name
	SetDlgItemText(IDC_EDITSELECTIMG2, selectDlg.GetPathName());
}



void CIMAGEMATCHOnSIFTDlg::OnMaxtextEditselectimg1() 
{
	// TODO: Add your control notification handler code here
	MessageBox("�ļ�·��������");
	SetDlgItemText(IDC_EDITSELECTIMG1, "");
}


void CIMAGEMATCHOnSIFTDlg::OnMaxtextEditselectimg2() 
{
	// TODO: Add your control notification handler code here
	MessageBox("�ļ�·��������");
	SetDlgItemText(IDC_EDITSELECTIMG2, "");
}

void CIMAGEMATCHOnSIFTDlg::OnCustomdrawSlideris(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	char	buf[10];
	CString edit;
	int		pos = m_SLIDERIS.GetPos();
	float	scale = pos*0.02+0.8;
	sprintf(buf, "%lf", scale);
	edit.Format("%s", buf);
	SetDlgItemText(IDC_EDITIS, edit);

	UpdateData(true);

	*pResult = 0;
}

void CIMAGEMATCHOnSIFTDlg::OnCustomdrawSlidercd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	char buf[10];
	int pos = m_SLIDERCD.GetPos();
	float scale = pos*0.005 + 0.03;
	CString edit;
	sprintf(buf, "%lf", scale);
	edit.Format("%s", buf);
	SetDlgItemText(IDC_EDITCD, edit);
	m_EDITCD.SetLimitText(4);

	UpdateData(true);
	
	*pResult = 0;
}

/*filepath:ͼ��·������img:ͼ����ţ�0or1*/
bool CIMAGEMATCHOnSIFTDlg::LoadSrcImg(CString fpathname, int img)
{
	//Ŀǰֻ����bmpͼ��
	CBitmap bmp;

	//λͼ���
	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), fpathname, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
	if (!hBmp)
	{
		if (img==0)
			MessageBox("����·�����Ҳ���ͼ��1!");
		else
			MessageBox("����·�����Ҳ���ͼ��2!");
		return false;
	}

	//attach
	bmp.Attach(hBmp);

	//DIBSECTION
	DIBSECTION ds;
	//λͼͷ��Ϣ
	BITMAPINFOHEADER &bmpInfo = ds.dsBmih;
	bmp.GetObject(sizeof(DIBSECTION), &ds); //����ռ�

	//ͼ�񳤶ȺͿ�ȣ�����Ϊ��λ
	int w = bmpInfo.biWidth;
	int h = bmpInfo.biHeight;

	if ((w>800)||(h>800))
	{
		MessageBox("�ݲ�֧��800x800���Ϸֱ���ͼ��!");
		return false;
	}

	//��ͼ�����ݵ���������
	CFile infile;
	BYTE *tmpimgbuf, *tmporgbuf, *tmpgraydata;		//��ʱ������
	infile.Open(fpathname, CFile::modeRead);
	UINT flen = (UINT)infile.GetLength(); //�õ�ͼ�񳤶�
	infile.SeekToBegin();		//��λ���ļ�ͷ��
	if (img==0)  //img 0
	{
		m_width1 = w;
		m_height1 = h;
		if (m_imgdata1)
			delete[] m_imgdata1;
		m_imgdata1	= new BYTE[flen];
		tmpimgbuf	= m_imgdata1;
	}
	else //image 2
	{
		m_width2 = w;
		m_height2 = h;
		if (m_imgdata2)
			delete[] m_imgdata2;
		m_imgdata2 = new BYTE[flen];
		tmpimgbuf = m_imgdata2;
	}
	//�����ݶ��뻺����
	infile.Read((void *)tmpimgbuf, flen);
	//infile.Flush();
	infile.Close();

	//�õ�rgb ���ݻ�Ҷ�����
	BITMAPFILEHEADER *bmpfile = (BITMAPFILEHEADER *)tmpimgbuf;
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(tmpimgbuf + sizeof(BITMAPFILEHEADER));
	if (bmpfile->bfType != 0x4d42)		//����bmpͼ��
	{
		AfxMessageBox("����ͼ����bmp��ʽ��");
		//�ͷ��ѷ���ռ�
		if (img==0)
		{
			if (m_orgdata1)
				delete[] m_orgdata1;
			if (m_imgdata1)
				delete[] m_imgdata1;
		}
		else
		{
			if (m_orgdata2)
				delete[] m_orgdata2;
			if (m_imgdata2)
				delete[] m_imgdata2;
		}
		return false;
	}
	if ((bmpinfo->biBitCount!=24)&&(bmpinfo->biBitCount!=8))
	{
		AfxMessageBox("Ŀǰֻ֧��24Ϊ��ɫ��8λ�Ҷ�ͼ��");
		//�ͷ��ѷ���ռ�
		if (img==0)
		{
			if (m_imgdata1)
				delete[] m_imgdata1;
		}
		else
		{
			if (m_imgdata2)
				delete[] m_imgdata2;
		}
		tmpimgbuf = NULL;
		return false;
	}

	int bbc = bmpinfo->biBitCount;  //24 or 8
	int bpl = ((bbc*w+31)/32)*4;	//ÿ��ռ�õ��ڴ�ռ䣬4bytes����
	int imgsize = bpl*h;			//���ͼ�����������ڴ�ռ�,�ֽ�
	BYTE *imgdata = (BYTE *)(tmpimgbuf + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));  //rgbdataָ��ͼ��������
	//Ϊ�Ҷ���Ϣ����ռ䣬��������Ϊcolor����gray�������������ת��Ϊ�Ҷ�ͼ���������ƥ��
	//int bpl_gray = ((8*w+31)/32)*4;
	int bpl_gray = w;
	int imgsize_gray = bpl_gray*h;
	if (img == 0)
	{
		if (m_orgdata1) //rgb����
			delete[] m_orgdata1;
		m_orgdata1 = new BYTE[imgsize];
		tmporgbuf = m_orgdata1;

		if (m_graydata1) //gray����
			delete[] m_graydata1;
		m_graydata1 = new BYTE[imgsize_gray];
		tmpgraydata = m_graydata1;
	}
	else
	{
		if (m_orgdata2)
			delete[] m_orgdata2;
		m_orgdata2 = new BYTE[imgsize];
		tmporgbuf = m_orgdata2;

		if (m_graydata2)
			delete[] m_graydata2;
		m_graydata2 = new BYTE[imgsize_gray];
		tmpgraydata = m_graydata2;
	}
	//����rgb��gray����
	for (int k=0; k<h; k++)
		memcpy(tmporgbuf+k*bpl, imgdata+k*bpl, bpl);

	//����Ҷ�ֵ
	if (bbc == 8) //ԭ��ͼ��Ϊ�Ҷ�ͼ��
	{
		for (int k=0; k<h; k++)
			memcpy(tmpgraydata+k*bpl_gray, imgdata+k*bpl, bpl_gray);
	}
	else		//ԭͼ��Ϊ��ɫͼ��
	{
		int i,j,co,con;
		int gray;
		double r, g, b;
		for (j=0; j<h; j++)
		{
			for (i=0; i<w; i++)
			{
				co = j*bpl + i*3;
				con = j*bpl_gray + i;
				b = imgdata[co];
				g = imgdata[co+1];
				r = imgdata[co+2];

				gray = (int)(0.11*r+0.59*g+0.3*b);
				gray = (gray<255) ? gray : 255;
				tmpgraydata[con] = gray;
			}
		}
	}

	return true;
}


void CIMAGEMATCHOnSIFTDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CIMAGEMATCHOnSIFTDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//
	CDlgMClose dlg;
	if (dlg.DoModal()==IDCANCEL)
		return;

	//�ͷſռ�
	if (m_orgdata1)
	{
		delete[] m_orgdata1;
		m_orgdata1 = NULL;
	}		
	if (m_orgdata2)
	{
		delete[] m_orgdata2;
		m_orgdata2 = NULL;
	}		
	if (m_imgdata1)
	{
		delete[] m_imgdata1;
		m_imgdata1 = NULL;
	}		
	if (m_imgdata2)
	{
		delete[] m_imgdata2;
		m_orgdata2 = NULL;
	}
	if (m_graydata1)
	{
		delete[] m_graydata1;
		m_graydata1 = NULL;
	}
	if (m_graydata2)
	{
		delete[] m_graydata2;
		m_graydata2 = NULL;
	}

	if (matchedcos)
	{
		delete[] matchedcos;
		matchedcos = NULL;
	}

	if (featVect1)
	{
		free_feature_nodes(featVect1);
		featVect1 = NULL;
	}		
	if (featVect2)
	{
		free_feature_nodes(featVect2);
		featVect2 = NULL;
	}

	::DestroyWindow(this->m_hWnd);
	CDialog::OnClose();
}

BOOL CIMAGEMATCHOnSIFTDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DestroyWindow();
}



int CIMAGEMATCHOnSIFTDlg::OnButtonshowimg() 
{
	// TODO: Add your control notification handler code here
	if (dspDlg.m_hWnd)
	{
		return 1;		//ͼ���Ѿ���
	}
	CWnd *wnd;
	//UpdateData(); //��ȡ�༭��������
	GetDlgItemText(IDC_EDITSELECTIMG1, m_img1path);
	GetDlgItemText(IDC_EDITSELECTIMG2, m_img2path);
	if (m_img1path.IsEmpty())
	{
		MessageBox("��ѡ��ͼ��1��·��!");
		wnd = GetDlgItem(IDC_BUTTONSELECTIMG1);
		wnd->SetFocus();
		return 0;
	}
	if (m_img2path.IsEmpty())
	{
		MessageBox("��ѡ��ͼ��2��·��!");
		wnd = GetDlgItem(IDC_BUTTONSELECTIMG2);
		wnd->SetFocus();
		return 0;
	}
	//���ñ༭��ֻ��
	CEdit *pEdit1 = (CEdit *)GetDlgItem(IDC_EDITSELECTIMG1);
	pEdit1->SetReadOnly(true);
	CEdit *pEdit2 = (CEdit *)GetDlgItem(IDC_EDITSELECTIMG2);
	pEdit2->SetReadOnly(true);
	if (!LoadSrcImg(m_img1path, 0))
	{
		MessageBox("����ͼ��1ʧ��!������ѡ��ͼ��");
		pEdit1->SetReadOnly(false);
		wnd = GetDlgItem(IDC_EDITSELECTIMG1);
		wnd->SetFocus();
		pEdit1->SetSel(0, pEdit1->LineLength(0));
		return 0;
	}		
	if (!LoadSrcImg(m_img2path, 1))
	{
		MessageBox("����ͼ��2ʧ��!������ѡ��ͼ��");
		pEdit2->SetReadOnly(false);
		wnd = GetDlgItem(IDC_EDITSELECTIMG2);
		wnd->SetFocus();
		pEdit2->SetSel(0, pEdit2->LineLength(0));
		return 0;
	}
	
	/*�½�һ���Ի��򲢽�ͼ����ʾ����*/
	ShowImage();

	return 1;
}

void CIMAGEMATCHOnSIFTDlg::ShowImage()
{
	BITMAPFILEHEADER *bmpfile1, *bmpfile2;
	BITMAPINFOHEADER *bmpinfo1, *bmpinfo2;
	int nw, nh;			//��ͼ��ĸ߶ȺͿ��,����Ϊ��λ
	
	bmpfile1 = (BITMAPFILEHEADER *)m_imgdata1;
	bmpinfo1 = (BITMAPINFOHEADER *)(m_imgdata1 + sizeof(BITMAPFILEHEADER));
	bmpfile2 = (BITMAPFILEHEADER *)m_imgdata2;
	bmpinfo2 = (BITMAPINFOHEADER *)(m_imgdata2 + sizeof(BITMAPFILEHEADER));
	
	nw = (m_width1>m_width2) ? m_width1 : m_width2;
	nh = m_height1 + m_height2;
	int bbc1 = bmpinfo1->biBitCount;
	int bbc2 = bmpinfo2->biBitCount;
	/*int nbbc = (bbc1>bbc2) ? bbc1 : bbc2;*/
	int nbbc = 24;  //��ͼ�����24λ��ʾ
	int bpl1 = ((bbc1*m_width1+31)/32)*4;
	int bpl2 = ((bbc2*m_width2+31)/32)*4;
	int nbpl = ((nbbc*nw+31)/32)*4;
	int nimgsize = nbpl*nh;

	//��ʱ���ݻ�����
	BYTE *newdata = new BYTE[nimgsize];
	
	//������ͼ������
	int i,j,k1,nk;
	if (bmpinfo1->biBitCount==8)  //8λ�Ҷ�����
	{
		for (j=0; j<m_height1; j++)
			for (i=0; i<m_width1; i++)
			{
				k1 = j*bpl1 + i;
				nk = j*nbpl + i*3;
				newdata[nk] = newdata[nk+1] = newdata[nk+2] = m_orgdata1[k1];
			}
	}
	else //24λ��ɫ����
	{
		for (j=0; j<m_height1; j++)
			memcpy(newdata+j*nbpl, m_orgdata1+j*bpl1, bpl1);
	}
	if (bmpinfo2->biBitCount==8)  //8λ�Ҷ�����
	{
		//nk = (m_height1-1)*nbpl;
		for (j=0; j<m_height2; j++)
			for (i=0; i<m_width2; i++)
			{
				k1 = j*bpl2 + i;
				nk = (j+m_height1)*nbpl + i*3;
				newdata[nk] = newdata[nk+1] = newdata[nk+2] = m_orgdata2[k1];
			}
	}
	else //24λ��ɫ����
	{
		for (j=0; j<m_height2; j++)
			memcpy(newdata+(m_height1+j)*nbpl, m_orgdata2+j*bpl2, bpl2);
	}
	/*��ʾ*/
	//����ͼ����Ϣ, �˺�������λ����ʾ֮ǰ
	BYTE *imgdata = (bbc1>bbc2) ? m_imgdata1:m_imgdata2;
	dspDlg.SetImgInfo(nw, nh, nimgsize, imgdata, newdata);
	dspDlg.Create(IDD_IMGDISPLAYER, this);  //������ʾͼ��ĶԻ���
	CWnd *pWnd = dspDlg.GetDlgItem(IDC_IMGDISPLAYER); //�õ�ͼƬ�ؼ�ָ��
	CRect rect;
	pWnd->GetWindowRect(&rect); //�õ�ͼ��ؼ��������Ļ���Ͻǵ�����
	dspDlg.ScreenToClient(&rect); //����Ļ����ת��Ϊ�û�����

	/*������ʾ�Ի����λ��*/
	//�õ���ǰ��Ҫ�Ի����λ��
	CRect dlgrect;
	::GetWindowRect(this->m_hWnd, &dlgrect);
	nw = nw + (int)(2.5*rect.left);
	int sysy = GetSystemMetrics(SM_CYSCREEN);
	nh = nh + (int)(4.5*rect.top);
	::SetWindowPos(dspDlg.m_hWnd, HWND_TOPMOST, dlgrect.right, dlgrect.top, nw, nh,SWP_SHOWWINDOW);	
	dspDlg.GetWindowRect(&dlgrect);
	m_showdlgh = dlgrect.bottom-dlgrect.top;
	
	dspDlg.ShowWindow(SW_SHOW);		//��ʾ�Ի���

	//���ù�����������Χ
	dspDlg.ScreenToClient(&dlgrect);
	int vmaxPos = (int)((nh-m_showdlgh+49)/50);  //suppose i unit means 50 pixels
	::SetScrollRange(dspDlg.m_hWnd, SB_VERT, 0, vmaxPos, true);

	//�ͷ���ʱ�ռ�
	if (newdata)
		delete[] newdata;
	else
		MessageBox("error");
	//note:��Ҫ��dspdlg�е�onpaint���ػ�	
}

void CIMAGEMATCHOnSIFTDlg::OnButtonclear() 
{
	// TODO: Add your control notification handler code here
	//���2���༭������
	if (dspDlg.m_hWnd)
	{
		MessageBox("ͼ���Ѵ򿪣����ȹر�ͼ��!");
		return;
	}
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDITSELECTIMG1);
	pEdit->SetReadOnly(false);
	pEdit = (CEdit *)GetDlgItem(IDC_EDITSELECTIMG2);
	pEdit->SetReadOnly(false);
	SetDlgItemText(IDC_EDITSELECTIMG1, "");
	SetDlgItemText(IDC_EDITSELECTIMG2, "");
}

void CIMAGEMATCHOnSIFTDlg::OnButtonfd() 
{
	// TODO: Add your control notification handler code here
	/*�ж϶����Ƿ��Ѿ���*/
	if (dspDlg.m_hWnd==NULL)
	{
		//����ǰͼ��δ���أ�����buttonshowimg����
		if (OnButtonshowimg()==0)
			return;
	}
	if (dspDlg.m_sifted)/*�Ѿ����������*/
		return;

	//��ȡ����
	CString buf;
	UpdateData(true);
	CComboBox *pCombo;

	//gauss���ڰ뾶s
	float	gsw;	
	pCombo = (CComboBox *)GetDlgItem(IDC_COMBOGWS);
	pCombo->GetLBText(m_gws, buf);
	gsw = atof(buf);

	//Ϊ���и�˹ƽ�����õı߽����
	int		bd;		
	pCombo = (CComboBox *)GetDlgItem(IDC_COMBOBD);
	pCombo->GetLBText(m_bd, buf);
	bd = atoi(buf);

	//��0��octave�ĵ�0��ĸ�˹ƽ��ϵ��
	float	sigma0;		
	sigma0 = atof(m_is);

	//Ϊ�����ͶԱȶ����õ���ֵ
	float	contr_thr;		
	contr_thr = atof(m_cd);

	//����������һ�����õ��ݶ���ֵ
	float norm_thresh;
	pCombo = (CComboBox *)GetDlgItem(IDC_COMBOMT);
	pCombo->GetLBText(m_mt, buf);
	norm_thresh = atof(buf);

	//������ͼ���Ƿ�Ҫdouble
	int db_img= ((CButton *)GetDlgItem(IDC_CHECKDBLBASEIMG))->GetCheck();
	if (db_img==BST_UNCHECKED)
		db_img = 0;
	else if (db_img==BST_CHECKED)
		db_img = 1;

	//���һ��ͼ��ķֱ���
	int top_oct_res;
	pCombo = (CComboBox *)GetDlgItem(IDC_COMBOMINIRES);
	pCombo->GetLBText(m_miniRes, buf);
	top_oct_res = atoi(buf);

	//�ٶ�ͼ���Ѿ����ڵ�ģ��ϵ��
	float sigman = 0.5f;		

// 	gsw = 2.5;							//gauss���ģ��뾶Ϊgwid*sigma
// 	db_img = 0;
// 	sigma0 = 1.6f;
// 	sigman = 0.5f;
// 	contr_thr	= 0.03f;					//���Աȶ���ֵ=contr_thr/scales
// 	bd = 5;
// 	norm_thresh = 0.2f;				//�wһ���ֵ

	//��������ͼ�����������
	HeadStand(m_width1, m_height1, m_graydata1);	//
	featVect1 = sifting(m_width1, m_height1, m_graydata1, gsw, db_img, sigma0, sigman, contr_thr, bd, norm_thresh, top_oct_res);
	CString keyn1;
	char chbuf[10];
	int keynum1 = featVect1->to_extr_num;
	itoa(keynum1, chbuf, 10);
	keyn1.Format("%s", chbuf);
	SetDlgItemText(IDC_EDITKEYPOINTSNUM1, keyn1);		//��ʾ��⵽�Ĺؼ�����

	HeadStand(m_width2, m_height2, m_graydata2);
	featVect2 = sifting(m_width2, m_height2, m_graydata2, gsw, db_img, sigma0, sigman, contr_thr, bd, norm_thresh, top_oct_res);
	CString keyn2;
	int keynum2 = featVect2->to_extr_num;
	itoa(keynum2, chbuf, 10);
	keyn2.Format("%s", chbuf);
	SetDlgItemText(IDC_EDITKEYPOINTSNUM2, keyn2);

	dspDlg.m_sifted = true;	
}
/*
ִ��sift������ȡ

w:			ͼ����
h:			ͼ��߶�
graydata:	ͼ������
wid:		gauss��������
db_img:		������ͼ���Ƿ�Ҫdouble
sigma0:     ��ײ�ͼ���ƽ������
sigman:		�ٶ���ʼͼ�����е�ƽ������
contr_thr:	�Աȶ���ֵ
sift_border:��ֵ�������߽�
norm_thresh:���������ݶ���ֵ 
*/
FeatureVect* CIMAGEMATCHOnSIFTDlg::sifting(int w, int h, BYTE *graydata, float wid, int db_img, float sigma0,\
										   float sigman, float contr_thr, int sift_border, float norm_thresh, int top_oct_res)
{
	FeatureVect *featVect;

	featVect = _sift_main("reserved", graydata, w, h, wid, db_img, sigma0, sigman, contr_thr, sift_border, norm_thresh, top_oct_res);

	//����⵽�Ĺؼ�����ʾ��ͼ����
	ShowKeypoints(0);
	//dspDlg.SetFocus();
	return featVect;
}
//���õ��Ĺؼ�����ʾ�ڽ�����
void CIMAGEMATCHOnSIFTDlg::ShowKeypoints(int img)
{
	//����
	dspDlg.SetFocus();
	dspDlg.Invalidate(FALSE);
	//dspDlg�е�onpaint��������ػ�
}



void CIMAGEMATCHOnSIFTDlg::OnSelchangeCombogws() 
{
	// TODO: Add your control notification handler code here
	CString gwsItem, bdItem;
	GetDlgItemText(IDC_COMBOBD, bdItem);
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBOGWS);
	pCombo->GetLBText(pCombo->GetCurSel(), gwsItem);

	UpdateData(true);
}


void CIMAGEMATCHOnSIFTDlg::OnSelchangeCombobd() 
{
	// TODO: Add your control notification handler code here
	CString gwsItem, bdItem;
	GetDlgItemText(IDC_COMBOGWS, gwsItem);
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBOBD);
	pCombo->GetLBText(pCombo->GetCurSel(), bdItem);

	UpdateData(true);
}

//������ʵ�ֵ����Ի����ƶ�ʱ���ӶԻ���������Ի����ƶ�
void CIMAGEMATCHOnSIFTDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);

	if (dspDlg.m_hWnd)
	{
		int nw = (m_width1>m_width2) ? m_width1 : m_width2;
		CWnd *pWnd = dspDlg.GetDlgItem(IDC_IMGDISPLAYER); //�õ�ͼƬ�ؼ�ָ��
		CRect dlgrect, rect;
		pWnd->GetWindowRect(&rect); //�õ�ͼ��ؼ��������Ļ���Ͻǵ�����
		dspDlg.ScreenToClient(&rect); //����Ļ����ת��Ϊ�û�����
		::GetWindowRect(this->m_hWnd, &dlgrect);
		nw = nw+(int)(2.5*rect.left);
		::SetWindowPos(dspDlg.m_hWnd, HWND_TOPMOST, dlgrect.right, dlgrect.top, nw, m_showdlgh,SWP_SHOWWINDOW);	
	}
	
	// TODO: Add your message handler code here	
}

void CIMAGEMATCHOnSIFTDlg::OnDropdownCombogws() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_COMBOGWS);
	pCombo->SetFocus();
}


int CIMAGEMATCHOnSIFTDlg::mem2D_alloc(double ***arr, int h, int w)
{
	*arr = new double*[h];
	for (int j=0; j<h; j++)
		(*arr)[j] = new double[w];

	return h*w*sizeof(double);
}

void CIMAGEMATCHOnSIFTDlg::mem2D_free(double **arr, int h)
{
	if (arr)
	{
		for (int j=0; j<h; j++)
			delete[] arr[j];
		delete[] arr;
	}
}

int CIMAGEMATCHOnSIFTDlg::mem3D_alloc(double ****arr, int h, int w, int o)
{
	*arr = new double**[h];
	for (int j=0; j<h; j++)
		mem2D_alloc((*arr)+j, w, o);
	return h*w*o*sizeof(double);
}

void CIMAGEMATCHOnSIFTDlg::mem3D_free(double ***arr, int h, int w)
{
	if (arr)
	{
		for (int j=0; j<h; j++)
			mem2D_free(arr[j], w);
		delete[] arr;
	}
}

int CIMAGEMATCHOnSIFTDlg::mem4D_alloc(double *****arr, int h, int w, int o, int b)
{
	*arr = new double ***[h];
	for (int j=0; j<h; j++)
		mem3D_alloc((*arr)+j, w, o, b);
	return h*w*o*b*sizeof(double);
}

void CIMAGEMATCHOnSIFTDlg::mem4D_free(double ****arr, int h, int w, int o)
{
	if (arr)
	{
		for (int j=0; j<h; j++)
			mem3D_free(arr[j], w, o);
		delete[] arr;
	}
}



void CIMAGEMATCHOnSIFTDlg::OnButtonmatch() 
{
	// TODO: Add your control notification handler code here
	if  (!dspDlg.m_sifted)
	{
		MessageBox("��������ƥ��");
		return;
	}
		
	int k;
	int matchednum = 0;		//ƥ������
	double distance1, distance2, distance;
	double dr;
	
	CString buf;
	UpdateData(true);
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBOSDR);
	pCombo->GetLBText(m_sdr, buf);
	dr = atof(buf);		
	dr = dr*dr;			//distance ratio 0.8*0.8

	//int (*matchedcos)[2][2];
	int keynum1 = featVect1->to_extr_num;
	int keynum2 = featVect2->to_extr_num;

	int keynum = (keynum1>keynum2) ? keynum1 : keynum2;
	matchedcos = new int[keynum][2][2];			//ƥ�������� 0:img1, 1:img2 0: y, 1:x

	int x12, x22, y12, y22;		//	y����ͼ��
	FeatureNode *node1, *node2;
	node1 = featVect1->first;
	float *descriptor1, *descriptor2;
	double diff;

	int bx, by, ex, ey;

	while(node1!=NULL)
	{
		bx = (int)(node1->feat->ox+0.5f);
		by = (int)(node1->feat->oy+0.5f);
		if ((bx==14)&&(by==84))
		{
			MessageBox("");
		}

		descriptor1 = node1->feat->descriptor;
		distance1 = distance2 = 100000000000000000000.00;
		node2 = featVect2->first;

		while(node2!=NULL)
		{
			ex = (int)(node2->feat->ox+0.5f);
			ey = (int)(node2->feat->oy+0.5f);
			if ((ex>254)&&(ex<264)&&(ey>9)&&(ey<19))
			{
				MessageBox("");
			}

			descriptor2 = node2->feat->descriptor;
			distance = 0.0;
			for (k=0; k<SIFT_DESC_LEN; k++)
			{
				diff = descriptor1[k]-descriptor2[k];
				distance += diff*diff;
			}
			if (distance<distance1)
			{
				distance2 = distance1;
				distance1 = distance;
				y22 = y12;
				x22 = x12;
				y12 = (int)(node2->feat->oy+0.5);
				x12 = (int)(node2->feat->ox+0.5);
			}
			else if (distance<distance2)
			{
				distance2 = distance;
				y22 = (int)(node2->feat->oy+0.5);
				x22 = (int)(node2->feat->ox+0.5);
			}
			node2 = node2->next;
		}
		if ((distance1/distance2<dr)) //����ƥ��
		{
			matchedcos[matchednum++][0][0] = (int)(node1->feat->oy+0.5);
			matchedcos[matchednum-1][0][1] = (int)(node1->feat->ox+0.5);
			matchedcos[matchednum-1][1][0] = y12;
			matchedcos[matchednum-1][1][1] = x12;
		}
		node1 = node1->next;
	}

	m_matchednum = matchednum;

	dspDlg.m_matched = true;
	ShowKeypoints(0);
	
	char chbuf[10];
	CString keyn;
	itoa(m_matchednum, chbuf, 10);
	keyn.Format("%s", chbuf);
	SetDlgItemText(IDC_EDITMATCHEDNUM, keyn);
}

/*deprecated. ����ʹ*/
void CIMAGEMATCHOnSIFTDlg::DrawMatchedLine()
{
	int k;
	CWnd *pWnd = GetDlgItem(IDC_IMGDISPLAYER);
	CClientDC dc(pWnd);
	CPen pen(PS_SOLID, 1, RGB(255,0,0));
	CPen *pOldpen = dc.SelectObject(&pen);
	dc.SelectStockObject(HOLLOW_BRUSH); 
	int nhnum = m_height1 + m_height2 -1;
	int y10;
	int x10;
	int y20;
	int x20;
	
	for (k=0; k<m_matchednum; k++)
	{
		y10 = matchedcos[k][0][0];
		x10 = matchedcos[k][0][1];
		y20 = matchedcos[k][1][0];
		x20 = matchedcos[k][1][1];
		
		dc.MoveTo(x10, nhnum-y10);
		dc.LineTo(x20, m_height2-1-y20);
	}
	dc.SelectObject(pOldpen);
}

/*
top->bottom,ͼ���rgb����˳������ʾ˳���෴

width: ͼ����
height:ͼ��߶�
imgbuf:ͼ���Ż�����
*/
void CIMAGEMATCHOnSIFTDlg::HeadStand(int width, int height, BYTE *imgbuf)
{
	int dist;
	BYTE *buftmp;

	dist	 = width*sizeof(BYTE);
	buftmp = new BYTE[dist];

	for (int i=0; i<height/2; i++)
	{
		memcpy(buftmp, imgbuf+i*dist, dist);
		memcpy(imgbuf+i*dist, imgbuf+(height-1)*dist-i*dist, dist);
		memcpy(imgbuf+(height-1)*dist-i*dist, buftmp, dist);
	}
	
	delete[] buftmp;
}
