#include "TCTHelper.h"


TCTHelper::TCTHelper()
{
	adsDirectory = "ADS/";
	quite = false;
}

// 通过str(通常为DFA的输出字符串)构造TCTHelper对象
TCTHelper::TCTHelper(std::string str)
{
	adsDirectory = "ADS/";
	analyze(str);
}

// 通过dfa构造TCTHelper对象
TCTHelper::TCTHelper(DFA & dfa)
{
	adsDirectory = "ADS/";
	std::stringstream ss;
	ss << dfa;
	std::string temp = ss.str();
	analyze(temp);
	ss.str("");
}


TCTHelper::~TCTHelper()
{
}

// 通过str(通常为DFA的输出字符串)重新构造当前对象
TCTHelper & TCTHelper::reconstruct(std::string str)
{
	this->Trans.clear();
	this->F.clear();
	this->Q.clear();
	this->V.clear();
	this->theDFA = "";
	this->num_state = 0;
	analyze(str);
	return (*this);
}

// 状态数
size_t TCTHelper::size()
{
	return num_state;
}

// 处理DFA输出的一行字符串
// 返回本行末尾字符'\n'的位置索引。如果处理结束，返回std::string::npos。
std::string::size_type TCTHelper::processLine(const std::string &str,std::string::size_type pos1)
{
	std::string line="";
	std::string::size_type pos2 = 0, pos3 = 0, pos4 = 0;
	std::string ss = "";
	pos2 = str.find_first_of('\n', pos1);
	if (pos2 == std::string::npos) return std::string::npos;

	line = str.substr(pos1, pos2-pos1); // 不包含行尾的'\n' 

	// 处理行，形如：Q = [0,20)，提取状态数
	if (line[0] == 'Q') 
	{
		pos3 = line.find_first_of(',', 0);
		pos4 = line.find_last_of(')');
		assert(pos3 != std::string::npos);
		assert(pos4 != std::string::npos);
		ss = line.substr(pos3 + 1, pos4 - pos3 - 1);
		num_state = stoi(ss);
		return pos2;
	}

	// 处理行，形如：F = { 1  2 }，提取接受状态，即使多个F，DFA输出也是在一行中。
	if (line[0] == 'F') 
	{
		pos4 = line.find_first_of('{', 0);
		assert(pos4 != std::string::npos);
		while (1) // 获得每个F
		{
			pos3 = line.find_first_not_of(' ', pos4 + 1); // not ' '
			assert(pos3 != std::string::npos);
			if (line[pos3] == '}') break; // F结束
			pos4 = line.find_first_of(' ', pos3+1); // ' '
			assert(pos4 != std::string::npos);
			ss = line.substr(pos3, pos4 - pos3); 
			F.push_back(stoi(ss));
		}
		return pos2;
	}

	// 处理行：Transitions =
	if (line[0] == 'T') // ex.
	{
		// 此行就是Transitions ='\n',下一行才是实质行
		transitionsLineNum = 0; // 总共将处理的行数等同于num_state
		return pos2;
	}
	else if(line.empty() || line[0] <'0' || line[0] > '9')
	{
		return pos2; // 防止意外行，例如空行或其他输出行(如DFA)，程序执行到此处，必须返回。
	}

	// 处理transitions line,形如：10->{ 'b'->19  '9'->12  'd'->8  ['c','e']->9 }，或15->{ ['C','E']->8  ['c','e']->9  'f'->12 }，或19->{}
	// 总共将处理的行数等同于num_state
	if (transitionsLineNum >= num_state) // 处理结束
	{
		return std::string::npos;
	}
	else
	{
		transitionsLineNum++;
		Transition T1;
		pos4 = line.find_first_of('-', 0);
		assert(pos4 != std::string::npos);
		ss = line.substr(0, pos4);
		T1.stprime = stoi(ss);  // 本行开始处的状态编号是本行所有Transitions的source

		// 以下删除式处理{ .... }
		pos3 = line.find_first_of('{', pos4);
		assert(pos3 != std::string::npos);
		pos4 = line.find_last_of('}');
		assert(pos4 != std::string::npos);
		line = line.substr(pos3 + 1, pos4 - pos3 - 1); // [pos, pos+count)

		// 删除式处理多个形如: ['c','e']->9
		std::string::size_type pos_s = 0, pos_e = 0;
		while (1)
		{
			pos_s = line.find_first_of('[', 0);
			if (pos_s == std::string::npos) break;
			pos3 = line.find_first_of(']', pos_s + 1);
			assert(pos3 != std::string::npos);
			pos_e = line.find_first_of(' ', pos3 + 1);
			assert(pos_e != std::string::npos);

			char sc = line[pos_s + 2], ec = line[pos3 - 2]; // ['c','e']
			pos3 = pos3 + 3; // ->9
			ss = line.substr(pos3, pos_e - pos3);
			T1.stdest = stoi(ss);
			for (label c = sc; c <= ec; c++)
			{
				T1.T = toADS_V(c);
				Trans.push_back(T1);
			}
			line.erase(pos_s, pos_e); // 用完即删
		}
		// 删除式处理多个形如: 'b'->19 
		while (line.size() > 0)
		{
			pos3 = line.find_first_of('-', 0);
			if (pos3 == std::string::npos) break;
			pos_s = pos3 - 3;
			pos_e = line.find_first_of(' ', pos_s);
			assert(pos_e != std::string::npos);
			T1.T = toADS_V(line[pos_s + 1]);
			pos3 = pos_s + 5;
			ss = line.substr(pos3, pos_e - pos3);
			T1.stdest = stoi(ss);
			Trans.push_back(T1);
			line.erase(pos_s, pos_e); // 用完即删
		}
	} // 处理transitions_line

	return pos2;
}

