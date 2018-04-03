
// Dlg1.h : 头文件
//

#pragma once


// CDlg1 对话框
class CDlg1 : public CDialogEx
{
// 构造
public:
	CDlg1(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CODE_AND_DECODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBlogin();
	afx_msg void OnBnClickedBreset();
	afx_msg void OnBnClickedBloginexit();
	CString edit_username;//输入的用户名
	CString edit_userpassword;//输入的密码
	afx_msg void OnEnChangeEusername();
	afx_msg void OnEnChangeEuserpassword();
};
