#pragma once
#define LIFE_YES 1
#define LIFE_NO 0
#define WALL_YES 1
#define WALL_NO 0

int size;
int speed;
short currentSeed;
bool isShapeDiamond = false;
bool isWallLive;

struct GameCell
{
	bool isLive;
	bool isWall;
};

struct GameCell** GameField = NULL;
struct GameCell** GameFieldFuture = NULL;

typedef enum Rules
{
	Original,
	HyperActive,
	HighLife,
	Spontaneous,
} rules;

rules rulesGame = Original;

void initialArray(int userSize)
{
	switch (userSize)
	{
	case 0:
		size = 6;
		break;
	case 1:
		size = 8;
		break;
	case 2:
		size = 10;
		break;
	case 3:
		size = 15;
		break;
	case 4:
		size = 20;
		break;
	case 5:
		size = 30;
		break;
	case 6:
		size = 50;
		break;
	}

	GameField = malloc(size * sizeof(struct GameCell*));

	for (int i = 0; i < size; i++)
		GameField[i] = malloc(size * sizeof(struct GameCell));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			GameField[i][j].isLive = LIFE_NO;
			GameField[i][j].isWall = WALL_NO;
		}
	}
}

bool checkAnswerSize(int userSize)
{
	if (userSize == 0 || userSize == 1 || userSize == 2 || userSize == 3 || userSize == 4 || userSize == 5 || userSize == 6)
		return true;
	else
	{
		printf("Error! Enter a number from the suggested options!");
		return false;
	}
}

void initialSize(void)
{
	int checkSize;
	bool checkerSizeAns = false;

	while (!checkerSizeAns)
	{
		printf("Enter the size of the field (0)6x6, (1)8x8, (2)10x10, (3)15x15, (4)20x20, (5)30x30, (6)50x50:");
		scanf_s("%d", &checkSize);
		checkerSizeAns = checkAnswerSize(checkSize);
		if (checkerSizeAns)
			initialArray(checkSize);
	}
}

void initializingResponseShape(int ans)
{
	if (ans == 1)
		isShapeDiamond = true;
	else
		isShapeDiamond = false;
}

bool checkAnswerYesOrNo(int ans)
{
	if (ans == 1 || ans == 2)
		return true;
	else
		return false;
}

void initialShape(void)
{
	bool checkerShapeAns = false;
	int checkShape;

	while (!checkerShapeAns)
	{
		printf("Diamond ? (Yes - choose 1 or No - choose 2):");
		scanf_s("%d", &checkShape);
		checkerShapeAns = checkAnswerYesOrNo(checkShape);

		if (checkerShapeAns)
			initializingResponseShape(checkShape);
	}
}

void initializingResponseWallsLive(int ans)
{
	if (ans == 1)
		isWallLive = true;
	else
		isWallLive = false;
}

void initialLiveWalls(void)
{
	bool checkerLiveWallsAns = false;
	int checkALive;

	while (!checkerLiveWallsAns)
	{
		printf("The walls alive? (Yes - choose 1 or No - choose 2):");
		scanf_s("%d", &checkALive);
		checkerLiveWallsAns = checkAnswerYesOrNo(checkALive);

		if (checkerLiveWallsAns)
			initializingResponseWallsLive(checkALive);
	}
}

bool checkAnswerSeed(int checkSeed)
{
	switch (checkSeed)
	{
	case 0:
		currentSeed = 10;
		return true;
	case 1:
		currentSeed = 30;
		return true;
	case 2:
		currentSeed = 50;
		return true;
	default:
		printf("Error! Enter a number from the suggested options!");
		return false;
	}
}

void initialSeed(void)
{
	bool checkerSeedAns = false;
	int checkSeed;

	while (!checkerSeedAns)
	{
		printf("Choose the seed live (0)Low, (1)Medium, (2)Large:");
		scanf_s("%d", &checkSeed);
		checkerSeedAns = checkAnswerSeed(checkSeed);
	}
}