// 将DFA的输出字符串解析成为本类可以识别的格式。
// 开始状态编号均为整数0
bool TCTHelper::analyze(std::string& str)
{
	theDFA = str;

	std::string::size_type pos1 = 0, pos2 = 0;
	std::string line="";
	bool transitions_line = false; 
	while (1)
	{
		pos2 = processLine(str, pos1); // 处理str的每行
		if (pos2 == std::string::npos) break;
		pos1 = pos2+1;
	}

	std::sort(F.begin(), F.end());

	std::sort(Trans.begin(), Trans.end());

	return false;
}

// 当前对象生成DFA_components对象
DFA_components TCTHelper::getDFA()
{
	
	DFA_components ret;

	size_t i = num_state;
	while (i--)
	{
		ret.Q.allocate();
	}

	ret.S.set_domain(ret.Q.size());
	ret.S.add(0);

	ret.F.set_domain(ret.Q.size());
	for (auto it = this->F.begin(); it != this->F.end(); it++)
	{
		ret.F.add((*it));
	}

	ret.T.set_domain(ret.Q.size());

	for (auto it = this->Trans.begin(); it != this->Trans.end(); it++)
	{
		ret.T.add_transition(it->stprime, toDFA_V(it->T), it->stdest);
	}
	return ret;
}

// 依据ADS/adsfilename.ADS文件，生成当前对象
bool TCTHelper::adsToDFA(std::string adsfilename)
{
	std::ifstream ifile;
	adsfilename = adsDirectory + adsfilename;
	ifile.open(adsfilename.c_str(), std::ios::in);
	if (!ifile)
	{
		std::cout << "No such a file: " << adsfilename << std::endl;
		return false;
	}

	std::string temp;

	// State size(State set will be(0, 1...., size - 1)) :
	while (1)
	{
		assert(!ifile.eof());
		if (ifile.eof())
		{
			std::cout << "Not a ADS file: " << adsfilename << std::endl;
			return false;
		}
		std::getline(ifile, temp);
		if (temp.find("State size") != std::string::npos) break;
	}
	while (1)
	{
		assert(!ifile.eof());
		if (ifile.eof())
		{
			std::cout << "Not a ADS file: " << adsfilename << std::endl;
			return false;
		}
		std::getline(ifile, temp);
		if (temp.empty() || temp[0] == '#') continue;  // 空行或注释行
		else break;
	}
	num_state = stoi(temp);

	//  Marker states:
	while (1)
	{
		assert(!ifile.eof());
		if (ifile.eof())
		{
			std::cout << "Not a ADS file: " << adsfilename << std::endl;
			return false;
		}
		std::getline(ifile, temp);
		if (temp.find("Marker states") != std::string::npos) break;
	}
	while (1)
	{
		assert(!ifile.eof());
		if (ifile.eof())
		{
			std::cout << "Not a ADS file: " << adsfilename << std::endl;
			return false;
		}
		std::getline(ifile, temp);
		if (temp.empty() || temp[0] == '#') continue;  // 空行或注释行
		else if (temp.find("Vocal states") != std::string::npos) break;
		else
		{
			this->F.push_back(stoi(temp));  // 接受状态
		}
	}
	
	// Vocal states:
	while (1)
	{
		assert(!ifile.eof());
		if (ifile.eof())
		{
			std::cout << "Not a ADS file: " << adsfilename << std::endl;
			return false;
		}
		std::getline(ifile, temp);
		if (temp.find("Transitions:") != std::string::npos) break;
	}

	// Transitions:
	state stprime;
	label llb;
	state stdest;
	Transition T;
	while (1)
	{
		if (ifile.eof()) break;
		std::getline(ifile, temp);
		if (temp.empty() || temp[0] == '#') continue;  // 空行或注释行
		else 
		{
			std::stringstream ss;
			ss << temp;
			ss >> stprime >> llb >> stdest;
			T.stprime = stprime;
			T.T = llb;
			T.stdest = stdest;
			Trans.push_back(T);
		}
	}

	return true;
}

