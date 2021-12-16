/*��Ŀ��  �ؼ��ּ���ϵͳ*/
/*2053380 ���*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
//��Ҫ������������srcfile���ı��ļ��в�ѯtarget�����˶��ٴ�
int  CountWord(const std::string& srcFile, std::string& target);
void DeleteComma(std::string& txt);
bool isLetter(char x) noexcept{//x �Ƿ���һ����ĸ
	return x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z';
}

int main()
{
	using namespace std;

	cout << "�������ļ���(���30���ַ���һ������Ϊ�����ַ�)��\n";
	string srcName;
	cin >> srcName;

	fstream srcFile;
	srcFile.open(srcName.c_str(), ios::out | ios::trunc);

	/*��ͬʱʹ�� cin >> , getline() ʱ����Ҫע����ǣ���cin >> ���������֮��getline()֮ǰ����Ҫͨ��
	str = "\n";
	getline(cin, str);
	�ķ�ʽ���س�����Ϊ������cin��������棬������������Ļ����ڿ���̨�ϾͲ������getline()��������ʾ����ֱ����������Ϊ����Ĭ�ϵؽ�֮ǰ�ı�����Ϊ��������*/

	string get_a_char = string("\n");
	getline(cin, get_a_char);

	cout << "������һ��Ӣ�ģ�\n";
	string inputTxt;
	getline(cin, inputTxt);

	srcFile << inputTxt;
	srcFile.close();
	cout << "�����ı��Ѿ�������" << srcName << "��\n";
	cout << "������Ҫ�����ĵ���: ";
	string target;
	cin >> target;

	cout << "��ʾԴ�ļ���\n";
	cout << inputTxt << endl;

	DeleteComma(inputTxt);
	string store_target = target;

	const int appear_num = CountWord(inputTxt, target);
	cout << "��Դ�ļ��й��������� " << appear_num << "���ؼ��� " << store_target;

	std::cout << "\n\n���س������˳�\n";
	std::cin.get();
	std::cin.get();

	return 0;

}

int CountWord(const std::string& srcFile, std::string& target)
{
	using namespace std;
	string temp_word;//��ʱ�洢��������
	transform(target.begin(), target.end(), target.begin(), ::toupper);

	stringstream input(srcFile);
	int count = 0;
	//<sstream>�ⶨ���������ࣺ
	//istringstream��ostringstream��stringstream���ֱ����������������롢����������������
	while (input >> temp_word)
	{
		//ͳһ��Сд
		transform(temp_word.begin(), temp_word.end(), temp_word.begin(), ::toupper);

		if (temp_word == target)
		{
			count++;
		}
	}
	return count;
}

void DeleteComma(std::string& txt)
{
	using namespace std;

	if(!isLetter(txt[txt.length() - 1]))//��������
		txt[txt.length() - 1] = ' ';

	int i = 0, j = 0;
	bool trueCondition = true;

	while (txt[i] != '\0')
	{
		trueCondition =
			(txt[i] >= 'a' && txt[i] <= 'z')
			|| (txt[i] >= 'A' && txt[i] <= 'Z')
			|| txt[i] == ' ';
		if (trueCondition)//ֻ����Ӣ�Ĵ�Сд��ĸ��ո�
		{
			txt[j] = txt[i];
			j++;
		}
		i++;
	}

	txt[j] = '\0';
}



