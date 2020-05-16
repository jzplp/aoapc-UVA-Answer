#include<cstdio>
#include<vector>
using namespace std;

int black_x, black_y;
int x,y;
struct point {
	char c;
	int x, y;
};
vector<point> v;

int sx[4] = {1,0,-1,0};
int sy[4] = {0,1,0,-1};

bool flyBlackGeneral() {
	int i, j;
	for(i=0; i<v.size(); ++i)
		if(v[i].c == 'G') {
			if(black_y == v[i].y) {
				j = i;
				break;
			} else
				return false;
		}
	for(i=0; i<v.size(); ++i) {
		if(i == j)
			continue;
		if(black_y == v[i].y && v[i].x > black_x && v[i].x < v[j].x)
			return false;
	}
	return true;
}

bool flyRedGeneral(int i) {
	int j;
	if(y != v[i].y)
		return false;
	for(j=0; j<v.size(); ++j) {
		if(i == j)
			continue;
		if(y == v[j].y && v[j].x > x && v[j].x < v[i].x)
			return false;
	}
	return true;
}

bool chaript(int i) {
	int j, beg, end;
	if(x != v[i].x && y != v[i].y)
		return false;
	if(x == v[i].x) {
		beg = (y > v[i].y) ? v[i].y : y;
		end = (y > v[i].y) ? y : v[i].y;
	}
	if(y == v[i].y) {
		beg = (x > v[i].x) ? v[i].x : x;
		end = (x > v[i].x) ? x : v[i].x;
	}
	for(j=0; j<v.size(); ++j) {
		if(i == j)
			continue;
		if(x == v[j].x && v[j].y > beg && v[j].y < end)
			return false;
		if(y == v[j].y && v[j].x > beg && v[j].x < end)
			return false;
	}
	return true;
}

int hx[8] = {-2,-2,1,-1, 2,2, 1,-1};
int hy[8] = { 1,-1,2, 2,-1,1,-2,-2};
int hxx[4] = {-1,0,1, 0};
int hyy[4] = { 0,1,0,-1};

bool horse(int i) {
	int j,k,hox,hoy,hoxx,hoyy;
	for(j=0; j<8; ++j) {
		hox = v[i].x + hx[j];
		hoy = v[i].y + hy[j];
		if(x != hox || y != hoy)
			continue;
		hoxx = v[i].x + hxx[j/2];
		hoyy = v[i].y + hyy[j/2];
		for(k=0; k<v.size(); ++k) {
			if(k == i)
				continue;
			if(hoxx == v[k].x && hoyy == v[k].y)
				break;
		}
		if(k != v.size())
			continue;
		return true;
	}
	return false;
}

bool cannon(int i) {
	int j, beg, end, k=0;
	if(x != v[i].x && y != v[i].y)
		return false;
	if(x == v[i].x) {
		beg = (y > v[i].y) ? v[i].y : y;
		end = (y > v[i].y) ? y : v[i].y;
	}
	if(y == v[i].y) {
		beg = (x > v[i].x) ? v[i].x : x;
		end = (x > v[i].x) ? x : v[i].x;
	}
	for(j=0; j<v.size(); ++j) {
		if(i == j)
			continue;
		if(x == v[j].x && v[j].y > beg && v[j].y < end)
			++k;
		if(y == v[j].y && v[j].x > beg && v[j].x < end)
			++k;
	}
	if(k == 1)
		return true;
	return false;
}

int main() {
	int n,i,j;
	point p, ptemp;
	int flag;
	bool eat;
	while(scanf("%d %d %d", &n, &black_x, &black_y) == 3 && n != 0) {
		v.clear();
		for(i=0; i!=n; ++i) {
			scanf(" %c %d %d", &p.c, &p.x, &p.y);
			v.push_back(p);
		}
		if(flyBlackGeneral() == true) {
			puts("NO");
			continue;
		}
		for(i=0; i<4; ++i) {
			x = black_x + sx[i];
			y = black_y + sy[i];
			if(x < 1 || x > 3 || y < 4 || y > 6)
				continue;
			eat = false;
			for(j=0;j<v.size();++j)
				if(x == v[j].x && y == v[j].y) {
					ptemp = v[j];
					v.erase(v.begin()+j);
					eat = true;
					break;
				}
			flag = 0;
			for(j=0; j<v.size(); ++j)
				switch(v[j].c) {
					case 'G':
						flag += flyRedGeneral(j);
						break;
					case 'R':
						flag += chaript(j);
						break;
					case 'H':
						flag += horse(j);
						break;
					case 'C':
						flag += cannon(j);
						break;
				}
			if(flag == 0)
				break;
			if(eat == true) {
				v.push_back(ptemp);
			}
		}
		if(flag == 0)
			puts("NO");
		else
			puts("YES");
	}
	return 0;
}
