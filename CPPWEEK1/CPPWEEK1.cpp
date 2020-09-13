

#include <bangtal.h>

using namespace bangtal;


int main() {

	//1.장면을 생성한다.
	ScenePtr scene1 = Scene::create("룸1", "images/배경-1.png");
	auto scene2 = Scene::create("룸2", "images/배경-2.png");
	auto scene3= Scene::create("룸3", "images/배경-1.png");
	// 열쇠를 만든다(열쇠->화분 순서여야함 //열쇠가 화분에 가려져야 함)
	auto key = Object::create("images/열쇠.png", scene1, 600, 150);
	key->setScale(0.2f);//20퍼센트로 크기 줄임

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();
		return true;
	});


	//화분을 만든다
	auto flowerpot_moved = false;

	auto flowerpot = Object::create("images/화분.png", scene1, 550, 150);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (flowerpot_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 450, 150);
				flowerpot_moved = true;

			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 650, 150);
				flowerpot_moved = true;
			}
		}


		return true;
	});


	//3.문을 생성한다.
	auto open1 = false;
	auto door1 = Object::create("images/문-오른쪽-닫힘.png", scene1, 800, 270);

	//4.문을 클릭하면 이동한다.	//람다함수
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		//5.문이 열린상태이면 게임종료
		//  문이 닫힌상태이면 문을 열어줌.
		if (open1 == true) {//문이 열린 상태
			scene2->enter();
		}
		else if (key->isHanded()) {//문이 닫힌 상태

			door1->setImage("images/문-오른쪽-열림.png");
			open1 = true;
		}
		else {
			showMessage("열쇠가 필요해!!");
		}

		return true;
	});



	auto door2 = Object::create("images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
	});


	auto open3 = false, locked3 = true;
	auto door3 = Object::create("images/문-오른쪽-닫힘.png", scene2, 910, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		//5.문이 열린상태이면 게임종료
		//  문이 닫힌상태이면 문을 열어줌.

		if (locked3) { //문이 잠긴 상태
			showMessage("문이 잠겨있다.");
		}
		else if (open3 == true) {//문이 열린 상태
			scene3->enter();
		}
		else { //문이 닫힌 상태
			door3->setImage("images/문-오른쪽-열림.png");
			open3 = true;
		}

		return true;
	});

	door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		locked3 = false;
		showMessage("철커덕~~");
		return true;
	});

	auto keypad = Object::create("images/키패드.png", scene2, 885, 420);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("BANGTAL", door3);
		return true;
	});


	auto password = Object::create("images/암호.png", scene2, 400, 100, false);


	auto button = Object::create("images/스위치.png", scene2, 880, 449);
	auto lighted = true;
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted) {//켜진상태
			scene2->setLight(0.2f);
			password->show();
			lighted = false;

		}
		else//꺼진상태
		{

			scene2->setLight(1.0f);
			password->hide();
			lighted = true;
		}


		return true;
	});


	//door4
	auto door4 = Object::create("images/문-왼쪽-열림.png", scene3, 180, 275);
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
	});




	//door5
	auto open5 = false;
	auto door5 = Object::create("images/문-오른쪽-닫힘.png", scene3, 800, 270,false);
	door5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		//5.문이 열린상태이면 게임종료
		//  문이 닫힌상태이면 문을 열어줌.

		if (open5 == true) {//문이 열린 상태
			endGame();
		}
		else { //문이 닫힌 상태
			door5->setImage("images/문-오른쪽-열림.png");
			open5 = true;
		}

		return true;
	});


	//door6을 만든다   //페이크 문
	auto door6_moved = false;
	auto door6 = Object::create("images/문-오른쪽-닫힘.png", scene3, 800, 270, false);
	door6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (door6_moved == false) {	// 문이 안움직였을 때
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				door6->locate(scene3, 700, 285);
				door6_moved = true;

			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				door6->locate(scene3, 900, 255);
				door6_moved = true;
			}
		}


		return true;
	});


	//스위치2를 만든다.
	auto button2 = Object::create("images/스위치.png", scene3, 1080, 449);
	auto lighted2 = true;
	button2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted2) {//켜진상태
			scene3->setLight(0.2f);
			door5->show();
			door6->show();
			lighted2 = false;

		}
		else//꺼진상태
		{

			scene3->setLight(1.0f);
			door5->hide();
			door6->hide();
			lighted2 = true;
		}


		return true;
	});


	//2.게임을 시작한다.
	startGame(scene1);

	return 0;
}
