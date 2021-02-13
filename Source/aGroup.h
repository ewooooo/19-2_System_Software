//#define _CRT_SECURE_NO_WARNINGS

#define debug 0

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100
#define SYMTAB 100

//SIC 프로그램에서 받아온 라인정보 구조체
struct  Statement {
	char *lineNo;
	char *label;
	char *opcode;
	char *operand;
	char *LOCCTR;
	char *objCode;
	char *opcodeHex;
}sic[MAXLINE];
int LastIndex;	//sic 구조체 마지막 인덱스 번호
char *programLength;	//LOCCTR로 구한 프로그램 전체 길이

//OPTAB
struct Store {
	char *opcode;
	char *Hex;
}op[MAXLINE];

//심볼테이블 구조체
struct entry {
	char *name;//레이블의 이름
	char *value;//레이블에 해당하는 값(=주소)
	int errorflag;//한 기호가 두 장소에서 정의되는 오류를 나타내는 플래그
}symtab[SYMTAB];//심볼테이블 배열 선언

char *strsearch(char *key);	//opcode search

int srchsym(char *s); //symbol search

void StoreOP();	//OPTAB Make

void pass1(int i);	//pass1

void pass2();	//pass2

void CreateObjCode(char *outFileName);	//object program, outfile