bool checkAnswerSpeed(int checkSpeed)
{
	switch (checkSpeed)
	{
	case 0:
		speed = 2000;
		return true;
	case 1:
		speed = 1000;
		return true;
	case 2:
		speed = 500;
		return true;
	case 3:
		speed = 200;
		return true;
	case 4:
		speed = 1;
		return true;
	default:
		printf("Error! Enter a number from the suggested options!");
		return false;
	}
}

void initialSpeed(void)
{
	bool checkerSpeedAns = false;
	int checkSpeed;

	while (!checkerSpeedAns)
	{
		printf("Choose the speed game (0)Very Slow, (1)Slow, (2)Normal, (3)Fast, (4)Very Fast:");
		scanf_s("%d", &checkSpeed);
		checkerSpeedAns = checkAnswerSpeed(checkSpeed);
	}
}

bool checkAnswerRule(int checkRules)
{
	switch (checkRules)
	{
	case 0:
		rulesGame = Original;
		return true;
	case 1:
		rulesGame = HyperActive;
		return true;
	case 2:
		rulesGame = HighLife;
		return true;
	case 3:
		rulesGame = Spontaneous;
		return true;
	default:
		printf("Error! Enter a number from the suggested options!");
		return false;
	}
}

void initialRules(void)
{
	bool checkerRuleAns = false;
	int checkRule;

	while (!checkerRuleAns)
	{
		printf("Choose the rules of the game (0)Conway: The original rules, (1)Hyper Active, (2)High Life, (3)Spontaneous:");
		scanf_s("%d", &checkRule);
		checkerRuleAns = checkAnswerRule(checkRule);
	}
}

void createDiamond()
{
	int count1 = size % 2 == 0 ? 1 : 0;
	int count2 = 0;

	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j < size / 2 - count1)
			{
				GameField[i][j].isWall = WALL_YES;
				GameField[i][j].isLive = isWallLive;
			}

			if (j > size / 2 + count2)
			{
				GameField[i][j].isWall = WALL_YES;
				GameField[i][j].isLive = isWallLive;
			}
		}
		count1++;
		count2++;
	}

	count1 = size % 2 == 0 ? 1 : 0;
	count2 = 0;

	for (int i = size - 1; i > size / 2; i--)
	{
		for (int j = 0; j < size; j++)
		{
			if (j < size / 2 - count1)
			{
				GameField[i][j].isWall = WALL_YES;
				GameField[i][j].isLive = isWallLive;
			}

			if (j > size / 2 + count2)
			{
				GameField[i][j].isWall = WALL_YES;
				GameField[i][j].isLive = isWallLive;
			}
		}
		count1++;
		count2++;
	}
}

void generationOfLivingCells()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (isShapeDiamond)
			{
				if (!GameField[i][j].isWall)
				{
					if (currentSeed > rand() % 100)
					{
						GameField[i][j].isLive = LIFE_YES;
						GameField[i][j].isWall = WALL_NO;
					}
					else
					{
						GameField[i][j].isLive = LIFE_NO;
						GameField[i][j].isWall = WALL_NO;
					}
				}
			}
			else
			{
				if (currentSeed > rand() % 100)
				{
					GameField[i][j].isLive = LIFE_YES;
					GameField[i][j].isWall = WALL_NO;
				}
				else
				{
					GameField[i][j].isLive = LIFE_NO;
					GameField[i][j].isWall = WALL_NO;
				}
			}
		}
	}
}

void printTable(void)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (GameField[i][j].isWall == true)
				printf("X");
			else if (GameField[i][j].isLive == true)
				printf("*");
			else
				printf(".");
		}
		printf("\n");
	}
	printf("\n");
}

void gameInitiation(void)
{
	initialSize();

	initialShape();

	if (isShapeDiamond)
		initialLiveWalls();

	initialSeed();

	initialSpeed();

	initialRules();

	if (isShapeDiamond)
		createDiamond();

	generationOfLivingCells();
	printTable();

	Sleep(speed);
}
