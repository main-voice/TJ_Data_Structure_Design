/*��Ŀ��  �´��Թ���Ϸ*/
/*2053380 ���*/


#include <iostream>
#include <fstream>
#include <string>

const int DIRECTION[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
const int DirectionNumber = 4;
const int defaultMapRow = 7;
const int defaultMapCol = 7;

// \����������һ��
const std::string defaultMap =
"# # # # # # #\n\
# 0 # 0 0 0 #\n\
# 0 # 0 # # #\n\
# 0 0 0 # 0 #\n\
# 0 # 0 0 0 #\n\
# 0 # 0 # 0 #\n\
# # # # # # #\n\
";

//�����Ϣ��
class Log//���ڵ��������Ϣ����,����Ҫʵ����
{
private:
	Log() = delete;
	Log(const Log&) = delete;
	Log(Log&&) = delete;

public:
	static void Error(const char* message) {
		std::cout << "[ERROR]" << message << std::endl;
	}

	static void Warn(const char* message) {
		std::cout << "[WARNING]" << message << std::endl;
	}

	static void Info(const char* message) {
		std::cout << "[INFO]" << message << std::endl;
	}
};

//�Թ��ඨ��
class Stack;
struct Position;//for the entrance position
class Maze
{
public:
	Maze(int row, int col)
		:m_row(row), m_col(col) {
		;
	}

	Maze() { m_row = m_col = 0; }//default constructor

	~Maze() {
		delete[] m_pMaze;
		delete[] m_mark;
	}

	//initialize this object with the file name
	bool initMaze(const char* mapFileName);
	bool initMaze(std::string mapFile);


	//find the way to get out the maze, the infomation is stored in the path stack
	//(�ҵ��Թ�·������·����Ϣ�洢��path��stack�У�
	//ertrance��������꣬exit�ǳ������꣬current�ǵ�ǰλ��
	bool seekPath(Stack& path, Position entrance, Position exit, Position current);

private:
	int   m_row;
	int   m_col;
	char* m_pMaze;
	bool* m_mark;//���һ��λ���Ƿ��Ѿ���̽����(Mark whether a location has been explored)
};

//��ʾ����Ľṹ��
struct Position {
	int x;
	int y;
	Position(int ix, int iy) {
		x = ix, y = iy;
	}
	Position() {
		x = 0, y = 0;
	}

	friend std::istream& operator>>(std::istream& input, Position& S);
};
//�ṹ����������

//ջ
struct PosNode 
{
public:
	PosNode(int ix, int iy)
		:x(ix), y(iy) {
		;
	}
	PosNode() { x = 0, y = 0; }
	int x;
	int y;
	PosNode* next;
};

class Stack
{
public:
	Stack();
	bool isEmpty();
	bool pop(PosNode& x);
	void push(const PosNode& x);
	void outPut();
private:
	PosNode* m_top;
};
//ջ��������


// ���ߺ�������
static bool checkNumber(int& input);

//�������ֵ��y/YΪyes��n/NΪno
static bool YesOrNo(char& yes);
//���ߺ�����������




int main()
{
	using namespace std;
	Stack path;
	Maze  maze(defaultMapRow, defaultMapCol);

	cout << "Ĭ�ϵ�ͼΪ:\n" << endl;
	cout << defaultMap << endl;

	maze.initMaze(defaultMap);
	

	cout << "��������㣨Ĭ�ϵ�ͼ�����Ϊ(1,1)\n";
	Position entrance;
	cin >> entrance;

	cout << "�������յ㣨Ĭ�ϵ�ͼ�����Ϊ(5,5)\n";
	Position exit;
	cin >> exit;


	std::cout << "�Թ�·��Ϊ��\n";

	maze.seekPath(path, entrance, exit, entrance);
	path.outPut();

	std::cout << "\n\n���س������˳�\n";
	std::cin.get();
	std::cin.get();
	return 0;
}


// --- ���ߺ���ʵ�� ---
static bool checkNumber(int& input)
{
	while (std::cin.fail() || input < 0) {
		std::cout << "��������!����������\n";
		std::cin.clear();
		std::cin.ignore(65535, '\n');
		std::cin >> input;
	}
	return true;
}

static bool YesOrNo(char& yes)
{
	while (1)
	{
		if (yes == 'y' || yes == 'Y')
		{
			return true;
		}
		else if (yes == 'n' || yes == 'N')
		{
			return false;
		}
		else
		{
			std::cout << "�����������������\n";
			std::cin >> yes;
		}
	}
}
// --- ���ߺ���ʵ�ֽ��� ---


// --- �Թ���ʵ�� --- 

bool Maze::initMaze(const char* mapFileName)
{
	if (m_col < 1 || m_row < 1) {
		Log::Warn("column or row is zero! An invalid maze");
		return false;
	}
	m_pMaze = new char[m_col * m_row];
	m_mark = new bool[m_col * m_row];

	if (m_pMaze == nullptr) {
		Log::Error("p_maze is nullptr in the function initMaze");
		return false;
	}
	if (m_mark == nullptr) {
		Log::Error("p_mark is nullptr in the function initMaze");
		return false;
	}

	char* temp = m_pMaze;

	std::ifstream maze;
	maze.open(mapFileName, std::ios::in);
	if (!maze) {
		Log::Warn("NULL FILE in the function initMaze");
		return false;
	}

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++) {
			maze >> *(temp + i * m_row + j);
			*(m_mark + i * m_row + j) = 0;
		}


	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			std::cout << *temp << ' ';
			temp++;
		}
		std::cout << "\n";
	}
	maze.close();
	return true;
}

