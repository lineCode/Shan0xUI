# Shan0xUI - Short Direct2D-GUI library.

## C0d3d by [Shkolnik Prahramist 寂](https://www.youtube.com/channel/UCmJT3IfHtpFJyln2UdABBKg)

**Avalable controls (доступные компоненты):**
* Base window
* Label
* Material button
* TextBox
* CheckBox
---
**Minimal code-example (минимальный пример):**
```
#include "Shan0xUI.h"

void ButtonClick()
{
	MessageBox(GetActiveWindow(), L"Hello world!", L"OK", MB_ICONINFORMATION);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	Shan0xUI::Window Form1(L"Form1", 600, 600, true);
	Shan0xUI::MaterialButton btn1(L"Click Me!", 10, 10);
	btn1.Connect.onClick = ButtonClick;
	btn1.SetStyle(Shan0xUI::MaterialButton::MaterialButtonStyles::CrimsonStyle);

	Form1.AddButton(btn1);
	return Form1.Run();
}
```
