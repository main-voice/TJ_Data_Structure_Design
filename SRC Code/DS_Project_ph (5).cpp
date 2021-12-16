/*��Ŀ��  Լɪ������������Ϸ*/
/*2053380 ���*/

#include <iostream>
#include <iomanip>

#define  Cout std::cout
#define  Cin std::cin

// --- �����Ա�� ---
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

// --- ������ ---
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

//�ඨ�����

//---���ߺ��������������Ϣ---
void Input(int& peopleNum, int& initPos, int& deadNum, int& aliveNum);

int main()
{

	Cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ��������M���˳��֣�������һ���˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ\n";
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

				Cout << "��" << std::setw(3) << std::setfill(' ') <<
					std::setiosflags(std::ios::left) << i + 1
					<< "������λ����:" << std::setw(4) << temp.m_pos << std::endl;

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
		Cout << "���ʣ��" << aliveNum << "��\n";
		linkList.Output();

		while (1)
		{
			Cout << "�Ƿ��˳�����Y/y)--Yes, (N/n)--No\n";
			char ifExit;
			Cin >> ifExit;
			if (ifExit == 'y' || ifExit == 'Y')
			{
				std::cout << "���س������˳�\n";
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


	std::cout << "���س������˳�\n";
	std::cin.get();
	std::cin.get();

	return 0;
}

//---���ߺ���ʵ��---
void Input(int& peopleNum, int& initPos, int& deadNum, int& aliveNum)
{
	Cout << "������������Ϸ��������N��";
	Cin >> peopleNum;
	while (Cin.fail() || peopleNum < 1)
	{
		Cout << "����������������룡\n";
		Cin.clear();
		Cin.ignore(65535, '\n');
		Cin >> peopleNum;
	}

	Cout << "��������Ϸ��ʼ��λ��S��  ";
	Cin >> initPos;
	while (Cin.fail() || initPos < 1 || initPos > peopleNum)
	{
		Cout << "����������������룡\n";
		Cin.clear();
		Cin.ignore(65535, '\n');
		Cin >> initPos;
	}

	Cout << "��������������M��        ";
	Cin >> deadNum;
	while (Cin.fail() || deadNum < 1)
	{
		Cout << "����������������룡\n";
		Cin.clear();
		Cin.ignore(65535, '\n');
		Cin >> deadNum;
	}

	Cout << "������ʣ�����������K��  ";
	Cin >> aliveNum;
	while (Cin.fail() || aliveNum < 1 || aliveNum >= peopleNum)
	{
		Cout << "����������������룡\n";
		Cin.clear();
		Cin.ignore(65535, '\n');
		Cin >> aliveNum;
	}
}


// --- ������ʵ�� ---

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

	Cout << "ʣ�������λ����: \n";
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


// --- ʵ�ֽ��� ---