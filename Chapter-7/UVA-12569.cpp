#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;

int n, m, s, t;
vector<int> graph[20];
// 0 空白 1 石头 2 机器人
int vertices[20];
bool foundFlag;

int paths[400000];

struct Path
{
  bool has;     // 是否已经访问过
  int preNode;  // 上一个节点的二进制值
  int preRobot; // 上一个节点的机器位置
  int stepBeg;  // 这一步起点
  int stepEnd;  // 这一步终点
};

struct Node
{
  int node;     // 节点的二进制值
  int robot;    // 节点的机器位置
  int stepBeg;  // 这一步起点
  int stepEnd;  // 这一步终点
  int num;      // 当前步数
  int preNode;  // 上一个节点的二进制值
  int preRobot; // 上一个节点的机器位置
};

queue<Node> qu;

// 是否访问过这个状态
Path mp[40000][16];

void setPaths(Node no)
{
  int i, j, k;
  Path p = mp[no.node][no.robot];
  for (i = no.num - 1; i >= 0; --i)
  {
    paths[i] = p.stepBeg + p.stepEnd * 20;
    p = mp[p.preNode][p.preRobot];
  }
}

int setRawVertices()
{
  int num = 0;
  for (int i = 0; i < n; ++i)
  {
    if (vertices[i] == 1)
      num = num * 2 + 1;
    else
      num = num * 2;
  }
  return num;
}

void getRawVertices(int node, int robot)
{
  int a, b;
  for (int i = n - 1; i >= 0; --i)
  {
    a = node % 2;
    node = node / 2;
    vertices[i] = a;
  }
  vertices[robot] = 2;
}

Node bfs()
{
  int i, j, jp, k;
  Node no = {setRawVertices(), s, 0, 0, 0, 0, 0};
  qu.push(no);
  while (qu.size())
  {
    no = qu.front();
    qu.pop();
    if (mp[no.node][no.robot].has)
      continue;
    mp[no.node][no.robot] = {true, no.preNode, no.preRobot, no.stepBeg, no.stepEnd};
    if (no.robot == t)
    {
      foundFlag = true;
      return no;
    }
    getRawVertices(no.node, no.robot);
    for (i = 0; i < n; ++i)
    {
      if (!vertices[i])
        continue;
      for (jp = 0; jp < graph[i].size(); ++jp)
      {
        j = graph[i][jp];
        if (vertices[j])
          continue;
        vertices[j] = vertices[i];
        vertices[i] = 0;
        Node newNode = {
            setRawVertices(),
            (i == no.robot ? j : no.robot),
            i, j, no.num + 1, no.node, no.robot};
        qu.push(newNode);
        // 改回去
        vertices[i] = vertices[j];
        vertices[j] = 0;
      }
    }
  }
  return {};
}

int main()
{
  int T, i, j, k = 0, a, b;
  scanf("%d", &T);
  while (++k <= T)
  {
    for (i = 0; i < 20; ++i)
      graph[i].clear();
    queue<Node>().swap(qu);
    memset(vertices, 0, sizeof(vertices));
    memset(mp, 0, sizeof(mp));
    memset(paths, 0, sizeof(paths));
    foundFlag = false;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    s = s - 1;
    t = t - 1;
    for (i = 0; i < m; ++i)
    {
      scanf("%d", &a);
      vertices[a - 1] = 1;
    }
    vertices[s] = 2;
    for (i = 1; i < n; ++i)
    {
      scanf("%d %d", &a, &b);
      a = a - 1;
      b = b - 1;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }
    if (s == t)
    {
      printf("Case %d: 0\n\n", k);
      continue;
    }
    Node no = bfs();
    if (!foundFlag)
    {
      printf("Case %d: -1\n\n", k);
      continue;
    }
    setPaths(no);
    printf("Case %d: %d\n", k, no.num);
    for (i = 0; i < no.num; ++i)
      printf("%d %d\n", paths[i] % 20 + 1, paths[i] / 20 + 1);
    putchar('\n');
  }

  return 0;
}
