/*��Ŀһ  ���Ա���ϵͳ*/
/*2053380 ���*/


#include <string>
#include <iostream>
#include <iomanip>

class Student;

//����ڵ���
template <class TypeName>
struct ListNode
{
public:
	ListNode(ListNode<TypeName>* ptr = NULL);
	ListNode(const TypeName& item, ListNode<TypeName>* ptr = NULL);
	ListNode(const TypeName& item);
	~ListNode();
public:
	TypeName m_data;
	ListNode<TypeName>* m_next;
};

//������
template <class TypeName>
class List
{
	template <typename TypeName>
	friend struct ListNode;
public:
	List();
	List(const TypeName& x);
	List(List<TypeName>& x);
	~List() {
		makeEmpty();
		delete head;
	}

	void makeEmpty();
	int  Length()const;

	ListNode<TypeName>* getHead()const { return head; }
	ListNode<TypeName>* Find(const TypeName& x);
	ListNode<TypeName>* Find(const TypeName& x, int& pos);
	ListNode<TypeName>* Locate(int i);

	bool getData(int i, TypeName& x)const;
	void setData(int i, TypeName& x);

	bool Insert(int i, TypeName& x);//insert an element in the postion of 'i'
	bool Remove(int i, TypeName& x);//the x is the element that is removed
	bool isEmpty()const { return (head->m_next == nullptr) ? true : false; }

	void Input();
	void Output();

	void Revise() { ; }
	List<TypeName>& operator=(List<TypeName>& x);

private:
	ListNode<TypeName>* head;
};

template<>
void List<Student>::Revise();


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

//ѧ����
class Student
{
private:
	using String = std::string;
	//the basic infomation of the student
	String m_stu_name;
	String m_exam_name;
	String m_sex;
	int    m_age;
	int    m_exam_number;

public:
	Student(int exam_num) {
		m_exam_number = exam_num;
	}
	Student() { ; }
	~Student() { ; }
	void setExamNumber(int num);
	int getExamNumber()const;

	void setSex(const String& sex);
	const String& getSex() const;

	void setStuName(const String& name);
	const String& getStuName()const;

	void setExamName(const String& name);
	const String& getExamName()const;

	void setAge(int age);
	int getAge()const;

	friend std::ostream& operator<<(std::ostream& output, const Student& S);
	friend std::istream& operator>>(std::istream& input, Student& S);
	bool operator==(const Student& x);
};

// --- ���ߺ���������ʼ ---
static bool checkNumber(int& input);

static bool checkChoice(int& input);

template <class T>
class List;
template <class T>
bool checkInsert(int& pos, const List<T>& list);

// --- ���ߺ�����������


 /*########## MAIN ############*/
