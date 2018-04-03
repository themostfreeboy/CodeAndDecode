// Dlg2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Code_And_Decode.h"
#include "Dlg2.h"
#include "afxdialogex.h"


// CDlg2 �Ի���

IMPLEMENT_DYNAMIC(CDlg2, CDialogEx)

CDlg2::CDlg2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg2::IDD, pParent)
	, CodeOrDecode(0)
	, EditChoosePath(_T(""))
{
}

CDlg2::~CDlg2()
{
}

void CDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RCODE, CodeOrDecode);
	DDX_Control(pDX, IDC_CBMODE, CBModeControl);
	DDX_Text(pDX, IDC_EFILEPATH, EditChoosePath);
}


BEGIN_MESSAGE_MAP(CDlg2, CDialogEx)
	ON_BN_CLICKED(IDC_RCODE, &CDlg2::OnBnClickedRcode)
	ON_BN_CLICKED(IDC_RDECODE, &CDlg2::OnBnClickedRcode)
	ON_BN_CLICKED(IDC_BCHOOSEFILE, &CDlg2::OnBnClickedBchoosefile)
	ON_BN_CLICKED(IDC_BSTART, &CDlg2::OnBnClickedBstart)
	ON_BN_CLICKED(IDC_BMAINEXIT, &CDlg2::OnBnClickedBmainexit)
	ON_EN_CHANGE(IDC_EFILEPATH, &CDlg2::OnEnChangeEfilepath)
END_MESSAGE_MAP()


// CDlg2 ��Ϣ�������


void CDlg2::OnBnClickedRcode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(CodeOrDecode==0)//����
	{
		CBModeControl.ResetContent();
		CBModeControl.AddString(_T("ģʽһ(С�ļ��Ƽ�)"));//RSA����+zlibѹ��
		CBModeControl.AddString(_T("ģʽ��(���ļ��Ƽ�)"));//DES����+zlibѹ��
		CBModeControl.SetCurSel(0);//���õ�0��Ϊ��ʾ������
		SetDlgItemText(IDC_BSTART,_T("��ʼ����"));
	}
	else if(CodeOrDecode==1)//����
	{
		CBModeControl.ResetContent();
		CBModeControl.AddString(_T("(�Զ�ƥ��ģʽ)"));//�Զ�ƥ��ģʽ
		CBModeControl.AddString(_T("ģʽһ"));//RSA����+zlib��ѹ��
		CBModeControl.AddString(_T("ģʽ��"));//DES����+zlib��ѹ��
		CBModeControl.SetCurSel(0);//���õ�0��Ϊ��ʾ������
		SetDlgItemText(IDC_BSTART,_T("��ʼ����"));
	}
}


BOOL CDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_CBMODE);
	pBox->ResetContent();
	pBox->AddString(_T("ģʽһ(С�ļ��Ƽ�)"));//RSA����+zlibѹ��
	pBox->AddString(_T("ģʽ��(���ļ��Ƽ�)"));//DES����+7zѹ��
	pBox->SetCurSel(0);//���õ�0��Ϊ��ʾ������
	SetDlgItemText(IDC_BSTART,_T("��ʼ����"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlg2::OnBnClickedBchoosefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString szPath = _T("");

	//CFileDialog::CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL);
    //�����������£�
    //bOpenFileDialog��ΪTRUE����ʾ�򿪶Ի���ΪFALSE����ʾ����Ի��ļ��Ի��� 
    //lpszDefExt��ָ��Ĭ�ϵ��ļ���չ���� 
    //lpszFileName��ָ��Ĭ�ϵ��ļ����� 
    //dwFlags��ָ��һЩ�ض���� 
    //lpszFilter��������Ҫ��һ����������ָ���ɹ�ѡ����ļ����ͺ���Ӧ����չ����

    CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);

    if (dlgFile.DoModal())
    {
        szPath = dlgFile.GetPathName();
    }
	if(!szPath.IsEmpty())
	{
	    SetDlgItemText(IDC_EFILEPATH,szPath);
	}
	else
	{
		//SetDlgItemText(IDC_EFILEPATH,_T(""));
        //AfxMessageBox(_T("��Ч���ļ���������ѡ��"),MB_OK,NULL);
	}
}


