
// Dlg1.h : ͷ�ļ�
//

#pragma once


// CDlg1 �Ի���
class CDlg1 : public CDialogEx
{
// ����
public:
	CDlg1(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CODE_AND_DECODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBlogin();
	afx_msg void OnBnClickedBreset();
	afx_msg void OnBnClickedBloginexit();
	CString edit_username;//������û���
	CString edit_userpassword;//���������
	afx_msg void OnEnChangeEusername();
	afx_msg void OnEnChangeEuserpassword();
};
