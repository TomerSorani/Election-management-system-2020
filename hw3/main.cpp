#define _CRT_SECURE_NO_WARNINGS
#include "simpleElectionRound.h"
#include "menu.h"
using namespace std;
using namespace elections;
enum choise { one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, eleven = 11, twelve = 12 };
void main()
{
	menu m;
	int num;
	electionRound* ed;
	m.printStartMenu();
	cin >> num;
	if (num == three)
		exit(-1);
	else if (num == two)
		ed = m.twoStart();
	else
		ed = m.oneStart();

	bool flag = true;
	while (flag)
	{
		m.printMainMenu();
		cin >> num;
		if (num == one)
			m.one(ed);
		else if (num == two)
			m.two(ed);
		else if (num == three)
			m.three(ed);
		else if (num == four)
			m.four(ed);
		else if (num == five)
			m.five(ed);
		else if (num == six)
			m.six(ed);
		else if (num == seven)
			m.seven(ed);
		else if (num == eight)
			m.eight(ed);
		else if (num == nine)
			m.nine(ed);
		else if (num == ten)
		{
			m.ten(ed);
			flag = false;
		}
		else if (num == eleven)
			m.eleven(ed);
		else if (num == twelve)
			ed=m.twelve(ed);
	}
}