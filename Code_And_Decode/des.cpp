#include "des.h"

#include "stdafx.h"

/*-------------------------------
 把DatIn开始的长度位Len位的二进制
 复制到DatOut后
--------------------------------*/
void BitsCopy(bool *DatOut,bool *DatIn,int Len)//数组复制 OK 
{
	int i=0;
	for(i=0;i<Len;i++)
	{
		DatOut[i]=DatIn[i];
	}
}

/*-------------------------------
 字节转换成位函数 
 每8次换一个字节 每次向右移一位
 和1与取最后一位 共64位 
--------------------------------*/
void ByteToBit(bool *DatOut,const unsigned char *DatIn,int Num)//OK
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatOut[i]=(DatIn[i/8]>>(i%8))&0x01;   
	}                                       
}

/*-------------------------------
 位转换成字节函数
 字节数组每8次移一位
 位每次向左移 与上一次或   
---------------------------------*/
void BitToByte(unsigned char *DatOut,const bool *DatIn,int Num)//OK
{
	int i=0;
	for(i=0;i<(Num/8);i++)
	{
		DatOut[i]=0;
	} 
	for(i=0;i<Num;i++)
	{
		DatOut[i/8]|=DatIn[i]<<(i%8);	
	}		
}


/*----------------------------------
 二进制密文转换为十六进制
 需要8个字符表示
-----------------------------------*/
void BitToHex(unsigned char *DatOut,const bool *DatIn,int Num)
{
	int i=0;
	for(i=0;i<Num/8;i++)
	{
		DatOut[i]=0;
	}
	for(i=0;i<Num/8;i++)
	{
		DatOut[i] = DatIn[i*8]+(DatIn[i*8+1]<<1)+(DatIn[i*8+2]<<2)+(DatIn[i*8+3]<<3)+(DatIn[i*8+4]<<4)+(DatIn[i*8+5]<<5)+(DatIn[i*8+6]<<6)+(DatIn[i*8+7]<<7);
	}
}

/*---------------------------------------------
 十六进制字符转二进制
----------------------------------------------*/
void HexToBit(bool *DatOut,const unsigned char *DatIn,int Num)
{
	int i=0; 
	for(i=0;i<Num;i++)
	{
		DatOut[i]=((DatIn[i/8])>>(i%8))&0x01;   			
	}	
}

//表置换函数  OK
void TablePermute(bool *DatOut,const bool *DatIn,const unsigned char *Table,int Num)  
{
	int i=0;
	bool Temp[256]={0};
	for(i=0;i<Num;i++)//Num为置换的长度 
	{
		Temp[i]=DatIn[Table[i]-1];//原来的数据按对应的表上的位置排列 
	}
	BitsCopy(DatOut,Temp,Num);//把缓存Temp的值输出 
} 

//子密钥的移位
void LoopMove(bool *DatIn,int Len,int Num)//循环左移 Len数据长度 Num移动位数
{
	bool Temp[256]={0};//缓存   OK
	BitsCopy(Temp,DatIn,Num);//将数据最左边的Num位(被移出去的)存入Temp 
	BitsCopy(DatIn,DatIn+Num,Len-Num);//将数据左边开始的第Num移入原来的空间
	BitsCopy(DatIn+Len-Num,Temp,Num); //将缓存中移出去的数据加到最右边 
} 

//按位异或
void Xor(bool *DatA,const bool *DatB,int Num)//异或函数
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatA[i]=DatA[i]^DatB[i];//异或 
	}
} 

//输入48位 输出32位 与Ri异或
void S_Change(bool DatOut[32],const bool DatIn[48])//S盒变换
{
	int i,X,Y;//i为8个S盒 
	for(i=0,Y=0,X=0;i<8;i++,DatIn+=6,DatOut+=4)//每执行一次,输入数据偏移6位 
	{    									   //每执行一次,输出数据偏移4位
		Y=(DatIn[0]<<1)+DatIn[5];//af代表第几行
		X=(DatIn[1]<<3)+(DatIn[2]<<2)+(DatIn[3]<<1)+DatIn[4];//bcde代表第几列
		ByteToBit(DatOut,&S_Box[i][Y][X],4);//把找到的点数据换为二进制	
	}
}

