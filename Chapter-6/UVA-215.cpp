#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
 
using namespace std;
 
struct Pos {
  int row, column;
};
 
struct Cell {
  // 1 纯数字 3 引用公式 
  int type;
  // 公式
  string express;
  // 值
  int value;
  // 公式中的引用
  vector<Pos> parents;
};
 
int rows, columns;
Cell arr[25][25];
 
void clearData() {
  int i, j, k;
  for(i = 0; i < 25; ++i) {
    for(j = 0; j < 25; ++j) {
      arr[i][j] = Cell();
    }
  }
}
 
void initCell(int row, int column) {
  int i, j, k, a, b, plus, v;
  // 引用
  Cell &ce = arr[row][column];
  i = 0;
  // 找出所有引用
  while(i < ce.express.length()) {
    if(ce.express[i] >= 'A' && ce.express[i] <= 'T') {
      a = ce.express[i] - 'A' + 1;
      ++i;
      b = ce.express[i] - '0' + 1;
      ce.parents.push_back({a, b});
    }
    ++i;
  }
  ce.type = 3;
}
 
void computedCell(int row, int column) {
  Cell &ce = arr[row][column];
  int i, j, k, plus, v, a, b;
  // 判断是否所有父亲都已经被计算了
  for(k = 0; k < ce.parents.size(); ++k) {
    if(arr[ce.parents[k].row][ce.parents[k].column].type == 3) {
      return;
    }
  }
  // 计算本级值
  // 无引用的情况下，计算值
  k = 0; i = 0; plus = 1; v = 0;
   while(i < ce.express.length()) {
    if(ce.express[i] == ' ') break;
    if(ce.express[i] >= 'A' && ce.express[i] <= 'T') {
      a = ce.express[i] - 'A' + 1;
      ++i;
      b = ce.express[i] - '0' + 1;
      v += plus * arr[a][b].value;
      ++i; continue;
    }
    if(ce.express[i] >= '0' && ce.express[i] <= '9') {
      if(k == 0) k = ce.express[i] - '0';
      else k = k * 10 + ce.express[i] - '0';
      ++i; continue;
    }
    v = v + plus * k;
    k = 0;
    if(ce.express[i] == '-') {
      plus = -1;
    }
    if(ce.express[i] == '+') {
      plus = 1;
    }
    ++i;
  }
  if(k != 0) {
    v = v + plus * k;
    k = 0;
  }
  ce.value = v;
  ce.type = 1;
}
 
int main() {
  int i, j, k;
  bool flag;
  while(scanf("%d %d", &rows, &columns) == 2 && rows != 0) {
    clearData();
    for(i = 1; i <= rows; ++i) {
      for(j = 1; j <= columns; ++j) {
        cin >> arr[i][j].express;
        // 计算初始值
        initCell(i, j);
      }
    }
    for(k = 0; k < rows * columns; ++k) {
      for(i = 1; i <= rows; ++i) {
        for(j = 1; j <= columns; ++j) {
          if(arr[i][j].type == 3) {
            computedCell(i, j);
          }
        }
      }
    }
    flag = false;
    for(i = 1; i <= rows; ++i) {
      for(j = 1; j <= columns; ++j) {
        if(arr[i][j].type == 3) {
          flag = true;
          printf("%c%d: %s\n", 'A' + i - 1, j - 1, arr[i][j].express.c_str());
        }
      }
    }
    if(flag == true) {
      putchar('\n');
      continue;
    }
    printf(" ");
    for(i = 1; i <= columns; ++i) printf("%6d", i-1);
    putchar('\n');
    for(i = 1; i <= rows; ++i) {
      printf("%c", 'A' + i - 1);
      for(j = 1; j <= columns; ++j) {
        printf("%6d", arr[i][j].value);
      }
      putchar('\n');
    }
    putchar('\n');
  }
  return 0;
}
