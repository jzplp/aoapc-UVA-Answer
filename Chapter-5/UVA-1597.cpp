#include<iostream>
#include<map>
#include<vector>
#include<sstream>
#include<set>
#include <algorithm>

using namespace std;

struct DID {
	int doci;
	int linei;
	bool hole;
	bool operator== (const DID &rhs) {
		if (this->doci != rhs.doci) {
			return false;
		}
		if(this->hole && rhs.hole) {
			return true; 
		}
		return this->linei == rhs.linei;
	}
};
vector<vector<string> > docs;
map<string, vector<DID>> mp;
set<string> se = {
	"a", "the", "to", "and", "or", "not" 
};

void getDocs(int i) {
	vector<string> doc;
	string line, word;
	int j, k = 0;
	
	while(getline(cin, line) && line != "**********") {
		doc.push_back(line);
		for(j = 0; j < line.length(); ++j) {
			if(line[j] >= 'A' && line[j] <= 'Z') {
				line[j] = (line[j] - 'A') + 'a';
			}
			if(line[j] < 'a' || line[j] > 'z') {
				line[j] = ' ';
			}
		}
		stringstream ss(line);
		while(ss >> word) {
			if(!se.count(word)) {
				DID d;
				d.doci = i;
				d.linei = k;
				d.hole = false;
				if(!mp.count(word)) {
					mp[word] = vector<DID>();
				}
				mp[word].push_back(d);
			}
		}
		++k;
	}
	docs.push_back(doc);
}
vector<DID> EMPTYVEC;
vector<DID> & getWordVec(string word) {
	if(!mp.count(word)) {
		return EMPTYVEC;
	} else {
		return mp[word]; 
	}
}

void putMPV(const vector<DID> &mpv) {
	if(!mpv.size()) {
		cout << "Sorry, I found nothing." << endl;
		return;
	} 
	int i, j, k;
	for(i = 0; i < mpv.size(); ++i) {
		if(i != 0 && mpv[i].doci != mpv[i-1].doci) {
			cout << "----------" << endl;
		}
		if(mpv[i].hole) {
			k = mpv[i].doci;
			for(j = 0; j < docs[k].size(); ++j) {
				cout << docs[k][j] << endl;
			}
			continue;
		}
		cout << docs[mpv[i].doci][mpv[i].linei] << endl;
	}
}

void getNOT(string word) {
	set<int> vse;
	int i;
	vector<DID> & v = getWordVec(word);
	for(i = 0; i < v.size(); ++i) {
		vse.insert(v[i].doci);
	}
	vector<DID> ve;
	for(i = 0; i < docs.size(); ++i) {
		if(!vse.count(i)) {
			DID d;
			d.doci = i;
			d.linei = 0;
			d.hole = true; 
			ve.push_back(d);
		}
	}
	putMPV(ve);
}

void getAND(vector<DID> &mpv, vector<DID> &mpv1, vector<DID> &mpv2) {
	set<int> vse1, vse2;
	int i;
	for(i = 0; i < mpv1.size(); ++i) {
		vse1.insert(mpv1[i].doci);
	}
	for(i = 0; i < mpv2.size(); ++i) {
		vse2.insert(mpv2[i].doci);
	}
	for(i = 0; i < mpv1.size(); ++i) {
		if(vse2.count(mpv1[i].doci)) {
			mpv.push_back(mpv1[i]);
		}
	}
	for(i = 0; i < mpv2.size(); ++i) {
		if(vse1.count(mpv2[i].doci)) {
			mpv.push_back(mpv2[i]);
		}
	}
}

bool cmp(const DID &lhs, const DID &rhs) {
	if(lhs.doci != rhs.doci) {
		return lhs.doci < rhs.doci;
	}
	return lhs.linei < rhs.linei; 
}

void handleQuery() {
	string query, word;
	int i;
	getline(cin, query);
	stringstream ss(query);
	vector<string> v;
	while(ss >> word) {
		v.push_back(word);
	}
	
	vector<DID> mpv;
	if(v.size() == 1) {
		mpv = getWordVec(v[0]);
	} else if(v.size() == 2) {
		getNOT(v[1]);
		return;
	} else {
		vector<DID> & mpv1 = getWordVec(v[0]), & mpv2 = getWordVec(v[2]);
		if(v[1] == "OR") {
			mpv = mpv1;
			for(i = 0; i < mpv2.size(); ++i) {
				mpv.push_back(mpv2[i]);
			}
		} else { //and
			getAND(mpv, mpv1, mpv2);
		}
	}
	sort(mpv.begin(), mpv.end(), cmp);
	mpv.erase(unique(mpv.begin(), mpv.end()), mpv.end());
	putMPV(mpv);
}

int main() {
	int N, M;
	int i, j, k;
	string s;
	cin >> N;
	getline(cin, s);
	for(i = 0; i < N; ++i) {
		getDocs(i);
	}
	/*
	for(auto bi = mp.begin(); bi !=mp.end(); ++bi) {
		vector<DID> & vt = bi->second;
		sort(vt.begin(), vt.end(), cmp);
		vt.erase(unique(vt.begin(), vt.end()), vt.end());
	}
	*/
	
	cin >> M;
	getline(cin, s);
	while(M--) {
		handleQuery();
		cout << "==========" << endl;
	} 
	return 0;
}
