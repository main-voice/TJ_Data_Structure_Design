/*项目八  电网建设造价模拟系统*/
/*2053380 彭浩*/


#include <iostream>
#include <limits.h>

//宏定义
#define _DEBUG_   0//是否输出一些调试信息
#define _MAXNUM_  INT_MAX
#define _INSIDE_  1//表示是否在当前最小生成树的顶点集合内
#define _OUTSIDE_ 0
//宏定义结束


//类定义
//表示边的类
class Edge
{
public:
	char m_src, m_dest;//起点与终点
	int  m_weight;//边的权值

	Edge(char src = 0, char dest = 0, int weight = 0)
		:m_src(src), m_dest(dest), m_weight(weight)
	{
		;
	}
	/*bool operator <= (Edge& other) noexcept { return this->m_weight <= other.m_weight; }
	bool operator >= (Edge& other) noexcept { return this->m_weight >= other.m_weight; }
	bool operator < (Edge& other)  noexcept { return this->m_weight < other.m_weight; }
	bool operator > (Edge& other)  noexcept { return this->m_weight > other.m_weight; }*/
};

//表示最小生成树的类，存储顶点信息，边信息，以及最小生成树信息
class Graph_MST
{
private:

	char* m_vex;//顶点表
	int* m_mtx;//邻接矩阵，用于存储边的权值, 使用一维数组，其大小为N x N
	int   m_edge_num;
	int   m_vex_num;

	Edge* a_EdgeNode;//存储最终结果的边值数组

	int   V_Num()const noexcept { return m_vex_num; }
	int   getVextexPos(char vex);
public:
	Graph_MST(int vex_num);//构造函数
	Graph_MST();

	void addNode();//向图中增加顶点
	void addEdge();//向图中增加边,即根据输入去创建邻接矩阵

	void MinSpanTree_Prim();//prim算法创建最小生成树

	void OutPutTree();
	~Graph_MST();
};


//tool function（工具函数声明）

void menu();// 初始化界面
bool check(char& choice);//检测输入是否正确（a-f，大小写不敏感）
//工具函数声明结束

//主函数
int main()
{	
	Graph_MST graph;

	//init
	menu();

	char choice = '0';
	enum CHOICE { add_node, add_edge, creat_MST, print_MST, exit, cls };

	while (1)
	{
		std::cout << "\n请选择操作： ";
		std::cin >> choice;
		check(choice);

		switch (static_cast<int>(choice - 'A'))
		{
		case add_node:
		{
			graph.addNode();
			break;
		}
		case add_edge:
		{
			graph.addEdge();
			break;
		}
		case creat_MST:
		{
			graph.MinSpanTree_Prim();
			break;
		}
		case print_MST:
		{
			graph.OutPutTree();
			break;
		}
		case exit:
		{
			std::cout << "按回车键以退出\n";
			std::cin.get();
			std::cin.get();
			return 0;
			break;
		}
		case cls:
		{
			system("cls");
			menu();
			break;
		}
		default:
		{
			break;
		}
		}

	}

}



//（工具函数实现）
void menu()
{
	using namespace std;
	cout << "*************************************************\n";
	cout << "**                                             **\n";
	cout << "**              电网造价模拟系统               **\n";
	cout << "**                                             **\n";
	cout << "*************************************************\n";
	cout << "**              A/a --- 创建电网顶点           **\n";
	cout << "**              B/b --- 添加电网的边           **\n";
	cout << "**              C/c --- 构造最小生成树         **\n";
	cout << "**              D/d --- 显示最小生成树         **\n";
	cout << "**              E/e --- 退出程序               **\n";
	cout << "**              F/f --- 清屏                   **\n";
	cout << "**                                             **\n";
	cout << "*************************************************\n\n";
}

bool check(char& choice)
{
	if (choice >= 'a' && choice <= 'f')
	{
		choice += 'A' - 'a'; // 统一大小写，只有A-E
		//std::cout << choice;
	}

	while (choice < 'A' || choice > 'F')     // 操作码检测
	{
		std::cout << "输入操作不存在！请重新输入： ";
		std::cin.clear();
		std::cin.ignore(65535, '\n');
		std::cin >> choice;

		if (choice >= 'a' && choice <= 'f')
		{
			choice += 'A' - 'a'; // 统一大小写，只有A-E
			//std::cout << choice;
		}
	}

	return true;
}

