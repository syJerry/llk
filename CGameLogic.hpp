#pragma once
#include "afxdialogex.h"
#include "pch.h"
#include<random>
#include"global.h"
#include<vector>

template<class T>
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic()
	{
		for (int i = 0; i < nRow; ++i) {
			delete[] m_anMap[i];
		}
		delete[] m_anMap;
	}

	void  DrawFrame(T* dlg,int row, int col);//画框

	void DrawLine(T* dlg,Vex point1, Vex point2);//划线

	void UpdataMap(CDC &m_dcMem, CDC &m_dcBG, CDC &m_dcMask, CDC &m_dcElement);//更新游戏地图

	bool IsLink(T* dlg, Vex firstpoint, Vex secpoint);//判断是否联通

	bool IsLinkInRow(Vex point1, Vex point2);//判断在横轴是否联通


	bool IsLinkInCol(Vex point1, Vex point2);//判断纵轴是否联通

	bool IsLinkOneCorner(T* dlg, Vex point1, Vex point2);//判断一个拐点是否能联通

	bool IsLinkTwoCorner(T* dlg, Vex point1, Vex point2);//判断两个拐点是否能联通

	void ReSet();//重排


	bool FindOtherPoint(T* dlg, Vex point1, Vex& point2);
	bool FindLink(Vex& point1, Vex& point2, T* dlg);

	bool IsWin();//判断是否胜利 0：未胜利 ；1：胜利

	

public:
	int** m_anMap;
	bool fistslect;//是否第一个点
	Vex firstpoint;//第一个选择点
	Vex secpoint;//第二个选择点

	CPoint m_ptGame;//游戏地图左上点
	CRect m_rcGame;


};
template<typename T>
void  CGameLogic<T>::DrawFrame(T* dlg,int row, int col)
{
	CClientDC dc(dlg);
	CBrush brush(RGB(0, 0, 255));
	CRect rect;
	rect.left = m_ptGame.x + col * sizeElem;
	rect.top = m_ptGame.y + row * sizeElem;
	rect.right = rect.left + sizeElem;
	rect.bottom = rect.top + sizeElem;
	dc.FrameRect(rect, &brush);
}

template<typename T>
CGameLogic<T>::CGameLogic()
{
	fistslect = 1;
	m_ptGame.x = 250;
	m_ptGame.y = 50;
	m_rcGame.left = m_ptGame.x;
	m_rcGame.top = m_ptGame.y;

	m_rcGame.right = m_ptGame.x + nRow * sizeElem;
	m_rcGame.bottom = m_ptGame.y + nCol * sizeElem;

	m_anMap = new int* [nRow]; // 创建指针数组

	for (int i = 0; i < nRow; ++i) {
		m_anMap[i] = new int[nCol]; // 每个指针指向一个数组
	}
	std::random_device rd;
	std::uniform_int_distribution<> dis(0, 9);
	std::mt19937 gen(rd());

	int num = 0;
	std::vector<int> v;
	for (int i = 0; i < nRow*nCol; i+=2)
	{
		num = dis(gen);
		v.push_back(num);
		v.push_back(num);
	}
	std::shuffle(v.begin(), v.end(), gen);
	for (int i = 0; i < nRow; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			m_anMap[i][j] = v[i * nRow + j];
		}
	}
	
}
template<typename T>
void CGameLogic<T>::UpdataMap(CDC& m_dcMem, CDC& m_dcBG, CDC& m_dcMask, CDC& m_dcElement)
{
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 350, 0, SRCCOPY);
	for (int i = 0; i < nRow; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			m_dcMem.BitBlt(m_ptGame.x + j * sizeElem, m_ptGame.y + i * sizeElem, sizeElem, sizeElem,
				&m_dcMask, 0, m_anMap[i][j] * sizeElem, SRCPAINT);
			m_dcMem.BitBlt(m_ptGame.x + j * sizeElem, m_ptGame.y + i * sizeElem, sizeElem, sizeElem,
				&m_dcElement, 0, m_anMap[i][j] * sizeElem, SRCAND);
		}
	}
}
template<typename T>
void CGameLogic<T>::DrawLine(T* dlg, Vex point1, Vex point2)
{
	CClientDC dc(dlg);
	CPen pen(PS_SOLID, 2, RGB(0, 0, 255));
	CPen* dcpen = dc.SelectObject(&pen);

	dc.MoveTo(m_ptGame.x + point1.x * sizeElem + sizeElem / 2,
		m_ptGame.y + point1.y * sizeElem + sizeElem / 2);
	dc.LineTo(m_ptGame.x + point2.x * sizeElem + sizeElem / 2,
		m_ptGame.y + point2.y * sizeElem + sizeElem / 2);
	dc.SelectObject(dcpen);
}


template<typename T>
bool CGameLogic<T>::IsLink(T* dlg,Vex firstpoint,Vex secpoint)
{
	if (m_anMap[firstpoint.y][firstpoint.x]
		== m_anMap[secpoint.y][secpoint.x])
	{
		Vex point1, point2;
		point1 = firstpoint;
		point2 = secpoint;
		//一条直线
		if (firstpoint.y == secpoint.y)
		{
			if (IsLinkInRow(point1, point2) == true)
			{
				DrawLine(dlg,point1, point2);
				return true;
			}

		}
		else if (firstpoint.x == secpoint.x)
		{
			if (IsLinkInCol(point1, point2) == true)
			{
				DrawLine(dlg,point1, point2);
				return true;
			}
		}
		//两条直线
		bool flag = IsLinkOneCorner(dlg, point1, point2);
		if (flag == true)
		{
			return flag;
		}
		else
		{
			return IsLinkTwoCorner(dlg, point1, point2);
		}

	}
	else
	{
		return false;
	}
	return false;
}

