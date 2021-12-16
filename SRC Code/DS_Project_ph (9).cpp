/*项目六  家谱管理系统*/
/*2053380 彭浩*/

#include <iostream>
#include <string>

//--- 类定义  ---

//1.家庭成员类
const bool Alive = true;
const bool Dead = false;

class FamilyMember
{
	using String = std::string;
private:
	String m_name;
	String m_sex;
	bool   m_ifAlive;

public:
	FamilyMember();
	FamilyMember(const String& name);
	FamilyMember(const String& name, const String& sex);
	FamilyMember(const String& name, const String& sex, bool health);

	void  setSex(const String& sex);
	const String& getSex() const;

	void  setName(const String& name);
	const String& getName()const;
	bool  modifyName(const String& newName);

	bool  ifAlive()const { return m_ifAlive; }
	void  setAlive(bool ifalive) {
		ifalive
			? m_ifAlive = true
			: m_ifAlive = false;
	}

	friend std::ostream& operator<<(std::ostream& output,
		const FamilyMember& member);
	friend std::ostream& operator>>(std::ostream& input, FamilyMember& member);
};

 
//2.树节点类

class TreeNode
{
	typedef TreeNode* pNode;
	typedef FamilyMember* pMember;

	friend class Tree;
public:
	TreeNode()
	{
		member = new FamilyMember();
		firstChild = NULL;
		nextSibling = NULL;
		parent = NULL;
	}
	TreeNode(std::string name)
	{
		member = new FamilyMember(name);
		firstChild = NULL;
		nextSibling = NULL;
		parent = NULL;
	}
	TreeNode(std::string name, pNode par,
		pNode fc = NULL, pNode ns = NULL)
	{
		member = new FamilyMember(name);
		firstChild = fc;
		nextSibling = ns;
		parent = par;
	}
	~TreeNode() { ; }
	pMember getMember()const { return member; }

private:

	pMember member;//指向此节点下的成员
	pNode   parent;//指向父节点
	pNode   firstChild;//指向第一个孩子
	pNode   nextSibling;//指向下一个兄弟姐妹
};

//3.树类

class Tree
{
	//typedef TreeNode* pNode;
	using pNode = TreeNode*;
public:
	Tree() { root = NULL; }
	Tree(pNode r) { root = r; }
	Tree(const std::string name);
	~Tree() { Destory(root); }

	void Destory(pNode p);//删除以p为根节点的子树

	pNode getRoot()const { return root; }//返回根节点
	pNode Find(const std::string& target)
	{
		return Find(root, target);
	}
	pNode Locate(const std::string& target)
	{
		return Locate(root, target);
	}
	pNode Parent(const std::string& target);

	bool  Remove(const std::string& target, int& tag) {
		pNode p_target = Locate(target);
		if (p_target == NULL) {
			std::cout << "不存在此人  ";
			return false;
		}
		if (Remove(p_target, target, tag)) {
			return true;
		}
		return false;
	}
	bool  addKid(const std::string& target) {
		pNode p_target = Locate(target);
		if (addKid(p_target, target))
		{
			return true;
		}
		return false;
	}
	bool  createFamily(const std::string& target) {
		pNode p_target = Locate(target);
		if (p_target == NULL)
		{
			std::cout << "查找目标失败！请重试\n";
			return false;
		}
		if (createFamily(p_target, target))
		{
			return true;
		}
		std::cout << "创建家庭失败, 请重试\n";
		return false;;
	}
	bool  modifyName(const std::string& target);
	bool  PrintKid(const std::string& target) {
		pNode p_target = Locate(target);
		if (PrintKid(p_target, target))
		{
			return true;
		}
		return false;
	}
private:
	pNode root;

	//在以p为根节点的子树里面寻找到名称为target的节点
	pNode Find(pNode p, const std::string& target);
	pNode Locate(pNode p, const std::string& target);

	//在target节点下面添加孩子
	bool  addKid(pNode p, const std::string& target);
	//在target节点下面创建家庭
	bool  createFamily(pNode p, const std::string& target);
	//删除target节点以及子节点，tag是标识是否整个家族都被删除
	bool  Remove(pNode p, const std::string& target, int& tag);
	//打印以p为父节点的第一代孩子的信息
	bool  PrintKid(const pNode p, const std::string& target);
};

