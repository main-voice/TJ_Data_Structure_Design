/*项目九  二叉排序数*/
/*2053380 彭浩*/

//由于放在一个cpp内，略显凌乱，main函数位于160行左右

#include <iostream>
#include <string>
#include <sstream>

//Macro（宏定义）
#ifndef DefaultVisit
	#define DefaultVisit 1
#endif // !DefaultVisit

#ifndef MaxChoice
	#define MaxChoice 5
#endif // !MaxChoice
//宏定义结束

//tool function（工具函数声明）
void menu();//输出菜单信息
void checkChoice(int& choice);//检查选择是否合法
void checkInput(int& input);//检查输入是否合法
bool isNumber(const std::string& src);//该字符串是否为数字

//工具函数声明结束


//类定义
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

template<class T>
class BinSortTree;//搜索二叉树的类声明

template<class T>
class BinSortTreeNode//树节点定义
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

	//把x插入到最小二叉树中
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

//类定义结束

//默认访问函数
//因模板函数，实现与声明应在一起（否则容易产生无法解析的外部符号）
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
				else { //先把所有节点清空掉
					tree.Destory(tree.getRoot());
					tree = *(new BinSortTree<int>);
				}
			}

			{const char temp = getchar(); }//不可删掉，读取上次输入的回车

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
			std::cout << "按回车键以退出\n";
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


//工具函数的实现
void menu()
{
	std::cout << "========================================\n";
	std::cout << "**        请选择要执行的操作：        **\n";
	std::cout << "**        1 --- 建立二叉排序树        **\n";
	std::cout << "**        2 --- 插入元素              **\n";
	std::cout << "**        3 --- 查询元素              **\n";
	std::cout << "**        4 --- 退出程序              **\n";
	std::cout << "**        5 --- 清空屏幕              **\n";
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
	if (src[0] == '-') {//负数应该被原谅
		i++;
	}
	for (; i < src.length(); i++) {
		if (!(src[i] >= '0' && src[i] <= '9')) {
			return false;
		}
	}
	return true;
}
//工具函数的实现结束


//类实现
// 
//二叉树函数实现

template<class T>
inline void BinSortTree<T>::createTree()
{
	std::string InputStr;
	std::getline(std::cin, InputStr);

	//暂存从输入字符串中读取的临时字符串 
	std::string temp;
	//将字符串读到input中 
	std::stringstream input(InputStr);
	//依次输出到result中，并存入res中 
	
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
	pNode par = current;//储存父节点

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
			current = current->_right;//x更大，向右移动
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
			current = current->_right;//x更大，向右移动
		}
		else
		{
			current = current->_left;
		}
	}

	return false;
}

