
// llkDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "llk.h"
#include "llkDlg.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include"HELPDLG.h"
#include"RelaxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CllkDlg 对话框



CllkDlg::CllkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	level = 1;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CllkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CllkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()

	//ON_BN_CLICKED(IDC_BUTTON1, &CllkDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_BASE, &CllkDlg::OnBnClickedButtonBase)
	//ON_BN_CLICKED(IDC_BUTTON4, &CllkDlg::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON6, &CllkDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_XIUXIAN, &CllkDlg::OnBnClickedButtonXiuxian)
	ON_BN_CLICKED(IDC_BUTTON_BANZHU, &CllkDlg::OnBnClickedButtonBanzhu)
	ON_BN_CLICKED(IDC_BUTTON_GAUNQIA, &CllkDlg::OnBnClickedButtonGaunqia)
END_MESSAGE_MAP()


// CllkDlg 消息处理程序

BOOL CllkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码| SWP_NOZORDER| SWP_NOACTIVATE
	SetWindowPos(NULL, 0, 0, 835, 635, SWP_NOMOVE );
	InitBackground();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CllkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CllkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rect;
		GetClientRect(&rect);
		CPaintDC dc(this);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, 808, 584, SRCCOPY);
		//dc.BitBlt(0,0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CllkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CllkDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// 调用父类实现
	CDialogEx::OnGetMinMaxInfo(lpMMI);

	// 设置对话框的最大和最小大小为初始大小
	/*lpMMI->ptMinTrackSize.x = GetIniDialogSize().cx;
	lpMMI->ptMinTrackSize.y = GetIniDialogSize().cy;
	lpMMI->ptMaxTrackSize.x = GetIniDialogSize().cx;
	lpMMI->ptMaxTrackSize.y = GetIniDialogSize().cy;*/
}


void CllkDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CGameDlg dlg;
	dlg.DoModal();
}







void CllkDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	int dlgitem[6] = {	IDC_BUTTON1,
						IDC_BUTTON2,
						IDC_BUTTON3,
						IDC_BUTTON4,
						IDC_BUTTON5,
						IDC_BUTTON6 };
}


void CllkDlg::InitBackground()
{
	//加载位图
	CBitmap bmpMain;
	//IDB_MAIN_BG
	bmpMain.LoadBitmapW(IDB_MAIN_BG);

	//创建兼容DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);

	//将位图载入DC
	m_dcMem.SelectObject(&bmpMain);


}



void CllkDlg::OnBnClickedButtonBase()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CllkDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CllkDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CllkDlg::OnBnClickedButtonXiuxian()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	RelaxDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);

}


void CllkDlg::OnBnClickedButtonBanzhu()
{
	// TODO: 在此添加控件通知处理程序代码
	HelpDlg dlg;
	dlg.DoModal();
}


void CllkDlg::OnBnClickedButtonGaunqia()
{
	int timeCount = 300;
	// TODO: 在此添加控件通知处理程序代码

		this->ShowWindow(SW_HIDE);
		CGameDlg dlg(300/(level), nullptr);
		dlg.DoModal();
		this->ShowWindow(SW_SHOW);



}