void CDlg2::OnBnClickedBstart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(EditChoosePath.IsEmpty())
	{
		SetDlgItemText(IDC_SMAINSTATE,_T("�ļ�·������Ϊ��"));
		AfxMessageBox(_T("�ļ�·������Ϊ��"),MB_OK,NULL);
		return;
	}
	if(CodeOrDecode==0)//����
	{
		errno_t err_read;
		FILE *fp_read = NULL;
	    err_read = fopen_s(&fp_read, MyCStringToConstChar(EditChoosePath), "rb");
	    if (err_read != 0)//�ļ���ʧ��
	    {
			SetDlgItemText(IDC_SMAINSTATE,_T("�������ļ���ʧ��"));
			AfxMessageBox(_T("�������ļ���ʧ��"),MB_OK,NULL);
		    return;
	    }
		fclose(fp_read);

		int nIndex = CBModeControl.GetCurSel();
		if(nIndex==0)//ģʽһ(С�ļ��Ƽ�)��RSA����+zlibѹ��
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("���ڼ�����..."));
			char RSA_Coded_path_name[100];
			char RSA_Coded_path_name_temp[100];
			char Zlib_Compress_path_name[100];
			char Origin_file_name[100];
			char Flag_path_name[100];
			printf("���ڼ�����...\n");
			MyCreatDirectory(_T(".\\Code_And_Decode_Cache"));//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//��·���л�ȡ�ļ���
			sprintf(RSA_Coded_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(RSA_Coded_path_name,MyAddFileName(RSA_Coded_path_name_temp,"(�������ʱ�ļ�1)"));
			strcpy(Zlib_Compress_path_name,MyAddFileName(RSA_Coded_path_name_temp,"(�������ʱ�ļ�2)"));
			strcpy(Flag_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(�Ѽ���)"));
			RSA_File_Code(MyCStringToConstChar(EditChoosePath),RSA_Coded_path_name,133,29213);//RSA�㷨���� e=133 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			Zlib_File_Compress(RSA_Coded_path_name,Zlib_Compress_path_name);//zlib�㷨ѹ��
			WriteFlag_Three_ASC(Zlib_Compress_path_name,Flag_path_name,'R','z','C');//RSA+zlib+Code
			DeleteFile(MyCharToLPCTSTR(RSA_Coded_path_name));//ɾ��RSA���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			DeleteFile(MyCharToLPCTSTR(Zlib_Compress_path_name));//ɾ��zlib��δд���ǵ���ʱ�ļ�
			RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
			SetDlgItemText(IDC_SMAINSTATE,_T("������ɣ�"));
			AfxMessageBox(_T("������ɣ�"),MB_OK,NULL);
		}
		else if(nIndex==1)//ģʽ��(���ļ��Ƽ�)��DES����+zlibѹ��
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("���ڼ�����..."));
			char DES_Coded_path_name[100];
			char DES_Coded_path_name_temp[100];
			char Zlib_Compress_path_name[100];
			char Origin_file_name[100];
			char Flag_path_name[100];
			printf("���ڼ�����...\n");
			MyCreatDirectory(_T(".\\Code_And_Decode_Cache"));//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//��·���л�ȡ�ļ���
			sprintf(DES_Coded_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(DES_Coded_path_name,MyAddFileName(DES_Coded_path_name_temp,"(�������ʱ�ļ�1)"));
			strcpy(Zlib_Compress_path_name,MyAddFileName(DES_Coded_path_name_temp,"(�������ʱ�ļ�2)"));
			strcpy(Flag_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(�Ѽ���)"));
			const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			des_code_forallfile(MyCStringToConstChar(EditChoosePath),(const unsigned char*)DES_Key,strlen(DES_Key),DES_Coded_path_name);//DES�㷨����
			Zlib_File_Compress(DES_Coded_path_name,Zlib_Compress_path_name);//zlib�㷨ѹ��
			WriteFlag_Three_ASC(Zlib_Compress_path_name,Flag_path_name,'D','z','C');//DES+zlib+Code
			DeleteFile(MyCharToLPCTSTR(DES_Coded_path_name));//ɾ��DES���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			DeleteFile(MyCharToLPCTSTR(Zlib_Compress_path_name));//ɾ��zlib��δд���ǵ���ʱ�ļ�
			RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
			SetDlgItemText(IDC_SMAINSTATE,_T("������ɣ�"));
			AfxMessageBox(_T("������ɣ�"),MB_OK,NULL);
		}
		else//����ģʽѡ������
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("����ģʽѡ������"));
			AfxMessageBox(_T("����ģʽѡ������"),MB_OK,NULL);
		    return;
		}
	}
	else if(CodeOrDecode==1)//����
	{
		errno_t err_read;
		FILE *fp_read = NULL;
	    err_read = fopen_s(&fp_read, MyCStringToConstChar(EditChoosePath), "rb");
	    if (err_read != 0)
	    {
			SetDlgItemText(IDC_SMAINSTATE,_T("�������ļ���ʧ��"));
			AfxMessageBox(_T("�������ļ���ʧ��"),MB_OK,NULL);
		    return;//�ļ���ʧ��
	    }
		fclose(fp_read);

		int nIndex = CBModeControl.GetCurSel();
		if(nIndex==0)//(�Զ�ƥ��ģʽ)���Զ�ƥ��ģʽ
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("���ڽ�����..."));
			char Zlib_Uncompress_path_name[100];
			char Zlib_Uncompress_path_name_temp[100];
			char RSAOrDES_Decoded_path_name[100];
			char Origin_file_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\Code_And_Decode_Cache");//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//��·���л�ȡ�ļ���
			sprintf(Zlib_Uncompress_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(NoFLag_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(�������ʱ�ļ�1)"));
			strcpy(Zlib_Uncompress_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(�������ʱ�ļ�2)"));
			strcpy(RSAOrDES_Decoded_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(�ѽ���)"));
			int flag_1=CheckFlag_Three_ASC(MyCStringToConstChar(EditChoosePath),NoFLag_path_name,'R','z','C');//RSA+zlib+Code
			if(flag_1==1)
			{
				Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib�㷨��ѹ��
			    RSA_File_Decode(Zlib_Uncompress_path_name,RSAOrDES_Decoded_path_name,217,29213);//RSA�㷨���� d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			    DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//ɾ��ȥ����־��δ����RSA���ܵ���ʱ�ļ�
			    DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//ɾ��RSA���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			    RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
			    SetDlgItemText(IDC_SMAINSTATE,_T("������ɣ�"));
			    AfxMessageBox(_T("������ɣ�"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-2)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("�޷��򿪴������ļ�������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷��򿪴������ļ�������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-3)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-1)
			{
				int flag_2=CheckFlag_Three_ASC(MyCStringToConstChar(EditChoosePath),NoFLag_path_name,'D','z','C');//DES+zlib+Code
			    if(flag_2==-2)
			    {
					RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				    SetDlgItemText(IDC_SMAINSTATE,_T("�޷��򿪴������ļ�������ʧ�ܣ�"));
			        AfxMessageBox(_T("�޷��򿪴������ļ�������ʧ�ܣ�"),MB_OK,NULL);
				    return;
			    }
			    else if(flag_2==-3)
			    {
					RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				    SetDlgItemText(IDC_SMAINSTATE,_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"));
			        AfxMessageBox(_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"),MB_OK,NULL);
				    return;
			    }
				else if(flag_2==-1)
			    {
					RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				    SetDlgItemText(IDC_SMAINSTATE,_T("�������ļ������ɴ˳����ģʽһ��ģʽ�����ܵģ�����ʧ�ܣ�"));
			        AfxMessageBox(_T("�������ļ������ɴ˳����ģʽһ��ģʽ�����ܵģ�����ʧ�ܣ�"),MB_OK,NULL);
				    return;
			    }
			    Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib�㷨��ѹ��
			    const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			    des_decode_forallfile(Zlib_Uncompress_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),RSAOrDES_Decoded_path_name);//DES�㷨����
			    DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//ɾ��ȥ����־��δ����DES���ܵ���ʱ�ļ�
			    DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//ɾ��DES���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			    RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
			    SetDlgItemText(IDC_SMAINSTATE,_T("������ɣ�"));
			    AfxMessageBox(_T("������ɣ�"),MB_OK,NULL);
			    }
		}
		else if(nIndex==1)//ģʽһ��RSA����+zlib��ѹ��
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("���ڽ�����..."));
			char Zlib_Uncompress_path_name[100];
			char Zlib_Uncompress_path_name_temp[100];
			char RSA_Decoded_path_name[100];
			char Origin_file_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\Code_And_Decode_Cache");//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//��·���л�ȡ�ļ���
			sprintf(Zlib_Uncompress_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(NoFLag_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(�������ʱ�ļ�1)"));
			strcpy(Zlib_Uncompress_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(�������ʱ�ļ�2)"));
			strcpy(RSA_Decoded_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(�ѽ���)"));
			int flag=CheckFlag_Three_ASC(MyCStringToConstChar(EditChoosePath),NoFLag_path_name,'R','z','C');//RSA+zlib+Code
			if(flag==-1)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("�������ļ������ɴ˳����ģʽһ���ܵģ�����ʧ�ܣ�"));
			    AfxMessageBox(_T("�������ļ������ɴ˳����ģʽһ���ܵģ�����ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag==-2)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("�޷��򿪴������ļ�������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷��򿪴������ļ�������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag==-3)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib�㷨��ѹ��
			RSA_File_Decode(Zlib_Uncompress_path_name,RSA_Decoded_path_name,217,29213);//RSA�㷨���� d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//ɾ��ȥ����־��δ����RSA���ܵ���ʱ�ļ�
			DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//ɾ��RSA���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
			SetDlgItemText(IDC_SMAINSTATE,_T("������ɣ�"));
			AfxMessageBox(_T("������ɣ�"),MB_OK,NULL);
		}
		else if(nIndex==2)//ģʽ����DES����+zlib��ѹ��
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("���ڽ�����..."));
			char Zlib_Uncompress_path_name[100];
			char Zlib_Uncompress_path_name_temp[100];
			char DES_Decoded_path_name[100];
			char Origin_file_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\Code_And_Decode_Cache");//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//��·���л�ȡ�ļ���
			sprintf(Zlib_Uncompress_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(NoFLag_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(�������ʱ�ļ�1)"));
			strcpy(Zlib_Uncompress_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(�������ʱ�ļ�2)"));
			strcpy(DES_Decoded_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(�ѽ���)"));
			int flag=CheckFlag_Three_ASC(MyCStringToConstChar(EditChoosePath),NoFLag_path_name,'D','z','C');//DES+zlib+Code
			if(flag==-1)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("�������ļ������ɴ˳����ģʽ�����ܵģ�����ʧ�ܣ�"));
			    AfxMessageBox(_T("�������ļ������ɴ˳����ģʽ�����ܵģ�����ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag==-2)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("�޷��򿪴������ļ�������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷��򿪴������ļ�������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			else if(flag==-3)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"));
			    AfxMessageBox(_T("�޷�д���ѽ����ļ�������ʧ�ܣ�"),MB_OK,NULL);
				return;
			}
			Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib�㷨��ѹ��
			const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			des_decode_forallfile(Zlib_Uncompress_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),DES_Decoded_path_name);//DES�㷨����
			DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//ɾ��ȥ����־��δ����DES���ܵ���ʱ�ļ�
			DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//ɾ��DES���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
			RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//ɾ����������ʱ�ļ���Code_And_Decode_Cache
			SetDlgItemText(IDC_SMAINSTATE,_T("������ɣ�"));
			AfxMessageBox(_T("������ɣ�"),MB_OK,NULL);
		}
		else//����ģʽѡ������
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("����ģʽѡ������"));
			AfxMessageBox(_T("����ģʽѡ������"),MB_OK,NULL);
		    return;
		}
	}
	else//���ܽ���ѡ��ѡ������
	{
		SetDlgItemText(IDC_SMAINSTATE,_T("���ܽ���ѡ��ѡ������"));
		AfxMessageBox(_T("���ܽ���ѡ��ѡ������"),MB_OK,NULL);
	}
}


void CDlg2::OnBnClickedBmainexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CDlg2::OnEnChangeEfilepath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}