int main()
{
	List<Student> list;
	ListNode<Student> listNode;
	Student input_stud;

	std::cout << std::endl << "�����뽨��������Ϣϵͳ " << std::endl;
	list.Input();

	enum menuDetail { exit, insert, delete_stu, find, modify, count };
	int choose = -1;

	while (1)
	{
		std::cout << "��ѡ����Ҫ���еĲ���(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������)" << std::endl;
		std::cin >> choose;
		checkChoice(choose);

		switch (choose) {
		case insert: {
			std::cout << "�����ѧ���Ĳ���λ��" << std::endl;
			int pos = 0;
			std::cin >> pos;
			checkInsert(pos, list);

			std::cout << "����������ѧ�����ţ��������Ա������Լ��������" << std::endl;
			std::cin >> input_stud;
			//input the information of the student
			auto Stud = new Student(input_stud);

			while (list.Find(*Stud)) {
				std::cout << "�Ѿ����ڸÿ��ŵ�ѧ��������������\n" << std::endl;
				std::cin >> input_stud;
				auto temp = Stud;
				delete temp;
				Stud = new Student(input_stud);
			}
			list.Insert(pos, *Stud);
			list.Output();
			break;
		}

		case count: {
			list.Output();
			std::cout << '\n';
			break;
		}

		case delete_stu: {
			std::cout << "������Ҫɾ���Ŀ����Ŀ���" << std::endl;
			int num = -1;
			std::cin >> num;
			checkNumber(num);
			Student temp(num);
			auto target = list.Find(temp, num);//can find the correct target
			if (target == NULL) {
				std::cout << "��ѧ�������ڣ�\n";
				break;
			}
			list.Remove(num, temp);
			std::cout << "ɾ����ѧ����ϢΪ��\n" << temp << std::endl;
			list.Output();
			break;
		}

		case modify:
		{
			list.Revise();
			break;
		}
		case find:
		{
			std::cout << "������Ҫ���ҵ�ѧ���Ŀ���\n";
			int num = -1;
			std::cin >> num;
			checkNumber(num);
			Student temp(num);
			auto target = list.Find(temp);//can find the correct target
			if (target == NULL) {
				std::cout << "��ѧ�������ڣ�\n";
				break;
			}
			else {
				std::cout << "����    ����    �Ա�    ����    �������\n";
				std::cout << target->m_data << std::endl;
			}
			break;
		}
		case exit: {

			std::cout << "���س������˳�\n";
			std::cin.get();
			std::cin.get();


			return 0;

		}
		default: {
			break;
		}
		}
	}

	return 0;
}


// -- ��⺯��ʵ�� ---
static bool checkNumber(int& input) {
	while (std::cin.fail() || input < 0) {
		std::cout << "��������!����������\n";
		std::cin.clear();
		std::cin.ignore(65535, '\n');
		std::cin >> input;
	}
	return true;
}

#ifndef MaxChoice
#define MaxChoice 7
static bool checkChoice(int& input) {
	while (std::cin.fail() || input < 0 || input > MaxChoice) {
		std::cout << "��������!����������\n";
		std::cin.clear();
		std::cin.ignore(65535, '\n');
		std::cin >> input;
	}
	return true;
}
#endif

template <class T>
class List;
template <class T>
bool checkInsert(int& pos, const List<T>& list) {
	while (std::cin.fail() || pos < 0 || pos > list.Length() + 1) {
		std::cout << "��������!����������\n";
		std::cin.clear();
		std::cin.ignore(65535, '\n');
		std::cin >> pos;
	}
	return true;
}

// --- ʵ�ֽ��� ---


// --- ����ʵ�� ---




template <class TypeName>
ListNode<TypeName>::ListNode(ListNode<TypeName>* ptr)
{
	m_next = ptr;
}

template<class TypeName>
ListNode<TypeName>::ListNode(const TypeName& item, ListNode<TypeName>* ptr)
{
	m_data = item;
	m_next = ptr;
}

template<class TypeName>
ListNode<TypeName>::ListNode(const TypeName& item)
{
	m_data = item;
}

template <class TypeName>
ListNode<TypeName>::~ListNode()
{
}

template<class TypeName>
List<TypeName>::List()
{
	head = new ListNode<TypeName>;
	if (NULL == head) {
		Log::Error("Empty ptr in class List's constructor");
	}
	head->m_next = NULL;
}

template<class TypeName>
List<TypeName>::List(const TypeName& x)
{
	head = new ListNode<TypeName>(x);
	if (NULL == head) {
		Log::Error("Empty ptr in class List's constructor");
	}
}

template<class TypeName>
List<TypeName>::List(List<TypeName>& x)
{
	TypeName value;
	ListNode<TypeName>* srcptr = x.getHead();
	ListNode<TypeName>* destptr = head = new ListNode<TypeName>;
	if (destptr == NULL) {
		Log::Error("destptr is NULL in List's copy construction function!");
	}
	if (srcptr->m_next == NULL) {//the list x is an empty list
		destptr->m_next = NULL;
		return;
	}

	while (srcptr->m_next != NULL) {
		value = srcptr->m_next->m_data;
		destptr->m_next = new ListNode<TypeName>(value);
		srcptr = srcptr->m_next;
		destptr = destptr->m_next;
	}
	destptr->m_next = NULL;
}