//4.输出信息类

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


//--- 类定义结束  ---

typedef TreeNode* pNode;

//工具函数
template<typename T>
static inline void print(const T& message)
{
	std::cout << message;
}

void inline menu()
{
	print("========================================\n");
	print("**        请选择要执行的操作：        **\n");
	print("**        A/a --- 完善家谱            **\n");
	print("**        B/b --- 添加家庭成员        **\n");
	print("**        C/c --- 解散局部家庭        **\n");
	print("**        D/d --- 更改家庭成员姓名    **\n");
	print("**        E/e --- 退出程序            **\n");
	print("**        F/f --- 第一代孩子          **\n");
	print("**        G/g --- 双亲结点            **\n");//后两项为拓展项
	print("**        H/h --- 清屏                **\n");
	print("**注：解散局部家庭指删除该节点以及子节**\n");
	print("**点，其兄弟节点作相应调整            **\n");
	print("========================================\n");
}

// 工具函数结束
int main()
{
	using namespace std;

	string temp_str;
	pNode  temp_pNode = NULL;

	menu();

	print("首先建立一个家谱！\n");
	print("请输入祖先的姓名: ");

	cin >> temp_str;
	Tree* family_tree = new Tree(temp_str);

	print("此家谱的祖先是：");
	cout << family_tree->getRoot()->getMember()->getName() << "\n\n";

	char choice;
	int tag = 0;//检测是否把整个家族全删了
	while (1)
	{

		if (tag == 1)
		{
			print("您已经删除整个家族，请重新构建家族。请输入祖先姓名: ");
			cin >> temp_str;
			family_tree = new Tree(temp_str);
			print("新家族的祖先是：");
			print(temp_str);
			print("\n");
			tag = 0;
		}

		print("请选择要执行的操作: ");
		cin >> choice;

		switch (choice)
		{
		case 'a':
		case 'A':
		{
			print("请输入要建立家庭的人的姓名：");
			cin >> temp_str;
			if (family_tree->createFamily(temp_str))
			{
				family_tree->PrintKid(temp_str);
			}
			print("\n\n");
			break;
		}
		case 'b':
		case 'B':
		{
			print("请输入要添加儿子（或女儿）的人的姓名：");
			cin >> temp_str;
			if (family_tree->addKid(temp_str))
			{
				family_tree->PrintKid(temp_str);
			}
			print("\n\n");
			break;
		}
		case 'c':
		case 'C':
		{
			print("请输入要解散家庭的成员名字：");
			cin >> temp_str;
			print("要解散家庭的人是：");
			cout << temp_str << endl;

			(family_tree->Remove(temp_str, tag))
				? print("解散成功!\n") : print("解散失败\n");

			break;
		}
		case 'd':
		case 'D':
		{
			print("请输入要修改姓名者的原姓名：");
			cin >> temp_str;
			if (family_tree->modifyName(temp_str))
			{
				print("修改成功！\n");
			}
			else
			{
				print("修改失败! \n");
			}
			print("\n\n");
			break;
		}
		case 'e':
		case 'E':
		{
			if (family_tree)
				delete family_tree;

			std::cout << "按回车键以退出\n";
			std::cin.get();
			std::cin.get();
			return 0;
		}
		case 'f':
		case 'F':
		{
			print("请输入父节点的姓名：");
			cin >> temp_str;
			family_tree->PrintKid(temp_str);
			print("\n\n");

			break;
		}
		case 'g':
		case 'G':
		{
			print("请输入其中一个子节点的名字: ");
			cin >> temp_str;
			temp_pNode = family_tree->Parent(temp_str);
			if (temp_pNode == NULL)
			{
				break;
			}
			cout << "父节点的名字为：";
			cout << temp_pNode->getMember()->getName();
			print("\n\n");

			break;
		}
		case 'h':
		case 'H':
		{
			system("cls");
			menu();
			break;
		}
		default:
		{
			cout << "输入错误，";
			continue;
		}
		}
	}
}


// --- 类成员函数实现 ---

//1.家庭成员类

FamilyMember::FamilyMember()
	:m_name("无名者"), m_sex("未知性别")
{
	m_ifAlive = Alive;//默认生者
}

