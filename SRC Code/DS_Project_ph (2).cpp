/*��Ŀ��  ����������*/
/*2053380 ���*/

//���ڷ���һ��cpp�ڣ��������ң�main����λ��160������

#include <iostream>
#include <string>
#include <sstream>

//Macro���궨�壩
#ifndef DefaultVisit
	#define DefaultVisit 1
#endif // !DefaultVisit

#ifndef MaxChoice
	#define MaxChoice 5
#endif // !MaxChoice
//�궨�����

//tool function�����ߺ���������
void menu();//����˵���Ϣ
void checkChoice(int& choice);//���ѡ���Ƿ�Ϸ�
void checkInput(int& input);//��������Ƿ�Ϸ�
bool isNumber(const std::string& src);//���ַ����Ƿ�Ϊ����

//���ߺ�����������


//�ඨ��
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

template<class T>
class BinSortTree;//������������������

template<class T>
class BinSortTreeNode//���ڵ㶨��
{
	using pNode = BinSortTreeNode<T>*;
	friend class BinSortTree<T>;

private:
	T	  _data;
	pNode _left;
	pNode _right;
	pNode _parent;

public:
	BinSortTreeNode(const T& data, pNode P = NULL,
		pNode L = NULL, pNode R = NULL)
		:_data(data), _left(L), _right(R) ,_parent(P) {
		;
	}

	T	  getData()const { return _data; }
	pNode getLeft()const { return _left; }
	pNode getParent()const { return _parent; }
	pNode getRight()const { return _right; }


};

template<class T>
class BinSortTree
{
	using pNode = BinSortTreeNode<T>*;
	using Node = BinSortTreeNode<T>;
public:
	BinSortTree(pNode p = NULL)
		:_root(p){
		;
	}
	~BinSortTree() { Destory(_root); }

	void createTree(T* src, size_t length) {
		for (size_t i = 0; i < length; i++) {
			Insert(*(src + i));
		}
	}

	void createTree();

	//��x���뵽��С��������
	bool Insert(const T& x);
	bool Search(const T& x);
	

	void InOrder(pNode subTree, void(*visit)(pNode p))
	{
		if (subTree == NULL) { return; }
		InOrder(subTree->_left, visit);
		visit(subTree);
		InOrder(subTree->_right, visit);
	}
	void preOrder(pNode subTree, void(*visit)(pNode p))
	{
		if (subTree == NULL) { return; }
		visit(subTree);
		InOrder(subTree->_left, visit);
		InOrder(subTree->_right, visit);
	}
	void postOrder(pNode subTree, void(*visit)(pNode p))
	{
		if (subTree == NULL) { return; }
		InOrder(subTree->_left, visit);
		InOrder(subTree->_right, visit);
		visit(subTree);
	}

	void Destory(pNode subTree) {
		if (subTree == NULL) { return; }

		Destory(subTree->_left);
		Destory(subTree->_right);
		delete subTree;
	}
	pNode getRoot()const { return _root; }
private:
	pNode _root;
};

//�ඨ�����

//Ĭ�Ϸ��ʺ���
//��ģ�庯����ʵ��������Ӧ��һ�𣨷������ײ����޷��������ⲿ���ţ�
template <typename T>
void defaultVisit(BinSortTreeNode<T>* p)
{
#if DefaultVisit
	std::cout << p->getData() << "->";
	//default visit function, just output the _data
#elif other
	std::cout << "user's visit function\n";
#endif
}





int main()
{
	BinSortTree<int> tree;
	int choice = 0;
	enum CHOICE { invaild, create, insert, search, exit, cls };

	menu();

	while (1)
	{

		printf("Please select: ");
		std::cin >> choice;

		checkChoice(choice);

		if (create == choice)
		{
			if (tree.getRoot() != NULL) {
				printf("The tree had been created, do you want to create a new tree?(y/Y -- yes)  ");
				char yesOrNo = 0;
				std::cin >> yesOrNo;
				if (yesOrNo != 'y' && yesOrNo != 'Y') { continue; }
				else { //�Ȱ����нڵ���յ�
					tree.Destory(tree.getRoot());
					tree = *(new BinSortTree<int>);
				}
			}

			{const char temp = getchar(); }//����ɾ������ȡ�ϴ�����Ļس�

			printf("Please input key(intger) to create BSort_Tree:\n");
			tree.createTree();

			printf("BSort_Tree is : ");
			tree.InOrder(tree.getRoot(), defaultVisit);
			printf("\n\n");
		}
		else if (insert == choice) {
			printf("Please input the key which will be inserted: ");
			int value;
			std::cin >> value;
			checkInput(value);
			if (tree.Insert(value)) {
				printf("BSort_Tree is : ");
				tree.InOrder(tree.getRoot(), defaultVisit);
			}
			else { ; }
			printf("\n\n");
		}
		else if (search == choice) {
			printf("Please input the key which will be searched: ");
			int value;
			std::cin >> value;
			checkInput(value);
			if (tree.Search(value)) {
				printf("Search successfully! \n\n");
			}
			else {
				printf("Find failed!\n\n");
			}
		}
		else if (exit == choice) {
			std::cout << "���س������˳�\n";
			std::cin.get();
			std::cin.get();
			return 0;
		}
		else if (cls == choice) {
			system("cls");
			menu();
		}

	}

	return 0;
}


