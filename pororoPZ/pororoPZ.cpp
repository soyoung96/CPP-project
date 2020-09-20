//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES	1

#include <stdio.h>
#include <time.h>
#include <bangtal.h>
#include <stdlib.h>



struct position {
	int x, y;
};

const position pos_arr[16] = {
	{300, 470}, {450, 470}, {600, 470}, {750, 470},
	{300, 320}, {450, 320}, {600, 320}, {750, 320},
	{300, 170}, {450, 170}, {600, 170}, {750, 170},
	{300, 20}, {450, 20}, {600, 20}, {750, 20},
};


TimerID t_id;
SceneID scene;
ObjectID start;
ObjectID initObj[16];
ObjectID gameObj[16];

int mix_num = 100;
bool g_ing;
int corner_num = 15;
int mix = 0;
Second wait_t = 0.02f;

void initialize();
bool game_move(int index);
int game_index(ObjectID oid);





void game_random_move()
{
	bool possible = false;
	int next = -1;
	while (!possible) {
		switch (rand() % 4) {
		case 0:		// UP
			next = corner_num - 4;
			break;
		case 1:		// DOWN
			next = corner_num + 4;
			break;
		case 2:		// LEFT
			next = (corner_num % 4 != 0) ? (corner_num - 1) : -1;
			break;
		case 3:		// RIGHT
			next = (corner_num % 4 != 3) ? (corner_num + 1) : -1;
			break;
		}

		possible = game_move(next);
	}
}

void game_prepare()
{
	hideObject(gameObj[corner_num]);

	mix = mix_num;

	// start to mix
	setTimer(t_id, wait_t);
	startTimer(t_id);
}

bool game_check()
{
	for (int i = 0; i < 16; i++) {
		if (gameObj[i] != initObj[i]) return false;
	}

	return true;
}

void game_end()
{
	g_ing = false;

	showObject(gameObj[corner_num]);
	showObject(start);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (g_ing) {
		game_move(game_index(object));

		if (game_check()) {
			game_end();
		}
	}
	else if (mix == 0 && object == start) {
		game_prepare();
	}
}

void timerCallback(TimerID timer)
{
	game_random_move();

	if (mix > 0) {
		--mix;

		setTimer(t_id, wait_t);
		startTimer(t_id);
	}
	else {
		hideObject(start);
		g_ing = true;
	}
}

int main()
{
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	initialize();

	startGame(scene);
}

void initialize()
{


	scene = createScene(" ", "Images/배경.png");
	g_ing = false;

	char image[20];

	//퍼즐로딩
	for (int i = 0; i < 16; i++) {

		sprintf(image, "Images/%d.png", i + 1);

		initObj[i] = createObject(image);
		gameObj[i] = initObj[i];

		locateObject(gameObj[i], scene, pos_arr[i].x, pos_arr[i].y);
		showObject(gameObj[i]);
	}

	start = createObject("Images/start.png");
	locateObject(start, scene, 540, 400);
	scaleObject(start, 2);
	showObject(start);

	corner_num = 15;
	g_ing = false;

	srand((unsigned int)time(NULL));
	t_id = createTimer();
}

int game_index(ObjectID oid) {
	for (int i = 0; i < 16; i++) {
		if (gameObj[i] == oid) return i;
	}

	return -1;
}

bool game_move(int index)
{
	if (index < 0) return false;
	if (index > 15) return false;

	if (index == (corner_num - 4) || index == (corner_num + 4) ||
		(index == (corner_num - 1) && (corner_num % 4) != 0) ||
		(index == (corner_num + 1) && (corner_num % 4) != 3)) {


		locateObject(gameObj[corner_num], scene, pos_arr[index].x, pos_arr[index].y);

		locateObject(gameObj[index], scene, pos_arr[corner_num].x, pos_arr[corner_num].y);

		ObjectID ya = gameObj[corner_num];
		gameObj[corner_num] = gameObj[index];
		gameObj[index] = ya;

		corner_num = index;

		return true;
	}

	return false;
}