#include "Shan0xUI.h"

Shan0xUI::Window Form1(L"MyForm", 600, 600, true);
Shan0xUI::MaterialButton btn;
Shan0xUI::CheckBox ChkBox1;
Shan0xUI::CheckBox ChkBox2;

void Checked()
{
	if (ChkBox1.getCheckBoxState_Checked())
	{
		MessageBox(Form1.GetHWND(), L"Checked!", L"OK", MB_ICONINFORMATION);
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	Form1.SetBackgroundColor(BaseColor::White);
	
	btn.Connect.onClick = Checked;
	
	ChkBox1.SetBackgroundColorOnClick(BaseColor::Black);

	ChkBox2.SetBackgroundColorOnClick(BaseColor::Black);
	ChkBox2.SetBorderColorOnHover(BaseColor::Red);

	ChkBox1.SetWidth(100);
	ChkBox1.SetHeight(18);
	ChkBox1.SetX(10);
	ChkBox1.SetY(50);

	ChkBox2.SetWidth(100);
	ChkBox2.SetHeight(18);
	ChkBox2.SetX(10);
	ChkBox2.SetY(120);

	Form1.AddButton(btn);
	Form1.AddCheckBox(ChkBox1);
	Form1.AddCheckBox(ChkBox2);
	return Form1.Run();
}