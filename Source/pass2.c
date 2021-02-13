
#include "agroup.h"

void pass2() {
	int a, b;
	for (int i = 1; i < LastIndex - 1; i++) {    // 모든 줄에서 start end 부분 제외 
		if (strcmp(sic[i].opcode, "RESW") == 0 || strcmp(sic[i].opcode, "RESB") == 0) { //지시어 RESW,RESB 제외
			sic[i].objCode = NULL;
		}
		else if (sic[i].opcodeHex != NULL) {    //opcode 존재 하는지 opcode가 존재하면 같이 존재하는 opcodeHEX 존재여부 체크 
			if (sic[i].operand != NULL) {		//operand가 null인 경우 체크
				char buf4[9] = { "NULL" };
				char *ptr = strstr(sic[i].operand, ",X");	 // Indexed-Addressing Mode 인지 체크
				int w = strlen(sic[1].operand);
				for (int z = 0; z < w; z++)
					buf4[z] = sic[i].operand[z];   //operand를 buf4에 저장
				if (b = srchsym(buf4)) { // 심볼테이블에 buf4가 존재 하는지 체크    
					if (ptr != NULL) {     //ptr에 값이 존재하면 Indexed Adressing mode이다.
						char buf3[5] = { "NULL" };
						for (int x = 0; x < 5; x++)
							buf3[x] = symtab[b].value[x];
						if (buf3[0] == '0') {             //첫째 자리에 8더해서 10넘어가면 A,B,C,D,E,F로 표현
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

						strcpy(buffer, sic[i].opcodeHex);      //buffer 에 opcodeHex저장  
						strcat(buffer, buf3);				   //buffer 에 operand 주소값 저장 

						sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));  //objectCode에 buffer의 크기 만큼 동적할당
						strcpy(sic[i].objCode, buffer);										//objectCode에 buffer 저장

					}

					else {
						char buffer1[10];
						char buffer[7];
						strcpy(buffer, sic[i].opcodeHex);      //buffer 에 opcodeHex저장  
						strcat(buffer, symtab[b].value);	    //buffer 에 operand 주소값 저장 
						sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));	//objectCode에 buffer의 크기 만큼 동적할당
						strcpy(sic[i].objCode, buffer);					//objectCode에 buffer 저장
					}
				}


				else {
					char buffer1[10];
					char buffer[7];
					strcpy(buffer, sic[i].opcodeHex);	//buffer 에 opcodeHex저장  
					strcat(buffer, symtab[i].value);	 //buffer 에 operand 주소값 저장
					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));	//objectCode에 buffer의 크기 만큼 동적할당
					strcpy(sic[i].objCode, buffer);							//objectCode에 buffer 저장

				}
			}
			else {
				if (strcmp(sic[i].opcode, "RSUB") == 0) {   //operand가 null일때 RSUB일때
					char buffer[7];
					strcpy(buffer, sic[i].opcodeHex);		//buffer 에 opcodeHex저장  
					strcat(buffer, "0000");					 //buffer 에 operand 주소값 저장
					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));		//objectCode에 buffer의 크기 만큼 동적할당
					strcpy(sic[i].objCode, buffer);			//objectCode에 buffer 저장
				}
				else {
					sic[i].objCode = "NULL";
				}

			}
		}
		else if (strcmp(sic[i].opcode, "WORD") == 0) {       //WORD면 저장된 문자열을 16진수로 바꾸어 저장
			char buffer[7];
			sprintf(buffer, "%0.6X", atoi(sic[i].operand));
			sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));	//objectCode에 buffer의 크기 만큼 동적할당
			strcpy(sic[i].objCode, buffer);		//objectCode에 buffer 저장

		}
		else if (strcmp(sic[i].opcode, "BYTE") == 0) {       //BYTE면 저장된 문자열을 16진수로 바꾸어 저장
			if (sic[i].operand[0] == 'X') {     //  Ex)  X'F1' 일때 첫번째 자리 X로 판단 
				char buf1[10] = { NULL };

				int q = strlen(sic[i].operand);
				for (int k = 2; k < q - 1; k++) {
					buf1[k - 2] = sic[i].operand[k];  //X'F1'에서 3번째 F부터 마지막 자리 (')에서 -1까지 저장 
				}
				sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buf1) + 1));	//objectCode에 buffer의 크기 만큼 동적할당
				strcpy(sic[i].objCode, buf1);		//objectCode에 buf1 저장
			}
			else {
				int c = strlen(sic[i].operand);           //문자 넣을때
				int d;
				if (c == 6) {           //C'EOF'   3글자 일때
					char buf2[4] = { NULL };
					for (int k = 2; k < 5; k++) {  //C'   '부분 제외 buf2에 저장
						buf2[k - 2] = sic[i].operand[k];
					}
					char a[3], b[3], c[3];
					sprintf(a, "%X", (int)buf2[0]);  // E부분 16진수로 a에 저장
					sprintf(b, "%X", (int)buf2[1]);	 // O부분 16진수로 b에 저장
					sprintf(c, "%X", (int)buf2[2]);  // F부분 16진수로 c에 저장

					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buf2) + 1));	//objectCode에 buff2의 크기 만큼 동적할당 
					strcpy(sic[i].objCode, a);		//objCode에 a,b,c 차례대로 저장
					strcat(sic[i].objCode, b);
					strcat(sic[i].objCode, c);

				}
				else if (c == 5) {       //C'OF'   2글자 일때
					char buf2[3] = { NULL };
					for (int k = 2; k < 4; k++) {  //C'   '부분 제외
						buf2[k - 2] = sic[i].operand[k];
					}
					char a[3], b[3];

					sprintf(a, "%X", (int)buf2[0]);  //첫 글자 16진수로 저장
					sprintf(b, "%X", (int)buf2[0]);  //두번째 글자 16진수로 저장

					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buf2) + 1));   //objectCode에 buff2의 크기 만큼 동적할당 
					strcpy(sic[i].objCode, "00");   // 00//첫글자//두글자 
					strcat(sic[i].objCode, a);
					strcat(sic[i].objCode, b);
				}

				else {				  //C'F'   1글자 일때
					char buf2[2] = { NULL };
					buf2[0] = sic[i].operand[2];
					char a[3];
					sprintf(a, "%X", (int)buf2[0]);

					sic[i].objCode = (char*)malloc(sizeof(char)*(strlen(buf2) + 1));
					strcpy(sic[i].objCode, "00");	 // 00//00//두글자 
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