template<class TypeName>
void List<TypeName>::makeEmpty()
{
	ListNode<TypeName>* current;
	//keep the head
	while (head->m_next != NULL) {
		current = head->m_next;
		head->m_next = current->m_next;
		delete current;
	}
}

template<class TypeName>
int List<TypeName>::Length() const
{
	int count = 0;
	ListNode<TypeName>* current = head->m_next;

	while (current != NULL) {
		count++;
		current = current->m_next;
	}
	return count;
}

template<class TypeName>
ListNode<TypeName>* List<TypeName>::Find(const TypeName& x)//need to overload the operator of "=="
{
	ListNode<TypeName>* current = head->m_next;

	//to keep normal when it's empty, can't use ---current->next != NULL
	while (current != NULL) {
		if (current->m_data == x)break;
		else current = current->m_next;
	}
	return current;
}

template<class TypeName>
ListNode<TypeName>* List<TypeName>::Find(const TypeName& x, int& pos)
{
	ListNode<TypeName>* current = head->m_next;
	if (current == NULL) { pos = -1; return NULL; }//the list is empty, so you can't find x

	int temp_pos = 1;
	//to keep normal when it's empty, can't use ---current->next != NULL
	while (current != NULL) {
		if (current->m_data == x)break;
		else current = current->m_next;
		temp_pos++;
	}
	pos = temp_pos;
	return current;
}

template<class TypeName>
ListNode<TypeName>* List<TypeName>::Locate(int i)
{
	if (i < 0) {
		Log::Warn("i is too small in Locate function!");
		return NULL;
	}
	else if (i == NULL) {
		return head;
	}
	else if (i > this->Length()) {
		Log::Warn("i is too big in Locate function!");
		return NULL;
	}

	ListNode<TypeName>* current = head;
	int count = 0;
	while (count < i && current != NULL) {
		current = current->m_next;
		count++;
	}
	return current;
}

template<class TypeName>
bool List<TypeName>::getData(int i, TypeName& x) const
{
	if (i <= 0) {
		Log::Warn("i is too small in getData function!");
		return false;
	}

	ListNode<TypeName>* target = Locate(i);
	if (target == NULL) {
		Log::Warn("The i is too big in getData function");
		return false;
	}//it represents the i is too big
	else {
		x = target->m_data;
	}
	return true;
}

template<class TypeName>
void List<TypeName>::setData(int i, TypeName& x)
{
	if (i <= 0) {
		Log::Warn("i is too small in setData function!");
		return false;
	}

	ListNode<TypeName>* target = Locate(i);
	if (target == NULL) {
		Log::Warn("The i is too big in getData function");
		return false;
	}//it represents the i is too big
	else {
		target->m_data = x;
	}
}

//insert an element in the position 'i'
template<class TypeName>
bool List<TypeName>::Insert(int i, TypeName& x)
{
	if (i <= 0) {
		Log::Warn("i is too small in Insert function!");
		return false;
	}
	if (i > Length() + 1) {
		Log::Warn("i is too big in Insert function!");
		return false;
	}

	ListNode<TypeName>* targetFormer = Locate(i - 1);//the former node of the target
	ListNode<TypeName>* newNode = new ListNode<TypeName>;

	if (NULL == newNode) {
		Log::Error("The newNode is null in insert function");
		return false;
	}
	newNode->m_data = x;
	newNode->m_next = targetFormer->m_next;
	targetFormer->m_next = newNode;

	return true;
}

