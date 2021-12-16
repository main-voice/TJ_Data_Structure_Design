/*��Ŀ��  ���׹���ϵͳ*/
/*2053380 ���*/

#include <iostream>
#include <string>

//--- �ඨ��  ---

//1.��ͥ��Ա��
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

 
//2.���ڵ���

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

	pMember member;//ָ��˽ڵ��µĳ�Ա
	pNode   parent;//ָ�򸸽ڵ�
	pNode   firstChild;//ָ���һ������
	pNode   nextSibling;//ָ����һ���ֵܽ���
};

//3.����

class Tree
{
	//typedef TreeNode* pNode;
	using pNode = TreeNode*;
public:
	Tree() { root = NULL; }
	Tree(pNode r) { root = r; }
	Tree(const std::string name);
	~Tree() { Destory(root); }

	void Destory(pNode p);//ɾ����pΪ���ڵ������

	pNode getRoot()const { return root; }//���ظ��ڵ�
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
			std::cout << "�����ڴ���  ";
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
			std::cout << "����Ŀ��ʧ�ܣ�������\n";
			return false;
		}
		if (createFamily(p_target, target))
		{
			return true;
		}
		std::cout << "������ͥʧ��, ������\n";
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

	//����pΪ���ڵ����������Ѱ�ҵ�����Ϊtarget�Ľڵ�
	pNode Find(pNode p, const std::string& target);
	pNode Locate(pNode p, const std::string& target);

	//��target�ڵ�������Ӻ���
	bool  addKid(pNode p, const std::string& target);
	//��target�ڵ����洴����ͥ
	bool  createFamily(pNode p, const std::string& target);
	//ɾ��target�ڵ��Լ��ӽڵ㣬tag�Ǳ�ʶ�Ƿ��������嶼��ɾ��
	bool  Remove(pNode p, const std::string& target, int& tag);
	//��ӡ��pΪ���ڵ�ĵ�һ�����ӵ���Ϣ
	bool  PrintKid(const pNode p, const std::string& target);
};

//4.�����Ϣ��

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


//--- �ඨ�����  ---

typedef TreeNode* pNode;

//���ߺ���
template<typename T>
static inline void print(const T& message)
{
	std::cout << message;
}

void inline menu()
{
	print("========================================\n");
	print("**        ��ѡ��Ҫִ�еĲ�����        **\n");
	print("**        A/a --- ���Ƽ���            **\n");
	print("**        B/b --- ��Ӽ�ͥ��Ա        **\n");
	print("**        C/c --- ��ɢ�ֲ���ͥ        **\n");
	print("**        D/d --- ���ļ�ͥ��Ա����    **\n");
	print("**        E/e --- �˳�����            **\n");
	print("**        F/f --- ��һ������          **\n");
	print("**        G/g --- ˫�׽��            **\n");//������Ϊ��չ��
	print("**        H/h --- ����                **\n");
	print("**ע����ɢ�ֲ���ָͥɾ���ýڵ��Լ��ӽ�**\n");
	print("**�㣬���ֵܽڵ�����Ӧ����            **\n");
	print("========================================\n");
}

// ���ߺ�������
int main()
{
	using namespace std;

	string temp_str;
	pNode  temp_pNode = NULL;

	menu();

	print("���Ƚ���һ�����ף�\n");
	print("���������ȵ�����: ");

	cin >> temp_str;
	Tree* family_tree = new Tree(temp_str);

	print("�˼��׵������ǣ�");
	cout << family_tree->getRoot()->getMember()->getName() << "\n\n";

	char choice;
	int tag = 0;//����Ƿ����������ȫɾ��
	while (1)
	{

		if (tag == 1)
		{
			print("���Ѿ�ɾ���������壬�����¹������塣��������������: ");
			cin >> temp_str;
			family_tree = new Tree(temp_str);
			print("�¼���������ǣ�");
			print(temp_str);
			print("\n");
			tag = 0;
		}

		print("��ѡ��Ҫִ�еĲ���: ");
		cin >> choice;

		switch (choice)
		{
		case 'a':
		case 'A':
		{
			print("������Ҫ������ͥ���˵�������");
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
			print("������Ҫ��Ӷ��ӣ���Ů�������˵�������");
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
			print("������Ҫ��ɢ��ͥ�ĳ�Ա���֣�");
			cin >> temp_str;
			print("Ҫ��ɢ��ͥ�����ǣ�");
			cout << temp_str << endl;

			(family_tree->Remove(temp_str, tag))
				? print("��ɢ�ɹ�!\n") : print("��ɢʧ��\n");

			break;
		}
		case 'd':
		case 'D':
		{
			print("������Ҫ�޸������ߵ�ԭ������");
			cin >> temp_str;
			if (family_tree->modifyName(temp_str))
			{
				print("�޸ĳɹ���\n");
			}
			else
			{
				print("�޸�ʧ��! \n");
			}
			print("\n\n");
			break;
		}
		case 'e':
		case 'E':
		{
			if (family_tree)
				delete family_tree;

			std::cout << "���س������˳�\n";
			std::cin.get();
			std::cin.get();
			return 0;
		}
		case 'f':
		case 'F':
		{
			print("�����븸�ڵ��������");
			cin >> temp_str;
			family_tree->PrintKid(temp_str);
			print("\n\n");

			break;
		}
		case 'g':
		case 'G':
		{
			print("����������һ���ӽڵ������: ");
			cin >> temp_str;
			temp_pNode = family_tree->Parent(temp_str);
			if (temp_pNode == NULL)
			{
				break;
			}
			cout << "���ڵ������Ϊ��";
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
			cout << "�������";
			continue;
		}
		}
	}
}


