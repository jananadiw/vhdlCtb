//include<stdio.h>
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

		while((Roll == 'Y') || (Roll == 'y'))
		{
			Sum = rolldice();
			printf("\n1차 굴리기 주사위의 합은 %d입니다.\n", Sum);
			if ((Sum == 7) || (Sum == 11))
			{
				winprint(Sum);
				NG = newgame();
				if ((NG == 'Y') || (NG == 'y'))
				{
					Roll = play();
					continue;
				}
				else break;
			}

			if ((Sum == 2) || (Sum == 3) ||(Sum == 12))
			{
				loseprint(Sum);
				NG = newgame();
				if ((NG == 'Y') || (NG == 'y'))
				{
					Roll = play();
					continue;
				}
				else break;
			}

			Score = Sum;

			while(1)
			{
				printf("\n2차 굴리기입니다. 기록된 점수는 %d입니다.\n", Score);
				Sum = rolldice();
				printf("\n2차 굴리기 주사위의 합은 %d입니다.\n", Sum);
				if (Sum == Score)
				{
					winprint(Sum);
					break;
				}

				if (Sum == 7)
				{
					loseprint(Sum);
					break;
				}
			}

			NG = newgame();
			if ((NG == 'Y') || (NG == 'y'))
				Roll = play();
			else break;
		}
		return 0;
	}
