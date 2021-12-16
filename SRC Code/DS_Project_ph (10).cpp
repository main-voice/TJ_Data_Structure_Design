/*项目七  表达式计算*/
/*2053380 彭浩*/
//本项目未存储括号信息

#include <iostream>
#include <string>


#define STL_STACK	false//是否使用STL 的标准 stack库，方便debug
#define DEFAULT_EXP true
#define DEBUG		false

#if STL_STACK
	#include <stack>
#else
	#ifndef _myStack_
	#define _myStack_
namespace myStack
{
	template <typename T, int* length>
	class stack
	{
	public:
		stack() {
			m_size = *length;
			m_array = new T[m_size];
			m_top = -1;
		}
		stack(void* p) {
			if (p == nullptr) {
				m_size = 0;
				m_array = nullptr;
				m_top = -1;
				std::cout << "ERROR:the top of stack is null\n";
			}
		}
		~stack() {
			delete[]m_array;
		}
		T top()const {
			if (m_top < 0)
			{
				std::cout << "ERROR: m_top is negative!\nIn line ";
				std::cout << __LINE__ << std::endl;
			}
			return *(m_array + m_top);
		}
		bool empty() {
			return m_top == -1;
		}
		bool full() {
			return m_top == m_size - 1;
		}

		int size()const {
			return m_top + 1;
		}
		int max_size()const {
			return m_size;
		}
		bool pop();

		bool push(const T& element);
	private:
		T* m_array;
		int m_top;//the top of the stack
		int m_size;
	};

	template<typename T, int* length>
	inline bool stack<T, length>::pop()
	{
		if (!empty())//未空才可以出栈
		{
			m_top--;
			return true;
		}
		return false;
	}

	template<typename T, int* length>
	inline bool stack<T, length>::push(const T& element)
	{
		if (!full())
		{
			m_top++;
			*(m_array + m_top) = element;
			return true;
		}
		return false;
	}

}

	#endif // !_myStack_

using namespace myStack;
#endif // STL_STACK or user type

int number_amount;
int opera_amount;//之所以用全局变量，是因为局部变量无法用作数组大小的初始化信息

//---工具函数声明---
void inline print(const char* message) {
	std::cout << message;
}
bool inline isNumber(char x) {
	return x <= '9' && x >= '0';
}

//字符串str的第index个位置是-，检测该-代表负数还是减号
bool isNegative(const std::string& str, const int index);

//计算一个字符串里面有多少数字符号(已成功处理多位数，负数与正数统一）
int countNumber(const std::string& str);
//计算一个字符串里面有多少非数字符号
int countOpera(const std::string& str);
//---工具函数声明结束---


//---二叉树类定义---
class BinTreeNode
{
	using pNode = BinTreeNode*;

	friend class BinTree;
private:
	std::string data;
	pNode left;
	pNode right;

public:

	BinTreeNode(std::string value, pNode L = NULL, pNode R = NULL)
		:data(value), left(L), right(R)
	{}

};

class BinTree
{
	using pNode = BinTreeNode*;

public:
	BinTree(pNode root)
		:m_root(root)
	{
	}
	BinTree(pNode root, pNode L, pNode R)
		:m_root(root)
	{
		m_root->left = L;
		m_root->right = R;
	}
	void postOrder(pNode p)
	{
		if (p == NULL) { return; }
		postOrder(p->left);
		postOrder(p->right);
		std::cout << p->data;
	}
	void InOrder(pNode p)
	{
		if (p == NULL) { return; }
		InOrder(p->left);
		std::cout << p->data;
		InOrder(p->right);
	}
	void preOrder(pNode p)
	{
		if (p == NULL) { return; }
		std::cout << p->data;
		preOrder(p->left);
		preOrder(p->right);
	}
	pNode getRoot()const { return m_root; }

private:
	pNode m_root;
};

//---二叉树类定义结束---