// 当前对象生成默认的ADS/DFA.ADS文件
bool TCTHelper::perform()
{
	// 输出数据到默认的文件“DFA.ADS”
	assert(num_state > 0);
	return perform("DFA.ADS");
}

// 当前对象生成ADS/filepath.ADS文件
bool TCTHelper::perform(std::string filepath)
{
	assert(num_state > 0);
	filepath = adsDirectory + filepath;
	std::ofstream ofile;
	ofile.open(filepath.c_str());
	if (!ofile.is_open())
	{
		std::cout << "Can't open file: " << filepath << std::endl;
		return false;
	}
	ofile << (*this);
	ofile.close();
	return true;
}

// DFA对象生成.ADS文件
bool TCTHelper::perform(DFA & dfa, std::string filepath)
{
	clear();
	std::string temp;
	std::stringstream ss;
	ss << dfa;
	temp = ss.str();
	analyze(temp);
	perform(filepath);
	return true;
}

TCTHelper& TCTHelper::clear()
{
	this->Trans.clear();
	this->F.clear();
	this->Q.clear();
	this->V.clear();
	this->theDFA = "";
	this->num_state = 0;
	return (*this);
}

bool TCTHelper::operator==(TCTHelper & D)
{
	if (num_state != D.num_state)
		return false;
	if (F.size() != D.F.size())
		return false;
	for (auto iter = F.begin(), iter2 = D.F.begin() ; iter != F.end() && iter2 != D.F.end(); iter++,iter2++)
	{
		if (*iter != *iter2)
			return false;
	}

	if (Trans.size() != D.Trans.size())
		return false;
	for (auto iter = Trans.begin(), iter2 = D.Trans.begin(); iter != Trans.end() && iter2 != D.Trans.end(); iter++, iter2++)
	{
		if (*iter != *iter2)
			return false;
	}
	return true;
}

bool TCTHelper::check(const state& t)
{
	if (t < num_state && t >= 0)
		return true;
	else
		return false;
}


std::istream& operator>>(std::istream& input, TCTHelper& D)
{
	D.clear();
	if (!D.quite)
	{
		std::cout << "input the number of state of the FA (type: unsigned int):" << std::endl;
	}
	
	input >> D.num_state;
	state temp;
	
	std::vector<state>::iterator result;
	std::vector<label>::iterator result2;
	if (!D.quite)
	{
		std::cout << "input the accepted state of the FA(type: unsigned int ,end with -1):" << std::endl;
	}
	
	while (input >> temp)
	{
		if (temp == -1)
			break;
		if (D.check(temp))
		{
			//D.F.push_back(temp);
			result = std::find(D.F.begin(), D.F.end(), temp);
			if (result == D.F.end())
			{
				D.F.push_back(temp);
			}
		}
		else
		{
			std::cout << "Invalid value: " << temp << std::endl;
		}

	}

	if (!D.quite)
	{
		std::cout << "input the transition relation of the FA(type: unsigned int ,end with -1)" << std::endl;
		std::cout << "Example: 2 0 1 (for transition labeled 0 from state 2 to state 1).  :" << std::endl;
		std::cout << "input label: [0,61]。 It's  map: [0,9] ==> ['0','9'], [10,35] ==> ['a','z'],  [36,61] ==> ['A','Z']" << endl;
	}
	
	Transition trans;
	
	// 输入转移关系
	while (input >> trans.stprime)
	{
		if (trans.stprime == -1)
			break;
		input >> trans.T >> trans.stdest;
		//if (D.check(trans.stprime) && D.check(trans.T) && D.check(trans.stdest)) //如果输入的转移关系有效
		if (D.check(trans.stprime) && D.check(trans.stdest) && trans.T >= 0 && trans.T <= 61) //如果输入的转移关系有效
		{
			// 将状态存入状态集
			D.Trans.push_back(trans);
			result = std::find(D.Q.begin(), D.Q.end(), trans.stprime);
			if (result == D.Q.end())
			{
				D.Q.push_back(trans.stprime);
			}
			result = std::find(D.Q.begin(), D.Q.end(), trans.stdest);
			if (result == D.Q.end())
			{
				D.Q.push_back(trans.stdest);
			}

			// 将“输入字符”保存
			result2 = std::find(D.V.begin(), D.V.end(), trans.T);
			if (result2 == D.V.end())
			{
				D.V.push_back(trans.T);
			}
		}
		else
		{
			std::cout << "Invalid argument: " << trans.stprime << " " << trans.T << " " << trans.stdest << std::endl;
		}
		trans.stprime = 0;
		trans.T = 0;
		trans.stdest = 0;
	}
	return input;
}