//F函数
void F_Change(bool DatIn[32],const bool DatKi[48])//F函数
{
	bool MiR[48]={0};//输入32位通过E选位变为48位
	TablePermute(MiR,DatIn,E_Table,48); 
	Xor(MiR,DatKi,48);//和子密钥异或
	S_Change(DatIn,MiR);//S盒变换
	TablePermute(DatIn,DatIn,P_Table,32);//P置换后输出
}

void SetKey(unsigned char KeyIn[8],bool SubKey[16][48])//设置密钥 获取子密钥Ki 
{
	int i=0;
	bool KeyBit[64]={0};//密钥二进制存储空间 
	bool *KiL=&KeyBit[0],*KiR=&KeyBit[28];//前28,后28共56
	ByteToBit(KeyBit,KeyIn,64);//把密钥转为二进制存入KeyBit 
	TablePermute(KeyBit,KeyBit,PC1_Table,56);//PC1表置换 56次
	for(i=0;i<16;i++)
	{
		LoopMove(KiL,28,Move_Table[i]);//前28位左移 
		LoopMove(KiR,28,Move_Table[i]);//后28位左移 
	 	TablePermute(SubKey[i],KeyBit,PC2_Table,48); 
	 	//二维数组 SubKey[i]为每一行起始地址 
	 	//每移一次位进行PC2置换得 Ki 48位 
	}		
}

void PlayDes(unsigned char MesOut[8],const unsigned char MesIn[8],bool SubKey[16][48])//执行DES加密
{                                           //字节输入 Bin运算 Hex输出 
	int i=0;
	bool MesBit[64]={0};//明文二进制存储空间 64位
	bool Temp[32]={0};
	bool *MiL=&MesBit[0],*MiR=&MesBit[32];//前32位 后32位 
	ByteToBit(MesBit,MesIn,64);//把明文换成二进制存入MesBit
	TablePermute(MesBit,MesBit,IP_Table,64);//IP置换 
	for(i=0;i<16;i++)//迭代16次 
	{
		BitsCopy(Temp,MiR,32);//临时存储
		F_Change(MiR,SubKey[i]);//F函数变换
		Xor(MiR,MiL,32);//得到Ri 
		BitsCopy(MiL,Temp,32);//得到Li 
	}					
	TablePermute(MesBit,MesBit,IPR_Table,64);
	BitToHex(MesOut,MesBit,64);
}

void KickDes(unsigned char MesOut[8],const unsigned char MesIn[8], bool SubKey[16][48])//执行DES解密
{												//Hex输入 Bin运算 字节输出 
	int i=0;
	bool MesBit[64]={0};//密文二进制存储空间 64位
	bool Temp[32]={0};
	bool *MiL=&MesBit[0],*MiR=&MesBit[32];//前32位 后32位
	HexToBit(MesBit,MesIn,64);//把密文换成二进制存入MesBit
	TablePermute(MesBit,MesBit,IP_Table,64);//IP置换 
	for(i=15;i>=0;i--)
	{
		BitsCopy(Temp,MiL,32);
		F_Change(MiL,SubKey[i]);
		Xor(MiL,MiR,32);
		BitsCopy(MiR,Temp,32);
	}	
	TablePermute(MesBit,MesBit,IPR_Table,64);
	BitToByte(MesOut,MesBit,64);		
}

void des_code_for64bit(const unsigned char origin_message[8], const unsigned char key[8], unsigned char coded_message[8])//des算法加密(消息与密匙均需64位)
{
	unsigned char set_key[8];
	for(int i=0;i<8;i++)
	{
		set_key[i]=key[i];
	}

    bool SubKey[16][48]={0};//16个子密钥K(1~16)
	SetKey(set_key,SubKey);//设置密钥 得到子密钥Ki
	PlayDes(coded_message,origin_message,SubKey);//执行DES加密
}

