#include<iostream>
#include<string>
#include<queue>
#include<map>
using namespace std;

struct MES {
	int id;
	int size;
	int price;
	int bs;
	bool operator< (const MES &rhs) const {
		if(this->price != rhs.price) {
			return this->price < rhs.price;
		}
		return this->id > rhs.id;
	}
	bool operator> (const MES &rhs) const {
		if(this->price != rhs.price) {
			return this->price > rhs.price;
		}
		return this->id > rhs.id;
	}
};

vector<MES> vmes;
priority_queue<MES, vector<MES>, less<MES>> buys;
priority_queue<MES, vector<MES>, greater<MES>> sells;
map<int, int> mpBuy, mpSell;

void deleteMes(int id) {
	if(id >= vmes.size() || !vmes[id].size) {
		return;
	}
	if(vmes[id].bs > 0) {
		mpBuy[vmes[id].price] -= vmes[id].size;
	} else {
		mpSell[vmes[id].price] -= vmes[id].size;
	}
	vmes[id].size = 0;
}

void buyMes(MES &m) {
	MES m1, m2;
	int size, price;
	while(!sells.empty() && m.size) {
		m1 = sells.top();
		if(vmes[m1.id].size == 0) {
			sells.pop();
			continue; 
		}
		if(vmes[m1.id].price > m.price) {
			break;
		}
		price = vmes[m1.id].price;
		if(m.size >= vmes[m1.id].size) {
			size = vmes[m1.id].size;
			sells.pop();
		} else {
			size = m.size;
		}
		mpSell[price] -= size;
		m.size -= size;
		vmes[m1.id].size -= size;
		cout << "TRADE " << size << " " << price << endl;
	}
}

void sellMes(MES &m) {
	MES m1, m2;
	int size, price;
	while(!buys.empty() && m.size) {
		m1 = buys.top();
		if(vmes[m1.id].size == 0) {
			buys.pop();
			continue; 
		}
		if(vmes[m1.id].price < m.price) {
			break;
		}
		price = vmes[m1.id].price;
		if(m.size >= vmes[m1.id].size) {
			size = vmes[m1.id].size;
			buys.pop();
		} else {
			size = m.size;
		}
		mpBuy[price] -= size;
		m.size -= size;
		vmes[m1.id].size -= size;
		cout << "TRADE " << size << " " << price << endl;
	}
}

int main() {
	int n, i, j, k;
	int id;
	string s;
	MES m1, m2;
	int size, price;
	bool flag = false; 
	while(cin >> n && n != 0) {
		if(flag == false) {
			flag = true;
		} else {
			cout << endl; 
		}
		priority_queue<MES, vector<MES>, less<MES>> buysT;
		priority_queue<MES, vector<MES>, greater<MES>> sellsT;
		buys = buysT;
		sells = sellsT;
		mpBuy.clear();
		mpSell.clear();
		vmes.clear();
		for(i = 0; i < n; ++i) {
			MES m;
			m.id = i;
			cin >> s;
			if(s == "CANCEL") {
				cin >> id;
				id = id - 1;
				deleteMes(id);
				m.price = 0;
				m.size = 0;
			} else {
				cin >> m.size >> m.price;
				if (s == "BUY") {
					m.bs = 1;
					buyMes(m);
					if(m.size > 0) {
						if(!mpBuy.count(m.price)) {
							mpBuy[m.price] = 0;
						}
						mpBuy[m.price] += m.size;
						buys.push(m);
					}
				} else { //sell
					m.bs = -1;
					sellMes(m);
					if(m.size > 0) {
						if(!mpSell.count(m.price)) {
							mpSell[m.price] = 0;
						}
						mpSell[m.price] += m.size;
						sells.push(m);
					}
				}
			}
			vmes.push_back(m);
			cout << "QUOTE ";
			size = 0; price = 0;
			while(!buys.empty()) {
				m1 = buys.top();
				if(vmes[m1.id].size == 0) {
					buys.pop();
					continue; 
				}
				price = vmes[m1.id].price;
				size =  mpBuy[vmes[m1.id].price];
				break; 
			}
			cout << size << " " << price;
			cout << " - ";
			size = 0; price = 99999;
			while(!sells.empty()) {
				m1 = sells.top();
				if(vmes[m1.id].size == 0) {
					sells.pop();
					continue; 
				}
				price = vmes[m1.id].price;
				size =  mpSell[vmes[m1.id].price];
				break;
			}
			cout << size << " " << price;
			cout << endl; 
		}
	}
	return 0;
}
