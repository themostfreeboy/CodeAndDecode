// Dlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "Code_And_Decode.h"
#include "Dlg2.h"
#include "afxdialogex.h"


// CDlg2 对话框

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


// CDlg2 消息处理程序


void CDlg2::OnBnClickedRcode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(CodeOrDecode==0)//加密
	{
		CBModeControl.ResetContent();
		CBModeControl.AddString(_T("模式一(小文件推荐)"));//RSA加密+zlib压缩
		CBModeControl.AddString(_T("模式二(大文件推荐)"));//DES加密+zlib压缩
		CBModeControl.SetCurSel(0);//设置第0项为显示的内容
		SetDlgItemText(IDC_BSTART,_T("开始加密"));
	}
	else if(CodeOrDecode==1)//解密
	{
		CBModeControl.ResetContent();
		CBModeControl.AddString(_T("(自动匹配模式)"));//自动匹配模式
		CBModeControl.AddString(_T("模式一"));//RSA解密+zlib解压缩
		CBModeControl.AddString(_T("模式二"));//DES解密+zlib解压缩
		CBModeControl.SetCurSel(0);//设置第0项为显示的内容
		SetDlgItemText(IDC_BSTART,_T("开始解密"));
	}
}


BOOL CDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_CBMODE);
	pBox->ResetContent();
	pBox->AddString(_T("模式一(小文件推荐)"));//RSA加密+zlib压缩
	pBox->AddString(_T("模式二(大文件推荐)"));//DES加密+7z压缩
	pBox->SetCurSel(0);//设置第0项为显示的内容
	SetDlgItemText(IDC_BSTART,_T("开始加密"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlg2::OnBnClickedBchoosefile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString szPath = _T("");

	//CFileDialog::CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL);
    //参数意义如下：
    //bOpenFileDialog：为TRUE则显示打开对话框，为FALSE则显示保存对话文件对话框。 
    //lpszDefExt：指定默认的文件扩展名。 
    //lpszFileName：指定默认的文件名。 
    //dwFlags：指明一些特定风格。 
    //lpszFilter：是最重要的一个参数，它指明可供选择的文件类型和相应的扩展名。

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
        //AfxMessageBox(_T("无效的文件，请重新选择"),MB_OK,NULL);
	}
}


