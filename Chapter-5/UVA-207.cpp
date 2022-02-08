#include<iostream>
#include<string>
#include<vector>
#include<sstream> 
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include <iomanip>
#define PRIZENUM 70
#define NAMELEN 21
using namespace std;

struct Player {
	string name;
	int rd[4];
	int total;
	double money;
	bool amateur;
	int place;
	bool t;
	bool hasMoney;
	int dqi; 
}; 

double sum;
double per[PRIZENUM];
vector<Player> v; 

void readPlayer(Player &p, string sline) {
	string s;
	int i, j, rd;
	int namelen = NAMELEN - 1;
	s = sline.substr(0, namelen);
	p.name = s;
	if(strchr(s.c_str(), '*')) {
		p.amateur = true;
	} else {
		p.amateur = false;
	}
	sline = sline.substr(namelen, sline.length() - namelen);
	stringstream ss(sline);
	p.total = 0;
	p.place= 0;
	p.t = false;
	p.hasMoney = false;
	p.dqi = -1;
	p.money = 0;
	memset(p.rd, 0, sizeof(p.rd)); 
	for(i = 0; i < 4 && (ss >> s); ++i) {
		if(s == "DQ") {
			break;
		}
		p.rd[i] = stoi(s);
		p.total += p.rd[i];
	}
	if(i < 4) {
		p.rd[i] = -1;
		p.dqi = i;
	}
}

void printOne(string s, int len, char c = ' ') {
	cout << s;
	len = len - s.length();
	while(len-- > 0) {
		cout << c;
	}
}

void printOne(int num, int len, char c = ' ') {
	ostringstream ss;
	ss << num;
	string s = ss.str();
	printOne(s, len, c);
}


void printOrder(int i) {
	if(v[i].dqi != -1) {
		printOne("", 10);
		return;
	}
	ostringstream ss;
	ss << v[i].place;
	string s = ss.str();
	if(v[i].t) {
		s = s + "T";
	}
	printOne(s, 10);
}

void print(int n) {
	int i, j;
	cout << "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won" << endl;
	printOne("", NAMELEN + 50, '-');
	cout << endl;
	for(i = 0; i < v.size(); ++i) {
		printOne(v[i].name, NAMELEN);
		printOrder(i);
		for(j = 0; j < 4; ++j) {
			if(v[i].dqi == j) {
				printOne("", 5*(4-j));
				break;
			} else {
				printOne(v[i].rd[j], 5);
			}
		}
		if(v[i].dqi != -1) {
			cout << "DQ";
		} else if(v[i].amateur || !v[i].hasMoney) {
			cout << v[i].total;
		} else {
			printOne(v[i].total, 10);
			// printf("$%9.2lf", v[i].money);
			cout << "$" << right << setw(9) << fixed << setprecision(2) << v[i].money;
		}
		cout << endl;
	}
	if(n != 0) {
		cout << endl;
	}
} 

bool cmpCut(const Player & a, const Player & b) {
	if(a.dqi < 2 && a.dqi != -1) return false;
	if(b.dqi < 2 && b.dqi != -1) return true;
	int suma = a.rd[0] +  a.rd[1];
	int sumb = b.rd[0] +  b.rd[1];
	return suma < sumb;
}

int sortCut() {
	int i, j, suma;
	sort(v.begin(), v.end(), cmpCut);
	for(i = 0; i < PRIZENUM && i < v.size(); ++i) {
		if(v[i].dqi < 2 && v[i].dqi != -1) {
			return i;
		}
	}
	suma = v[i-1].rd[0] + v[i-1].rd[1];
	while(i < v.size()) {
		if(v[i].dqi < 2 && v[i].dqi != -1) {
			break;
		}
		if(suma != v[i].rd[0] + v[i].rd[1]) {
			break;
		}
		++i;
	}
	return i;
}

bool cmpFinal(const Player & a, const Player & b) {
	if(a.dqi != -1 && b.dqi != -1) {
		if(a.dqi != b.dqi) {
			return a.dqi > b.dqi;
		}
		if(a.total != b.total) {
			return a.total < b.total;
		}
		return a.name < b.name;
	}
	if(a.dqi != -1) return false;
	if(b.dqi != -1) return true;
	if(a.total != b.total) {
		return a.total < b.total; 
	}
	return a.name < b.name;
}

void setPlace() {
	int i;
	for(i = 0; i < v.size(); ++i) {
		if(v[i].dqi != -1) {
			return;
		}
		if(i != 0 && v[i].total == v[i-1].total) {
			v[i].place = v[i-1].place;
		} else {
			v[i].place = i + 1;
		}
	}
}

void setMoney() {
	int i = 0, j, k;
	int num, pnum = 0;
	double money;
	while(i < v.size() && pnum < PRIZENUM) {
		if(v[i].dqi != -1) {
			return;
		}
		if(v[i].amateur) {
			++i;
			continue; 
		}
		num = 1;
		money = per[pnum++];
		v[i].hasMoney = true;
		for(j = i+1; j < v.size() && v[j].place == v[i].place; ++j) {
			if(v[j].dqi != -1) {
				break; 
			}
			if(v[j].amateur) continue;
			++num;
			if(pnum < PRIZENUM) {
				money += per[pnum++];
			}
			v[j].hasMoney = true;
		}
		money = money * sum / num / 100;
		for(k = i; k < j; ++k) {
			if(v[k].amateur) continue;
			if(v[k].hasMoney == false) continue;
			v[k].money = money;
			if(num > 1) {
				v[k].t = true; 
			}
		}
		i = j;
	}
}

int main() {
	int n, i, j, k;
	int num;
	string sline, s;
	cin >> n;
	while(n--) {
		v.clear();
		cin >> sum;
		for(i = 0; i < PRIZENUM; ++i) {
			cin >> per[i];
		}
		cin >> num;
		getline(cin, sline);
		for(i = 0; i < num; ++i) {
			Player p;
			getline(cin, sline);
			readPlayer(p, sline);
			v.push_back(p);
		}
		int cut = sortCut();
		v.resize(cut);
		sort(v.begin(), v.end(), cmpFinal);
		setPlace();
		setMoney();
		print(n);
	}
	return 0;
}