//���ߺ�����ʵ��
void menu()
{
	std::cout << "========================================\n";
	std::cout << "**        ��ѡ��Ҫִ�еĲ�����        **\n";
	std::cout << "**        1 --- ��������������        **\n";
	std::cout << "**        2 --- ����Ԫ��              **\n";
	std::cout << "**        3 --- ��ѯԪ��              **\n";
	std::cout << "**        4 --- �˳�����              **\n";
	std::cout << "**        5 --- �����Ļ              **\n";
	std::cout << "========================================\n";
}

void checkChoice(int& choice)
{
	using namespace std;
	while (cin.fail() || choice > MaxChoice || choice < 1)
	{
		cout << "Choose Error, please choose between 0 and " << MaxChoice << "\n";
		cin.clear();
		cin.ignore(65535, '\n');
		cin >> choice;
	}
}

void checkInput(int& input)
{
	using namespace std;
	while (cin.fail())
	{
		cout << "Error input! Please input again: ";
		cin.clear();
		cin.ignore(65535, '\n');
		cin >> input;
	}
}

bool isNumber(const std::string& src)
{
	size_t i = 0u;
	if (src[0] == '-') {//����Ӧ�ñ�ԭ��
		i++;
	}
	for (; i < src.length(); i++) {
		if (!(src[i] >= '0' && src[i] <= '9')) {
			return false;
		}
	}
	return true;
}
//���ߺ�����ʵ�ֽ���


//��ʵ��
// 
//����������ʵ��

template<class T>
inline void BinSortTree<T>::createTree()
{
	std::string InputStr;
	std::getline(std::cin, InputStr);

	//�ݴ�������ַ����ж�ȡ����ʱ�ַ��� 
	std::string temp;
	//���ַ�������input�� 
	std::stringstream input(InputStr);
	//���������result�У�������res�� 
	
	while (input >> temp)
	{
		if (!isNumber(temp))
		{
			printf("%s is not a number! It has been ignored.\n", temp.c_str());
			continue;
		}
		int itemp = std::stoi(temp);//C++ style, transform a string to an integer
		checkInput(itemp);
		Insert(itemp);
	}
}

template<class T>
inline bool BinSortTree<T>::Insert(const T& x)
{
	if (_root == NULL)
	{
		_root = new Node(x, NULL);//the root's parent is null
		if (_root == NULL) {
			Log::Error("_root is null, storage allocation is failed");
			return false;
		}
		return true;
	}

	pNode current = getRoot();
	pNode par = current;//���游�ڵ�

	enum LorR { left, right };
	enum LorR direction = right;//just a default value without any other meanings

	while (current != NULL)
	{
		par = current;
		if (current->getData() == x)
		{
			printf("%d has been in the tree\n", x);
			return false;
		}

		if (current->getData() < x)
		{
			current = current->_right;//x���������ƶ�
			direction = right;
		}
		else
		{
			current = current->_left;
			direction = left;
		}
	}

	current = new Node(x, par);

	if (current == NULL) {
		Log::Error("current is null, storage allocation is failed");
		return false;
	}

	if (direction == right)
	{
		par->_right = current;
	}
	else if (direction == left)
	{
		par->_left = current;
	}
	else {
		Log::Info("that's impossible in insert function");
	}

	return true;
}

template<class T>
inline bool BinSortTree<T>::Search(const T& x)
{
	if (_root == NULL)
	{
		return false;
	}
	pNode current = getRoot();

	while (current != NULL)
	{
		if (current->getData() == x)
		{
			return true;
		}

		if (current->getData() < x)
		{
			current = current->_right;//x���������ƶ�
		}
		else
		{
			current = current->_left;
		}
	}

	return false;
}

