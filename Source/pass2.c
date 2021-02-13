
#include "agroup.h"

void pass2() {
	int a, b;
	for (int i = 1; i < LastIndex - 1; i++) {    // ��� �ٿ��� start end �κ� ���� 
		if (strcmp(sic[i].opcode, "RESW") == 0 || strcmp(sic[i].opcode, "RESB") == 0) { //���þ� RESW,RESB ����
			sic[i].objCode = NULL;
		}
		else if (sic[i].opcodeHex != NULL) {    //opcode ���� �ϴ��� opcode�� �����ϸ� ���� �����ϴ� opcodeHEX ���翩�� üũ 
			if (sic[i].operand != NULL) {		//operand�� null�� ��� üũ
				char buf4[9] = { "NULL" };
				char *ptr = strstr(sic[i].operand, ",X");	 // Indexed-Addressing Mode ���� üũ
				int w = strlen(sic[1].operand);
				for (int z = 0; z < w; z++)
					buf4[z] = sic[i].operand[z];   //operand�� buf4�� ����
				if (b = srchsym(buf4)) { // �ɺ����̺� buf4�� ���� �ϴ��� üũ    
					if (ptr != NULL) {     //ptr�� ���� �����ϸ� Indexed Adressing mode�̴�.
						char buf3[5] = { "NULL" };
						for (int x = 0; x < 5; x++)
							buf3[x] = symtab[b].value[x];
						if (buf3[0] == '0') {             //ù° �ڸ��� 8���ؼ� 10�Ѿ�� A,B,C,D,E,F�� ǥ��
							buf3[0] = '8';
						}
						else if (buf3[0] == '1') {
							buf3[0] = '9';
						}
						else if (buf3[0] == '2') {
							buf3[0] = 'A';
						}
						else if (buf3[0] == '3') {
							buf3[0] = 'B';
						}
						else if (buf3[0] == '4') {
							buf3[0] = 'C';
						}
						else if (buf3[0] == '5') {
							buf3[0] = 'D';
						}
						else if (buf3[0] == '6') {
							buf3[0] = 'E';
						}
						else {
							buf3[0] = 'F';
						}

						char buffer[7];

						strcpy(buffer, sic[i].opcodeHex);      //buffer �� opcodeHex����  
						strcat(buffer, buf3);				   //buffer �� operand �ּҰ� ���� 

						sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));  //objectCode�� buffer�� ũ�� ��ŭ �����Ҵ�
						strcpy(sic[i].objCode, buffer);										//objectCode�� buffer ����

					}

					else {
						char buffer1[10];
						char buffer[7];
						strcpy(buffer, sic[i].opcodeHex);      //buffer �� opcodeHex����  
						strcat(buffer, symtab[b].value);	    //buffer �� operand �ּҰ� ���� 
						sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));	//objectCode�� buffer�� ũ�� ��ŭ �����Ҵ�
						strcpy(sic[i].objCode, buffer);					//objectCode�� buffer ����
					}
				}


				else {
					char buffer1[10];
					char buffer[7];
					strcpy(buffer, sic[i].opcodeHex);	//buffer �� opcodeHex����  
					strcat(buffer, symtab[i].value);	 //buffer �� operand �ּҰ� ����
					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));	//objectCode�� buffer�� ũ�� ��ŭ �����Ҵ�
					strcpy(sic[i].objCode, buffer);							//objectCode�� buffer ����

				}
			}
			else {
				if (strcmp(sic[i].opcode, "RSUB") == 0) {   //operand�� null�϶� RSUB�϶�
					char buffer[7];
					strcpy(buffer, sic[i].opcodeHex);		//buffer �� opcodeHex����  
					strcat(buffer, "0000");					 //buffer �� operand �ּҰ� ����
					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));		//objectCode�� buffer�� ũ�� ��ŭ �����Ҵ�
					strcpy(sic[i].objCode, buffer);			//objectCode�� buffer ����
				}
				else {
					sic[i].objCode = "NULL";
				}

			}
		}
		else if (strcmp(sic[i].opcode, "WORD") == 0) {       //WORD�� ����� ���ڿ��� 16������ �ٲپ� ����
			char buffer[7];
			sprintf(buffer, "%0.6X", atoi(sic[i].operand));
			sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));	//objectCode�� buffer�� ũ�� ��ŭ �����Ҵ�
			strcpy(sic[i].objCode, buffer);		//objectCode�� buffer ����

		}
		else if (strcmp(sic[i].opcode, "BYTE") == 0) {       //BYTE�� ����� ���ڿ��� 16������ �ٲپ� ����
			if (sic[i].operand[0] == 'X') {     //  Ex)  X'F1' �϶� ù��° �ڸ� X�� �Ǵ� 
				char buf1[10] = { NULL };

				int q = strlen(sic[i].operand);
				for (int k = 2; k < q - 1; k++) {
					buf1[k - 2] = sic[i].operand[k];  //X'F1'���� 3��° F���� ������ �ڸ� (')���� -1���� ���� 
				}
				sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buf1) + 1));	//objectCode�� buffer�� ũ�� ��ŭ �����Ҵ�
				strcpy(sic[i].objCode, buf1);		//objectCode�� buf1 ����
			}
			else {
				int c = strlen(sic[i].operand);           //���� ������
				int d;
				if (c == 6) {           //C'EOF'   3���� �϶�
					char buf2[4] = { NULL };
					for (int k = 2; k < 5; k++) {  //C'   '�κ� ���� buf2�� ����
						buf2[k - 2] = sic[i].operand[k];
					}
					char a[3], b[3], c[3];
					sprintf(a, "%X", (int)buf2[0]);  // E�κ� 16������ a�� ����
					sprintf(b, "%X", (int)buf2[1]);	 // O�κ� 16������ b�� ����
					sprintf(c, "%X", (int)buf2[2]);  // F�κ� 16������ c�� ����

					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buf2) + 1));	//objectCode�� buff2�� ũ�� ��ŭ �����Ҵ� 
					strcpy(sic[i].objCode, a);		//objCode�� a,b,c ���ʴ�� ����
					strcat(sic[i].objCode, b);
					strcat(sic[i].objCode, c);

				}
				else if (c == 5) {       //C'OF'   2���� �϶�
					char buf2[3] = { NULL };
					for (int k = 2; k < 4; k++) {  //C'   '�κ� ����
						buf2[k - 2] = sic[i].operand[k];
					}
					char a[3], b[3];

					sprintf(a, "%X", (int)buf2[0]);  //ù ���� 16������ ����
					sprintf(b, "%X", (int)buf2[0]);  //�ι�° ���� 16������ ����

					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buf2) + 1));   //objectCode�� buff2�� ũ�� ��ŭ �����Ҵ� 
					strcpy(sic[i].objCode, "00");   // 00//ù����//�α��� 
					strcat(sic[i].objCode, a);
					strcat(sic[i].objCode, b);
				}

				else {				  //C'F'   1���� �϶�
					char buf2[2] = { NULL };
					buf2[0] = sic[i].operand[2];
					char a[3];
					sprintf(a, "%X", (int)buf2[0]);

					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buf2) + 1));
					strcpy(sic[i].objCode, "00");	 // 00//00//�α��� 
					strcat(sic[i].objCode, "00");
					strcat(sic[i].objCode, a);
				}
			}
		}
		else {
			sic[i].objCode = "NULL";
		}

	}
}