FamilyMember::FamilyMember(const String& name)
	: m_name(name), m_sex("未知性别")
{
	m_ifAlive = Alive;//默认生者
}

FamilyMember::FamilyMember(const String& name, const String& sex)
	: m_name(name), m_sex(sex)
{
	m_ifAlive = Alive;//默认生者
}

FamilyMember::FamilyMember(const String& name, const String& sex, bool health)
	: m_name(name), m_sex(sex)
{
	m_ifAlive = health;
}

void FamilyMember::setSex(const String& sex)
{
	m_sex = sex;
}

const std::string& FamilyMember::getSex() const
{
	return m_sex;
}

void FamilyMember::setName(const String& name)
{
	m_name = name;
}

const std::string& FamilyMember::getName() const
{
	return m_name;
}

bool FamilyMember::modifyName(const String& newName)
{
	if (newName == m_name)//若名字已经是要修改的名字，则没必要修改
	{
		return false;
	}

	m_name = newName;
	return true;
}

std::ostream& operator<<(std::ostream& output, const FamilyMember& member)
{
	std::cout << member.getName();
	return output;
}

std::ostream& operator>>(std::ostream& input, FamilyMember& member)
{
	std::string tem_name;
	std::cin >> tem_name;
	member.setName(tem_name);
	return input;
}
// --- 家庭成员类实现结束

// 2.树类实现

typedef TreeNode* pNode;

Tree::Tree(const std::string name)
{
	root = new TreeNode;
	root->member->setName(name);
}

void Tree::Destory(pNode p)
{
	if (p == NULL) { return; }
	Destory(p->firstChild);
	Destory(p->nextSibling);
	delete p;
}

pNode Tree::Parent(const std::string& target)
{
	pNode p_target = Locate(target);
	if (p_target == NULL)
	{
		std::cout << "查找目标失败！请重试\n";
		return NULL;
	}
	if (p_target == root)
	{
		std::cout << "此为根节点！没有父节点\n";
		return NULL;
	}
	return p_target->parent;
}

bool Tree::modifyName(const std::string& target)
{
	pNode p_target = Find(root, target);
	if (p_target == NULL)
	{
		print("查找目标失败！请重试\n");
		return false;
	}

	print("请输入新名字: ");
	std::string newName;
	std::cin >> newName;

	p_target->member->setName(newName);

	return true;
}

pNode Tree::Find(pNode p, const std::string& target)
{
	if (p == NULL) { return NULL; }
	if (p->member->getName() == target)
	{
		return p;
	}
	pNode backup = p;
	if ((p = Find(p->firstChild, target)) != NULL)
	{
		return p;
	}
	else
	{
		return Find(backup->nextSibling, target);
	}

}

pNode Tree::Locate(pNode p, const std::string& target)
{
	if (p == NULL) { return NULL; }
	if (p->member->getName() == target)
	{
		return p;
	}
	pNode backup = p;
	if ((p = Locate(p->firstChild, target)) != NULL)
	{
		return p;
	}
	else
	{
		//若无备份指针，则在经历上面语句后，p已经是空指针，自然也无兄弟指针可言
		return Locate(backup->nextSibling, target);
	}
}

