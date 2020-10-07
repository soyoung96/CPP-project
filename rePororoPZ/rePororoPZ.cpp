#include <bangtal.h>
#include<iostream>
#include<ctime>

using namespace bangtal;
using namespace std;



int main() {

	srand((unsigned int)time(NULL));
	time_t start_time;
	auto scene = Scene::create("뽀로로", "images/배경.png");

	ObjectPtr game_board[16];
	ObjectPtr init_board[16];

	

	int blank = 15;
	for (int i = 0; i < 16; i++) {
		string filename = "images/" + to_string(i + 1) + ".png";
		cout << filename << endl;

		game_board[i] = Object::create(filename, scene, 375 + 150 * (i % 4), 514 - (i / 4) * 150);
		init_board[i] = game_board[i];

		game_board[i]->setOnMouseCallback([&](ObjectPtr obj, int, int, MouseAction)->bool {
			int j = 0;
			for (j; j < 16; j++) {
				if (game_board[j] == obj) {
					break;
				}
			}

			if ((j%4>0&&j-1==blank)||
				(j%4<3&&j+1==blank)||
				(j>3&&j-4==blank)||
				(j < 12 && j + 4 == blank)) {
				//방탈라이브러리 비주얼 바꿈
				game_board[j]->locate(scene, 375 + 150 * (blank % 4), 514 - (blank / 4) * 150);
				game_board[blank]->locate(scene, 375 + 150 * (j % 4), 514 - (j / 4) * 150);


				//배열에서 순서바꿈
				game_board[j] = game_board[blank];
				game_board[blank] = obj;
				blank = j;

				//정답인지 확인

				int k = 0;
				for (k; k < 16; k++) {
					if (init_board[k] != game_board[k]) {
						break;
					}
				}
				if (k == 16) {

					auto end_time = time(NULL);
					string buf = to_string(difftime(end_time,start_time))+"걸렸습니다.";
					showMessage(buf.c_str());
				}
			}

		

			return true;
		});
	
	}

	//시작하기 버튼
	auto start = Object::create("images/start.png", scene, 590, 450);

	auto timer = Timer::create(0.1f);

	int count = 0;
	timer->setOnTimerCallback([&](TimerPtr t)->bool {



		int j = 0;
		do {
			switch (rand() % 4) {

			case 0://좌
				j = blank - 1; break;
			case 1://우
				j = blank + 1; break;
			case 2:
				j = blank - 4; break;
			case 3:
				j = blank + 4; break;


			}


		} while (j < 0 || j > 15 || !((j % 4 > 0 && j - 1 == blank) ||
			(j % 4 < 3 && j + 1 == blank) ||
			(j > 3 && j - 4 == blank) ||
			(j < 12 && j + 4 == blank)));
		//방탈라이브러리 비주얼 바꿈
		game_board[j]->locate(scene, 375 + 150 * (blank % 4), 514 - (blank / 4) * 150);
		game_board[blank]->locate(scene, 375 + 150 * (j % 4), 514 - (j / 4) * 150);


		//배열에서 순서바꿈
		auto object = game_board[j];
		game_board[j] = game_board[blank];
		game_board[blank] = object;
		blank = j;



		count++;
		if (count < 10) {
			t->set(0.1f);
			t->start();

		}


		return true;

	});

	//스타트버튼 누르면 동작
	start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		start->hide();
		game_board[blank]->hide();

		
		

		timer->start();


		
		return true;
	});


	


	start_time = time(NULL);
	startGame(scene);

	return 0;
}