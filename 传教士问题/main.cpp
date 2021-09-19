#include <iostream>
using namespace std;
struct States {
	int leftmen;		//左岸的传教士数量
	int leftsavages;		//左岸的野人数量
	int rightmen = 0;		//右岸的传教士数量
	int rightsavages = 0;	//右岸的野人数量
	bool boat = 0;			//表示船的位置，0：位于左岸，1：位于右岸
};

States states[500];		//保存每一步后的情况
States solution[500];	//用来保存一条最佳路径
int solutioncount = 0;
int shortest = 0;
int step = 0, temp = 1;
int boatload;
int n;

void showSolution()
{
	solutioncount++;
	cout << "第" << solutioncount << "种方案";
	for (int i = 0; i < step; i++)
		cout << states[i].leftmen << states[i].leftsavages
		<< states[i].boat << "-->";
	cout << states[step].leftmen << states[step].leftsavages
		<< states[step].boat << endl;
	if (shortest == 0)		//存储最短路径
	{
		for (int i = 0; i < step; i++)
			solution[i] = states[i];
	}
	else if (step < shortest) {
		for (int i = 0; i < step; i++)
			solution[i] = states[i];
	}
}

bool isSafe() {
	if ((states[temp].leftmen >= 0) && (states[temp].leftsavages >= 0) &&
		(states[temp].rightmen >= 0) && (states[temp].rightsavages >= 0))
	{
		if ((states[temp].leftmen < states[temp].leftsavages) &&
			(states[temp].leftmen != 0))
			return false;
		else if ((states[temp].rightmen < states[temp].rightsavages) &&
			(states[temp].rightmen != 0))
			return false;
		else return true;
		
	}
	else return false;
}

bool isrepeat() {
	for (int p = 0; p <= step; p++)		//判断当前状态是否和已知状态重复
	{
		if (states[p].leftmen == states[temp].leftmen &&
			states[p].leftsavages == states[temp].leftsavages &&
			states[p].boat == states[temp].boat)
			return false;
	}
	return true;
}

void nextstep()
{
	if ((states[step].leftmen == 0) && (states[step].leftsavages == 0))
	{
		showSolution();
		return;
	}
	for (int m = 0; m <= boatload; m++)
	{
		for (int n = 0; n <= boatload - m; n++)
		{
			if (!(m == 0 && n == 0))
			{
				if (states[step].boat == 0)	//船在左侧
				{
					states[temp].leftmen = states[step].leftmen - m;
					states[temp].rightmen = states[step].rightmen + m;
					states[temp].leftsavages = states[step].leftsavages - n;
					states[temp].rightsavages = states[step].rightsavages + n;
					states[temp].boat = 1;
					if (isSafe() == true && isrepeat() == true)
					{
						step++;
						temp++;
						nextstep();
						step--;
						temp--;
					}
				}
				else {
					states[temp].leftmen = states[step].leftmen + m;
					states[temp].rightmen = states[step].rightmen - m;
					states[temp].leftsavages = states[step].leftsavages + n;
					states[temp].rightsavages = states[step].rightsavages - n;
					states[temp].boat = 0;
					if (isSafe() == true && isrepeat() == true)
					{
						step++;
						temp++;
						nextstep();
						step--;
						temp--;
					}
				}
			}
		}
	}
}

void main()
{
	cout << "请输入传教士数量（即野人数量）";
	cin >> n;
	cout << "请输入小船承载能力";
	cin >> boatload;
	states[0].leftmen = n;
	states[0].leftsavages = n;
	nextstep();
}