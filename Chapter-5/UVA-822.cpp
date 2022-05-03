#include<iostream>
#include<vector>
#include<queue>
#include<algorithm> 

using namespace std;

struct REQ {
	int id, num, elap, serv, btwe;
}; 
vector<REQ> reqs;

struct PER {
	int id;
	vector<int> v;
	int eart, endt;
};
vector<PER> pers;
int MAXTOPLEN;

struct TIME {
	int t;
	int flag;
	int i;
	bool operator== (const TIME & rhs) const {
		if(this->t == rhs.t && this->i == rhs.i && this->flag == rhs.flag) {
			return true;
		}
		return false;
	}
	bool operator< (const TIME & rhs) const {
		if(this->t != rhs.t) {
			return this->t < rhs.t;
		}
		if(this->flag != rhs.flag)
			return this->flag < rhs.flag;
		return this->i < rhs.i;
	}
	bool operator> (const TIME & rhs) const {
		if(*this == rhs || *this < rhs) {
			return false;
		}
		return true;
	}
};

bool cmp(const TIME & lhs, const TIME & rhs) {
	if(lhs.t != rhs.t) {
		return lhs.t < rhs.t;
	}
	return lhs.i < rhs.i;
}

int judgePer(int i, int j) {
	if(pers[i].eart > pers[j].eart) {
		return j;
	}
	if(pers[i].eart < pers[j].eart) {
		return i;
	}
	if(pers[i].id > pers[j].id) {
		return j;
	}
	if(pers[i].id < pers[j].id) {
		return i;
	}
}

int choosePerson(int r, int t) {
	int i, j, k;
	bool flag;
	int choose;
	for(i = 0; i < MAXTOPLEN; ++i) {
		flag = false; 
		for(j = 0; j < pers.size(); ++j) {
			if(pers[j].v.size() <= i || pers[j].endt > t) {
				continue;
			}
			if(pers[j].v[i] == reqs[r].id) {
				if(flag == false) {
					flag = true;
					choose = j;
				} else {
					choose = judgePer(j, choose);
				}
			}
		}
		if(flag == true) {
			return choose;
		}
	}
	return -1;
}


int simulate() {
	int t = 0, i, j, k;
	TIME ti, tt;
	priority_queue<TIME, vector<TIME>, greater<TIME>> pq;
	queue<int> qth;
	for(i = 0; i < reqs.size(); ++i) {
		for(j = 0; j < reqs[i].num; ++j) {
			TIME tim;
			tim.t = reqs[i].elap + reqs[i].btwe * j;
			tim.i = i;
			tim.flag = 1;
			pq.push(tim);
		}
	}

	while(pq.size() || qth.size()) {
		if(pq.size()) {
			ti = pq.top();
			pq.pop();
			if(ti.flag > 0) {
				qth.push(ti.i);
			}
			t = ti.t;
			while(pq.size()) {
				tt = pq.top();
				if(tt.t == t) {
					if(tt.flag > 0) {
						qth.push(tt.i);
					}
					pq.pop();
				} else {
					break;
				}
			}
		}
		k = qth.size();
		for(i = 0; i < k; ++i) {
			j = qth.front();
			qth.pop();
			int perCho = choosePerson(j, t);
			if(perCho < 0) {
				qth.push(j);
				continue;
			}
			pers[perCho].eart = t;
			pers[perCho].endt = t + reqs[j].serv;
			TIME tim;
			tim.t = pers[perCho].endt;
			tim.flag = -1;
			pq.push(tim);
		}
	}
	return t;
}


int main() {
	int m, n, i, j, k, t = 0;
	while(cin >> m && m != 0) {
		reqs.clear();
		pers.clear();
		MAXTOPLEN = 0;
		while(m--) {
			REQ r;
			cin >> r.id >> r.num >> r.elap >> r.serv >> r.btwe;
			reqs.push_back(r);
		}
		cin >> n;
		while(n--) {
			PER p;
			cin >> p.id >> i;
			if(i > MAXTOPLEN) {
				MAXTOPLEN = i;
			}
			while(i--) {
				cin >> j;
				p.v.push_back(j);
			}
			p.eart = 0;
			p.endt = 0;
			pers.push_back(p);
		}
		k = simulate();
		cout << "Scenario " << ++t << ": All requests are serviced within " << k << " minutes." << endl;
	}
	return 0;
} 
