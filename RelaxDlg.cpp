// RelaxDlg.cpp: 实现文件
//

#include "pch.h"
#include "llk.h"
#include "afxdialogex.h"
#include "RelaxDlg.h"
#include"HelpDlg.h"
#include"llkDlg.h"
// RelaxDlg 对话框

IMPLEMENT_DYNAMIC(RelaxDlg, CDialogEx)

RelaxDlg::RelaxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_XIUXIAN, pParent)
{
	bPause = false;
	bStart = false;
}

RelaxDlg::~RelaxDlg()
{
}

void RelaxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RelaxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &RelaxDlg::OnBnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_RESET, &RelaxDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_TIP, &RelaxDlg::OnBnClickedButtonTip)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &RelaxDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &RelaxDlg::OnBnClickedButtonHelp)
END_MESSAGE_MAP()


// RelaxDlg 消息处理程序
void RelaxDlg::InitBackground()
{
	//读入背景图片
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_BITMAP2); 
	CClientDC dc(this);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmpMain);

	//初始化内存dc
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//把背景图片载入内层dc
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 350, 0, SRCCOPY);
}

void RelaxDlg::InitElement()
{
	//载入元素
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmp);

	//载入mask
	bmp = ::LoadImage(NULL, _T("theme\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(bmp);
}

BOOL RelaxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitElement();
	InitBackground();
	//设置图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);

	SetWindowPos(NULL, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	this->GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void RelaxDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}


void RelaxDlg::OnBnClickedButtonStart()
{
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(TRUE);

	// TODO: 在此添加控件通知处理程序代码
	game.UpdataMap(m_dcMem, m_dcBG, m_dcMask, m_dcElement);

	Invalidate(FALSE);
}



void RelaxDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x< game.m_ptGame.x || point.y < game.m_ptGame.y
		|| point.x>game.m_ptGame.x + nCol * sizeElem ||
		point.y>game.m_ptGame.y + nCol * sizeElem)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (bPause == true || bStart == false)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int row = (point.y - game.m_ptGame.y) / sizeElem;//行号
	int col = (point.x - game.m_ptGame.x) / sizeElem;
	if (game.fistslect)
	{
		game.DrawFrame(this, row, col);
		game.firstpoint.x = col;
		game.firstpoint.y = row;
	}
	else
	{
		game.DrawFrame(this, row, col);
		game.secpoint.x = col;
		game.secpoint.y = row;
		//判断是否同一图片
		if (game.IsLink(this, game.firstpoint, game.secpoint))
		{

			game.m_anMap[game.firstpoint.y][game.firstpoint.x] = -1;
			game.m_anMap[game.secpoint.y][game.secpoint.x] = -1;
			game.UpdataMap(m_dcMem, m_dcBG, m_dcMask, m_dcElement);
			JudgeWin(timeCount);
		}
		Sleep(100);
		InvalidateRect(game.m_rcGame, FALSE);
	}
	game.fistslect = !game.fistslect;
}


void RelaxDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	game.ReSet();
	game.UpdataMap(m_dcMem, m_dcBG, m_dcMask, m_dcElement);
	InvalidateRect(game.m_rcGame, FALSE);
}


void RelaxDlg::OnBnClickedButtonTip()
{
	// TODO: 在此添加控件通知处理程序代码
	Vex p1, p2;
	game.FindLink(p1, p2, this);
}


void RelaxDlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);

	//如果游戏没有暂停
	if (bPause == false)
	{
		// 绘制背景到内存DC中
		m_dcMem.BitBlt(game.m_ptGame.x, game.m_ptGame.y, 640, 400, &m_dcBG, 0, 0, SRCCOPY);
		//GetDlgItem(IDC_BUTTON_START)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(0);
		GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(0);

		InvalidateRect(game.m_rcGame, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextW(_T("继续游戏"));
	}
	else
	{
		game.UpdataMap(m_dcMem, m_dcBG, m_dcMask, m_dcElement);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(1);

		InvalidateRect(game.m_rcGame, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextW(_T("暂停游戏"));
	}
	bPause = !bPause;
}


void RelaxDlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	HelpDlg dlg;
	dlg.DoModal();
}

void RelaxDlg::JudgeWin(int timecount)
{
	if (game.IsWin() == 0)
	{
		return;
	}
	else
	{
		KillTimer(IDC_PROGRESS1);
		//提示获胜
		CString strTitle;
		if (timecount <= 0)
		{
			MessageBox(_T("很遗憾，时间到了！"), strTitle);
			this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
			this->ShowWindow(SW_HIDE);
			CllkDlg dlg;
			dlg.DoModal();
		}
		else
		{
			MessageBox(_T("获胜！"), strTitle);
			this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
			this->ShowWindow(SW_HIDE);
			CllkDlg dlg;
			dlg.DoModal();
		}
		this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	}
}