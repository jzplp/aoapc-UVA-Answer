#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

int oproomNum, reroomNum, startTime, transTime, preop, prere, patiNum; 
struct Patient {
	char name[105];
	int opTime, reTime;
	int opNum, opBeg, opEnd, reNum, reBeg, reEnd;
}; 
vector<Patient> v;

struct Room {
	int useTime;
	bool use;
	int endTime;
};
vector<Room> opV;
vector<Room> reV;

// type说明
// 1 离开oproom
// -1 准备好 oproom

struct PrioItem {
	int time;
	int type;
	int pai;
	int roomi;
	bool operator< (const PrioItem &rhs) const {
		if(time != rhs.time) {
			return time > rhs.time;
		}
		if(type != rhs.type) {
			return type > rhs.type;
		}
		return roomi > rhs.roomi;
	}
};

int pai, timeNow, endTime;
priority_queue<PrioItem> pq;
 
// 病人开始手术
void useOpNum(int pai, int roomi) {
	PrioItem pi;
	opV[roomi].use = true;
	opV[roomi].useTime += v[pai].opTime;
	opV[roomi].endTime = timeNow + v[pai].opTime + preop;
	v[pai].opNum = roomi;
	v[pai].opBeg = timeNow;
	v[pai].opEnd = timeNow + v[pai].opTime;
	pi.time = v[pai].opEnd;
	pi.type = 1;
	pi.pai = pai;
	pi.roomi = roomi;
	pq.push(pi);
}

void handleN1(PrioItem pi) {
	if(pai >= patiNum) {
		return;
	} 
	for(int i = 0; i < opV.size(); ++i) {
		if(opV[i].endTime <= timeNow) {
			useOpNum(pai++, i);
		}
	}
}

void handle1(PrioItem pi) {
	// 转运病人
	// 转运的时候就要选择恢复室
	int i, j, k;
	for(i = 0; i < reroomNum; ++i) {
		if(reV[i].endTime <= timeNow) {
			break;
		}
	}
	if(i == reroomNum) {
		//printf("怎么会出现没有恢复室的情况？\n");
		return; 
	}
	reV[i].useTime += v[pi.pai].reTime;
	v[pi.pai].reNum = i;
	v[pi.pai].reBeg = timeNow + transTime;
	v[pi.pai].reEnd = v[pi.pai].reBeg + v[pi.pai].reTime;
	if(v[pi.pai].reEnd > endTime) {
		endTime = v[pi.pai].reEnd;
	}
	reV[i].endTime = v[pi.pai].reEnd + prere;
	
	// 清理手术室事件 
	PrioItem piNew2;
	piNew2.type = -1;
	piNew2.roomi = pi.roomi;
	piNew2.time = timeNow + preop;
	pq.push(piNew2);
}

void oper() {
	int i, j, k;
	timeNow = startTime;
	PrioItem pi;
	for(pai = 0; pai < oproomNum && pai < patiNum; ++pai) {
		useOpNum(pai, pai);
	}
	while(pq.size()) {
		pi = pq.top();
		pq.pop();
		timeNow = pi.time;
		switch(pi.type) {
			case -1:
				handleN1(pi);
				break;
			case 1:
				handle1(pi);
				break;
		}
	}
	if(pai != patiNum) {
		// printf("怎么会出现没有做手术的情况？\n");
		return; 
	}
}

void outTime(int t) {
	int hour = t / 60;
	int min = t % 60;
	printf("%2d:%02d", hour, min); 
}

void outPatient() {
	printf(" Patient          Operating Room          Recovery Room\n");
	printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
	printf(" ------------------------------------------------------\n");
	int i;
	for(i = 0; i < v.size(); ++i) {
		printf("%2d  %-9s %2d   ", i+1, v[i].name, v[i].opNum + 1);
		outTime(v[i].opBeg);
		printf("   ");
		outTime(v[i].opEnd);
		printf("     %2d   ", v[i].reNum + 1);
		outTime(v[i].reBeg);
		printf("   ");
		outTime(v[i].reEnd);
		printf("\n");
	}
	
}

double outUsed(int i, int type) {
	if(endTime == startTime) {
		return 0.0;
	}
	if(type == 0) {
		return (double)opV[i].useTime / (endTime-startTime) * 100;
	}
	if(type == 1) {
		return (double)reV[i].useTime / (endTime-startTime) * 100;
	}
}

void outFac() {
	printf("Facility Utilization\n");
	printf("Type  # Minutes  %% Used\n");
	printf("-------------------------\n");
	int i;
	for(i = 0; i < opV.size(); ++i) {
		printf("Room %2d %7d %7.2lf\n",i+1, opV[i].useTime, outUsed(i, 0));
	}
	for(i = 0; i < reV.size(); ++i) {
		printf("Bed  %2d %7d %7.2lf\n",i+1, reV[i].useTime, outUsed(i, 1));
	}
}

int main() {
	int i, j;
	while(scanf("%d%d%d%d%d%d%d", &oproomNum, &reroomNum, &startTime, &transTime, &preop, &prere, &patiNum) == 7) {
	v.clear();
	opV.clear();
	reV.clear();
	pq = priority_queue<PrioItem>();
	
	startTime = startTime * 60;
	endTime = startTime;
	for(i = 0; i < oproomNum; ++i) {
		Room m;
		m.use = false;
		m.useTime = 0;
		opV.push_back(m);
	}
	for(i = 0; i < reroomNum; ++i) {
		Room m;
		m.use = false;
		m.useTime = 0;
		m.endTime = 0;
		reV.push_back(m);
	}
	
	for(i = 0; i < patiNum; ++i) {
		Patient p;
		scanf("%s", p.name);
		scanf("%d%d", &p.opTime, &p.reTime);
		v.push_back(p);
	}
	oper();
	outPatient();
	printf("\n");
	outFac();
	printf("\n");
}
	
	return 0;
}