template<typename T>
bool CGameLogic<T>::IsLinkInRow(Vex point1, Vex point2)
{
	int row1 = point1.x;
	int row2 = point2.x;
	int i = 0;
	if (row1 > row2)
	{
		int tem = row1;
		row1 = row2;
		row2 = tem;
	}
	for (i = row1 + 1; i < row2; i++)
	{
		if (m_anMap[point1.y][i] != -1)
		{
			return false;
		}
	}
	if (i == row2)
	{
		return true;
	}
	return false;
}

template<typename T>
bool CGameLogic<T>::IsLinkInCol(Vex point1, Vex point2)
{
	int col1 = point1.y;
	int col2 = point2.y;
	int i = 0;
	if (col1 > col2)
	{
		int tem = col1;
		col1 = col2;
		col2 = tem;
	}
	for (i = col1 + 1; i < col2; i++)
	{
		if (m_anMap[i][point1.x] != -1)
		{
			return false;
		}
	}
	if (i == col2)
	{
		return true;
	}
	return false;
}
template<typename T>
bool CGameLogic<T>::IsLinkOneCorner(T* dlg, Vex point1, Vex point2)
{
	int row1 = point1.x;
	int row2 = point2.x;
	int col1 = point1.y;
	int col2 = point2.y;
	if (m_anMap[col1][row2] == -1 && IsLinkInRow(Vex(row1, col1), Vex(row2, col1)))
	{
		if (IsLinkInCol(Vex(row2, col1), Vex(row2, col2)))
		{
			DrawLine(dlg, Vex(row1, col1), Vex(row2, col1));
			DrawLine(dlg, Vex(row2, col1), Vex(row2, col2));
			return true;
		}
	}
	if (m_anMap[col2][row1] == -1 && IsLinkInCol(Vex(row1, col1), Vex(row1, col2)))
	{
		if (IsLinkInRow(Vex(row1, col2), Vex(row2, col2)))
		{
			DrawLine(dlg, Vex(row1, col1), Vex(row1, col2));
			DrawLine(dlg, Vex(row1, col2), Vex(row2, col2));
			return true;
		}
	}
	return false;
}

template<typename T>
bool CGameLogic<T>::IsLinkTwoCorner(T* dlg, Vex point1, Vex point2)
{
	int row1 = point1.x;
	int row2 = point2.x;
	int col1 = point1.y;
	int col2 = point2.y;
	//向下
	for (int i = col1 + 1; i < nCol && m_anMap[i][row1] == -1; i++)
	{
		if (IsLinkOneCorner(dlg, Vex(row1, i), point2) == true)
		{
			DrawLine(dlg, point1, Vex(row1, i));
			return true;
		}
	}
	//向右
	for (int i = row1 + 1; i < nRow && m_anMap[col1][i] == -1; i++)
	{
		if (IsLinkOneCorner(dlg, Vex(i, col1), point2) == true)
		{
			DrawLine(dlg, point1, Vex(i, col1));
			return true;
		}
	}
	//向左
	for (int i = row1 - 1; i >= 0 && m_anMap[col1][i] == -1; i--)
	{
		if (IsLinkOneCorner(dlg, Vex(i, col1), point2) == true)
		{
			DrawLine(dlg, point1, Vex(i, col1));
			return true;
		}
	}
	//向上
	for (int i = col1 - 1; i >= 0 && m_anMap[i][row1] == -1; i--)
	{
		if (IsLinkOneCorner(dlg, Vex(row1, i), point2) == true)
		{
			DrawLine(dlg, point1, Vex(row1, i));
			return true;
		}
	}

	return false;

}

template<typename T>
void CGameLogic<T>::ReSet()
{
	std::vector<int> arr;
	for (int i = 0; i < nRow; ++i) {
		for (int j = 0; j < nCol; ++j) {
			arr.push_back(m_anMap[i][j]);
		}
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(arr.begin(), arr.end(), gen);
	int index = 0;
	for (int i = 0; i < nRow; ++i) {
		for (int j = 0; j < nCol; ++j) {
			m_anMap[i][j] = arr[index++];
		}
	}
}

template<typename T>
bool CGameLogic<T>::IsWin()
{
	for (int i = 0; i < nRow; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			if (m_anMap[i][j] != -1)
			{
				return false;
			}
		}
	}
	return true;
}

template<typename T>
bool CGameLogic<T>::FindLink(Vex& point1, Vex& point2, T* dlg)
{
	for (int i = 0; i < nRow; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			if (m_anMap[i][j] == -1)
			{
				continue;
			}
			else
			{
				if (FindOtherPoint(dlg, Vex(j, i), point2))
				{
					DrawFrame(dlg, i, j);
					DrawFrame(dlg, point2.y, point2.x);
					return true;
				}
			}
		}
	}
}

template<typename T>
bool CGameLogic<T>::FindOtherPoint(T* dlg, Vex point1, Vex& point2)
{
	for (int i = 0; i < nRow; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			if(IsLink(dlg, point1, Vex(j, i)))
			{
				point2.x=j;
				point2.y=i;
				return true;
			}
		}
	}
	return false;
}