bool Maze::initMaze(std::string mapFile)
{

	if (m_col < 1 || m_row < 1) {
		Log::Warn("column or row is zero! An invalid maze");
		return false;
	}

	m_pMaze = new char[m_col * m_row];
	m_mark = new bool[m_col * m_row];

	if (m_pMaze == nullptr) {
		Log::Error("p_maze is nullptr in the function initMaze");
		return false;
	}
	if (m_mark == nullptr) {
		Log::Error("p_mark is nullptr in the function initMaze");
		return false;
	}

	size_t index = 0;

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++) {
			if (mapFile[index] == '\n' || mapFile[index] == ' ') {
				index++;
				j--;
				continue;
			}
			*(m_pMaze + i * m_row + j) = mapFile[index];
			index++;
			*(m_mark + i * m_row + j) = 0;
		}

	char* mapStart = m_pMaze;
#if 0
	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			std::cout << *mapStart << ' ';
			mapStart++;
		}
		std::cout << "\n";
	}
#endif
	return true;

}

bool Maze::seekPath(Stack& path, Position entrance, Position exit, Position current)
{
	int next_row = 0, next_col = 0;

	if (current.x == exit.x && current.y == exit.y)
	{//the current position is the destination
		std::cout << "(" << entrance.x << "," << entrance.y << ")";
		return true;
	}

	for (int i = 0, currentOffset = 0; i < DirectionNumber; i++)
	{
		current.x = next_row = current.x + DIRECTION[i][0];
		current.y = next_col = current.y + DIRECTION[i][1];
		currentOffset = next_row * m_col + next_col;

		if (*(m_pMaze + currentOffset) == '0' && *(m_mark + currentOffset) == 0)
		{

			*(m_mark + currentOffset) = 1;
			*(m_pMaze + currentOffset) = 'x';
			if (seekPath(path, entrance, exit, current))
			{
				path.push(PosNode(next_row, next_col));
				return true;
			}
		}
	}

	if (current.x == entrance.x && current.y == entrance.y)
	{
		std::cout << "û����Ч·����\n";
	}
	return false;
}


std::istream& operator>>(std::istream& input, Position& Pos)
{
	using namespace std;
	cout << "������x����" << endl;
	cin >> Pos.x;
	checkNumber(Pos.x);

	cout << "������y����" << endl;
	cin >> Pos.y;
	checkNumber(Pos.y);
	return input;
}

// --- �Թ���ʵ�ֽ��� ---


// --- ջ��ʵ�� --- 
void Stack::push(const PosNode& x)
{
	PosNode* newNode = new PosNode(x);
	if (newNode == NULL) {
		std::cout << "the newNode is NULL in stack's push\n";
		return;
	}
	newNode->next = m_top;
	m_top = newNode;
}
void Stack::outPut()
{
	PosNode* p = m_top;
	while (p->next != NULL) {
		std::cout << " ---> (" << p->x << "," << p->y << ") ";
		p = p->next;
	}
}
Stack::Stack()
{
	m_top = new PosNode;
	m_top->next = NULL;
}
bool Stack::isEmpty()
{
	return (m_top == NULL);
}

bool Stack::pop(PosNode& temp_store)
{
	if (isEmpty()) { return false; }
	temp_store.x = m_top->x;
	temp_store.y = m_top->y;

	PosNode* p = m_top;
	m_top = m_top->next;
	delete p;
	return true;
}

// --- ջʵ�ֽ��� ---