// --- ���Ա����ʵ�� ---

//1.��ͥ��Ա��

FamilyMember::FamilyMember()
	:m_name("������"), m_sex("δ֪�Ա�")
{
	m_ifAlive = Alive;//Ĭ������
}

FamilyMember::FamilyMember(const String& name)
	: m_name(name), m_sex("δ֪�Ա�")
{
	m_ifAlive = Alive;//Ĭ������
}

FamilyMember::FamilyMember(const String& name, const String& sex)
	: m_name(name), m_sex(sex)
{
	m_ifAlive = Alive;//Ĭ������
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
	if (newName == m_name)//�������Ѿ���Ҫ�޸ĵ����֣���û��Ҫ�޸�
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
// --- ��ͥ��Ա��ʵ�ֽ���

// 2.����ʵ��

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
		std::cout << "����Ŀ��ʧ�ܣ�������\n";
		return NULL;
	}
	if (p_target == root)
	{
		std::cout << "��Ϊ���ڵ㣡û�и��ڵ�\n";
		return NULL;
	}
	return p_target->parent;
}

bool Tree::modifyName(const std::string& target)
{
	pNode p_target = Find(root, target);
	if (p_target == NULL)
	{
		print("����Ŀ��ʧ�ܣ�������\n");
		return false;
	}

	print("������������: ");
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
		//���ޱ���ָ�룬���ھ�����������p�Ѿ��ǿ�ָ�룬��ȻҲ���ֵ�ָ�����
		return Locate(backup->nextSibling, target);
	}
}

bool Tree::addKid(pNode p, const std::string& target)
{
	using namespace std;
	pNode p_target = p;

	if (p_target == NULL)
	{
		Log::Warn("���޴��ˣ�����������");
		return false;
	}

	if (p_target->firstChild == NULL)
	{
		print("�ó�Ա��δ������ͥ���Ƿ��Ϊ������ͥ?(y/Y--yes, n/N--no\n");

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

	//���˴���ض��Ѿ���һ������
	pNode current = p_target->firstChild;

	while (current->nextSibling != NULL)//������һ�����ӣ��򲻻�����ѭ��
	{
		current = current->nextSibling;//�ҵ����һ���ֵ�
	}

	cout << "������" << target << "����ӵĶ��ӣ���Ů���������֣�";

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
		Log::Warn("���޴��ˣ�����������");
		return false;
	}
	if (p_target->firstChild != NULL)
	{
		std::cout << "�ó�Ա���м�ͥ���Ƿ��Ϊ��Ӽ�ͥ��Ա?(y/Y--yes, n/N--no\n";
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

	cout << "������" << target << "�Ķ�Ů����(����Ӧ����0)\n";
	int kid_num = 0;

	cin >> kid_num;

	while (cin.fail() || kid_num < 1)
	{
		print("����������������룺");
		cin.clear();
		cin.ignore(65535, '\n');
		cin >> kid_num;
	}
	cout << "����������" << target << "�Ķ�Ů��������";

	string str_name;
	pNode before = NULL;//��������ֵ�ʱ����ѭ���������һ���ֵ�
	pNode newChild = NULL;

	while (kid_num--)
	{
		cin >> str_name;
		newChild = new TreeNode(str_name, p);//�º��ӵĸ��ڵ㶼��p

		if (newChild == NULL)
		{
			Log::Error("newChild is null in createFamily function");
			return false;
		}

		if (p->firstChild == NULL)
		{
			//Log::Info("create the first child");
			p->firstChild = newChild;
			before = newChild;//������һ����˵�����ε��º�����ǰһ���ֵ�
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
		print("������ɾ���������ף�ɾ����������¹������ף��Ƿ������(y/Y--yes , n/N--no)");
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

	if (p->parent->firstChild == p && p->nextSibling == NULL)//p�Ǹ��ڵ��Ψһһ������
	{
		Destory(p->firstChild);
		p->parent->firstChild = NULL;//���ڵ�û�к�����
		delete p;
		return true;
	}

	if (p->parent->firstChild == p)//delete the first child
	{
		Destory(p->firstChild);
		p->parent->firstChild = p->nextSibling;//���ڵ�ĵ�һ�����ӱ���˶���
		delete p;
		return true;
	}

	//���������������Ҫ�õ�p��ǰһ���ֵܣ������Ҫѭ���ҵ�ǰһ���ֵ�
	pNode target_before = p->parent->firstChild;
	while (target_before->nextSibling != p)
	{
		target_before = target_before->nextSibling;
	}

	//ʵ������������������һ������Ϊ���׶��Ի��Ǳ���������
	if (p->nextSibling == NULL)//delete the last child(ɾ���������һ������)
	{
		target_before->nextSibling = NULL;//ʵ���ϱ���������ĸ�ֵ����ͬ

		Destory(p->firstChild);
		delete p;
		return true;
	}
	//p���м��ĳһ������
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
		print("�ó�Աû�к���");
		return true;
	}
	std::cout << target << "�ĵ�һ�������ǣ�";

	pNode current = p->firstChild;
	while (current != NULL)
	{
		std::cout << current->getMember()->getName() << "     ";
		current = current->nextSibling;
	}
	return true;
}


// ��ʵ�ֽ���

// --- ���Ա����ʵ�ֽ��� ---