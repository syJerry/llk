#pragma once
#include "afxdialogex.h"
#include "global.h"


// HelpDlg 对话框

class HelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HelpDlg)

public:
	HelpDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~HelpDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	HICON m_hIcon;    //系统图片
	CDC m_dcMem;      //内存DC
	CDC m_dcHelp;     //帮助图片DC
	CRect m_rtHelp;   //帮助图片显示区

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);  // 响应滚动条函数
	void UpdateHelp(int nPos);    //根据滚动条的位置，设置帮助图片的位置显示的内容
	afx_msg void OnNMThemeChangedScrollbar1(NMHDR* pNMHDR, LRESULT* pResult);
};
