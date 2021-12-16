/*��Ŀ��  ���ʽ����*/
/*2053380 ���*/
//����Ŀδ�洢������Ϣ

#include <iostream>
#include <string>


#define STL_STACK	false//�Ƿ�ʹ��STL �ı�׼ stack�⣬����debug
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
		if (!empty())//δ�ղſ��Գ�ջ
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
int opera_amount;//֮������ȫ�ֱ���������Ϊ�ֲ������޷����������С�ĳ�ʼ����Ϣ

//---���ߺ�������---
void inline print(const char* message) {
	std::cout << message;
}
bool inline isNumber(char x) {
	return x <= '9' && x >= '0';
}

//�ַ���str�ĵ�index��λ����-������-���������Ǽ���
bool isNegative(const std::string& str, const int index);

//����һ���ַ��������ж������ַ���(�ѳɹ������λ��������������ͳһ��
int countNumber(const std::string& str);
//����һ���ַ��������ж��ٷ����ַ���
int countOpera(const std::string& str);
//---���ߺ�����������---


//---�������ඨ��---
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

//---�������ඨ�����---


int main()
{
	using pNode = BinTreeNode*;


#if DEFAULT_EXP
	std::string exp = "5+3*(7-8/2)+6";
	print("�Ƿ�ʹ��Ĭ���ַ�����(��5+3*(7-8/2)+6)\n(y/Y --yes)\n");
#endif // DEFAULT_EXP

	//std::string exp = "((5000)+378*((-7)-(8/2)+(-6)))";
	//����������ͨ��

#if DEFAULT_EXP
	{//����choice������ͻ���⣬�������پֲ�������life time
		char choice;
		std::cin >> choice;
		if ('y' != choice && 'Y' != choice)
		{
			print("��������ʽ(ע�����ʽ�в�Ӧ���пո�)\n");
			std::cin >> exp;
		}
	}
#endif // DEFAULT_EXP

	number_amount = countNumber(exp);
	opera_amount = countOpera(exp);

#if DEBUG
	std::cout << exp << std::endl;
	std::cout << "����������" << number_amount << "\n";
	std::cout << "�����������" << opera_amount << "\n";
#endif

#if STL_STACK
	std::stack<char> Operator;
	std::stack<pNode> StackNumber;//������
#else
	myStack::stack<char, &opera_amount> Operator;
	myStack::stack<pNode, &number_amount> StackNumber;//������
#endif // STL_STACK

	const int length = exp.length();
	int index = 0;

	{
		std::string number = "";
		if (exp[0] == '-')//��һ�������Ǹ���
		{
			{
				std::string temp = "-";
				number = temp + number;
			}
			index++;//��һ�������ַ�
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
		if (tag == 1)//���δ���һ�����֣�ֱ�ӽ�������ջ����
		{
			pNode temp = new BinTreeNode(number);//************
			StackNumber.push(temp);
			continue;
		}

		if (Operator.empty())//��һ�ν�ջ�Ĳ�����  ����ջ�պ����Ҳ�����˷�֧���
		{
			Operator.push(exp[index]);
			index++;
			continue;
		}

		//�������������Ҫ���в��������ȼ��ıȽ�
		char stack_top = Operator.top();

		switch (exp[index])
		{
		case '+':
		case '-':
		{
			if (isNegative(exp, index))
			{
				//std::cout << "\n�Ǹ���\n";
				std::string tag = "-";
				number = tag + number;//��ɸ��������۸о���
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
				StackNumber.pop();//�ֱ�õ����ڵ���������Һ���

				std::string subRoot = ".";
				subRoot[0] = stack_top;

				pNode newRoot = new
					BinTreeNode(subRoot, temp_left, temp_right);

				StackNumber.push(newRoot);
				Operator.pop();//ԭ�еĶ����ڵ��ȳ�ջ
				//Operator.push(a[index]);
			}
			break;
		}
		case '*':
		case '/':
		{
			if (stack_top == '+' || stack_top == '-' || stack_top == '(')//ջ�����ȼ��ͣ���ջ
			{
				Operator.push(exp[index]);
			}
			else
			{
				pNode temp_right = StackNumber.top();
				StackNumber.pop();
				pNode temp_left = StackNumber.top();
				StackNumber.pop();//�ֱ�õ����ڵ���������Һ���

				std::string subRoot = ".";
				subRoot[0] = stack_top;
				pNode newRoot = new
					BinTreeNode(subRoot, temp_left, temp_right);

				StackNumber.push(newRoot);
				Operator.pop();//ԭ�еĶ����ڵ��ȳ�ջ
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
			while (current != '(')//�����ź�������֮����ܻ��ж��������������Ҫѭ������
			{
				pNode temp_right = StackNumber.top();
				StackNumber.pop();
				pNode temp_left = StackNumber.top();
				StackNumber.pop();//�ֱ�õ����ڵ���������Һ���

				std::string subRoot = ".";
				subRoot[0] = current;
				pNode newRoot = new
					BinTreeNode(subRoot, temp_left, temp_right);
				StackNumber.push(newRoot);

				Operator.pop();
				current = Operator.top();
			}
			Operator.pop();//�������ų�ջ
			index++;
			break;
		}
		default:
		{
			print("�����ַ�: ");
			std::cout << exp[index];
			index++;
		}
		}
	}

	BinTree* tree = nullptr;

	
	if (Operator.empty() && StackNumber.size() == 1)//��������������һ�������/ ���߽���һ������ʱ��ִ�д˷�֧
	{
		tree = new BinTree((StackNumber.top()));
		StackNumber.pop();
	}
	else
	{
		pNode temp_right = StackNumber.top();
		StackNumber.pop();
		pNode temp_left = StackNumber.top();
		StackNumber.pop();//�ֱ�õ����ڵ���������Һ���

		char stack_top = Operator.top();
		std::string temp = ".";
		temp[0] = stack_top;

		pNode newRoot = new
			BinTreeNode(temp, temp_left, temp_right);

		tree = new BinTree(newRoot);
	}

	print("�������ʽ�����������\n");
	tree->postOrder(tree->getRoot());
	print("\n\n");

	print("������ʽ�����������\n");
	tree->InOrder(tree->getRoot());
	print("\n\n");

	print("�沨�����ʽ��ǰ�������\n");
	tree->preOrder(tree->getRoot());
	print("\n\n");

	std::cout << "���س������˳�";
	std::cin.get();
	std::cin.get();

	if(tree)
		delete tree;

	return 0;

}


//���ߺ���ʵ��
bool isNegative(const std::string& str, const int index)//the index should represent the negative
{
	const bool result = str[index] == '-'
		&& (index - 1) >= 0
		&& (!isNumber(str[index - 1]))
		&& str[index - 1] != ')';
	return result;
}

//����һ���ַ��������ж������ַ���(�ѳɹ������λ��������������ͳһ��
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
//���ߺ���ʵ�ֽ���