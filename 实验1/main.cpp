#include <stdio.h>
struct State
{
	int monkey; /*-1:Monkey at A; 0: Monkey at B; 1:Monkey at C;*/
	int box; /*-1:box at A ;0:box at B;	1:box at C;*/
	int banana; /*Banana at B,Banana=0*/
	int monbox; /*-1: monkey not on the box;	1: monkey on the box;*/
};
struct State States[150];
const char* routesave[150];
/*function monkeygoto,it makes the monkey goto the other place*/
void monkeygoto(int b, int i)
{
	int a = b;
	if (a == -1)
	{
		routesave[i] = "Monkey go to A";
		States[i + 1] = States[i];
		States[i + 1].monkey = -1;
	}
	else if (a == 0)
	{
		routesave[i] = "Monkey go to B";
		States[i + 1] = States[i];
		States[i + 1].monkey = 0;
	}
	else if (a == 1)
	{
		routesave[i] = "Monkey go to C";
		States[i + 1] = States[i];
		States[i + 1].monkey = 1;
	}
	else
	{
		printf("parameter is wrong");
	}
}
/*end function monkeyygoto*/
/*function movebox,the monkey move the box to the other place*/
void movebox(int a, int i)
{
	int B = a;
	if (B == -1)
	{
		routesave[i] = "monkey move box to A";
		States[i + 1] = States[i];
		States[i + 1].monkey = -1;
		States[i + 1].box = -1;
	}
	else if (B == 0)
	{
		routesave[i] = "monkey move box to B";
		States[i + 1] = States[i];
		States[i + 1].monkey = 0;
		States[i + 1].box = 0;
	}
	else if (B == 1)
	{
		routesave[i] = "monkey move box to C";
		States[i + 1] = States[i];
		States[i + 1].monkey = 1;
		States[i + 1].box = 1;
	}
	else
	{
		printf("parameter is wrong");
	}
}
/*end function movebox*/
/*function climbonto,the monkey climb onto the box*/
void climbonto(int i)
{
	routesave[i] = "Monkey climb onto the box";
	States[i + 1] = States[i];
	States[i + 1].monbox = 1;
}
/*function climbdown,monkey climb down from the box*/
void climbdown(int i)
{
	routesave[i] = "Monkey climb down from the box";
	States[i + 1] = States[i];
	States[i + 1].monbox = -1;
}
/*function reach,if the monkey,box,and banana are at the same place,the monkey reach banana*/
void reach(int i)
{
	routesave[i] = "Monkey reach the banana";
}
/*output the solution to the problem*/
void showSolution(int i)
{
	int c;
	printf("%s \n", "Result to problem:");
	for (c = 0; c < i + 1; c++)
	{
		printf("Step %d : %s \n", c + 1, routesave[c]);
	}
	printf("\n");
}

void nextStep(int i) 
{
	int c;
	if (i >= 150)
	{
		printf("%s  \n", "steplength reached 150,have problem ");
		return;
	}
		for (c = 0; c < i; c++) /*if the current state is same to previous,retrospect*/
	{
		if (States[c].monkey == States[i].monkey && States[c].box == States[i].box && States[c].banana ==
			States[i].banana && States[c].monbox == States[i].monbox)
		{
			return;
		}
	}
	if (States[i].box == States[i].banana)		//若箱子在香蕉下
	{
		if (States[i].monkey == States[i].banana)	//若箱子在香蕉下，且猴子也在香蕉下
		{
			if (States[i].monbox == 1)	
				//若箱子在香蕉下，且猴子也在香蕉下，且猴子已经爬上香蕉，则猴子摘到香蕉
			{
				reach(i);
				showSolution(i);
				printf("Press any key to continue \n");
				getchar();
				return;
			}
			else {
				climbonto(i);
				nextStep(++i);
			}
		}
		else {		//若箱子在香蕉下，但猴子不在香蕉下
			monkeygoto(States[i].box, i);	//猴子移动到箱子处
			nextStep(++i);
		}
	}
	else if(States[i].monkey==States[i].box){		//箱子不在香蕉下,且猴子和箱子在一起
		if (States[i].monbox == 1)			//箱子不在香蕉下,且猴子在箱子上
		{
			climbdown(i);		//猴子爬下箱子
			nextStep(++i);
		}
		else{		//箱子不在香蕉下,且猴子和箱子在一起,但猴子没爬上箱子
			movebox(States[i].banana, i);	//猴子把箱子搬到香蕉下
			nextStep(++i);
		}
	}
	else{		//箱子不在香蕉下,且猴子和箱子也不在一起
		monkeygoto(States[i].box, i);	//猴子走到箱子处
		nextStep(++i);
	}
}
int main()
{
	States[0].monkey = -1;	//-1：猴子初始在A处
	States[0].box = 1;		//1：箱子初始在C处
	States[0].banana = 0;	//0：香蕉初始在B处
	States[0].monbox = -1;	//-1：猴子初始不在箱子上
	nextStep(0);
}