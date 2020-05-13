#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;

struct Stu {
	char sid[13];
	int cid;
	char name[13];
	int score[4];
	int rank, sum;
	double aver;
	int num;
	bool operator<(const Stu & rhs) const {
		return sum > rhs.sum;
	}
};
int num = 0;
#define OFFSET 1e-5
vector<Stu> arr;

void rankStu() {
	int i;
	if(arr.empty())
		return ;
	arr[0].rank = 1;
	for(i=1; i<arr.size(); ++i) {
		if(arr[i].sum == arr[i-1].sum)
			arr[i].rank = arr[i-1].rank;
		else
			arr[i].rank = i+1;
	}
}

void addStu() {
	int i;
	Stu s;
	puts("Please enter the SID, CID, name and four scores. Enter 0 to finish.");
	while(scanf("%s", s.sid) == 1) {
		if(strlen(s.sid) == 1 && s.sid[0] == '0')
			break;
		scanf("%d %s",&(s.cid), s.name);
		s.sum = 0;
		for(i=0; i<4; ++i) {
			scanf("%d", &(s.score[i]));
			s.sum += s.score[i];
		}
		s.aver = (double)s.sum / 4 + OFFSET;
		auto ip = arr.begin();
		while(ip != arr.end()) {
			if(strcmp(s.sid, ip->sid) == 0)
				break;
			else
				++ip;
		}
		if(ip != arr.end())
			puts("Duplicated SID.");
		else {
			s.num = num++;
			arr.push_back(s);
		}
		puts("Please enter the SID, CID, name and four scores. Enter 0 to finish.");
	}
	sort(arr.begin(), arr.end());
	rankStu();
}

void removeStu() {
	int c;
	char s[30];
	puts("Please enter SID or name. Enter 0 to finish.");
	while(scanf("%s", s) == 1) {
		c = 0;
		if(strlen(s) == 1 && s[0] == '0')
			break;
		auto ip = arr.begin();
		while(ip != arr.end()) {
			if(strcmp(s, ip->sid) == 0 || strcmp(s, ip->name) == 0) {
				ip = arr.erase(ip);
				++c;
			} else
				++ip;
		}
		printf("%d student(s) removed.\n", c);
		puts("Please enter SID or name. Enter 0 to finish.");
	}
	rankStu();
}

bool compNum(const int &i, const int &j) {
	return arr[i].num < arr[j].num;
} 

void queryStu() {
	puts("Please enter SID or name. Enter 0 to finish.");
	int i,j,k;
	char s[30];
	while(scanf("%s", s) == 1) {
		if(strlen(s) == 1 && s[0] == '0')
			break;
		vector<int> v;
		for(int i = 0; i != arr.size(); ++i)
			if(strcmp(s, arr[i].sid) == 0 || strcmp(s, arr[i].name) == 0)
				v.push_back(i);
		if(!v.empty()) {
			sort(v.begin(), v.end(), compNum);
			for(auto i = 0; i != v.size(); ++i) {
				printf("%d %s %d %s ", arr[v[i]].rank, arr[v[i]].sid, arr[v[i]].cid, arr[v[i]].name);
				for(j=0; j<4; ++j)
					printf("%d ", arr[v[i]].score[j]);
				printf("%d %.2lf\n", arr[v[i]].sum,arr[v[i]].aver);
			}
		}
		puts("Please enter SID or name. Enter 0 to finish.");
	}
}
char s_score[4][20] = {"Chinese", "Mathematics", "English", "Programming"};

void showStat() {
	puts("Please enter class ID, 0 for the whole statistics.");
	int i,j,k=0,cid;
	scanf("%d", &cid);
	int arrSum[4] = {0,0,0,0};
	int arrPass[4] = {0,0,0,0};
	int arrOverall[5] = {0,0,0,0,0};
	for(auto ip = arr.begin(); ip != arr.end(); ++ip)
		if(cid == 0 || ip->cid == cid) {
			++k;
			j = 0;
			for(i=0;i<4;++i) {
				arrSum[i] += ip->score[i];
				if(ip->score[i] >= 60) {
					++arrPass[i];
					++j;
				}
			}
			arrOverall[j]++; 
		}
	for(i=0;i<4;++i) {
		puts(s_score[i]);
		if(k != 0)
			printf("Average Score: %.2lf\n", (double)arrSum[i]/k+OFFSET);
		else
			printf("Average Score: %.2lf\n", (double)0);
		printf("Number of passed students: %d\n",  arrPass[i]);
		printf("Number of failed students: %d\n\n", k-arrPass[i]);
	} 
	puts("Overall:");
	j = 0;
	for(i=4;i>0;--i) {
		printf("Number of students who passed ");
		j += arrOverall[i];
		if(i == 4)
			printf("all ");
		else
			printf("%d or more " , i);
		printf("subjects: %d\n", j);
	}
	printf("Number of students who failed all subjects: %d\n\n", arrOverall[0]);
}

int main() {
	char s[30];
	while(1) {
		puts("Welcome to Student Performance Management System (SPMS).\n");
		puts("1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n");
		scanf("%s", s);
		if(s[0] == '0')
			break;
		switch(s[0]) {
			case '1':
				addStu();
				break;
			case '2':
				removeStu();
				break;
			case '3':
				queryStu();
				break;
			case '4':
				puts("Showing the ranklist hurts students' self-esteem. Don't do that.");
				break;
			case '5':
				showStat();
				break;
		}
	}
	return 0;
}
