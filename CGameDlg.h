#pragma once
#include "afxdialogex.h"
#include "CGameLogic.hpp"
#include "global.h"
#include <string>


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CGameDlg(int timeCount,CWnd* pParent=nullptr);
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	CDC m_dcMem;//内存dc
	CDC m_dcBG;//背景
	CDC m_dcElement;//元素
	CDC m_dcMask;//掩码
	

	bool bPause;//是否暂停
	int timeCount;//时间
	bool isLevel;//是否为关卡模式
	std::string dlgname;//对话框名称
	CGameLogic<CGameDlg> game;//游戏逻辑类
	CProgressCtrl m_GameProgress;//进度条控制



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

protected:
	void InitBackground();
	void InitElement();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
	int JudgeWin(int timecount);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonTip();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtonHelp();
};