void CDlg2::OnBnClickedBstart()
{
	// TODO: 在此添加控件通知处理程序代码
	if(EditChoosePath.IsEmpty())
	{
		SetDlgItemText(IDC_SMAINSTATE,_T("文件路径不能为空"));
		AfxMessageBox(_T("文件路径不能为空"),MB_OK,NULL);
		return;
	}
	if(CodeOrDecode==0)//加密
	{
		errno_t err_read;
		FILE *fp_read = NULL;
	    err_read = fopen_s(&fp_read, MyCStringToConstChar(EditChoosePath), "rb");
	    if (err_read != 0)//文件打开失败
	    {
			SetDlgItemText(IDC_SMAINSTATE,_T("待加密文件打开失败"));
			AfxMessageBox(_T("待加密文件打开失败"),MB_OK,NULL);
		    return;
	    }
		fclose(fp_read);

		int nIndex = CBModeControl.GetCurSel();
		if(nIndex==0)//模式一(小文件推荐)：RSA加密+zlib压缩
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("正在加密中..."));
			char RSA_Coded_path_name[100];
			char RSA_Coded_path_name_temp[100];
			char Zlib_Compress_path_name[100];
			char Origin_file_name[100];
			char Flag_path_name[100];
			printf("正在加密中...\n");
			MyCreatDirectory(_T(".\\Code_And_Decode_Cache"));//在当前目录下新建一个临时文件夹Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//从路径中获取文件名
			sprintf(RSA_Coded_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(RSA_Coded_path_name,MyAddFileName(RSA_Coded_path_name_temp,"(半加密临时文件1)"));
			strcpy(Zlib_Compress_path_name,MyAddFileName(RSA_Coded_path_name_temp,"(半加密临时文件2)"));
			strcpy(Flag_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(已加密)"));
			RSA_File_Code(MyCStringToConstChar(EditChoosePath),RSA_Coded_path_name,133,29213);//RSA算法加密 e=133 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			Zlib_File_Compress(RSA_Coded_path_name,Zlib_Compress_path_name);//zlib算法压缩
			WriteFlag_Three_ASC(Zlib_Compress_path_name,Flag_path_name,'R','z','C');//RSA+zlib+Code
			DeleteFile(MyCharToLPCTSTR(RSA_Coded_path_name));//删除RSA加密后但未进行zlib压缩时产生的临时文件
			DeleteFile(MyCharToLPCTSTR(Zlib_Compress_path_name));//删除zlib后但未写入标记的临时文件
			RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
			SetDlgItemText(IDC_SMAINSTATE,_T("加密完成！"));
			AfxMessageBox(_T("加密完成！"),MB_OK,NULL);
		}
		else if(nIndex==1)//模式二(大文件推荐)：DES加密+zlib压缩
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("正在加密中..."));
			char DES_Coded_path_name[100];
			char DES_Coded_path_name_temp[100];
			char Zlib_Compress_path_name[100];
			char Origin_file_name[100];
			char Flag_path_name[100];
			printf("正在加密中...\n");
			MyCreatDirectory(_T(".\\Code_And_Decode_Cache"));//在当前目录下新建一个临时文件夹Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//从路径中获取文件名
			sprintf(DES_Coded_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(DES_Coded_path_name,MyAddFileName(DES_Coded_path_name_temp,"(半加密临时文件1)"));
			strcpy(Zlib_Compress_path_name,MyAddFileName(DES_Coded_path_name_temp,"(半加密临时文件2)"));
			strcpy(Flag_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(已加密)"));
			const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			des_code_forallfile(MyCStringToConstChar(EditChoosePath),(const unsigned char*)DES_Key,strlen(DES_Key),DES_Coded_path_name);//DES算法加密
			Zlib_File_Compress(DES_Coded_path_name,Zlib_Compress_path_name);//zlib算法压缩
			WriteFlag_Three_ASC(Zlib_Compress_path_name,Flag_path_name,'D','z','C');//DES+zlib+Code
			DeleteFile(MyCharToLPCTSTR(DES_Coded_path_name));//删除DES加密后但未进行zlib压缩时产生的临时文件
			DeleteFile(MyCharToLPCTSTR(Zlib_Compress_path_name));//删除zlib后但未写入标记的临时文件
			RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
			SetDlgItemText(IDC_SMAINSTATE,_T("加密完成！"));
			AfxMessageBox(_T("加密完成！"),MB_OK,NULL);
		}
		else//加密模式选择有误
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("加密模式选择有误"));
			AfxMessageBox(_T("加密模式选择有误"),MB_OK,NULL);
		    return;
		}
	}
	else if(CodeOrDecode==1)//解密
	{
		errno_t err_read;
		FILE *fp_read = NULL;
	    err_read = fopen_s(&fp_read, MyCStringToConstChar(EditChoosePath), "rb");
	    if (err_read != 0)
	    {
			SetDlgItemText(IDC_SMAINSTATE,_T("待解密文件打开失败"));
			AfxMessageBox(_T("待解密文件打开失败"),MB_OK,NULL);
		    return;//文件打开失败
	    }
		fclose(fp_read);

		int nIndex = CBModeControl.GetCurSel();
		if(nIndex==0)//(自动匹配模式)：自动匹配模式
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("正在解密中..."));
			char Zlib_Uncompress_path_name[100];
			char Zlib_Uncompress_path_name_temp[100];
			char RSAOrDES_Decoded_path_name[100];
			char Origin_file_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\Code_And_Decode_Cache");//在当前目录下新建一个临时文件夹Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//从路径中获取文件名
			sprintf(Zlib_Uncompress_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(NoFLag_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(半解密临时文件1)"));
			strcpy(Zlib_Uncompress_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(半解密临时文件2)"));
			strcpy(RSAOrDES_Decoded_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(已解密)"));
			int flag_1=CheckFlag_Three_ASC(MyCStringToConstChar(EditChoosePath),NoFLag_path_name,'R','z','C');//RSA+zlib+Code
			if(flag_1==1)
			{
				Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib算法解压缩
			    RSA_File_Decode(Zlib_Uncompress_path_name,RSAOrDES_Decoded_path_name,217,29213);//RSA算法解密 d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			    DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//删除去除标志后但未进行RSA解密的临时文件
			    DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//删除RSA解密后但未进行zlib压缩时产生的临时文件
			    RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
			    SetDlgItemText(IDC_SMAINSTATE,_T("解密完成！"));
			    AfxMessageBox(_T("解密完成！"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-2)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("无法打开待解密文件，解密失败！"));
			    AfxMessageBox(_T("无法打开待解密文件，解密失败！"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-3)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("无法写入已解密文件，解密失败！"));
			    AfxMessageBox(_T("无法写入已解密文件，解密失败！"),MB_OK,NULL);
				return;
			}
			else if(flag_1==-1)
			{
				int flag_2=CheckFlag_Three_ASC(MyCStringToConstChar(EditChoosePath),NoFLag_path_name,'D','z','C');//DES+zlib+Code
			    if(flag_2==-2)
			    {
					RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				    SetDlgItemText(IDC_SMAINSTATE,_T("无法打开待解密文件，解密失败！"));
			        AfxMessageBox(_T("无法打开待解密文件，解密失败！"),MB_OK,NULL);
				    return;
			    }
			    else if(flag_2==-3)
			    {
					RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				    SetDlgItemText(IDC_SMAINSTATE,_T("无法写入已解密文件，解密失败！"));
			        AfxMessageBox(_T("无法写入已解密文件，解密失败！"),MB_OK,NULL);
				    return;
			    }
				else if(flag_2==-1)
			    {
					RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				    SetDlgItemText(IDC_SMAINSTATE,_T("待解密文件不是由此程序的模式一或模式二加密的，解密失败！"));
			        AfxMessageBox(_T("待解密文件不是由此程序的模式一或模式二加密的，解密失败！"),MB_OK,NULL);
				    return;
			    }
			    Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib算法解压缩
			    const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			    des_decode_forallfile(Zlib_Uncompress_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),RSAOrDES_Decoded_path_name);//DES算法解密
			    DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//删除去除标志后但未进行DES解密的临时文件
			    DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//删除DES解密后但未进行zlib压缩时产生的临时文件
			    RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
			    SetDlgItemText(IDC_SMAINSTATE,_T("解密完成！"));
			    AfxMessageBox(_T("解密完成！"),MB_OK,NULL);
			    }
		}
		else if(nIndex==1)//模式一：RSA解密+zlib解压缩
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("正在解密中..."));
			char Zlib_Uncompress_path_name[100];
			char Zlib_Uncompress_path_name_temp[100];
			char RSA_Decoded_path_name[100];
			char Origin_file_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\Code_And_Decode_Cache");//在当前目录下新建一个临时文件夹Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//从路径中获取文件名
			sprintf(Zlib_Uncompress_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(NoFLag_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(半解密临时文件1)"));
			strcpy(Zlib_Uncompress_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(半解密临时文件2)"));
			strcpy(RSA_Decoded_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(已解密)"));
			int flag=CheckFlag_Three_ASC(MyCStringToConstChar(EditChoosePath),NoFLag_path_name,'R','z','C');//RSA+zlib+Code
			if(flag==-1)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("待解密文件不是由此程序的模式一加密的，解密失败！"));
			    AfxMessageBox(_T("待解密文件不是由此程序的模式一加密的，解密失败！"),MB_OK,NULL);
				return;
			}
			else if(flag==-2)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("无法打开待解密文件，解密失败！"));
			    AfxMessageBox(_T("无法打开待解密文件，解密失败！"),MB_OK,NULL);
				return;
			}
			else if(flag==-3)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("无法写入已解密文件，解密失败！"));
			    AfxMessageBox(_T("无法写入已解密文件，解密失败！"),MB_OK,NULL);
				return;
			}
			Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib算法解压缩
			RSA_File_Decode(Zlib_Uncompress_path_name,RSA_Decoded_path_name,217,29213);//RSA算法解密 d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
			DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//删除去除标志后但未进行RSA解密的临时文件
			DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//删除RSA解密后但未进行zlib压缩时产生的临时文件
			RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
			SetDlgItemText(IDC_SMAINSTATE,_T("解密完成！"));
			AfxMessageBox(_T("解密完成！"),MB_OK,NULL);
		}
		else if(nIndex==2)//模式二：DES解密+zlib解压缩
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("正在解密中..."));
			char Zlib_Uncompress_path_name[100];
			char Zlib_Uncompress_path_name_temp[100];
			char DES_Decoded_path_name[100];
			char Origin_file_name[100];
			char NoFLag_path_name[100];
			MyCreatDirectory(".\\Code_And_Decode_Cache");//在当前目录下新建一个临时文件夹Code_And_Decode_Cache
			strcpy(Origin_file_name,MyGetFileName(MyCStringToConstChar(EditChoosePath)));//从路径中获取文件名
			sprintf(Zlib_Uncompress_path_name_temp,".\\Code_And_Decode_Cache\\%s",Origin_file_name);
			strcpy(NoFLag_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(半解密临时文件1)"));
			strcpy(Zlib_Uncompress_path_name,MyAddFileName(Zlib_Uncompress_path_name_temp,"(半解密临时文件2)"));
			strcpy(DES_Decoded_path_name,MyAddFileName(MyCStringToConstChar(EditChoosePath),"(已解密)"));
			int flag=CheckFlag_Three_ASC(MyCStringToConstChar(EditChoosePath),NoFLag_path_name,'D','z','C');//DES+zlib+Code
			if(flag==-1)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("待解密文件不是由此程序的模式二加密的，解密失败！"));
			    AfxMessageBox(_T("待解密文件不是由此程序的模式二加密的，解密失败！"),MB_OK,NULL);
				return;
			}
			else if(flag==-2)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("无法打开待解密文件，解密失败！"));
			    AfxMessageBox(_T("无法打开待解密文件，解密失败！"),MB_OK,NULL);
				return;
			}
			else if(flag==-3)
			{
				RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
				SetDlgItemText(IDC_SMAINSTATE,_T("无法写入已解密文件，解密失败！"));
			    AfxMessageBox(_T("无法写入已解密文件，解密失败！"),MB_OK,NULL);
				return;
			}
			Zlib_File_Uncompress(NoFLag_path_name,Zlib_Uncompress_path_name);//zlib算法解压缩
			const char DES_Key[]="abcdefghijklmnopqrstuvwxyz";
			des_decode_forallfile(Zlib_Uncompress_path_name,(const unsigned char*)DES_Key,strlen(DES_Key),DES_Decoded_path_name);//DES算法解密
			DeleteFile(MyCharToLPCTSTR(NoFLag_path_name));//删除去除标志后但未进行DES解密的临时文件
			DeleteFile(MyCharToLPCTSTR(Zlib_Uncompress_path_name));//删除DES解密后但未进行zlib压缩时产生的临时文件
			RemoveDirectory(_T(".\\Code_And_Decode_Cache"));//删除产生的临时文件夹Code_And_Decode_Cache
			SetDlgItemText(IDC_SMAINSTATE,_T("解密完成！"));
			AfxMessageBox(_T("解密完成！"),MB_OK,NULL);
		}
		else//加密模式选择有误
		{
			SetDlgItemText(IDC_SMAINSTATE,_T("加密模式选择有误"));
			AfxMessageBox(_T("加密模式选择有误"),MB_OK,NULL);
		    return;
		}
	}
	else//加密解密选项选择有误
	{
		SetDlgItemText(IDC_SMAINSTATE,_T("加密解密选项选择有误"));
		AfxMessageBox(_T("加密解密选项选择有误"),MB_OK,NULL);
	}
}


void CDlg2::OnBnClickedBmainexit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CDlg2::OnEnChangeEfilepath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}
