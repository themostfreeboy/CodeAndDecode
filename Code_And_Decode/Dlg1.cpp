
// Dlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "Code_And_Decode.h"
#include "Dlg1.h"
#include "afxdialogex.h"
#include "Dlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlg1 对话框




CDlg1::CDlg1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg1::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EUSERNAME, edit_username);
	DDX_Text(pDX, IDC_EUSERPASSWORD, edit_userpassword);
}

BEGIN_MESSAGE_MAP(CDlg1, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BLOGIN, &CDlg1::OnBnClickedBlogin)
	ON_BN_CLICKED(IDC_BRESET, &CDlg1::OnBnClickedBreset)
	ON_BN_CLICKED(IDC_BLOGINEXIT, &CDlg1::OnBnClickedBloginexit)
	ON_EN_CHANGE(IDC_EUSERNAME, &CDlg1::OnEnChangeEusername)
	ON_EN_CHANGE(IDC_EUSERPASSWORD, &CDlg1::OnEnChangeEuserpassword)
END_MESSAGE_MAP()


// CDlg1 消息处理程序

BOOL CDlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDlg1::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDlg1::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDlg1::OnBnClickedBlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	bool loginstate=UserCheck(MyCStringToConstChar(edit_username),MyCStringToConstChar(edit_userpassword));
	if(loginstate==true)//登录成功
	{
		SetDlgItemText(IDC_EUSERNAME,_T(""));
		SetDlgItemText(IDC_EUSERPASSWORD,_T(""));
		SetDlgItemText(IDC_SLOGINSTATE,_T("登录成功"));
		ShowWindow(SW_HIDE);//隐藏此对话框
		CDlg2 dlg_2;
	    INT_PTR nResponse = dlg_2.DoModal();
		exit(0);
	}
	else if(loginstate==false)//登录失败
	{
		if(edit_username.IsEmpty()&&edit_userpassword.IsEmpty())
		{
		    GetDlgItem(IDC_EUSERNAME)->SetFocus();
		    SetDlgItemText(IDC_SLOGINSTATE,_T("用户名和密码不能为空，请重新输入"));
			AfxMessageBox(_T("用户名和密码不能为空，请重新输入"),MB_OK,NULL);
		}
		else if(edit_username.IsEmpty())
		{
		    GetDlgItem(IDC_EUSERNAME)->SetFocus();
		    SetDlgItemText(IDC_SLOGINSTATE,_T("用户名不能为空，请重新输入"));
			AfxMessageBox(_T("用户名不能为空，请重新输入"),MB_OK,NULL);
		}
		else if(edit_userpassword.IsEmpty())
		{
		    GetDlgItem(IDC_EUSERPASSWORD)->SetFocus();
		    SetDlgItemText(IDC_SLOGINSTATE,_T("密码不能为空，请重新输入"));
			AfxMessageBox(_T("密码不能为空，请重新输入"),MB_OK,NULL);
		}
		else
		{
			SetDlgItemText(IDC_EUSERNAME,_T(""));
		    SetDlgItemText(IDC_EUSERPASSWORD,_T(""));
		    GetDlgItem(IDC_EUSERNAME)->SetFocus();
		    SetDlgItemText(IDC_SLOGINSTATE,_T("用户名或密码不正确，请重新输入"));
			AfxMessageBox(_T("用户名或密码不正确，请重新输入"),MB_OK,NULL);
		}
	}
}


void CDlg1::OnBnClickedBreset()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EUSERNAME,_T(""));
	SetDlgItemText(IDC_EUSERPASSWORD,_T(""));
}


void CDlg1::OnBnClickedBloginexit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CDlg1::OnEnChangeEusername()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CDlg1::OnEnChangeEuserpassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}
