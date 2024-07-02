#pragma once
#include "afxdialogex.h"
#include "CGameLogic.hpp"
#include "global.h"



// RelaxDlg 对话框

class RelaxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RelaxDlg)

public:
	RelaxDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RelaxDlg();

protected:
	CDC m_dcMem;
	CDC m_dcBG;
	CDC m_dcElement;
	CDC m_dcMask;

	bool bStart;
	bool bPause;
	int timeCount;
	CGameLogic<RelaxDlg> game;

	CProgressCtrl m_GameProgress;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_XIUXIAN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

protected:
	void InitBackground();
	void InitElement();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	void JudgeWin(int timecount);

	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonTip();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonSet();
};
