/*项目五  关键字检索系统*/
/*2053380 彭浩*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
//主要操作函数，在srcfile的文本文件中查询target出现了多少次
int  CountWord(const std::string& srcFile, std::string& target);
void DeleteComma(std::string& txt);
bool isLetter(char x) noexcept{//x 是否是一个字母
	return x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z';
}

int main()
{
	using namespace std;

	cout << "请输入文件名(最多30个字符，一个中文为两个字符)：\n";
	string srcName;
	cin >> srcName;

	fstream srcFile;
	srcFile.open(srcName.c_str(), ios::out | ios::trunc);

	/*当同时使用 cin >> , getline() 时，需要注意的是，在cin >> 输入流完成之后，getline()之前，需要通过
	str = "\n";
	getline(cin, str);
	的方式将回车符作为输入流cin以清除缓存，如果不这样做的话，在控制台上就不会出现getline()的输入提示，而直接跳过，因为程序默认地将之前的变量作为输入流。*/

	string get_a_char = string("\n");
	getline(cin, get_a_char);

	cout << "请输入一段英文：\n";
	string inputTxt;
	getline(cin, inputTxt);

	srcFile << inputTxt;
	srcFile.close();
	cout << "本段文本已经保持在" << srcName << "中\n";
	cout << "请输入要检索的单词: ";
	string target;
	cin >> target;

	cout << "显示源文件：\n";
	cout << inputTxt << endl;

	DeleteComma(inputTxt);
	string store_target = target;

	const int appear_num = CountWord(inputTxt, target);
	cout << "在源文件中共检索到： " << appear_num << "个关键字 " << store_target;

	std::cout << "\n\n按回车键以退出\n";
	std::cin.get();
	std::cin.get();

	return 0;

}

int CountWord(const std::string& srcFile, std::string& target)
{
	using namespace std;
	string temp_word;//临时存储单个单词
	transform(target.begin(), target.end(), target.begin(), ::toupper);

	stringstream input(srcFile);
	int count = 0;
	//<sstream>库定义了三种类：
	//istringstream、ostringstream和stringstream，分别用来进行流的输入、输出和输入输出操作
	while (input >> temp_word)
	{
		//统一大小写
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

	if(!isLetter(txt[txt.length() - 1]))//处理最后的
		txt[txt.length() - 1] = ' ';

	int i = 0, j = 0;
	bool trueCondition = true;

	while (txt[i] != '\0')
	{
		trueCondition =
			(txt[i] >= 'a' && txt[i] <= 'z')
			|| (txt[i] >= 'A' && txt[i] <= 'Z')
			|| txt[i] == ' ';
		if (trueCondition)//只保留英文大小写字母与空格
		{
			txt[j] = txt[i];
			j++;
		}
		i++;
	}

	txt[j] = '\0';
}