void des_decode_for64bit(const unsigned char origin_message[8], const unsigned char key[8], unsigned char decoded_message[8])//des算法解密(消息与密匙均需64位)
{
	unsigned char set_key[8];
	for(int i=0;i<8;i++)
	{
		set_key[i]=key[i];
	}

	bool SubKey[16][48]={0};//16个子密钥K(1~16)
	SetKey(set_key,SubKey);//设置密钥
	KickDes(decoded_message,origin_message,SubKey);//解密输出到decoded_message
}

void des_print(const unsigned char* message, int length)//以16进制形式显示加密后或解密后的信息
{
	printf("des:");
	for (int i = 0; i < length; i++)
	{
		printf("%02x ", message[i]);
	}
	printf("\n");
}

int des_code_foralldata(const unsigned char* origin_message, long origin_message_length, const unsigned char* key, long key_length, unsigned char* coded_message, long* coded_message_length)//des算法加密(对所有长度数据消息)
{
	//对原消息进行不足字符填充
	*coded_message_length=(origin_message_length/8+1)*8;
	unsigned char origin_message_new[1000];
	for(int i=0;i<origin_message_length;i++)
	{
		origin_message_new[i]=origin_message[i];
	}
	for(int i=origin_message_length;i<*coded_message_length;i++)//不足字符填充
	{
		origin_message_new[i]=*coded_message_length-origin_message_length;
	}

	//转化key至64位(8 byte)
	unsigned char key_md5[16];
	unsigned char key_new[8];
	MD5Calc((unsigned char*)key,key_md5,key_length);//计算原key的md5转化为128位(16 byte)
	for(int i=0;i<8;i++)//进一步转化key至64位(8 byte)
	{
		key_new[i]=(key_md5[2*i]+key_md5[2*i+1])%256;
	}

	//进行des算法加密
	for(int i=0;i<*coded_message_length/8;i++)
	{
		des_code_for64bit((const unsigned char*)&(origin_message_new[8*i]),(const unsigned char*)key_new,&(coded_message[8*i]));
	}
	return 1;//加密成功
}

int des_decode_foralldata(const unsigned char* origin_message, long origin_message_length, const unsigned char* key, long key_length, unsigned char* decoded_message, long* decoded_message_length)//des算法解密(对所有长度数据消息)
{
	//转化key至64位(8 byte)
	unsigned char key_md5[16];
	unsigned char key_new[8];
	MD5Calc((unsigned char*)key,key_md5,key_length);//计算原key的md5转化为128位(16 byte)
	for(int i=0;i<8;i++)//进一步转化key至64位(8 byte)
	{
		key_new[i]=(key_md5[2*i]+key_md5[2*i+1])%256;
	}

	if (origin_message_length%8!=0)//待解密数据错误
	{
		return -1;//待解密数据错误
	}

	//定义部分变量
	unsigned char decoded_message_temp[1000];

	//进行des算法解密
	for(int i=0;i<origin_message_length/8;i++)
	{
		des_decode_for64bit((const unsigned char*)&(origin_message[8*i]),(const unsigned char*)key_new,&(decoded_message_temp[8*i]));
	}
	
	//去掉加密时的填充字符
	*decoded_message_length=origin_message_length-decoded_message_temp[origin_message_length-1];
	for(int i=0;i<*decoded_message_length;i++)
	{
		decoded_message[i]=decoded_message_temp[i];
	}
	return 1;//解密成功
}

