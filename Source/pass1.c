
#include "aGroup.h"

//�������α׷� ������

int lastentry = 0;//�ɺ����̺��� ���ο� ���� �� �迭 ÷�� ��ġ
int srchsym(char *s) {
	int j;
	for (j = 0; j < lastentry; j++)
		if (strcmp(symtab[j].name, s) == 0)	//�ɺ����̺��� ���̺� �̸��� ���Ͽ� ������ �ε��� ��ȯ
			return j;
	return 0;
}

//�ɺ����̺� �ۼ�
void pass1(int i) {
	int found;// Ž�� ���

	if (sic[i].label != NULL) {//label�� ������ �ִٸ�
		if (found = srchsym(sic[i].label)) //�ɺ����̺��� Ž���Ͽ� �̹� ����Ǿ������� errorflag�� 1�� ����(�ߺ� ����)
			symtab[found].errorflag = 1;
		else {//�ɺ����̺� ����Ǿ����� ���� ������ �ɺ����̺� ����
			symtab[lastentry].name = sic[i].label;	//label ����
			symtab[lastentry].value = sic[i].LOCCTR;	//label�� �� LOCCTR ����
			lastentry += 1;	//�ɺ����̺� ���� 1 �߰�
		}
	}
}

