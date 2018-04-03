#pragma once
#include "afxwin.h"


// CDlg2 对话框

class CDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg2)

public:
	CDlg2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg2();

// 对话框数据
	enum { IDD = IDD_DLGMAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRcode();
	int CodeOrDecode;
	CComboBox CBModeControl;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBchoosefile();
	afx_msg void OnBnClickedBstart();
	afx_msg void OnBnClickedBmainexit();
	CString EditChoosePath;
	afx_msg void OnEnChangeEfilepath();
};
