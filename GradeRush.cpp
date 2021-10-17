#include <bangtal>
#include <cstdlib>
#include <random>
#include <ctime>
#include <windows.h>
#include <cmath>
using namespace bangtal;

ObjectPtr start;
TimerPtr timer;

//장면 생성
auto screen1 = Scene::create("시작화면", "Images/제목.jpg");
auto screen2 = Scene::create("게임화면", "Images/게임화면.png");

auto over_F = Object::create("Images/gameover.png", screen2, 400, 400, false);

int move = 30;
int count = 0;

int score = 0;

constexpr int MIN = 1;
constexpr int MAX = 1200;
constexpr int MAX2 = 600;


void start_game()
{
	start->hide();
	screen2->enter();

	showTimer(timer);
	timer->start();
}


int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	
	srand((unsigned int)time(NULL));

	auto AplusgradeX = rand() % MAX, AgradeX = rand() % MAX, BgradeX = rand() % MAX, CgradeX = rand() % MAX, FgradeX = rand() % MAX;
	auto AplusgradeY = rand() % MAX2, AgradeY = rand() % MAX2, BgradeY = rand() % MAX2, CgradeY = rand() % MAX2, FgradeY = rand() % MAX2;

	auto Aplus = Object::create("Images/1.png", screen2, AplusgradeX, AplusgradeY);	Aplus->setScale(0.35f);

	auto A = Object::create("Images/2.png", screen2, AgradeX, AgradeY);				A->setScale(0.35f);;

	auto B = Object::create("Images/3.png", screen2, BgradeX, BgradeY);				B->setScale(0.35f);

	auto C = Object::create("Images/4.png", screen2, CgradeX, CgradeY);				C->setScale(0.35f);

	auto F = Object::create("Images/5.png", screen2, FgradeX, FgradeY);				F->setScale(0.35f);


	auto professor = Object::create("Images/professor.png", screen2, 100, 500);
	professor->setScale(0.5f);


	auto studentX = 600, studentY = 10;
	auto student = Object::create("Images/Student.png", screen2, studentX, studentY);
	student->setScale(0.8f);


	screen2->setOnKeyboardCallback([&](ScenePtr screen2, KeyCode key, bool pressed)->bool {
		if (key == KeyCode::KEY_RIGHT_ARROW) {
			studentX = studentX + move;
			student->locate(screen2, studentX, studentY);
			return true;
		}
		else if (key == KeyCode::KEY_LEFT_ARROW) {
			studentX = studentX - move;
			student->locate(screen2, studentX, studentY);
			return true;
		}
		else if (key == KeyCode::KEY_UP_ARROW) {
			studentY = studentY + move;
			student->locate(screen2, studentX, studentY);
			return true;
		}
		else if (key == KeyCode::KEY_DOWN_ARROW) {
			studentY = studentY - move;
			student->locate(screen2, studentX, studentY);
			return true;
		}
		});

	
	timer = Timer::create(60.f);
	timer->setOnTimerCallback([&](TimerPtr)-> bool{

		showMessage("시간 초과, 게임 오버!");
		endGame();

		return true;
	});

	
	int space = 50;

	if (abs(AplusgradeX - studentX) < space && abs(AplusgradeY - studentY) < space) {
		Aplus->hide();
		student->setImage("Images/A+grade.png");
		count++;
	}
		
	if (abs(AgradeX - studentX) < space && abs(AgradeY - studentY) < space) {
		student->setImage("Images/Agrade.png");
		A->hide();
	}

	if (abs(BgradeX - studentX) < space && abs(BgradeY - studentY) < space) {
		student->setImage("Images/Bgrade.png");
		B->hide();
	}
		
	if (abs(CgradeX - studentX) < space && abs(CgradeY - studentY) < space) {
		student->setImage("Images/Cgrade.png");
		C->hide();
	}

	if (abs(FgradeX - studentX) < space && abs(FgradeY - studentY) < space) {
		student->setImage("Images/Fgrade.png");
		showMessage("으악! F다!");
		over_F->show();
		timer->stop();
	}

	if (count == 1) {
		showMessage("A+이다!");
		timer->stop();
		endGame();
	}

	

	start = Object::create("Images/시작버튼.png", screen1, 530, 50);
	start->setScale(0.25f);
	start->setOnMouseCallback([&](auto, auto, auto, auto)->bool
		{
			start_game();
			return true;
		});

	startGame(screen1);

	return 0;
}