inline void print(const char* message) {
	std::cout << message << std::endl;
}
//（工具函数实现结束）


//
//Graph_MST类函数实现

int Graph_MST::getVextexPos(char vex)
{
	for (int i = 0; i < m_vex_num; i++) {
		if (m_vex[i] == vex) {
			return i;
		}
	}
	return -1;
}


Graph_MST::Graph_MST(int vex_num)
{
	m_vex_num = vex_num;
	if (m_vex_num <= 0)
	{
		print("顶点数量小于0，输入错误");
	}
	m_vex = new char[m_vex_num];

	if (m_vex == nullptr)
	{
		print("分配错误，顶点数组为空指针");
	}

	print("请依次输入各顶点的名称：");
	for (int i = 0; i < m_vex_num; i++)
	{
		char temp = 0;
		std::cin >> temp;
		m_vex[i] = temp;
	}
#if _DEBUG_
	for (int i = 0; i < m_vex_num; i++)
	{
		std::cout << m_vex[i] << " ";
	}
#endif

	a_EdgeNode = new Edge[V_Num() - 1];
	if (a_EdgeNode == nullptr)
	{
		print("边值数组分配空间错误！\n");
		return;
	}
}

Graph_MST::Graph_MST()
{
	a_EdgeNode = nullptr;
	m_vex = nullptr;
	m_mtx = nullptr;

	m_edge_num = 0;
	m_vex_num = 0;
}

void Graph_MST::addNode()
{
	std::cout << "请输入顶点的个数： ";
	int nodeNum;
	std::cin >> nodeNum;

	while (std::cin.fail() || nodeNum <= 1)
	{
		std::cout << "输入错误，请输入大于1的正整数： ";
		std::cin.clear();
		std::cin.ignore(6555, '\n');
		std::cin >> nodeNum;
	}
	m_vex_num = nodeNum;
	m_vex = new char[m_vex_num];

	std::cout << "请输入各顶点的名称：\n";

	for (int i = 0; i < m_vex_num; i++) {
		std::cin >> m_vex[i];
	}// 存储结点，建立下标与字符一一对应的关系

	a_EdgeNode = new Edge[V_Num() - 1];
	if (a_EdgeNode == nullptr)
	{
		print("边值数组分配空间错误！\n");
		return;
	}
}

void Graph_MST::addEdge()
{
	if (m_vex_num == 0 && m_vex == nullptr)
	{
		std::cout << "无顶点，创建边关系！请创建顶点：\n";
		addNode();
	}

	char vex_1 = 0, vex_2 = 0;
	int edgeWeight = 0;

	m_mtx = new int[m_vex_num * m_vex_num];

	if (m_mtx == nullptr)
	{
		print("allocation error in addEdge function");
		return;
	}

	for (int i = 0; i < m_vex_num * m_vex_num; i++) {
		m_mtx[i] = _MAXNUM_;
	}

	for (int i = 0; i < m_vex_num; i++)
	{
		m_mtx[i * m_vex_num + i] = 0;
	}
	while (1)
	{
		print("\n请输入两个顶点及边的权值:");
		std::cin >> vex_1;
		std::cin >> vex_2;
		std::cin >> edgeWeight;

		//输入终止条件 ： ? ? 0
		if (vex_1 == '?' && vex_2 == '?' && edgeWeight == 0) {
			break;
		}

		
		if (std::cin.fail()||edgeWeight <= 0) {
			print("权值输入错误，权值应该是大于0的正整数，请重新输入:\n");
			std::cin.clear();
			std::cin.ignore(65535, '\n');
			continue;
		}

		//x and y represent the position in the matrix
		int x = getVextexPos(vex_1);
		int y = getVextexPos(vex_2);

		if (x == y) {
			print("顶点输入重复，请重新输入\n");
			std::cin.clear();
			std::cin.ignore(65535, '\n');
			continue;
		}

		if (x == -1 || y == -1) {
			print("顶点不存在！请重新输入顶点");
			std::cin.clear();
			std::cin.ignore(65535, '\n');
			continue;
		}

		if (m_mtx[x * m_vex_num + y] != _MAXNUM_)
		{
			print("这两个顶点已经输入过，确定要更新路径吗？(默认更新)(y--yes/n--no)");
			char if_not = '0';
			std::cin >> if_not;
			if (if_not == 'n')
			{
				continue;//不更新，直接输入下一对顶点
			}
		}
		m_mtx[x * m_vex_num + y] = edgeWeight;
		m_mtx[y * m_vex_num + x] = edgeWeight;

		m_edge_num++;
	}

#if _DEBUG_
	for (int i = 0; i < m_vex_num * m_vex_num; i++) {
		std::cout << m_mtx[i] << " ";
		if ((i + 1) % m_vex_num == 0) {
			std::cout << std::endl;
		}
	}
#endif

}

