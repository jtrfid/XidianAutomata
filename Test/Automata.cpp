// Automata.cpp: 定义控制台应用程序的入口点。
//


#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "FiniteAutomata.h"

using namespace std;

void djtTest(); // djtTest.cpp

void AutomataTest();  // AutomataTest.cpp

void usage();

void hint();

bool generatedata(std::string filename);

struct CompareResult
{
	size_t n; 
	std::string temp1; 
	std::string temp2;
};

int main()
{
	std::string temp;
	FiniteAutomata ffa;
	bool flag = false; // 用来标记 3 选项是否被执行过
	usage();
	while (cin>>temp)
	{
		if (temp=="g"||temp=="1")
		{
			system("cls");
			std::cout << "\n\n\n\n             processing" << std::endl;
			if (generatedata("Standard_Data.txt"))
			{
				std::cout << "             process done!" << endl;
			}
			hint();
			usage();
		}
		else if (temp == "c" || temp == "2")
		{
			system("cls");
			std::cout << "\n\n\n\n             processing..." << std::endl;
			if (!generatedata("Data.txt"))
			{
				continue;
			}

			std::ifstream sdata;  // Standard Data
			sdata.open("Standard_Data.txt", ios::in);
			if (sdata.eof())
			{
				cout << " no such a File : Standard_Data.txt" << endl;
				hint();
				continue;
			}

			std::ifstream data;  // Data
			data.open("Data.txt", ios::in);
			if (data.eof())
			{
				cout << " no such a File : Data.txt" << endl;
				hint();
				continue;
			}
			
			std::cout << "             process done!" << endl;
			std::cout << "             compare standard data and current data..." << endl;

			std::vector<CompareResult> result;
			CompareResult cr;
			std::string temp1, temp2;
			size_t counter = 0;
			bool end1 = false;
			bool end2 = false;
			while (true)
			{
				if (!(getline(sdata, temp1)))
				{
					end1 = true;
				}

				if (!(getline(data, temp2)))
				{
					end2 = true;
				}

				if (end1&&end2)
				{
					break;
				}
				counter++;
				if (temp1 != temp2)
				{
					cr.n = counter;
					cr.temp1 = temp1;
					cr.temp2 = temp2;
					result.push_back(cr);
				}
				temp1 = "";
				temp2 = "";
			}
			
			if (!result.empty())
			{
				std::cout << "something changed:" << std::endl;
				for (auto iter = result.begin(); iter != result.end(); iter++)
				{
					std::cout << "\nline :" << iter->n << endl;
					std::cout << "Standard data :" << iter->temp1 << endl;
					std::cout << "current  data :" << iter->temp2 << endl;
				}
			}
			else
			{
				std::cout << "             compare done!" << endl;
				std::cout << "             Standard data = current  data\n             Nothing changed!" << std::endl;
			}
			hint();
			result.clear();
			usage();

		}
		else if (temp == "f" || temp == "3")
		{
			system("cls");
			cin >> ffa;  // 通过控制台输入，简化 TCT 的输入过程。

			// 生成的类 DFA 的对象
			DFA_components dfa_com = ffa.getDFA();
			DFA dfa1(dfa_com); 

			std::cout << "Now you have a object of TCT Tool and class DFA\n" << std::flush;
			
			std::cout << dfa1 << std::endl;// 简单的把 DFA 对象输出来看一下，也可以用这个 DFA 的对象干别的事情。



			hint();
			flag = true;
			usage();
		}
		else if (temp == "d" || temp == "4")
		{
			system("cls");
			if (!flag)
			{
				std::cout << "before execute this step, you must execute step 3(d)" << std::endl;
			}
			else
			{
				std::string tctfilename;
				std::cout << "type in file name : " << endl;
				while (std::cin>>tctfilename)
				{
					if (!tctfilename.empty())
						break;
				}
				int i = tctfilename.find(".ADS");
				if (i == -1)
				{
					tctfilename += ".ADS";
				}
				std::transform(tctfilename.begin(), tctfilename.end(), tctfilename.begin(), ::toupper); // 把输出文件名转换成大写
				ffa.perform(tctfilename);
				std::cout << "See details at : " << tctfilename << endl;
			}
			hint();
			usage();
		}
		else if (temp == "r" || temp == "5")  // 读入一个ADS文件，实例化一个DFA对象
		{
			system("cls");
			std::cout << "type in the .ADS file's name: " << std::flush;
			std::string filename;
			std::cin >> filename;
			while (filename == "")
			{
				std::cin >> filename;
			}
			if (-1 == filename.find(".ads") && -1 == filename.find(".ADS"))
			{
				filename += ".ADS";
			}

			//std::transform(filename.begin(), filename.end(), filename.begin(), ::toupper); // 把输出文件名转换成大写

			if (ffa.adsToDFA(filename))
			{
				DFA_components  dfa_com = ffa.getDFA();
				DFA dfa1(dfa_com);
				std::cout << dfa1 << std::endl; //简单的输出一下
			}
			hint();
			usage();
		}
		else if(temp=="q"||temp=="6")
		{
			break;
		}
		else if (temp == "t" || temp == "7")
		{
		   djtTest();
		   system("pause");
		   break;
        }
		else
		{
		usage();
		}
	}

	return 0;
}

void usage()
{
	system("cls");
	std::cout << "#######################################################################################################" << std::endl;
	std::cout << "##                                                                                                   ##\n" << std::flush;
	std::cout << "##                                                                                                   ##\n" << std::flush;
	std::cout << "##        g , type g or 1 to generate a standard data                                                ##\n" << std::flush;
	std::cout << "##        c , type c or 2 compare with the standard data                                             ##\n" << std::flush;
	std::cout << "##        f , type f or 3 to type in a DFA for TCT Tool and get a DFA's object for the FIRE engine   ##\n" << std::flush;
	std::cout << "##        d , type d or 4 to generate a ADS file for TCT Tools(after step 3)                         ##\n" << std::flush;
	std::cout << "##        r , type r or 5 to read in a ADS file to instant an object of DFA                          ##\n" << std::flush;
	std::cout << "##        q , type q or 6 to quit                                                                    ##\n" << std::flush;
	std::cout << "##        t , type t or 7 to test                                                                    ##\n" << std::flush;
	std::cout << "##                                                                                                   ##\n" << std::flush;
	std::cout << "##                                                                                                   ##\n" << std::flush;
	std::cout << "#######################################################################################################" << std::endl;
}

void hint()
{
	fflush(stdin);
	std::cout << "\n\n  press Enter to continue" << endl;
	char c;
	c = getchar();
	c = 0;
	while (c=getchar())
	{
		if (c == '\n')
			break;
	}
}

bool generatedata(std::string filename)
{
	// 重定向 cout 的数据到文件
	std::ofstream fs;
	fs.open(filename.c_str(), ios::out | ios::trunc); // 删除并新建文件

	if (!fs)  // 如果没能打开成功
	{
		return false;
	}

	streambuf *stream_buffer_cout = cout.rdbuf(); // cout buffer
	streambuf *stream_buffer_file = fs.rdbuf(); // file buffer
	cout.rdbuf(stream_buffer_file);

	AutomataTest();

	// 恢复 cout 的数据到标准输出
	fs.close();
	std::cout.rdbuf(stream_buffer_cout);

	return true;  

}


