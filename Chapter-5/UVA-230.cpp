#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>

using namespace std;

struct book {
	string title;
	string author;
	int has;
	bool operator < (const book &rhs) {
		if(this->author != rhs.author) {
			return this->author < rhs.author;
		} else {
			return this->title < rhs.title;
		}
	}
};

vector<book> v;
map<string, int> mp;

book getBook(string s) {
	book b;
	s = s.substr(1);
	int pos = s.find("\"");
	b.title = s.substr(0, pos);
	b.author = s.substr(pos + 5);
	b.has = 0;
	return b;
}

void shelve() {
	int i;
	string fore = "";
	for(i = 0; i < v.size(); ++i) {
		if(v[i].has == 0) {
			fore = v[i].title;
		}
		if(v[i].has == 2) {
			cout << "Put \"" << v[i].title << "\" ";
			if(fore == "") {
				cout << "first";
			} else {
				cout << "after \"" << fore << "\""; 
			}
			cout << endl;
			v[i].has = 0;
			fore = v[i].title;
		}
	}
	cout << "END" << endl;
}

int main() {
	string s, out;
	book b;
	int i;
	while(getline(cin, s) && s != "END") {
		b = getBook(s);
		v.push_back(b);
	}
	sort(v.begin(), v.end());
	for(i = 0; i < v.size(); ++i) {
		mp[v[i].title] = i;
	}
	while(getline(cin, s) && s != "END") {
		string st = s.substr(0, 6);
		if(st == "SHELVE") {
			shelve();
			continue;
		}
		string name = s.substr(8, s.length() - 9);
		if(st == "BORROW") {
			v[mp[name]].has = 1;
		}
		if(st == "RETURN") {
			v[mp[name]].has = 2;
		}
	}
	return 0;
}
