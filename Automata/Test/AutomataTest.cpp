//#include "../stdafx.h"  // fatal error C1010: 在查找预编译头时遇到意外的文件结尾。是否忘记了向源中添加“#include "stdafx.h"”?
#include "stdafx.h"  // 虽然在Test目录下无此文件，但是却骗取了编译器，无上述错误了

void CRSetTest();
void StateSetTest();
void StateToStateSetTest();
void StateRelTest();
void TransTest();
void ThompsonTest();
void RFATest();

void AutomataTest()
{
	//CRSetTest();
	//StateSetTest();
	//StateToStateSetTest();
	//StateRelTest();
	//TransTest();
	//ThompsonTest();
	RFATest();
}