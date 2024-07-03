// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "llk.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include<random>
#include"HelpDlg.h"
#include"llkDlg.h"
#include<string>

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	bPause = false;
	bStart = false;
	timeCount = 10;
	isLevel = false;
	dlgname = "舟舟连连看-基本模式";
}
CGameDlg::CGameDlg(int timeCount,CWnd* pParent)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	bStart = false;
	bPause = false;
	this->timeCount = timeCount;
	isLevel = true;
	dlgname = "舟舟连连看-关卡模式 ";
	std::string levelname = "第" + std::to_string(level)+"/3关";
	dlgname = dlgname + levelname;
	
}

CGameDlg::~CGameDlg()
{

}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	//ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON2, &CGameDlg::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON5, &CGameDlg::OnBnClickedButton5)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CGameDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_TIP, &CGameDlg::OnBnClickedButtonTip)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CGameDlg::OnBnClickedButtonPause)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CGameDlg::OnNMCustomdrawProgress1)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, &CGameDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CGameDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CGameDlg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序
void CGameDlg::InitBackground()
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

void CGameDlg::InitElement()
{
	//载入元素
	CClientDC dc(this);
	CBitmap bmpElem;
	bmpElem.LoadBitmapW(IDB_BITMAP4);
	/*HANDLE bmp = ::LoadImage(NULL, _T("theme\\001.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	*/m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmpElem);
	
	//载入mask
	CBitmap bmpMask;
	bmpMask.LoadBitmapW(IDB_BITMAP6);
	/*HANDLE bmp = ::LoadImage(NULL, _T("theme\\inv0031.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	*/m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(bmpMask);

}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitElement();
	InitBackground();
		//设置图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); 
	SetIcon(hIcon, TRUE);

	SetWindowText((LPCTSTR)_bstr_t(dlgname.c_str()));

	SetWindowPos(NULL, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	this->GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
	

}




void CGameDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

}



void CGameDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码	

}





void CGameDlg::OnBnClickedButtonStart()
{
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);
	this->GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(TRUE);

	// TODO: 在此添加控件通知处理程序代码
	bStart = true;
	game.UpdataMap(m_dcMem, m_dcBG, m_dcMask, m_dcElement);
	//初始化进度条
	m_GameProgress.SetRange(0, timeCount);    //初始范围
	m_GameProgress.SetStep(-1);            //初始步数值
	m_GameProgress.SetPos(timeCount);
	this->SetTimer(IDC_PROGRESS1, 1000, NULL);

	Invalidate(FALSE);
}

void CGameDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	game.ReSet();
	game.UpdataMap(m_dcMem, m_dcBG, m_dcMask, m_dcElement);
	InvalidateRect(game.m_rcGame, FALSE);
}
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x< game.m_ptGame.x || point.y < game.m_ptGame.y
		|| point.x>game.m_ptGame.x + nCol * sizeElem || 
		point.y>game.m_ptGame.y + nCol * sizeElem)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (bPause==true || bStart==false)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int row = (point.y - game.m_ptGame.y) / sizeElem;//行号
	int col= (point.x - game.m_ptGame.x) / sizeElem;
	if (game.fistslect)
	{
		game.DrawFrame(this,row, col);
		game.firstpoint.x = col;
		game.firstpoint.y = row;
	}
	else
	{
		game.DrawFrame(this,row, col);
		game.secpoint.x = col;
		game.secpoint.y = row;
		//判断是否同一图片
		if (game.IsLink(this,game.firstpoint,game.secpoint))
		{

			game.m_anMap[game.firstpoint.y][game.firstpoint.x] = -1;
			game.m_anMap[game.secpoint.y][game.secpoint.x] = -1;
			game.UpdataMap(m_dcMem,m_dcBG,m_dcMask,m_dcElement);
			JudgeWin(timeCount);
		}
		Sleep(100);
		InvalidateRect(game.m_rcGame, FALSE);
	}
	game.fistslect = !game.fistslect;
}






void CGameDlg::OnBnClickedButtonTip()
{
	// TODO: 在此添加控件通知处理程序代码
	Vex p1, p2;
	game.FindLink(p1, p2, this);
}


void CGameDlg::OnBnClickedButtonPause()
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


void CGameDlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == IDC_PROGRESS1 && bPause == false)
	{
	
		//游戏时间减一秒
		if (timeCount > -1)
		{
        //设置初始值
			CString str;
			str.Format(_T("%d"), timeCount);
			SetDlgItemText(IDC_EDIT1, str);
			UpdateData(false);
			--timeCount;
			JudgeWin(timeCount);
			
			m_GameProgress.StepIt();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CGameDlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	HelpDlg dlg;
	dlg.DoModal();
}

int CGameDlg::JudgeWin(int timecount)
{
	CString strTitle;
	if (game.IsWin() == 1)
	{
		KillTimer(IDC_PROGRESS1);
		MessageBox(_T("博士，你怎么还在玩！"), strTitle);
		this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		this->ShowWindow(SW_HIDE);
		if (isLevel == true)
		{
			if (level <=2)
			{
				level++;
				EndDialog(0);
				CGameDlg dlg(300 / (level), nullptr);
				dlg.DoModal();
			}

		}
		else
		{
			/*CllkDlg dlg;
			dlg.DoModal();*/
			EndDialog(0);
		}

		return 1;

	}
	else
	{

		//提示获胜
		if(timecount<=-1)
		{
			KillTimer(IDC_PROGRESS1);
			MessageBox(_T("这都过不了，快去玩明日方舟！"), strTitle);
			this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BUTTON_TIP)->EnableWindow(FALSE);
			this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
			this->ShowWindow(SW_HIDE);
			/*CllkDlg dlg;
			dlg.DoModal();*/
			EndDialog(0);
			return -1;

		}
		else
		{
			return 0;
		}
		this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	}
}


void CGameDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTitle;
	MessageBox(_T("这里不是设置！"), strTitle);

}
