#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

string user_input;
float number = 1.0f;
float rightCount = 0.0f;
float wrongCount = 0.0f;
vector<string> wrongList;

bool isSame(string str1, string str2)
{
	return strcmp(str1.c_str(), str2.c_str()) ? 0 : 1;
}

string split(string str, int h, int e)
{
	for (int i = 0; i < h; i++)
		str[i] = '\0';
	for (int j = e; j < str.length(); j++)
		str[j] = '\0';
	return str;
}

string bSplit(string str, char c = ' ')
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] == c)
		{
			str = split(str, i, str.length());
			break;
		}
	return str;
}

string fSplit(string str, char c = ' ')
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] == c)
		{
			str = split(str, 0, i);
			break;
		}
	return str;
}

class Word
{
public:
	string word;
	string mean;

	Word(string str)
	{
		word = fSplit(str);
		mean = bSplit(str);
	}
};

void Read(int order = 0)
{
	ifstream ifs;
	string data;

	ifs.open("wl/wordlist.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "无法打开文件\n";
		return;
	}

	bool start = false;
	while (ifs.good())
	{
		bool isFailed = false;
		bool isRec = false;
		getline(ifs, data);

		if (data[0] == '-' || data == "")
		{
			continue;
		}

		Word word(data);

		while (true)
		{
			system("cls");
			cout << "第" << number << "个" << "    "
				<< "正确: " << rightCount << "    "
				<< "错误: " << wrongCount << "\n\n";
			cout << word.mean << '\n';
			if (order == 0)
			{
				cout << word.word << '\n';
			}

			cin >> user_input;
			if (user_input == "<q>")
			{
				return;
			}

			if (isSame(user_input, word.word))
			{
				isRec = false;
				rightCount += isFailed ? 0 : 1;
				number++;
				break;
			}
			else
			{
				isFailed = true;
				if (!isRec)
				{
					wrongCount++;
					wrongList.push_back(data);
				}
				isRec = true;
				continue;
			}
		}
	}
	ifs.close();
}

void Write()
{
	Read(1);
}

void Conclusion()
{
	system("cls");
	float acc = (rightCount / --number) * 100;
	cout << "共" << number << "个" << "    "
		<< "正确: " << rightCount << "    "
		<< "错误: " << wrongCount << '\n';
	if (number != 0)
		cout << "正确率: " << acc << "%" << "\n\n";
	cout << "错误的单词: \n\n";

	for (int i = 0; i < wrongList.size(); i++)
	{
		cout << wrongList[i] << '\n';
	}
	cout << '\n';
	system("pause");
}

int main()
{
	int i;
	while (true)
	{
		system("cls");
		cout << "[1] 退出\n"
			<< "[2]记忆模式\n"
			<< "[3]默写模式\n"
			<< "请输入： [ ]\b\b";
		cin >> i;
		if (i == 1)
			return 0;
		if (i == 2 || i == 3 || i == 4)
			break;
	}
	

	if (i == 2)
		Read();

	if (i == 3)
		Write();

	Conclusion();
	return 0;
}
