#include"MyGame.h"
// DirectInputƒo[ƒWƒ‡ƒ“‚ÌéŒ¾
#define DIRECTINPUT_VERSION 0x0800
#include  <dinput.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Framework* Mygame = new MyGame();

	Mygame->Run();

	delete Mygame;

	return 0;
}

