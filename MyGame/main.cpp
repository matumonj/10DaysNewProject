
#include"MyGame.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Framework* Mygame = new MyGame();

	Mygame->Run();

	delete Mygame;

	return 0;
}

