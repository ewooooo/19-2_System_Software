
#include "aGroup.h"

//목적프로그램 생성부

int lastentry = 0;//심볼테이블에서 새로운 라벨이 들어갈 배열 첨자 위치
int srchsym(char *s) {
	int j;
	for (j = 0; j < lastentry; j++)
		if (strcmp(symtab[j].name, s) == 0)	//심볼테이블의 레이블 이름과 비교하여 같으면 인덱스 반환
			return j;
	return 0;
}

//심볼테이블 작성
void pass1(int i) {
	int found;// 탐색 결과

	if (sic[i].label != NULL) {//label에 내용이 있다면
		if (found = srchsym(sic[i].label)) //심볼테이블에서 탐색하여 이미 저장되어있으면 errorflag를 1로 저장(중복 방지)
			symtab[found].errorflag = 1;
		else {//심볼테이블에 저장되어있지 않은 내용은 심볼테이블에 저장
			symtab[lastentry].name = sic[i].label;	//label 저장
			symtab[lastentry].value = sic[i].LOCCTR;	//label의 값 LOCCTR 저장
			lastentry += 1;	//심볼테이블 길이 1 추가
		}
	}
}

