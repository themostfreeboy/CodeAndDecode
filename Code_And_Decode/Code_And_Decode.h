
// Code_And_Decode.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCode_And_DecodeApp:
// �йش����ʵ�֣������ Code_And_Decode.cpp
//

class CCode_And_DecodeApp : public CWinApp
{
public:
	CCode_And_DecodeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCode_And_DecodeApp theApp;