template<class TypeName>
bool List<TypeName>::Remove(int i, TypeName& x)//the x is the element that is removed
{
	if (i <= 0) {
		Log::Warn("i is too small in Remove function!");
		return false;
	}

	ListNode<TypeName>* targetFormer = Locate(i - 1);//the former node of the target
	ListNode<TypeName>* target = targetFormer->m_next;

	if (NULL == target || NULL == targetFormer) {
		Log::Error("target and its formal in Remove function!");
		return false;
	}
	targetFormer->m_next = target->m_next;
	x = target->m_data;
	delete target;

	return true;
}

template<class TypeName>
void List<TypeName>::Input()
{
	makeEmpty();//maybe it's useless
	int stu_number = 0;
	TypeName value;
	ListNode<TypeName>* last = head, *newNode = nullptr;

	std::cout << "������ѧ������" << std::endl;
	std::cin >> stu_number;

	while (std::cin.fail() || stu_number <= 0) {
		std::cout << "��������!����������\n";
		std::cin.clear();
		std::cin.ignore(65535, '\n');
		std::cin >> stu_number;
	}

	std::cout << "���������뿼���Ŀ��ţ��������Ա����估�������\n";

	for (int i = 0; i < stu_number; i++) {
		std::cin >> value;
		newNode = new ListNode<TypeName>;
		newNode->m_data = value;
		if (newNode == NULL) {
			Log::Error("the new node is null in input function");
			return;
		}
		last->m_next = newNode;
		last = newNode;
	}

}

template<class TypeName>
void List<TypeName>::Output()
{
	std::cout << "����    " << "����    " << "�Ա�    " << "����    " << "�������" << std::endl;
	ListNode<TypeName>* current = head->m_next;
	while (current != NULL) {
		std::cout << current->m_data << std::endl;
		current = current->m_next;
	}

}


template<>
void List<Student>::Revise()
{
	using namespace std;

	char YesOrNo = 'N';
	std::cout << "������Ҫ�����޸���Ϣ��ѧ���Ŀ���\n(ע����֧���޸����� �Ա� ���� �������)\n";
	int num = -1;
	std::cin >> num;
	checkNumber(num);
	Student temp(num);
	auto target = this->Find(temp);//can find the correct target
	if (target == NULL) {
		cout << "��ѧ�������ڣ�\n";
		return;
	}

	if (1)//if modify the sudent's name
	{
		std::cout << "�����Ƿ��޸����� Y(Yes) N(No)";
		std::cin >> YesOrNo;

		if (YesOrNo == 'y' || YesOrNo == 'n') {
			YesOrNo -= 'a' - 'A';
			cout << "Yes Or No: " << YesOrNo << endl;
		}
		const bool flag = (YesOrNo == 'Y' ? true : false);
		if (flag) {
			string stu_name;
			cout << "�������޸ĺ��������";
			cin >> stu_name;
			(target->m_data).setStuName(stu_name);
			cout << "�޸ĺ�:" << target->m_data << endl;
		}
	}

	if (2)//if modify the sudent's sex
	{
		cout << "�����Ƿ��޸��Ա� Y(Yes) N(No)";
		cin >> YesOrNo;

		if (YesOrNo == 'y' || YesOrNo == 'n') {
			YesOrNo -= 'a' - 'A';
			cout << "Yes Or No: " << YesOrNo << endl;
		}
		const bool flag = (YesOrNo == 'Y' ? true : false);
		if (flag) {
			std::string sex;
			cout << "�������޸ĺ���Ա�";
			std::cin >> sex;
			target->m_data.setSex(sex);
			std::cout << "�޸ĺ�:" << target->m_data << std::endl;
		}
	}

	if (3)//if modify the sudent's sex
	{
		std::cout << "�����Ƿ��޸����� Y(Yes) N(No)";
		std::cin >> YesOrNo;

		if (YesOrNo == 'y' || YesOrNo == 'n') {
			YesOrNo -= 'a' - 'A';
			std::cout << "Yes Or No: " << YesOrNo << std::endl;
		}
		const bool flag = (YesOrNo == 'Y' ? true : false);
		if (flag) {
			int age = -1;
			std::cout << "�������޸ĺ�����䣺";
			std::cin >> age;
			checkNumber(age);
			target->m_data.setAge(age);
			std::cout << "�޸ĺ�:" << target->m_data << std::endl;
		}
	}

	if (4)//if modify the sudent's sex
	{
		cout << "�����Ƿ��޸ı������ Y(Yes) N(No)";
		cin >> YesOrNo;

		if (YesOrNo == 'y' || YesOrNo == 'n') {
			YesOrNo -= 'a' - 'A';
			cout << "Yes Or No: " << YesOrNo << std::endl;
		}
		const bool flag = (YesOrNo == 'Y' ? true : false);
		if (flag) {
			std::string exam_name;
			std::cout << "�������޸ĺ�ı������";
			std::cin >> exam_name;
			target->m_data.setExamName(exam_name);
			std::cout << "�޸ĺ�:" << target->m_data << std::endl;
		}
	}
}


