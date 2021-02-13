#include "aGroup.h"

#define MAXCOL   80

//String 16진수 => 정수로 변환
int AscConvert(char *charValue) {
	int decSum = 0;
	int stayValue = 1;
	for (int i = strlen(charValue) - 1; i >= 0; i--) {
		int decValue = charValue[i] - 48;	
		if (decValue > 9) {
			decValue = decValue - 7;
		}

		decSum = decSum + decValue * stayValue;

		stayValue = stayValue * 16;
	}
	return decSum;
}

int main(int argc, char* argv[])
{
	char *inputFileName = NULL;
	char *outputFileName = "aout.o";
	char dir[] = "./";
	
	if (argc == 1) {
		printf("program load error:파일명을 입력해주세요 \n");
		exit(0);
	}
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0) {
			if (argc <= i + 1) {
				printf("program load error: 명령어를 확인하세요 (-o : 출력파일명 지정)\n");
				exit(0);
			}
			i++;
			outputFileName = argv[i];
#if debug == 1
			printf("출력파일명확인\n");	//debug print
#endif
		}else if (strstr(argv[i], ".sic") != NULL) {
			inputFileName = argv[i];
#if debug == 1
			printf("입력파일명확인\n");	//debug print
#endif
			strcat(dir, inputFileName);
			
		}else {
			printf("program load error: 명령어를 확인하세요.\n(-o : 출력파일명 지정)\n(.sic만 가능)\n");
			exit(0);
		}
	}

	FILE *in;
	char str[MAXCOL];
	int i = 0;
	int LOCCTR_PASS1=0;

	in = fopen(dir, "r");
	if (in == NULL) {
		printf("can't open the file!\n");
		return 1;
	}

	StoreOP();
	while (fgets(str, MAXCOL, in) != NULL) {

		char *buffer[4];
#if debug == 1
		printf("%s", str); //debug print
#endif
		buffer[0]= strtok(str, " \t\n");
		buffer[1] = strtok(NULL, " \t\n");
		buffer[2] = strtok(NULL, " \t\n");
		buffer[3] = strtok(NULL, " \t\n"); 

		char *commentFind = buffer[1];
		if (commentFind[0] == '.') { //comment line 첫 글자 . 인지 확인
			continue;
		}

		//각 문자 길이의 맞게 메모리 할당
		sic[i].lineNo = (char*)malloc(sizeof(char)*(strlen(buffer[0]) + 1));
		sic[i].label = (char*)malloc(sizeof(char)*(strlen(buffer[1]) + 1));
		
		strcpy(sic[i].lineNo, buffer[0]);
		strcpy(sic[i].label, buffer[1]);
		
		if (buffer[2] != NULL) {
			sic[i].opcode = (char*)malloc(sizeof(char)*(strlen(buffer[2]) + 1));
			strcpy(sic[i].opcode, buffer[2]);
		}

		//Label 없는 라인 처리
		if (buffer[3] == NULL) {
			sic[i].operand = sic[i].opcode;
			sic[i].opcode = sic[i].label;
			sic[i].label = NULL;
		}
		else {
			sic[i].operand = (char*)malloc(sizeof(char)*(strlen(buffer[3]) + 1));
			strcpy(sic[i].operand, buffer[3]);
		}

		//opcode 찾아서 저장
		sic[i].opcodeHex = strsearch(sic[i].opcode);

		if (strcmp(sic[i].opcode, "START") == 0) {
			//LOCCTR 설정 및 opcode HEX(string) 변환
			//start address 받을 떄 hex 로 받아야 하고 LOCCTR 넣어줄때는 string 으로 넣어야함.
			LOCCTR_PASS1 = AscConvert(sic[i].operand);
			sic[i].LOCCTR = sic[i].operand;
		}
		else {
			//구조체에 LOCCTR 저장
			char strBuffer[7];
			sprintf(strBuffer, "%X", LOCCTR_PASS1);
			sic[i].LOCCTR = (char*)malloc(sizeof(char)*(strlen(strBuffer) + 1));
			strcpy(sic[i].LOCCTR, strBuffer);
			

			if (sic[i].opcodeHex != NULL) {
				
				LOCCTR_PASS1 = LOCCTR_PASS1 + 3;
			}
			else if (strcmp(sic[i].opcode, "WORD") == 0) {
				LOCCTR_PASS1 = LOCCTR_PASS1 + 3;
			}
			else if (strcmp(sic[i].opcode, "RESW") == 0) {
				LOCCTR_PASS1 = LOCCTR_PASS1 + atoi(sic[i].operand) * 3;
			}
			else if (strcmp(sic[i].opcode, "RESB") == 0) {
				LOCCTR_PASS1 = LOCCTR_PASS1 + atoi(sic[i].operand);
			}
			else if (strcmp(sic[i].opcode, "BYTE") == 0) {
				int strLenth = strlen(sic[i].operand);
				//사진 error 검출
				if (sic[i].operand[1] != '\'' || sic[i].operand[strLenth - 1] != '\'') {
					printf("BYTE operand error 형식이 다릅니다.");
					exit(0);
				}

				if (sic[i].operand[0] == 'C') {
					LOCCTR_PASS1 = LOCCTR_PASS1 + (strLenth - 3);
				}
				else if (sic[i].operand[0] == 'B') {
					LOCCTR_PASS1 = LOCCTR_PASS1 + ((strLenth - 3) / 8) + ((strLenth - 3) % 8 == 0 ? 0 : 1);
				}
				else if (sic[i].operand[0] == 'X') {
					//Hex 는 2개 당 1 byte 이므로 길이의 /2 값 추가 홀수 일시 1추가
					LOCCTR_PASS1 = LOCCTR_PASS1 + ((strLenth - 3) / 2) + ((strLenth - 3) % 2 == 0 ? 0 : 1);
				}
				else {
					printf("BYTE operand error 형식이 맞지 않습니다.");
					exit(0);
				}
			}
			else {
				LOCCTR_PASS1 = LOCCTR_PASS1 + 3;
			}
		}

		pass1(i);

		i++;
	}
	char strBuffer[6];
	sprintf(strBuffer, "%X", LOCCTR_PASS1);
	programLength = strBuffer;

	LastIndex = i;

	fclose(in);
	
	pass2();



#if debug == 1
	//debug print
	printf("\n=============== after paa1 ===========\n");
	for (int j = 0; j < 18; j++)
		printf("%d\tLabel: %s\tOperator: %s\terrer : %d\n",
			j, symtab[j].name, symtab[j].value, symtab[j].errorflag);
	printf("\n=============== after paa2 ===========\n");
	for (int k = 0; k < LastIndex; k++)
		printf("%s\t%s\t%s\t%s\t||\t%s\t%s\t%s\n",
			sic[k].lineNo, sic[k].label, sic[k].opcode, sic[k].operand, sic[k].LOCCTR, sic[k].opcodeHex, sic[k].objCode);
#endif


	CreateObjCode(outputFileName);
	printf("success! Export File: %s\n", outputFileName);

	return 0;
}

