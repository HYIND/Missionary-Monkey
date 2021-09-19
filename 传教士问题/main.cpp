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
int solutioncount = 0;	//计数，解决方案数目
int shortest = 0, shortestcount;
//shortrest存储一条最短路径的长度，shortrestcount指明其在所有输出路径中的位置
int step = 0, temp = 1;	//step表示已走步数，temp临时存储的下一步
int boatload;			//船的装载量
int n;					//传教士人数(即野人数)

void showSolution()		//输出一条解决方案
{
	solutioncount++;
	if (solutioncount == 1)
	{
		cout << "successed!" << endl;
	}
	cout << "第" << solutioncount << "种方案";
	for (int i = 0; i < step; i++)
		cout << states[i].leftmen << states[i].leftsavages
		<< states[i].boat << "-->";
	cout << states[step].leftmen << states[step].leftsavages
		<< states[step].boat << endl;
	if (shortest == 0)		//存储其中一条最短路径
	{
		for (int i = 0; i <= step; i++)
			solution[i] = states[i];
		shortest = step;
		shortestcount = solutioncount;
	}
	else if (step < shortest) {		//若发现更短的方案，则用新的方案替换
		for (int i = 0; i <= step; i++)
			solution[i] = states[i];
		shortest = step;
		shortestcount = solutioncount;
	}
}

void showshortest() {
	if (shortest != 0)
	{
		cout << "\n找到其中一条最佳方案：方案" << shortestcount << endl;
		for (int i = 0; i < shortest; i++)
			cout << solution[i].leftmen << solution[i].leftsavages << solution[i].boat << "-->";
		cout << solution[shortest].leftmen << solution[shortest].leftsavages << solution[shortest].boat
			<< "\t共" << shortest << "步\n";
	}
	else cout << "Failed!";
}

bool isSafe() {		//判断该情况是否安全，合法
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

bool isrepeat() {		//判断当前状态是否和已知状态重复
	for (int p = 0; p <= step; p++)
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
		//全部人抵达对岸，到达目标状态
	{
		showSolution();
		return;
	}
	for (int m = 0; m <= boatload; m++)
		//m表示渡船的传教士数量，n表示渡船的野人数量。
		//表示循环寻找可能的渡船方案，并逐一尝试
	{
		for (int n = 0; n <= boatload - m; n++)
		{
			if (!(m == 0 && n == 0))	//排除掉 0 0 的渡船方案
			{
				if (states[step].boat == 0)		//船在左侧时
				{
					states[temp].leftmen = states[step].leftmen - m;
					states[temp].rightmen = states[step].rightmen + m;
					states[temp].leftsavages = states[step].leftsavages - n;
					states[temp].rightsavages = states[step].rightsavages + n;
					states[temp].boat = 1;
					if (isSafe() == true && isrepeat() == true)		//判断新的情况是否合法
					{
						step++;
						temp++;
						nextstep();
						step--;		//回溯
						temp--;		//回溯
					}
				}
				else {		//若船在右岸，情况同左岸
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
	showshortest();
}