template<class TypeName>
List<TypeName>& List<TypeName>::operator=(List<TypeName>& x)
{
	TypeName value;
	ListNode<TypeName>* srcptr = x.getHead();
	ListNode<TypeName>* destptr = head = new ListNode<TypeName>;
	if (destptr == NULL) {
		Log::Error("destptr is NULL in operator = function!");
	}
	if (srcptr->m_next == NULL) {//the list x is an empty list
		destptr->m_next = NULL;
		return *this;
	}

	while (srcptr->m_next != NULL) {
		value = srcptr->m_next->m_data;
		destptr->m_next = new ListNode<TypeName>(value);
		srcptr = srcptr->m_next;
		destptr = destptr->m_next;
	}
	destptr->m_next = NULL;
	return *this;
}


//����ʵ�ֽ���


// --- ѧ����ʵ�� ---
using String = std::string;

void Student::setExamNumber(int num)
{
	m_exam_number = num;
}

int Student::getExamNumber()const
{
	return m_exam_number;
}

void Student::setSex(const String& sex)
{
	m_sex = sex;
}

const String& Student::getSex() const
{
	return m_sex;
}

void Student::setStuName(const String& name)
{
	m_stu_name = name;
}

const String& Student::getStuName()const
{
	return m_stu_name;
}

void Student::setExamName(const String& name)
{
	m_exam_name = name;
}

const String& Student::getExamName()const
{
	return m_exam_name;
}

void Student::setAge(int age)
{
	m_age = age;
}
int Student::getAge()const
{
	return m_age;
}

bool Student::operator==(const Student& x)
{
	return this->m_exam_number == x.getExamNumber();
}

std::ostream& operator<<(std::ostream& output, const Student& S)
{
	using namespace std;

	output << setw(8) << setfill(' ') << setiosflags(ios::left) << S.getExamNumber()
		<< setw(8) << setfill(' ') << S.getStuName()
		<< setw(8) << setfill(' ') << S.getSex()
		<< setw(8) << setfill(' ') << S.getAge()
		<< setw(8) << setfill(' ') << S.getExamName();
	return output;
}

std::istream& operator>>(std::istream& input, Student& S)
{
	int examNumber, age;
	std::string stuName, sex, examName;
	using namespace std;

	cin >> examNumber;
	cin >> stuName;
	cin >> sex;
	cin >> age;
	cin >> examName;
#define MaxExamNumber 2147483647
	while (cin.fail() || examNumber < 0 || examNumber > MaxExamNumber) {
		cout << "�����ʽ��������������\n";
		cin.clear();
		cin.ignore(65535, '\n');

		cin >> examNumber;
		cin >> stuName;
		cin >> sex;
		cin >> age;
		cin >> examName;
	}


	S.setExamNumber(examNumber);
	S.setSex(sex);
	S.setAge(age);
	S.setStuName(stuName);
	S.setExamName(examName);

	return input;
}
// --- ѧ����ʵ�ֽ��� ---