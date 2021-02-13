//#define _CRT_SECURE_NO_WARNINGS

#define debug 0

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100
#define SYMTAB 100

//SIC ���α׷����� �޾ƿ� �������� ����ü
struct  Statement {
	char *lineNo;
	char *label;
	char *opcode;
	char *operand;
	char *LOCCTR;
	char *objCode;
	char *opcodeHex;
}sic[MAXLINE];
int LastIndex;	//sic ����ü ������ �ε��� ��ȣ
char *programLength;	//LOCCTR�� ���� ���α׷� ��ü ����

//OPTAB
struct Store {
	char *opcode;
	char *Hex;
}op[MAXLINE];

//�ɺ����̺� ����ü
struct entry {
	char *name;//���̺��� �̸�
	char *value;//���̺� �ش��ϴ� ��(=�ּ�)
	int errorflag;//�� ��ȣ�� �� ��ҿ��� ���ǵǴ� ������ ��Ÿ���� �÷���
}symtab[SYMTAB];//�ɺ����̺� �迭 ����

char *strsearch(char *key);	//opcode search

int srchsym(char *s); //symbol search

void StoreOP();	//OPTAB Make

void pass1(int i);	//pass1

void pass2();	//pass2

void CreateObjCode(char *outFileName);	//object program, outfile

