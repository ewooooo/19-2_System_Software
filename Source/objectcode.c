
#include "aGroup.h"

void addzero(char * strHex, int len);
char *HeaderRecord();
char *TextRecord(int *pStartIndex);
char *EndRecord();

void CreateObjCode(char *outFileName) {

	char *objProgram[MAXLINE];
	//H Record
	objProgram[0] = HeaderRecord();

	//T Record
	int startIndex = 1;
	int lineNum = 1;
	while (lineNum < MAXLINE && startIndex < LastIndex-1) {
		//남은 sic code가 모두 NULL 이면 빈 T recode가 생성되므로 막는다.
		if (sic[startIndex].objCode == NULL) { 
			startIndex++;
			continue;
		}

			objProgram[lineNum] = TextRecord(&startIndex);
			lineNum++;
	}

	//E Record
	objProgram[lineNum] = EndRecord();

	//outFile 저장
	FILE *out;
	if ((out = fopen(outFileName, "w")) == NULL) {
		printf("출력파일 열기 실패");
		exit(1);
	}


	for (int i = 0; i <= lineNum; i++) {
		fprintf(out, "%s\n", objProgram[i]);
	}

	fclose(out);

#if debug == 1
	//debug print
	printf("\n=============== make objectProgram ===========\n");
	for (int i = 0; i <= lineNum; i++) {
		printf("%s\n", objProgram[i]);
	}
	
#endif
}


char *HeaderRecord() {

	char str[20]; //Header record col 1-19

	char programName[7];	//col 2-7
	strcpy(programName, sic[0].label);
	while (strlen(programName) < 6) {
		strcat(programName, " ");
	}

	char startAddress[7];	//col 8-13
	strcpy(startAddress, sic[0].operand);
	addzero(startAddress, 6);

	char lenProgram[7];		//col 14-19
	strcpy(lenProgram, programLength);
	addzero(lenProgram, 6);

	strcpy(str, "H");
	strcat(str, programName);
	strcat(str, startAddress);
	strcat(str, lenProgram);

	char *Hstr = (char*)malloc(sizeof(char)*(strlen(str) + 1));
	strcpy(Hstr, str);

	return Hstr;
}

char *TextRecord(int *pStartIndex) {

	char str[70]; //text record col 1-69
	int byteCount = 0;

	char startAddress[7];	//col 2-7
	strcpy(startAddress, sic[*pStartIndex].LOCCTR);
	addzero(startAddress, 6);

	char strbuffer[60] = ""; //col 10-69
	while (*pStartIndex < LastIndex-1) {  
		if (sic[*pStartIndex].objCode != NULL) { //objCode 있는지 검사
			byteCount = byteCount + strlen(sic[*pStartIndex].objCode);
			if (byteCount > 60) { //60 colum 넘는지 검사
				break;
			}
			strcat(strbuffer, sic[*pStartIndex].objCode);
		}
			*pStartIndex = *pStartIndex + 1;
	}

	char lenByte[3];	//col 8-9
	sprintf(lenByte, "%X", byteCount);
	addzero(lenByte, 2);

	strcpy(str, "T");
	strcat(str, startAddress);
	strcat(str, lenByte);
	strcat(str, strbuffer);

	char *tstr = (char*)malloc(sizeof(char)*(strlen(str) + 1));
	strcpy(tstr, str);

	return tstr;
}



char *EndRecord() {

	char str[8]; //End record 1-7

	char startAddress[7];	////col 2-7
	strcpy(startAddress, sic[0].operand);
	addzero(startAddress, 6);

	strcpy(str, "E");
	strcat(str, startAddress);

	char *Estr = (char*)malloc(sizeof(char)*(strlen(str) + 1));
	strcpy(Estr, str);

	return Estr;
}

void addzero(char * strHex, int len) {
	while (strlen(strHex) < len) {
		char tmp[7] = "0";
		strcat(tmp, strHex);
		strcpy(strHex, tmp);
	}
}