std::ostream & operator<<(std::ostream & output, TCTHelper & D)
{
	output << "# CTCT ADS auto-generated\n" << std::endl;
	output << "FA\n" << std::endl;
	output << "State size (State set will be (0,1....,size-1)):\n# <-- Enter state size, in range 0 to 2000000, on line below." << std::endl;
	output << D.num_state << std::endl;
	output << "\nMarker states:\n# <-- Enter marker states, one per line.\n# To mark all states, enter *.\n# If no marker states, leave line blank.\n# End marker list with blank line." << std::endl;
	
	for (auto it = D.F.begin(); it != D.F.end(); ++it)
	{
		output << *it << std::endl;
	}
	output << "\nVocal states:\n# <-- Enter vocal output states, one per line.\n# Format: State  Vocal_Output.Vocal_Output in range 10 to 99.\n# Example : 0 10\n# If no vocal states, leave line blank.\n# End vocal list with blank line.\n" << std::endl;
	output << "Transitions:\n# <-- Enter transition triple, one per line.\n# Format: Exit_(Source)_State  Transition_Label  Entrance_(Target)_State.\n# Transition_Label in range 0 to 999.\n# Example: 2 0 1 (for transition labeled 0 from state 2 to state 1)." << std::endl;
	output << "# DFA Label to ADS: ['0','9'] ==> [0,9],['a','z'] ==> [10,35],['A','Z'] ==> [36,61]" << endl;
	
	for (auto iter = D.Trans.begin(); iter != D.Trans.end(); iter++)
	{
		output << iter->stprime << " " << iter->T << " " << iter->stdest << std::endl;
	}
	
	return output;
}

/*******************************************
 按照约定，DFA转移表字母的整数值:
 case 1: ['0','9'] <== [0,9]
 case 2: ['a','z'] <== [10,35]
 case 3: ['A','Z'] <== [36,61]
 other case is illegal.
 *******************************************/
char TCTHelper::toDFA_V(label v)
{
	label ret;
	if (v >= 0 && v <= 9) // ['0','9'] <== [0,9]
		ret = v + '0';
	else if (v >= 10 && v <= 35) // ['a','z'] <== [10,35]
		ret = v + 'a' - 10;
	else if (v >= 36 && v <= 61) // ['A','Z'] <== [36,61]
		ret = v + 'A' - 36;
	else
		assert(0); // illegal

	return ret;
}

/*******************************************
 按照约定，DFA转移表字母的整数值:
 case 1: ['0','9'] ==> [0,9]
 case 2: ['a','z'] ==> [10,35]
 case 3: ['A','Z'] ==> [36,61]
 other case is illegal.
 *******************************************/
label TCTHelper::toADS_V(char v)
{
	int ret;
	if (v >= '0' && v <= '9') // ['0','9'] ==> [0,9]
		ret = v - '0';
	else if (v >= 'a' && v <= 'z') // ['a','z'] ==> [10,35]
		ret = v - 'a' + 10;
	else if (v >= 'A' && v <= 'Z') // ['A','Z'] ==> [36,61]
		ret = v - 'A' + 36;
	else
		assert(0); // illegal

	return ret;
}

/*******************************************
 按照约定，字母必须是['0','9'] || ['a','z'] || ['A','Z'].
 other case is illegal.
 *******************************************/
bool TCTHelper::isV(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))  return true;
	else return false;
}