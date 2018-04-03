#include "flag.h"

#include "stdafx.h"

int WriteFlag_One_ASC(const char* readfilename, const char* writefilename, char char_1)//写入一个ASC2编码字符的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	fprintf(fp_write,"%c",char_1);

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志写入成功
}

int CheckFlag_One_ASC(const char* readfilename, const char* writefilename, char char_1)//校检一个ASC2编码字符的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	char tempchar_1;
	fscanf(fp_read,"%c",&tempchar_1);

	if(tempchar_1!=char_1)
	{
		fclose(fp_read);
		return -1;//标志校检失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志校检成功
}

int WriteFlag_One_Int(const char* readfilename, const char* writefilename, int int_1)//写入一个整数的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	fprintf(fp_write,"%c",(int_1)&(0xff));

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志写入成功
}

int CheckFlag_One_Int(const char* readfilename, const char* writefilename, int int_1)//校检一个整数的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	char tempInt_1;
	fscanf(fp_read,"%c",&tempInt_1);

	if(tempInt_1!=(int_1&(0xff)))
	{
		fclose(fp_read);
		return -1;//标志校检失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志校检成功
}

int WriteFlag_Two_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2)//写入两个ASC2编码字符的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	fprintf(fp_write,"%c",char_1);
	fprintf(fp_write,"%c",char_2);

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志写入成功
}

int CheckFlag_Two_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2)//校检两个ASC2编码字符的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	char tempchar_1,tempchar_2;
	fscanf(fp_read,"%c%c",&tempchar_1,&tempchar_2);

	if(tempchar_1!=char_1 || tempchar_2!=char_2)
	{
		fclose(fp_read);
		return -1;//标志校检失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志校检成功
}

int WriteFlag_Two_Int(const char* readfilename, const char* writefilename, int int_1, int int_2)//写入两个整数的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	fprintf(fp_write,"%c",(int_1)&(0xff));
	fprintf(fp_write,"%c",(int_2)&(0xff));

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志写入成功
}

int CheckFlag_Two_Int(const char* readfilename, const char* writefilename, int int_1, int int_2)//校检两个整数的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	char tempInt_1,tempInt_2;
	fscanf(fp_read,"%c%c",&tempInt_1,&tempInt_2);

	if(tempInt_1!=(int_1&(0xff)) || tempInt_2!=(int_2&(0xff)))
	{
		fclose(fp_read);
		return -1;//标志校检失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志校检成功
}

int WriteFlag_Three_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2, char char_3)//写入三个ASC2编码字符的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	fprintf(fp_write,"%c",char_1);
	fprintf(fp_write,"%c",char_2);
	fprintf(fp_write,"%c",char_3);

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志写入成功
}

int CheckFlag_Three_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2, char char_3)//校检三个ASC2编码字符的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	char tempchar_1,tempchar_2,tempchar_3;
	fscanf(fp_read,"%c%c%c",&tempchar_1,&tempchar_2,&tempchar_3);

	if(tempchar_1!=char_1 || tempchar_2!=char_2 || tempchar_3!=char_3)
	{
		fclose(fp_read);
		return -1;//标志校检失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志校检成功
}

int WriteFlag_Three_Int(const char* readfilename, const char* writefilename, int int_1, int int_2, int int_3)//写入三个整数的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	fprintf(fp_write,"%c",(int_1)&(0xff));
	fprintf(fp_write,"%c",(int_2)&(0xff));
	fprintf(fp_write,"%c",(int_3)&(0xff));

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志写入成功
}

int CheckFlag_Three_Int(const char* readfilename, const char* writefilename, int int_1, int int_2, int int_3)//校检三个整数的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	char tempInt_1,tempInt_2,tempInt_3;
	fscanf(fp_read,"%c%c%c",&tempInt_1,&tempInt_2,&tempInt_3);

	if(tempInt_1!=(int_1&(0xff)) || tempInt_2!=(int_2&(0xff)) || tempInt_3!=(int_3&(0xff)))
	{
		fclose(fp_read);
		return -1;//标志校检失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志校检成功
}

int WriteFlag_Multi_ASC(const char* readfilename, const char* writefilename, int number, const char char_Multi[])//写入number个ASC2编码字符的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	for(int i=0;i<number;i++)
	{
		fprintf(fp_write,"%c",char_Multi[i]);
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志写入成功
}

int CheckFlag_Multi_ASC(const char* readfilename, const char* writefilename, int number, const char char_Multi[])//校检number个ASC2编码字符的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	char tempchar_Multi;
	for(int i=0;i<number;i++)
	{
		fscanf(fp_read,"%c",&tempchar_Multi);
		if(tempchar_Multi!=char_Multi[i])
	    {
		    fclose(fp_read);
		    return -1;//标志校检失败
	    }
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志校检成功
}

int WriteFlag_Multi_Int(const char* readfilename, const char* writefilename, int number, int int_Multi[])//写入number个整数的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	for(int i=0;i<number;i++)
	{
		fprintf(fp_write,"%c",(int_Multi[i])&(0xff));
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志写入成功
}

int CheckFlag_Multi_Int(const char* readfilename, const char* writefilename, int number, int int_Multi[])//校检number个整数的标志
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;

	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -2;//readfilename文件打开失败
	}

	char tempInt_Multi;
	for(int i=0;i<number;i++)
	{
		fscanf(fp_read,"%c",&tempInt_Multi);
		if(tempInt_Multi!=int_Multi[i])
	    {
		    fclose(fp_read);
		    return -1;//标志校检失败
	    }
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -3;//writefilename文件打开失败
	}

	char tempchar;
	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//标志校检成功
}