#include "RacingGame.h"
#include <time.h>

int main()
{
	setlocale(LC_ALL, "rus");
	srand((unsigned)time(NULL));

	RECT rect;
	::SetConsoleTitle(L"Graphics");
	::system("mode con cols=200 lines=70");

	HandleCons = ::GetStdHandle(STD_OUTPUT_HANDLE);
	hWnd = ::FindWindow(NULL, L"Graphics");
	::GetClientRect(hWnd, &rect);

	Graphics::CreateGraphics();
	COORD dummy;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), 1, &dummy);

	heg = rect.bottom;
	wid = rect.right;
	Sleep(500);
	
	RunGame();

	Graphics::DeleteGraphics();
	cin.get();
	return 0;
}