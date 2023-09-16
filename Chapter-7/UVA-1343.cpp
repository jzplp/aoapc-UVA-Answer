#include<stdio.h>
#include<map> 
#include<string.h>

#define MAXLEN 20

using namespace std;

int arr[24];
int arrCon[4][7];
// �Ƿ���ʹ��ļ�¼
map<long long, int> mp;
// ��¼�����������ʱ���ƶ���� 
char moves[3][MAXLEN + 5];
// �ƶ�����ĳ��� 
int moveCount[3];
// ÿ���ƶ����������ƶ����ͣ����ܲ������±���ָʾ���Ǹ��� 
int moveType[3];

// ����������ת��Ϊ������ģʽ 
void convertArr() {
	int i;
	arrCon[0][0] = arr[0]; arrCon[1][0] = arr[1];
	arrCon[0][1] = arr[2]; arrCon[1][1] = arr[3];
	for(i = 0; i < 7; ++i) arrCon[2][i] = arr[4 + i];
	arrCon[0][2] = arr[6]; arrCon[1][2] = arr[8];
	arrCon[0][3] = arr[11]; arrCon[1][3] = arr[12];
	for(i = 0; i < 7; ++i) arrCon[3][i] = arr[13 + i];
	arrCon[0][4] = arr[15]; arrCon[1][4] = arr[17];
	arrCon[0][5] = arr[20]; arrCon[1][5] = arr[21];
	arrCon[0][6] = arr[22]; arrCon[1][6] = arr[23];
}

// ��һ�������ƶ�λ�� type->0 �����ƶ� type->1 ��С�ƶ�
void moveArr(int *arrSrc, int type) {
	int t, i;
	if(type == 0) {
		t = arrSrc[6];
		for(i = 6; i > 0; --i) arrSrc[i] = arrSrc[i-1];
		arrSrc[0] = t;
	} else {
		t = arrSrc[0];
		for(i = 0; i < 6; ++i) arrSrc[i] = arrSrc[i+1];
		arrSrc[6] = t;
	}
}

// ����ĳ�������ƶ�  flag->1 �ƶ� flag->0 �ָ��ƶ� 
void moveStep(int num, bool flag) {
	bool type;
	switch(num) {
		case 0:
		case 5:
			type = num < 4 ? 1 : 0;
			type = flag ? type : !type;
			moveArr(arrCon[0], type);
			arrCon[2][2] = arrCon[0][2];
			arrCon[3][2] = arrCon[0][4];
			break;
		case 1:
		case 4:
			type = num < 4 ? 1 : 0;
			type = flag ? type : !type;
			moveArr(arrCon[1], type);
			arrCon[2][4] = arrCon[1][2];
			arrCon[3][4] = arrCon[1][4];
			break;
		case 2:
		case 7:
			type = num < 4 ? 0 : 1;
			type = flag ? type : !type;
			moveArr(arrCon[2], type);
			arrCon[0][2] = arrCon[2][2];
			arrCon[1][2] = arrCon[2][4];
			break;
		case 3:
		case 6:
			type = num < 4 ? 0 : 1;
			type = flag ? type : !type;
			moveArr(arrCon[3], type);
			arrCon[0][4] = arrCon[3][2];
			arrCon[1][4] = arrCon[3][4];
			break;
	}
}

// �Ƿ�ɹ� ���سɹ����ַ� ����0 
int isArrive() {
	int num = arrCon[0][2];
	if(arrCon[0][3] != num || arrCon[0][4] != num || arrCon[1][2] != num || arrCon[1][3] != num) 
		return 0;
	if(arrCon[1][4] != num || arrCon[2][3] != num || arrCon[3][3] != num)
		return 0;
	return num;
}

// �����������������е�λ�ã�ת��Ϊ0-27���������� 
long long getArrPos(int num) {
	int i, j;
	long long sum = 0;
	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 7; ++j) {
			if(arrCon[i][j] == num) {
				if(i < 2) {
					sum = (sum << 5) + i * 7 + j;
				} else {
					if(j == 2 || j == 4) continue;
					sum = (sum << 5) + i * 7 + j;
				}
			}
		}
	}
	return sum;
}

// ���ۺ��� true�����л��� false����û���� 
bool hvalue(int num, int stepCount, int k) {
	int i, j, value = 0;
	for(i = 0; i < 4; ++i) {
		if(arrCon[i][3] != num) value += 1;
	}
	if(arrCon[0][2] != num) value += 1;
	if(arrCon[0][4] != num) value += 1;
	if(arrCon[1][2] != num) value += 1;
	if(arrCon[1][4] != num) value += 1;
	return stepCount + value <= k;
}

//�ݹ�Ѱ�� 
int getValue(int num, int stepCount, int k) {
	int resArr = isArrive();
	if(resArr) {
		moveType[num - 1] = resArr;
		return stepCount;
	}
	if(stepCount >= k) return 0;
	if(!hvalue(num, stepCount, k))	return 0;
	int i, count, res;
	long long sum; 
	for(i = 0; i < 8; ++i) {
		// �ƶ�
		moveStep(i, true);
		sum = getArrPos(num);
		count = mp[sum];
		if(!count || count > stepCount) {
			mp[sum] = stepCount;
			// ��¼���� 
			moves[num-1][stepCount] = i;
			// �����ӽڵ�
			res = getValue(num, stepCount+1, k);
			if(res) {
				// ��λ
				moveStep(i, false); 
				return res;
			}
		}
		// ��λ
		moveStep(i, false);
	}
	return 0;
}

int getRes(int k) {
	int i, j, mini, minV;
	for(i = 0; i < 3; ++i) {
		mp.clear();
		long long sum = getArrPos(i+1);
		mp[sum] = 0;
		moveCount[i] = getValue(i+1, 0, k);
		if(moveCount[i] > 0) k = moveCount[i];
	}
	minV = MAXLEN + 10;
	mini = -1;
	for(i = 0; i < 3; ++i) {
		if(moveCount[i] == 0) continue;
		if(minV > moveCount[i]) {
			minV = moveCount[i];
			mini = i;
		} else if(minV == moveCount[i]) {
			if(strcmp(moves[mini], moves[i]) > 0) {
				minV = moveCount[i];
				mini = i;
			}
		}
	}
	return mini;
}

int main() {
	int i, j, k;
	while(1) {
		if(scanf("%d", &arr[0]) != 1 || arr[0] == 0) break;
		for(i = 1; i < 24; ++i) {
			scanf("%d", &arr[i]);
		}
		convertArr();
		int resType = isArrive();
		if(resType) {
			printf("No moves needed\n");
			printf("%d\n", resType);
			continue;
		}
		for(i = 1; i < MAXLEN; ++i) {
			k = getRes(i);
			if(k >= 0) break;
		}
		for(i = 0; i < moveCount[k]; ++i) {
			printf("%c", moves[k][i] + 'A');
		}
		putchar('\n'); 
		printf("%d\n", moveType[k]);
	}
	return 0;
}