int main()
{
	using pNode = BinTreeNode*;


#if DEFAULT_EXP
	std::string exp = "5+3*(7-8/2)+6";
	print("是否使用默认字符串？(即5+3*(7-8/2)+6)\n(y/Y --yes)\n");
#endif // DEFAULT_EXP

	//std::string exp = "((5000)+378*((-7)-(8/2)+(-6)))";
	//测试样例，通过

#if DEFAULT_EXP
	{//避免choice命名冲突问题，尽量减少局部变量的life time
		char choice;
		std::cin >> choice;
		if ('y' != choice && 'Y' != choice)
		{
			print("请输入表达式(注：表达式中不应含有空格)\n");
			std::cin >> exp;
		}
	}
#endif // DEFAULT_EXP

	number_amount = countNumber(exp);
	opera_amount = countOpera(exp);

#if DEBUG
	std::cout << exp << std::endl;
	std::cout << "数字数量：" << number_amount << "\n";
	std::cout << "运算符数量：" << opera_amount << "\n";
#endif

#if STL_STACK
	std::stack<char> Operator;
	std::stack<pNode> StackNumber;//操作数
#else
	myStack::stack<char, &opera_amount> Operator;
	myStack::stack<pNode, &number_amount> StackNumber;//操作数
#endif // STL_STACK

	const int length = exp.length();
	int index = 0;

	{
		std::string number = "";
		if (exp[0] == '-')//第一个数字是负数
		{
			{
				std::string temp = "-";
				number = temp + number;
			}
			index++;//第一个数字字符
			while (isNumber(exp[index]))
			{
				std::string temp = "?";
				temp[0] = exp[index];
				number = number + temp;
				index++;
			}
			pNode temp = new BinTreeNode(number);
			StackNumber.push(temp);
		}
	}

	while (index < length)
	{
		int tag = 0;
		std::string number = "";
		while (isNumber(exp[index]))
		{
			std::string temp = "?";
			temp[0] = exp[index];
			number = number + temp;
			tag = 1;
			index++;
		}
		if (tag == 1)//本次处理一个数字，直接将数字入栈即可
		{
			pNode temp = new BinTreeNode(number);//************
			StackNumber.push(temp);
			continue;
		}

		if (Operator.empty())//第一次进栈的操作符  包括栈空后可能也会进入此分支语句
		{
			Operator.push(exp[index]);
			index++;
			continue;
		}

		//第三种情况，需要进行操作符优先级的比较
		char stack_top = Operator.top();

		switch (exp[index])
		{
		case '+':
		case '-':
		{
			if (isNegative(exp, index))
			{
				//std::cout << "\n是负数\n";
				std::string tag = "-";
				number = tag + number;//变成负数（肉眼感觉）
				index++;
				while (isNumber(exp[index]))
				{
					std::string temp = "?";
					temp[0] = exp[index];
					number = number + temp;
					tag = 1;
					index++;
				}
				pNode temp = new BinTreeNode(number);
				StackNumber.push(temp);
				continue;
			}

			if (stack_top == '(')
			{
				Operator.push(exp[index]);
				index++;
				continue;
			}
			else
			{
				pNode temp_right = StackNumber.top();
				StackNumber.pop();
				pNode temp_left = StackNumber.top();
				StackNumber.pop();//分别得到根节点的左孩子与右孩子

				std::string subRoot = ".";
				subRoot[0] = stack_top;

				pNode newRoot = new
					BinTreeNode(subRoot, temp_left, temp_right);

				StackNumber.push(newRoot);
				Operator.pop();//原有的顶部节点先出栈
				//Operator.push(a[index]);
			}
			break;
		}
		case '*':
		case '/':
		{
			if (stack_top == '+' || stack_top == '-' || stack_top == '(')//栈顶优先级低，入栈
			{
				Operator.push(exp[index]);
			}
			else
			{
				pNode temp_right = StackNumber.top();
				StackNumber.pop();
				pNode temp_left = StackNumber.top();
				StackNumber.pop();//分别得到根节点的左孩子与右孩子

				std::string subRoot = ".";
				subRoot[0] = stack_top;
				pNode newRoot = new
					BinTreeNode(subRoot, temp_left, temp_right);

				StackNumber.push(newRoot);
				Operator.pop();//原有的顶部节点先出栈
				Operator.push(exp[index]);
			}
			index++;
			break;
		}
		case '(':
		{
			Operator.push(exp[index]);
			index++;
			break;
		}
		case ')':
		{
			char current = Operator.top();
			while (current != '(')//左括号和右括号之间可能会有多个运算符，因此需要循环处理
			{
				pNode temp_right = StackNumber.top();
				StackNumber.pop();
				pNode temp_left = StackNumber.top();
				StackNumber.pop();//分别得到根节点的左孩子与右孩子

				std::string subRoot = ".";
				subRoot[0] = current;
				pNode newRoot = new
					BinTreeNode(subRoot, temp_left, temp_right);
				StackNumber.push(newRoot);

				Operator.pop();
				current = Operator.top();
			}
			Operator.pop();//把左括号出栈
			index++;
			break;
		}
		default:
		{
			print("错误字符: ");
			std::cout << exp[index];
			index++;
		}
		}
	}

	BinTree* tree = nullptr;

	
	if (Operator.empty() && StackNumber.size() == 1)//仅有两个数字与一个运算符/ 或者仅有一个数字时会执行此分支
	{
		tree = new BinTree((StackNumber.top()));
		StackNumber.pop();
	}
	else
	{
		pNode temp_right = StackNumber.top();
		StackNumber.pop();
		pNode temp_left = StackNumber.top();
		StackNumber.pop();//分别得到根节点的左孩子与右孩子

		char stack_top = Operator.top();
		std::string temp = ".";
		temp[0] = stack_top;

		pNode newRoot = new
			BinTreeNode(temp, temp_left, temp_right);

		tree = new BinTree(newRoot);
	}

	print("波兰表达式（后序遍历）\n");
	tree->postOrder(tree->getRoot());
	print("\n\n");

	print("中序表达式（中序遍历）\n");
	tree->InOrder(tree->getRoot());
	print("\n\n");

	print("逆波兰表达式（前序遍历）\n");
	tree->preOrder(tree->getRoot());
	print("\n\n");

	std::cout << "按回车键以退出";
	std::cin.get();
	std::cin.get();

	if(tree)
		delete tree;

	return 0;

}


//工具函数实现
bool isNegative(const std::string& str, const int index)//the index should represent the negative
{
	const bool result = str[index] == '-'
		&& (index - 1) >= 0
		&& (!isNumber(str[index - 1]))
		&& str[index - 1] != ')';
	return result;
}

//计算一个字符串里面有多少数字符号(已成功处理多位数，负数与正数统一）
int countNumber(const std::string& str)
{
	int count = 0;
	char temp;
	for (size_t i = 0; i < str.length(); i++)
	{
		temp = str[i];
		if (isNumber(temp))
		{
			while (isNumber(temp))
			{
				temp = str[++i];
			}
			count++;
		}
	}
	return count;
}

int countOpera(const std::string& str)
{
	int count = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '-')
		{
			if (!isNegative(str, i))
			{
				count++;
				continue;
			}
		}
		if (!isNumber(str[i]))
		{
			count++;
		}
	}

	return count;
}
//工具函数实现结束