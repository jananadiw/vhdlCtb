	//include<stdio.h>;
    //include<stdlib.h>
    //include<time.h>

	char newgame(void);
	void loseprint(int);
	void winprint(int);
	int rolldice(void);
	char play(void);

	int main(void)
	{
		char Roll, NG;
		int Sum, Score;

		Roll = ' ';
		NG = ' ';
		Sum = 0;
		Score = 0;

		srand((unsigned)time(NULL));

		Roll = play();

		if ((Roll == 'Y') || (Roll == 'y')) goto StartFirstRoll;
		else goto Stop;

	StartFirstRoll:
		Sum = rolldice();
		printf("\n1차 굴리기 주사위의 합은 %d입니다.\n", Sum);
		if ((Sum == 7) || (Sum == 11)) goto Win;
		if ((Sum == 2) || (Sum == 3) ||(Sum == 12)) goto Lose;
		Score = Sum;

	SecondRoll:
		printf("\n2차 굴리기입니다. 기록된 점수는 %d입니다.\n", Score);
		Sum = rolldice();
		printf("\n2차 굴리기 주사위의 합은 %d입니다.\n", Sum);
		if (Sum == Score) goto Win;
		if (Sum == 7) goto Lose;
		goto SecondRoll;

	Win:
		winprint(Sum);
		NG = newgame();
		if ((NG == 'Y') || (NG == 'y')) goto StartFirstRoll;
		else goto Stop;

	Lose:
		loseprint(Sum);
		NG = newgame();
		if ((NG == 'Y') || (NG == 'y')) goto StartFirstRoll;

	Stop:
		return 0;
	}

	char play(void)
	{
		char YN;

		printf("주사위를 굴리시겠습니까?(y/n): ");
		scanf("%c", &YN);
		fflush(stdin);
		return YN;
	}

	int rolldice(void)
	{
		int Sum, dice1, dice2;

		Sum = 0;
	
		while(1)
		{
			dice1 = rand();
			if((dice1<=0)||(7<=dice1)) continue;
			else break;
		}

		while(1)
		{
			dice2 = rand();
			if((dice2<=0)||(7<=dice2)) continue;
			else break;
		}

		Sum = dice1 + dice2;
		return Sum;
	}

	void winprint(int Sum)
	{
		printf("\n\t주사위의 합은 %d입니다.\n", Sum);
		printf("\t\t이겼습니다.\n");
	}

	void loseprint(int Sum)
	{
		printf("\n\t주사위의 합은 %d입니다.\n", Sum);
		printf("\t\t졌습니다.\n");
	}

	char newgame(void)
	{
		char YN;

		YN = ' ';
		printf("새로 게임을 하시겠습니까?(y/n): ");
		scanf("%c", &YN);
		fflush(stdin);
		return YN;
	}