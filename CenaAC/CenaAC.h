
// CenaAC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCenaACApp: 
// �йش����ʵ�֣������ CenaAC.cpp
//

class CCenaACApp : public CWinApp
{
public:
	CCenaACApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCenaACApp theApp;