// Automata.cpp: 定义控制台应用程序的入口点。
//


#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "TCTHelper.h"

using namespace std;

void AutomataTest();  // AutomataTest.cpp

void djtTest();      // void djtTest.cpp

void usage();

void hint();

bool generatedata(std::string filename);

bool compare(std::string file1, std::string file2);

#ifdef _WIN32
#include<Windows.h>
#include<fileapi.h>
// 创建用于存放ADS文件的文件夹
bool createADSdirectory();
#endif // _WIN32

// Windows 系统与 Linux 系统的清屏命令不一样
#ifdef _WIN32
#define CLSINFO "cls"
#else
#define CLSINFO "clear"
#endif // _WIN32


int main()
{
#ifdef _WIN32
	if (!createADSdirectory())
	{
		std::cout << "Can't create directory \"ADS\" " << std::endl;
		hint();
		return 0;
	}
#endif // _WIN32

	std::string temp;
	TCTHelper ffa;
	bool flag = false; // 用来标记 3 选项是否被执行过
	usage();
	while (cin>>temp)
	{
		if (temp=="g"||temp=="1")      //     选项 1，生成一个标准文件
		{
			system(CLSINFO);
			std::cout << "\n\n\n\n             processing" << std::endl;
			if (generatedata("Standard_Data.txt"))
			{
				std::cout << "             process done!" << endl;
			}
			hint();
			usage();
		}
		else if (temp == "c" || temp == "2")  //   选项 2 ，生成本次的数据，并与标准数据进行比较
		{
			system(CLSINFO);
			std::cout << "\n\n\n\n             processing..." << std::endl;
			if (!generatedata("Data.txt"))
			{
				continue;
			}

			std::cout << "             process done!" << endl;
			std::cout << "             compare standard data and current data..." << endl;

			compare("Standard_Data.txt", "Data.txt");

			hint();
			usage();

		}
		else if (temp == "f" || temp == "3")    // 选项  3，从键盘输入一个DFA
		{
			system(CLSINFO);
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
		else if (temp == "d" || temp == "4")   // 选项 4，把第三步生成的DFA转换成ADS文件。
		{
			system(CLSINFO);
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
		else if (temp == "r" || temp == "5")  // 选项5，读入一个ADS文件，实例化一个DFA对象
		{
			system(CLSINFO);
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
			cout << "\nEnter any char for exist!";
			cin.get(); // 消费上一cin的'\n'
			cin.get();
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
	system(CLSINFO);
	std::cout << "#######################################################################################################" << std::endl;
	std::cout << "##                                                                                                    ##\n" << std::flush;
	std::cout << "##                                                                                                    ##\n" << std::flush;
	std::cout << "##        g , type g or 1 for generate a standard data (Standard_Data.txt)                            ##\n" << std::flush;
	std::cout << "##        c , type c or 2 for compare with the standard data (Standard_Data.txt and Data.txt)         ##\n" << std::flush;
	std::cout << "##        f , type f or 3 for type in a DFA for TCT Tool and get a DFA's object for the FIRE engine   ##\n" << std::flush;
	std::cout << "##        d , type d or 4 for generate a ADS file for TCT Tools(after step 3)                         ##\n" << std::flush;
	std::cout << "##        r , type r or 5 for read in a ADS file to instant an object of DFA                          ##\n" << std::flush;
	std::cout << "##        q , type q or 6 for quit                                                                    ##\n" << std::flush;
	std::cout << "##        t , type t or 7 for test                                                                    ##\n" << std::flush;
	std::cout << "##                                                                                                    ##\n" << std::flush;
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

bool compare(std::string file1, std::string file2)
{

	std::ifstream sdata;  // Standard Data
	sdata.open(file1.c_str(), ios::in);
	if (sdata.eof())
	{
		cout << " no such a File : " << file1 << endl;
		hint();
		return false;
	}

	std::ifstream data;  // Data
	data.open(file2.c_str(), ios::in);
	if (data.eof())
	{
		cout << " no such a File : "<< file2 << endl;
		hint();
		return false;
	}

	struct CompareResult
	{
		size_t n;
		std::string temp1;
		std::string temp2;
	};

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
		size_t i = 0;

		std::ofstream resultlog;
		resultlog.open("resultlog.txt", ios::out | ios::trunc);

		for (auto iter = result.begin(); iter != result.end(); iter++)
		{
			i++;
			if (i < 4)
			{
				std::cout << "\nline :" << iter->n << endl;
				std::cout << "Standard data :" << iter->temp1 << endl;
				std::cout << "current  data :" << iter->temp2 << endl;
			}
			resultlog << "\nline :" << iter->n << endl;
			resultlog << "Standard data :" << iter->temp1 << endl;
			resultlog << "current  data :" << iter->temp2 << endl;
		}
		if (i > 4)
		{
			std::cout << "See more info at resultlog.txt" << std::endl;
		}
		resultlog.close();
	}
	else
	{
		std::cout << "             compare done!" << endl;
		std::cout << "             Standard data = current  data\n             Nothing changed!" << std::endl;
	}
	result.clear();
	return true;
}

#ifdef _WIN32
bool createADSdirectory()
{
	DWORD ftyp = GetFileAttributesA("ADS");
	if (ftyp == INVALID_FILE_ATTRIBUTES) //检查文件夹是否存在
	{
		if (CreateDirectory("ADS", NULL))  //不存在则创建它
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
#endif // _WIN32