int des_code_forallfile(const char* origin_filename, const unsigned char* key, long key_length, const char* coded_filename)//des算法加密(对所有大小文件内容)
{
	//检测origin_filename文件是否存在
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, origin_filename, "rb");
	if (err_read != 0)
	{
		return -1;//文件打开失败
	}
	fclose(fp_read);

	//origin_filename文件存在
	errno_t err_write;
	FILE *fp_write = NULL;

	//转化key至64位(8 byte)
	unsigned char key_md5[16];
	unsigned char key_new[8];
	MD5Calc((unsigned char*)key,key_md5,key_length);//计算原key的md5转化为128位(16 byte)
	for(int i=0;i<8;i++)//进一步转化key至64位(8 byte)
	{
		key_new[i]=(key_md5[2*i]+key_md5[2*i+1])%256;
	}

	long origin_filesize=des_MyGetFileSize(origin_filename);//获取原文件大小
	unsigned char temp_in[8];
	unsigned char temp_out[8];
	long read_time=origin_filesize/8+1;
	err_read = fopen_s(&fp_read, origin_filename, "rb");
	if (err_read != 0)
	{
		return -2;//文件打开失败
	}
	err_write = fopen_s(&fp_write, coded_filename, "wb");
	if (err_write != 0)
	{
		return -3;//文件打开失败
	}
	for(int i=0;i<read_time-1;i++)
	{
		for(int j=0;j<8;j++)
		{
			fscanf(fp_read,"%c",&(temp_in[j]));
		}
		des_code_for64bit(temp_in,key_new,temp_out);
		for(int j=0;j<8;j++)
		{
			fprintf(fp_write,"%c",temp_out[j]);
		}
	}	
	for(int i=0;i<origin_filesize%8;i++)
	{
		fscanf(fp_read,"%c",&(temp_in[i]));
	}
	for(int i=origin_filesize%8;i<8;i++)
	{
		temp_in[i]=8-origin_filesize%8;
	}
	des_code_for64bit(temp_in,key_new,temp_out);
	for(int i=0;i<8;i++)
	{
		fprintf(fp_write,"%c",temp_out[i]);
	}
	fclose(fp_read);
	fclose(fp_write);
	return 1;//加密成功
}

int des_decode_forallfile(const char* origin_filename, const unsigned char* key, long key_length, const char* decoded_filename)//des算法加解密(对所有大小文件内容)
{
	//检测origin_filename文件是否存在
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, origin_filename, "rb");
	if (err_read != 0)
	{
		return -1;//文件打开失败
	}
	fclose(fp_read);

	//origin_filename文件存在
	errno_t err_write;
	FILE *fp_write = NULL;

	//转化key至64位(8 byte)
	unsigned char key_md5[16];
	unsigned char key_new[8];
	MD5Calc((unsigned char*)key,key_md5,key_length);//计算原key的md5转化为128位(16 byte)
	for(int i=0;i<8;i++)//进一步转化key至64位(8 byte)
	{
		key_new[i]=(key_md5[2*i]+key_md5[2*i+1])%256;
	}

	long origin_filesize=des_MyGetFileSize(origin_filename);//获取原文件大小
	if(origin_filesize%8!=0)//待解密文件错误
	{
		return -2;//待解密文件错误
	}
	unsigned char temp_in[8];
	unsigned char temp_out[8];
	long read_time=origin_filesize/8;
	err_read = fopen_s(&fp_read, origin_filename, "rb");
	if (err_read != 0)
	{
		return -3;//文件打开失败
	}
	err_write = fopen_s(&fp_write, decoded_filename, "wb");
	if (err_write != 0)
	{
		return -4;//文件打开失败
	}
	for(int i=0;i<read_time-1;i++)
	{
		for(int j=0;j<8;j++)
		{
			fscanf(fp_read,"%c",&(temp_in[j]));
		}
		des_decode_for64bit(temp_in,key_new,temp_out);
		for(int j=0;j<8;j++)
		{
			fprintf(fp_write,"%c",temp_out[j]);
		}
	}
	for(int i=0;i<8;i++)
	{
		fscanf(fp_read,"%c",&(temp_in[i]));
	}
	des_decode_for64bit(temp_in,key_new,temp_out);
	for(int i=0;i<8-temp_out[7];i++)
	{
		fprintf(fp_write,"%c",temp_out[i]);
	}
	fclose(fp_read);
	fclose(fp_write);
	return 1;//解密成功
}

long des_MyGetFileSize(const char* filename)//获取文件大小，调用此函数时此文件必须处于未打开读写状态
{
	FILE *fp = NULL;
	errno_t err;
	err = fopen_s(&fp, filename, "rb");
	if (err != 0)
	{
		return -1;//文件打开失败
	}
    fseek(fp,0,SEEK_SET);
    fseek(fp,0,SEEK_END);
    long filesize=ftell(fp);
    rewind(fp);
	fclose(fp);
	return filesize;
}