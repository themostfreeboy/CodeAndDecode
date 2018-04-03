#pragma once

#ifndef __FLAG_H
#define __FLAG_H

#include <stdio.h>

/*
函数返回值说明：
1：写入标志或校检标志成功
-1：校检标志失败
-2：readfilename文件打开失败
-3：writefilename文件打开失败
*/

int WriteFlag_One_ASC(const char* readfilename, const char* writefilename, char char_1);//写入一个ASC2编码字符的标志
int CheckFlag_One_ASC(const char* readfilename, const char* writefilename, char char_1);//校检一个ASC2编码字符的标志
int WriteFlag_One_Int(const char* readfilename, const char* writefilename, int int_1);//写入一个整数的标志
int CheckFlag_One_Int(const char* readfilename, const char* writefilename, int int_1);//校检一个整数的标志

int WriteFlag_Two_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2);//写入两个ASC2编码字符的标志
int CheckFlag_Two_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2);//校检两个ASC2编码字符的标志
int WriteFlag_Two_Int(const char* readfilename, const char* writefilename, int int_1, int int_2);//写入两个整数的标志
int CheckFlag_Two_Int(const char* readfilename, const char* writefilename, int int_1, int int_2);//校检两个整数的标志

int WriteFlag_Three_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2, char char_3);//写入三个ASC2编码字符的标志
int CheckFlag_Three_ASC(const char* readfilename, const char* writefilename, char char_1, char char_2, char char_3);//校检三个ASC2编码字符的标志
int WriteFlag_Three_Int(const char* readfilename, const char* writefilename, int int_1, int int_2, int int_3);//写入三个整数的标志
int CheckFlag_Three_Int(const char* readfilename, const char* writefilename, int int_1, int int_2, int int_3);//校检三个整数的标志

int WriteFlag_Multi_ASC(const char* readfilename, const char* writefilename, int number, const char char_Multi[]);//写入number个ASC2编码字符的标志
int CheckFlag_Multi_ASC(const char* readfilename, const char* writefilename, int number, const char char_Multi[]);//校检number个ASC2编码字符的标志
int WriteFlag_Multi_Int(const char* readfilename, const char* writefilename, int number, int int_Multi[]);//写入number个整数的标志
int CheckFlag_Multi_Int(const char* readfilename, const char* writefilename, int number, int int_Multi[]);//校检number个整数的标志

#endif