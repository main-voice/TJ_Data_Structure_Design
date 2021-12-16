/*项目二  约瑟夫生者死者游戏*/
/*2053380 彭浩*/

#include <iostream>
#include <iomanip>

#define  Cout std::cout
#define  Cin std::cin

// --- 链表成员类 ---
class Passenger
{
public:
	int		   m_pos;
	Passenger* m_next;

public:
	void setPos(int pos) { m_pos = pos; }
	Passenger() { ; }
	Passenger(int pos);
};

// --- 链表类 ---
class LinkList
{
public:
	LinkList();
	~LinkList() {
		makeEmpty();
		delete m_head;
	}

	void makeEmpty();
	int  Length()const;

	void initList(int number);
	void Output();

	Passenger* Locate(int i);
	Passenger* getHead()const { return m_head; }
	bool Remove(Passenger* target, Passenger& x);
	bool Remove(int i, Passenger& x);
	//the x is the element that is removed
private:
	Passenger* m_head;
};

//输出信息类
class Log//用于调试输出信息的类,不需要实例化
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

//类定义结束

//---工具函数，输入基本信息---
void Input(int& peopleNum, int& initPos, int& deadNum, int& aliveNum);

int main()
{

	Cout << "现有N人围成一圈，从第S个人开始报数，报M的人出局，再由下一个人开始报数，如此循环，直到剩下K个人为止\n";
	int peopleNum = 0, initPos = 0, deadNum = 0, aliveNum = 0;

	while (true)
	{
		Input(peopleNum, initPos, deadNum, aliveNum);
		const int circleNum = peopleNum - aliveNum;

		Cout << "\n";

		LinkList linkList;
		linkList.initList(peopleNum);//so everyone has a position

		int count = 1;//begin with the number one

		Passenger temp;//store the element that is removed temporarily
		Passenger* current = linkList.Locate(initPos);


		for (int i = 0; i < circleNum; )
		{
			if (current == linkList.getHead()) {
				current = current->m_next;
			}
			if (count == deadNum)
			{
				Passenger* keepData = current->m_next;
				linkList.Remove(current, temp);

				Cout << "第" << std::setw(3) << std::setfill(' ') <<
					std::setiosflags(std::ios::left) << i + 1
					<< "个死者位置是:" << std::setw(4) << temp.m_pos << std::endl;

				i++;//when a people die, you can actually go on the next circle
				count = 1;//start with number one
				current = keepData;

				continue;
			}
			current = current->m_next;
			if (current == linkList.getHead()) {
				current = current->m_next;
			}
			count++;
		}
		Cout << "最后剩下" << aliveNum << "人\n";
		linkList.Output();

		while (1)
		{
			Cout << "是否退出？（Y/y)--Yes, (N/n)--No\n";
			char ifExit;
			Cin >> ifExit;
			if (ifExit == 'y' || ifExit == 'Y')
			{
				std::cout << "按回车键以退出\n";
				std::cin.get();
				std::cin.get();
				return 0;
			}
			else if (ifExit == 'n' || ifExit == 'N')
			{
				break;
			}
			else
			{
				continue;
			}
		}

	}


	std::cout << "按回车键以退出\n";
	std::cin.get();
	std::cin.get();

	return 0;
}

//---工具函数实现---
void Input(int& peopleNum, int& initPos, int& deadNum, int& aliveNum)
{
	Cout << "请输入生死游戏的总人数N：";
	Cin >> peopleNum;
	while (Cin.fail() || peopleNum < 1)
	{
		Cout << "输入错误，请重新输入！\n";
		Cin.clear();
		Cin.ignore(65535, '\n');
		Cin >> peopleNum;
	}

	Cout << "请输入游戏开始的位置S：  ";
	Cin >> initPos;
	while (Cin.fail() || initPos < 1 || initPos > peopleNum)
	{
		Cout << "输入错误，请重新输入！\n";
		Cin.clear();
		Cin.ignore(65535, '\n');
		Cin >> initPos;
	}

	Cout << "请输入死亡数字M：        ";
	Cin >> deadNum;
	while (Cin.fail() || deadNum < 1)
	{
		Cout << "输入错误，请重新输入！\n";
		Cin.clear();
		Cin.ignore(65535, '\n');
		Cin >> deadNum;
	}

	Cout << "请输入剩余的生者人数K：  ";
	Cin >> aliveNum;
	while (Cin.fail() || aliveNum < 1 || aliveNum >= peopleNum)
	{
		Cout << "输入错误，请重新输入！\n";
		Cin.clear();
		Cin.ignore(65535, '\n');
		Cin >> aliveNum;
	}
}


// --- 链表类实现 ---

Passenger::Passenger(int pos)
{
	this->setPos(pos);
}

LinkList::LinkList()
{
	m_head = new Passenger;
	m_head->m_next = m_head;//a single circle linked list
}

void LinkList::makeEmpty()
{
	Passenger* current = NULL;
	while (m_head->m_next != m_head) {
		current = m_head->m_next;
		m_head->m_next = current->m_next;
		delete current;
	}
}

int LinkList::Length() const
{
	Passenger* current = m_head->m_next;
	int count = 0;
	while (current != m_head) {
		count++;
		current = current->m_next;
	}
	return count;
}

void LinkList::initList(int number)
{
	Passenger* last = m_head;
	for (int i = 0; i < number; i++)
	{
		Passenger* newNode = new Passenger(i + 1);
		last->m_next = newNode;
		last = newNode;
		last->m_next = m_head;
	}
}

void LinkList::Output()
{
	Passenger* current = m_head->m_next;
	if (NULL == current) {
		Log::Warn("The list in the Output function is empty!");
	}

	Cout << "剩余的生者位置是: \n";
	int count = 0;
	while (current != m_head)
	{
		Cout << std::setw(5) << current->m_pos;
		if (0 == (count + 1) % 5) { Cout << '\n'; }
		current = current->m_next;
		count++;
	}
	Cout << '\n';
}

Passenger* LinkList::Locate(int i)
{
	if (i < 0) {
		Log::Warn("i is too small in Locate function!");
		return NULL;
	}
	else if (i == 0) {
		return m_head;
	}
	else if (i > this->Length()) {
		Log::Warn("i is too big in Locate function!");
		return NULL;
	}

	Passenger* current = m_head->m_next;
	int count = 1;
	while (current != m_head && count < i) {
		count++;
		current = current->m_next;
	}
	return current;
}

bool LinkList::Remove(Passenger* target, Passenger& x)
{

	Passenger* former = m_head->m_next;
	if (target == NULL || former == NULL) {
		Log::Error("the target and its former is empty in remove function!");
	}

	if (former == target) {//you delete the first object
		m_head->m_next = former->m_next;
		x.m_pos = former->m_pos;;
		//x = former->next 
		//wtf, there is a totally new object created here and it call the construction, so you can use a integer to assign a Passenger object
		delete target;
		return true;
	}

	while ((former->m_next != target) && former != m_head)
	{
		former = former->m_next;
	}
	auto target_temp = former->m_next;

	if (NULL == target_temp || NULL == former) {
		Log::Error("target and its former are NULL in Remove function!");
		return false;
	}
	former->m_next = target_temp->m_next;
	x.m_pos = target_temp->m_pos;
	delete target_temp;

	return true;
}


// --- 实现结束 ---