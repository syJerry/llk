// HelpDlg.cpp: 实现文件
//

#include "pch.h"
#include "llk.h"
#include "afxdialogex.h"
#include "HelpDlg.h"


// HelpDlg 对话框

IMPLEMENT_DYNAMIC(HelpDlg, CDialogEx)

HelpDlg::HelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{

}

HelpDlg::~HelpDlg()
{
}

void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()



// HelpDlg 消息处理程序
BOOL HelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);

	CClientDC dc(this);
	//加载Help图片资源
	//加载BMP图片资源
	CBitmap hBmpHelp;
	hBmpHelp.LoadBitmapW(IDB_BITMAP3);
	//创建与视频内容兼容的内存DC
	m_dcHelp.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcHelp.SelectObject(hBmpHelp);
	//创建内存DC大小
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 453, 1074);
	m_dcMem.SelectObject(&bmpMem);

	//绘制白色背景
	m_dcMem.BitBlt(0, 0,10000, 10000, NULL, 0, 0, WHITENESS);

	//绘制帮助信息显示区域
	this->GetDlgItem(IDC_STATIC)->GetWindowRect(&m_rtHelp);
	this->ScreenToClient(&m_rtHelp);
	//绘制帮助
	UpdateHelp(0);

	//设置滚动条范围
	CBitmap bmpHelp;
	bmpHelp.Attach(hBmpHelp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);

	//设置滚动条的范围
	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(0, bmpInfo.bmHeight);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void HelpDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码

	//绘制背景图片
	dc.BitBlt(0, 0, 453, 375, &m_dcMem, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();

}

void HelpDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int pos = pScrollBar->GetScrollPos();
	int nMinPos;
	int nMaxPos;
	pScrollBar->GetScrollRange(&nMinPos, &nMaxPos);    //得到滚动条的范围

	switch (nSBCode)
	{
	case SB_LINEUP:           //点击向上按钮
		pos -= 1;
		break;
	case SB_LINEDOWN:         //点击向下按钮
		pos += 1;
		break;
	case SB_PAGEUP:           //向上翻页
		pos -= 10;
		break;
	case SB_PAGEDOWN:         //向下翻页
		pos += 10;
		break;
	case SB_TOP:              //顶部
		pos = nMinPos;
		break;
	case SB_BOTTOM:           //底部
		pos = nMaxPos;
		break;
	case SB_THUMBPOSITION:    //点击在滑块上
		pos = nPos;
		break;
	default:
		break;
	}

	//设置滚动条当前点的值
	pScrollBar->SetScrollPos(pos, TRUE);
	//更新帮助信息
	UpdateHelp(pos);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void HelpDlg::UpdateHelp(int nPos)
{
	//将重绘区，绘制成白色
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, 0,
		0, NULL, 0, 0, WHITENESS);
	//绘制当前点的帮助信息
	m_dcMem.BitBlt(0, 4, 453,
		1074, &m_dcHelp, 0, nPos, SRCCOPY);
	// 更新页面
	InvalidateRect(m_rtHelp, FALSE);
}