bool Tree::addKid(pNode p, const std::string& target)
{
	using namespace std;
	pNode p_target = p;

	if (p_target == NULL)
	{
		Log::Warn("查无此人，请重新输入");
		return false;
	}

	if (p_target->firstChild == NULL)
	{
		print("该成员尚未创建家庭，是否改为创建家庭?(y/Y--yes, n/N--no\n");

		char yesOrNo = 'y';
		std::cin >> yesOrNo;

		if (yesOrNo == 'y' || yesOrNo == 'Y')
		{
			if (createFamily(p, target)) {
				return true;
			}
			else {
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	//到此处则必定已经有一个孩子
	pNode current = p_target->firstChild;

	while (current->nextSibling != NULL)//若仅有一个孩子，则不会进入此循环
	{
		current = current->nextSibling;//找到最后一个兄弟
	}

	cout << "请输入" << target << "新添加的儿子（或女儿）的名字：";

	string newkid_name;
	cin >> newkid_name;
	pNode newChild = new TreeNode(newkid_name, p);

	if (newChild == NULL)
	{
		Log::Error("newChild is null in addkid function");
		return false;
	}
	else
	{
		current->nextSibling = newChild;
		return true;
	}
	return true;
}

bool Tree::createFamily(pNode p, const std::string& target)
{
	using namespace std;
	const pNode p_target = p;

	if (p_target == NULL)
	{
		Log::Warn("查无此人，请重新输入");
		return false;
	}
	if (p_target->firstChild != NULL)
	{
		std::cout << "该成员已有家庭，是否改为添加家庭成员?(y/Y--yes, n/N--no\n";
		char yesOrNo = 'y';
		std::cin >> yesOrNo;

		if (yesOrNo == 'y' || yesOrNo == 'Y')
		{
			return (addKid(p, target)) ? true : false;
		}
		else
		{
			return false;
		}
	}

	cout << "请输入" << target << "的儿女人数(人数应大于0)\n";
	int kid_num = 0;

	cin >> kid_num;

	while (cin.fail() || kid_num < 1)
	{
		print("输入错误，请重新输入：");
		cin.clear();
		cin.ignore(65535, '\n');
		cin >> kid_num;
	}
	cout << "请依次输入" << target << "的儿女的姓名：";

	string str_name;
	pNode before = NULL;//避免添加兄弟时不断循环查找最后一个兄弟
	pNode newChild = NULL;

	while (kid_num--)
	{
		cin >> str_name;
		newChild = new TreeNode(str_name, p);//新孩子的父节点都是p

		if (newChild == NULL)
		{
			Log::Error("newChild is null in createFamily function");
			return false;
		}

		if (p->firstChild == NULL)
		{
			//Log::Info("create the first child");
			p->firstChild = newChild;
			before = newChild;//对于下一次来说，本次的新孩子是前一个兄弟
			continue;
		}
		else
		{
			// Log::Info("create not first child");
			before->nextSibling = newChild;
			before = newChild;
		}
	}

	return true;
}

bool Tree::Remove(pNode p, const std::string& target, int& tag)
{
	if (p == root)
	{
		print("您即将删除整个家谱，删除后必须重新构建家谱，是否继续？(y/Y--yes , n/N--no)");
		char yesOrNo = 'y';
		std::cin >> yesOrNo;

		if (yesOrNo == 'y' || yesOrNo == 'Y')
		{
			Destory(p->firstChild);
			delete p;
			tag = 1;
			return true;
		}
		else
		{
			return false;
		}
	}

	if (p->parent->firstChild == p && p->nextSibling == NULL)//p是父节点的唯一一个孩子
	{
		Destory(p->firstChild);
		p->parent->firstChild = NULL;//父节点没有孩子了
		delete p;
		return true;
	}

	if (p->parent->firstChild == p)//delete the first child
	{
		Destory(p->firstChild);
		p->parent->firstChild = p->nextSibling;//父节点的第一个孩子变成了二弟
		delete p;
		return true;
	}

	//以下两种情况都需要用到p的前一个兄弟，因此需要循环找到前一个兄弟
	pNode target_before = p->parent->firstChild;
	while (target_before->nextSibling != p)
	{
		target_before = target_before->nextSibling;
	}

	//实际上以下两种情况语句一样，但为了易读性还是保持两部分
	if (p->nextSibling == NULL)//delete the last child(删除的是最后一个孩子)
	{
		target_before->nextSibling = NULL;//实际上本句与下面的赋值语句等同

		Destory(p->firstChild);
		delete p;
		return true;
	}
	//p是中间的某一个孩子
	else
	{
		target_before->nextSibling = p->nextSibling;

		Destory(p->firstChild);
		delete p;
		return true;
	}
	return true;
}

bool Tree::PrintKid(const pNode p, const std::string& target)
{
	if (p == NULL)
	{
		Log::Warn("p is null in printKid function");
		return false;
	}
	if (p->firstChild == NULL)
	{
		print("该成员没有孩子");
		return true;
	}
	std::cout << target << "的第一代子孙是：";

	pNode current = p->firstChild;
	while (current != NULL)
	{
		std::cout << current->getMember()->getName() << "     ";
		current = current->nextSibling;
	}
	return true;
}


// 树实现结束

// --- 类成员函数实现结束 ---