#pragma once

int currentLivesCells = 0;
int pastLivesCells = 0;
int generation = 0;

int getNeighborValue(int row, int col)
{
	if (row < 0 || row >= size || col < 0 || col >= size)
		return 0;
	else
		return GameField[row][col].isLive;
}

int getNeighborCount(int row, int col)
{
	int neighbor = 0;

	neighbor += getNeighborValue(row - 1, col - 1);
	neighbor += getNeighborValue(row - 1, col);
	neighbor += getNeighborValue(row - 1, col + 1);
	neighbor += getNeighborValue(row, col - 1);
	neighbor += getNeighborValue(row, col + 1);
	neighbor += getNeighborValue(row + 1, col - 1);
	neighbor += getNeighborValue(row + 1, col);
	neighbor += getNeighborValue(row + 1, col + 1);

	return neighbor;
}
//there is a counting of living cells around a particular cell

void original(int i, int j, int neighbor)
{
	if (neighbor == 3 && GameField[i][j].isLive == LIFE_NO)
	{
		GameFieldFuture[i][j].isLive = LIFE_YES;
		currentLivesCells++;
	}
	else if ((neighbor == 2 || neighbor == 3) && GameField[i][j].isLive == LIFE_YES)
		GameFieldFuture[i][j].isLive = LIFE_YES;
	else
		GameFieldFuture[i][j].isLive = LIFE_NO;
}

void hyperActive(int i, int j, int neighbor)
{
	if (GameField[i][j].isLive = LIFE_YES && neighbor < 2 && neighbor > 5)
		GameFieldFuture[i][j].isLive = LIFE_NO;
	else if (neighbor == 3 && GameField[i][j].isLive == LIFE_NO)
	{
		GameFieldFuture[i][j].isLive = LIFE_YES;
		currentLivesCells++;
	}
	else if ((neighbor == 2 || neighbor == 3) && GameField[i][j].isLive == LIFE_YES)
		GameFieldFuture[i][j].isLive = LIFE_YES;
	else
		GameFieldFuture[i][j].isLive = LIFE_NO;
}

void highLife(int i, int j, int neighbor)
{
	if (GameField[i][j].isLive = LIFE_YES && neighbor < 2 && neighbor > 3)
		GameFieldFuture[i][j].isLive = LIFE_NO;
	else if (neighbor == 3 && GameField[i][j].isLive == LIFE_NO)
	{
		GameFieldFuture[i][j].isLive = LIFE_YES;
		currentLivesCells++;
	}
	else if ((neighbor == 2 || neighbor == 3) && GameField[i][j].isLive == LIFE_YES)
		GameFieldFuture[i][j].isLive = LIFE_YES;
	else
		GameFieldFuture[i][j].isLive = LIFE_NO;
}

void spontaneous(int i, int j, int neighbor)
{
	if (neighbor == 3 && GameField[i][j].isLive == LIFE_NO)
	{
		GameFieldFuture[i][j].isLive = LIFE_YES;
		currentLivesCells++;
	}
	else if ((neighbor == 2 || neighbor == 3) && GameField[i][j].isLive == LIFE_YES)
		GameFieldFuture[i][j].isLive = LIFE_YES;
	else if (GameField[i][j].isLive == LIFE_NO && rand() % 1000 == 5)
	{
		GameFieldFuture[i][j].isLive = LIFE_YES;
		currentLivesCells++;
	}
	else
		GameFieldFuture[i][j].isLive = LIFE_NO;
}

void calculate(void)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			GameFieldFuture[i][j].isLive = GameField[i][j].isLive;
			GameFieldFuture[i][j].isWall = GameField[i][j].isWall;
		}
	}

	int neighbor;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (!GameField[i][j].isWall)
			{
				neighbor = getNeighborCount(i, j, GameField);

				if (rulesGame == Original)
					original(i, j, neighbor);
				else if (rulesGame == HyperActive)
					hyperActive(i, j, neighbor);
				else if (rulesGame == HighLife)
					highLife(i, j, neighbor);
				else if (rulesGame == Spontaneous)
					spontaneous(i, j, neighbor);
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			GameField[i][j].isLive = GameFieldFuture[i][j].isLive;
			GameField[i][j].isWall = GameFieldFuture[i][j].isWall;
		}
	}
}

bool gameStart()
{
	GameFieldFuture = malloc(size * sizeof(struct GameCell*));

	for (int i = 0; i < size; i++)
		GameFieldFuture[i] = malloc(size * sizeof(struct GameCell));

	system("cls");
	pastLivesCells = currentLivesCells;
	calculate();
	printTable();
	generation++;
	printf("Generation %d\n", generation);
	Sleep(speed);

	if (currentLivesCells == pastLivesCells)
	{
		int again;
		printf("Game over... Again? (Yes - choose 1 or No - choose 2):");
		scanf_s("%d", &again);
		if (again == 1)
		{
			generation = 0;
			Game();
		}
		else if (again == 2)
			return false;
	}
	else
		return true;
}