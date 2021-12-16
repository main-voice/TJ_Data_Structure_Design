/*��Ŀ��  �����������ģ��ϵͳ*/
/*2053380 ���*/


#include <iostream>
#include <limits.h>

//�궨��
#define _DEBUG_   0//�Ƿ����һЩ������Ϣ
#define _MAXNUM_  INT_MAX
#define _INSIDE_  1//��ʾ�Ƿ��ڵ�ǰ��С�������Ķ��㼯����
#define _OUTSIDE_ 0
//�궨�����


//�ඨ��
//��ʾ�ߵ���
class Edge
{
public:
	char m_src, m_dest;//������յ�
	int  m_weight;//�ߵ�Ȩֵ

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

//��ʾ��С���������࣬�洢������Ϣ������Ϣ���Լ���С��������Ϣ
class Graph_MST
{
private:

	char* m_vex;//�����
	int* m_mtx;//�ڽӾ������ڴ洢�ߵ�Ȩֵ, ʹ��һά���飬���СΪN x N
	int   m_edge_num;
	int   m_vex_num;

	Edge* a_EdgeNode;//�洢���ս���ı�ֵ����

	int   V_Num()const noexcept { return m_vex_num; }
	int   getVextexPos(char vex);
public:
	Graph_MST(int vex_num);//���캯��
	Graph_MST();

	void addNode();//��ͼ�����Ӷ���
	void addEdge();//��ͼ�����ӱ�,����������ȥ�����ڽӾ���

	void MinSpanTree_Prim();//prim�㷨������С������

	void OutPutTree();
	~Graph_MST();
};


//tool function�����ߺ���������

void menu();// ��ʼ������
bool check(char& choice);//��������Ƿ���ȷ��a-f����Сд�����У�
//���ߺ�����������

//������
int main()
{	
	Graph_MST graph;

	//init
	menu();

	char choice = '0';
	enum CHOICE { add_node, add_edge, creat_MST, print_MST, exit, cls };

	while (1)
	{
		std::cout << "\n��ѡ������� ";
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
			std::cout << "���س������˳�\n";
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



//�����ߺ���ʵ�֣�
void menu()
{
	using namespace std;
	cout << "*************************************************\n";
	cout << "**                                             **\n";
	cout << "**              �������ģ��ϵͳ               **\n";
	cout << "**                                             **\n";
	cout << "*************************************************\n";
	cout << "**              A/a --- ������������           **\n";
	cout << "**              B/b --- ��ӵ����ı�           **\n";
	cout << "**              C/c --- ������С������         **\n";
	cout << "**              D/d --- ��ʾ��С������         **\n";
	cout << "**              E/e --- �˳�����               **\n";
	cout << "**              F/f --- ����                   **\n";
	cout << "**                                             **\n";
	cout << "*************************************************\n\n";
}

bool check(char& choice)
{
	if (choice >= 'a' && choice <= 'f')
	{
		choice += 'A' - 'a'; // ͳһ��Сд��ֻ��A-E
		//std::cout << choice;
	}

	while (choice < 'A' || choice > 'F')     // ��������
	{
		std::cout << "������������ڣ����������룺 ";
		std::cin.clear();
		std::cin.ignore(65535, '\n');
		std::cin >> choice;

		if (choice >= 'a' && choice <= 'f')
		{
			choice += 'A' - 'a'; // ͳһ��Сд��ֻ��A-E
			//std::cout << choice;
		}
	}

	return true;
}

inline void print(const char* message) {
	std::cout << message << std::endl;
}
//�����ߺ���ʵ�ֽ�����


//
//Graph_MST�ຯ��ʵ��

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
		print("��������С��0���������");
	}
	m_vex = new char[m_vex_num];

	if (m_vex == nullptr)
	{
		print("������󣬶�������Ϊ��ָ��");
	}

	print("�������������������ƣ�");
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
		print("��ֵ�������ռ����\n");
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
	std::cout << "�����붥��ĸ����� ";
	int nodeNum;
	std::cin >> nodeNum;

	while (std::cin.fail() || nodeNum <= 1)
	{
		std::cout << "����������������1���������� ";
		std::cin.clear();
		std::cin.ignore(6555, '\n');
		std::cin >> nodeNum;
	}
	m_vex_num = nodeNum;
	m_vex = new char[m_vex_num];

	std::cout << "���������������ƣ�\n";

	for (int i = 0; i < m_vex_num; i++) {
		std::cin >> m_vex[i];
	}// �洢��㣬�����±����ַ�һһ��Ӧ�Ĺ�ϵ

	a_EdgeNode = new Edge[V_Num() - 1];
	if (a_EdgeNode == nullptr)
	{
		print("��ֵ�������ռ����\n");
		return;
	}
}

void Graph_MST::addEdge()
{
	if (m_vex_num == 0 && m_vex == nullptr)
	{
		std::cout << "�޶��㣬�����߹�ϵ���봴�����㣺\n";
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
		print("\n�������������㼰�ߵ�Ȩֵ:");
		std::cin >> vex_1;
		std::cin >> vex_2;
		std::cin >> edgeWeight;

		//������ֹ���� �� ? ? 0
		if (vex_1 == '?' && vex_2 == '?' && edgeWeight == 0) {
			break;
		}

		
		if (std::cin.fail()||edgeWeight <= 0) {
			print("Ȩֵ�������ȨֵӦ���Ǵ���0��������������������:\n");
			std::cin.clear();
			std::cin.ignore(65535, '\n');
			continue;
		}

		//x and y represent the position in the matrix
		int x = getVextexPos(vex_1);
		int y = getVextexPos(vex_2);

		if (x == y) {
			print("���������ظ�������������\n");
			std::cin.clear();
			std::cin.ignore(65535, '\n');
			continue;
		}

		if (x == -1 || y == -1) {
			print("���㲻���ڣ����������붥��");
			std::cin.clear();
			std::cin.ignore(65535, '\n');
			continue;
		}

		if (m_mtx[x * m_vex_num + y] != _MAXNUM_)
		{
			print("�����������Ѿ��������ȷ��Ҫ����·����(Ĭ�ϸ���)(y--yes/n--no)");
			char if_not = '0';
			std::cin >> if_not;
			if (if_not == 'n')
			{
				continue;//�����£�ֱ��������һ�Զ���
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
		std::cout << "�޶�����ߣ��봴��������ߣ�\n";
		addNode();
		addEdge();
	}
	else if (m_edge_num == 0 && m_mtx == nullptr)
	{
		std::cout << "�ޱ߹�ϵ�����ȴ����߹�ϵ��\n";
		addEdge();
	}


	print("��������С����������ʼ���㣺 \n");
	char charStart;// ��ʼ��
	std::cin >> charStart;

	while (getVextexPos(charStart) == -1)// ��ʼ�������
	{
		print("���������ʼ���㲻���ڣ����������룺\n");
		std::cin >> charStart;
	}

	int startV = getVextexPos(charStart);   // ��ʼ�����

	int* lowcost = new int[V_Num()]; //lowcost[j]��ʾ��������֮��ߵ�Ȩֵ
	int* closest = new int[V_Num()];//closest[j]��ʾV-U�еĽڵ�j������U�е����ٽ���
	bool* inside = new bool[V_Num()];//inside[i]��ʾ��i���ڵ��Ƿ��ڼ�������

	//init
	for (int i = 0; i < V_Num(); i++)
	{
		inside[i] = _OUTSIDE_;//��ʼ�������棨U_V���ϣ�

		if (i != startV)
		{
			lowcost[i] = m_mtx[startV * V_Num() + i];
			closest[i] = startV;
		}
	}

	lowcost[startV] = 0;
	inside[startV] = _INSIDE_;

	int count = 0;             // ����

	for (int i = 1; i < V_Num(); i++)
	{
		int minWeight = _MAXNUM_;
		int v = startV;

		for (int i = 0; i < V_Num(); i++) {//�ҵ�U��U_V֮�����·���Լ���·�����յ�
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

	std::cout << "����Prim��С��������\n";

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

//Graph_MSTʵ�ֽ���