#include "Shan0xUI.h"
Shan0xUI::Window Form1(L"Form1", 600, 600, true);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	Shan0xUI::CheckBox chk1(L"Eshkere some long text lololo gagaga 12345 123", 10, 150, 207, 35);
	Shan0xUI::CheckBox chk2;
	Shan0xUI::CheckBox chk3(L"Eshhhhhhhkere", 10, 300, 125, 55);

	Shan0xUI::MaterialButton btn1(L"Click Me!", 220, 10, 150, 40);
	btn1.SetStyle(Shan0xUI::MaterialButton::MaterialButtonStyles::CrimsonStyle);

	Form1.AddCheckBox(chk1);
	Form1.AddCheckBox(chk2);
	Form1.AddCheckBox(chk3);
	Form1.AddButton(btn1);
	return Form1.Run();
}