void Graph_MST::MinSpanTree_Prim()
{
	if (m_vex_num == 0 && m_vex == nullptr)
	{
		std::cout << "无顶点与边，请创建顶点与边：\n";
		addNode();
		addEdge();
	}
	else if (m_edge_num == 0 && m_mtx == nullptr)
	{
		std::cout << "无边关系，请先创建边关系：\n";
		addEdge();
	}


	print("请输入最小生成树的起始顶点： \n");
	char charStart;// 起始点
	std::cin >> charStart;

	while (getVextexPos(charStart) == -1)// 起始顶点测试
	{
		print("你输入的起始顶点不存在，请重新输入：\n");
		std::cin >> charStart;
	}

	int startV = getVextexPos(charStart);   // 起始顶点号

	int* lowcost = new int[V_Num()]; //lowcost[j]表示这两个点之间边的权值
	int* closest = new int[V_Num()];//closest[j]表示V-U中的节点j到集合U中的最临近点
	bool* inside = new bool[V_Num()];//inside[i]表示第i个节点是否在集合里面

	//init
	for (int i = 0; i < V_Num(); i++)
	{
		inside[i] = _OUTSIDE_;//初始都在外面（U_V集合）

		if (i != startV)
		{
			lowcost[i] = m_mtx[startV * V_Num() + i];
			closest[i] = startV;
		}
	}

	lowcost[startV] = 0;
	inside[startV] = _INSIDE_;

	int count = 0;             // 计数

	for (int i = 1; i < V_Num(); i++)
	{
		int minWeight = _MAXNUM_;
		int v = startV;

		for (int i = 0; i < V_Num(); i++) {//找到U与U_V之间最短路径以及该路径的终点
			if (inside[i] == _OUTSIDE_ && lowcost[i] < minWeight)
			{
				v = i;
				minWeight = lowcost[i];
			}
		}

		if (v != startV)
		{
			Edge e(m_vex[closest[v]], m_vex[v], minWeight);

#if _DEBUG_
			std::cout << m_vex[closest[v]] << " and "
				<< m_vex[v] << " (whose weight is) "
				<< minWeight << " have been placed\n";
#endif

			a_EdgeNode[count] = e;
			count++;
			inside[v] = _INSIDE_;

			for (int k = 0; k < V_Num(); k++)
			{
				if (inside[k] == _OUTSIDE_ && m_mtx[v * V_Num() + k] < lowcost[k])
				{
					lowcost[k] = m_mtx[v * V_Num() + k];
					closest[k] = v;
				}
			}
		}

	}

	std::cout << "生成Prim最小生成树！\n";

	delete[] lowcost;
	delete[] closest;
	delete[] inside;
}

Graph_MST::~Graph_MST()
{
	if (m_mtx)
		delete[]m_mtx;

	if (m_vex)
		delete[]m_vex;

	if (a_EdgeNode)
		delete[]a_EdgeNode;
}

void Graph_MST::OutPutTree()
{
	for (int i = 0; i < V_Num() - 1; i++)
		std::cout << a_EdgeNode[i].m_src << " -<"
		<< a_EdgeNode[i].m_weight << ">-> "
		<< a_EdgeNode[i].m_dest << "     ";
	print("\n");
}

//Graph_MST实现结束