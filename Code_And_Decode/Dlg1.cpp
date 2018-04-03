
// Dlg1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Code_And_Decode.h"
#include "Dlg1.h"
#include "afxdialogex.h"
#include "Dlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlg1 �Ի���




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


// CDlg1 ��Ϣ�������

BOOL CDlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDlg1::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDlg1::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDlg1::OnBnClickedBlogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool loginstate=UserCheck(MyCStringToConstChar(edit_username),MyCStringToConstChar(edit_userpassword));
	if(loginstate==true)//��¼�ɹ�
	{
		SetDlgItemText(IDC_EUSERNAME,_T(""));
		SetDlgItemText(IDC_EUSERPASSWORD,_T(""));
		SetDlgItemText(IDC_SLOGINSTATE,_T("��¼�ɹ�"));
		ShowWindow(SW_HIDE);//���ش˶Ի���
		CDlg2 dlg_2;
	    INT_PTR nResponse = dlg_2.DoModal();
		exit(0);
	}
	else if(loginstate==false)//��¼ʧ��
	{
		if(edit_username.IsEmpty()&&edit_userpassword.IsEmpty())
		{
		    GetDlgItem(IDC_EUSERNAME)->SetFocus();
		    SetDlgItemText(IDC_SLOGINSTATE,_T("�û��������벻��Ϊ�գ�����������"));
			AfxMessageBox(_T("�û��������벻��Ϊ�գ�����������"),MB_OK,NULL);
		}
		else if(edit_username.IsEmpty())
		{
		    GetDlgItem(IDC_EUSERNAME)->SetFocus();
		    SetDlgItemText(IDC_SLOGINSTATE,_T("�û�������Ϊ�գ�����������"));
			AfxMessageBox(_T("�û�������Ϊ�գ�����������"),MB_OK,NULL);
		}
		else if(edit_userpassword.IsEmpty())
		{
		    GetDlgItem(IDC_EUSERPASSWORD)->SetFocus();
		    SetDlgItemText(IDC_SLOGINSTATE,_T("���벻��Ϊ�գ�����������"));
			AfxMessageBox(_T("���벻��Ϊ�գ�����������"),MB_OK,NULL);
		}
		else
		{
			SetDlgItemText(IDC_EUSERNAME,_T(""));
		    SetDlgItemText(IDC_EUSERPASSWORD,_T(""));
		    GetDlgItem(IDC_EUSERNAME)->SetFocus();
		    SetDlgItemText(IDC_SLOGINSTATE,_T("�û��������벻��ȷ������������"));
			AfxMessageBox(_T("�û��������벻��ȷ������������"),MB_OK,NULL);
		}
	}
}


void CDlg1::OnBnClickedBreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EUSERNAME,_T(""));
	SetDlgItemText(IDC_EUSERPASSWORD,_T(""));
}


void CDlg1::OnBnClickedBloginexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CDlg1::OnEnChangeEusername()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CDlg1::OnEnChangeEuserpassword()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}
