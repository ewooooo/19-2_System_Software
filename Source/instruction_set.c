

#include "aGroup.h"

//opcode와 16진수 형태를 array 형태로 저장
void StoreOP()
{
	int i;
	for (i = 0; i < 59; i++) {
		op[i].opcode = malloc(sizeof(char) * 10);
		op[i].Hex = malloc(sizeof(char) * 5);
	}
	strcpy(op[0].opcode, "ADD");   strcpy(op[0].Hex, "18");
	strcpy(op[1].opcode, "ADDF");   strcpy(op[1].Hex, "58");
	strcpy(op[2].opcode, "ADDR");   strcpy(op[2].Hex, "90");
	strcpy(op[3].opcode, "AND");   strcpy(op[3].Hex, "40");
	strcpy(op[4].opcode, "CLEAR");   strcpy(op[4].Hex, "B4");
	strcpy(op[5].opcode, "COMP");   strcpy(op[5].Hex, "28");
	strcpy(op[6].opcode, "COMPF");   strcpy(op[6].Hex, "88");
	strcpy(op[7].opcode, "COMPR");   strcpy(op[7].Hex, "A0");
	strcpy(op[8].opcode, "DIV");   strcpy(op[8].Hex, "24");
	strcpy(op[9].opcode, "DIVF");   strcpy(op[9].Hex, "64");
	strcpy(op[10].opcode, "DIVR");   strcpy(op[10].Hex, "9C");
	strcpy(op[11].opcode, "FIX");   strcpy(op[11].Hex, "C4");
	strcpy(op[12].opcode, "FLOAT");   strcpy(op[12].Hex, "C0");
	strcpy(op[13].opcode, "HIO");   strcpy(op[13].Hex, "F4");
	strcpy(op[14].opcode, "J");   strcpy(op[14].Hex, "3C");
	strcpy(op[15].opcode, "JEQ");   strcpy(op[15].Hex, "30");
	strcpy(op[16].opcode, "JGT");   strcpy(op[16].Hex, "34");
	strcpy(op[17].opcode, "JLT");   strcpy(op[17].Hex, "38");
	strcpy(op[18].opcode, "JSUB");   strcpy(op[18].Hex, "48");
	strcpy(op[19].opcode, "LDA");   strcpy(op[19].Hex, "00");
	strcpy(op[20].opcode, "LDB");   strcpy(op[20].Hex, "68");
	strcpy(op[21].opcode, "LDCH");   strcpy(op[21].Hex, "50");
	strcpy(op[22].opcode, "LDF");   strcpy(op[22].Hex, "70");
	strcpy(op[23].opcode, "LDL");   strcpy(op[23].Hex, "08");
	strcpy(op[24].opcode, "LDS");   strcpy(op[24].Hex, "6C");
	strcpy(op[25].opcode, "LDT");   strcpy(op[25].Hex, "74");
	strcpy(op[26].opcode, "LDX");   strcpy(op[26].Hex, "04");
	strcpy(op[27].opcode, "LPS");   strcpy(op[27].Hex, "D0");
	strcpy(op[28].opcode, "MUL");   strcpy(op[28].Hex, "20");
	strcpy(op[29].opcode, "MULF");   strcpy(op[29].Hex, "60");
	strcpy(op[30].opcode, "MULR");   strcpy(op[30].Hex, "98");
	strcpy(op[31].opcode, "NORM");   strcpy(op[31].Hex, "C8");
	strcpy(op[32].opcode, "OR");   strcpy(op[32].Hex, "44");
	strcpy(op[33].opcode, "RD");   strcpy(op[33].Hex, "D8");
	strcpy(op[34].opcode, "RMO");   strcpy(op[34].Hex, "AC");
	strcpy(op[35].opcode, "RSUB");   strcpy(op[35].Hex, "4C");
	strcpy(op[36].opcode, "SHIFTL");   strcpy(op[36].Hex, "A4");
	strcpy(op[37].opcode, "SHIFTR");   strcpy(op[37].Hex, "A8");
	strcpy(op[38].opcode, "SIO");   strcpy(op[38].Hex, "F0");
	strcpy(op[39].opcode, "SSK");   strcpy(op[39].Hex, "EC");
	strcpy(op[40].opcode, "STA");   strcpy(op[40].Hex, "0C");
	strcpy(op[41].opcode, "STB");   strcpy(op[41].Hex, "78");
	strcpy(op[42].opcode, "STCH");   strcpy(op[42].Hex, "54");
	strcpy(op[43].opcode, "STF");   strcpy(op[43].Hex, "80");
	strcpy(op[44].opcode, "STI");   strcpy(op[44].Hex, "D4");
	strcpy(op[45].opcode, "STL");   strcpy(op[45].Hex, "14");
	strcpy(op[46].opcode, "STS");   strcpy(op[46].Hex, "7C");
	strcpy(op[47].opcode, "STSW");   strcpy(op[47].Hex, "E8");
	strcpy(op[48].opcode, "STT");   strcpy(op[48].Hex, "84");
	strcpy(op[49].opcode, "STX");   strcpy(op[49].Hex, "10");
	strcpy(op[50].opcode, "SUB");   strcpy(op[50].Hex, "1C");
	strcpy(op[51].opcode, "SUBF");   strcpy(op[51].Hex, "5C");
	strcpy(op[52].opcode, "SUBR");   strcpy(op[52].Hex, "94");
	strcpy(op[53].opcode, "SVC");   strcpy(op[53].Hex, "B0");
	strcpy(op[54].opcode, "TD");   strcpy(op[54].Hex, "E0");
	strcpy(op[55].opcode, "TIO");   strcpy(op[55].Hex, "F8");
	strcpy(op[56].opcode, "TIX");   strcpy(op[56].Hex, "2C");
	strcpy(op[57].opcode, "TIXR");   strcpy(op[57].Hex, "B8");
	strcpy(op[58].opcode, "WD");   strcpy(op[58].Hex, "DC");

}

//opcode 입력 받았을 시 해당하는 16진수로 출력
char *strsearch(char *key)
{
	int low = 0;
	int high = 59;
	int mid;

	// 이진 탐색
	while (low <= high) {
		mid = (low + high) / 2;
		if (strcmp(key, op[mid].opcode) == 0)
			return op[mid].Hex;
		else if (strcmp(key, op[mid].opcode) > 0)
			low = mid;
		else if (strcmp(key, op[mid].opcode) < 0)
			high = mid;

		if (mid + 1 == high)
			break;
	}

	return NULL;
}