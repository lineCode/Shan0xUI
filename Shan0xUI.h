#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#pragma warning(disable: 4244)
#pragma warning(disable: 4240)
#pragma warning(disable: 4267)
#pragma warning(disable: 4091)
#pragma warning(disable: 4311)
#pragma warning(disable: 4302)

#include <Windows.h>
#include <string>
#include <vector>
#include <d2d1.h>
#include <dwrite.h>
typedef D2D1::ColorF BaseColor;
typedef D2D1_COLOR_F ParamColor;

// ����� GUI-����������.
class Shan0xUI
{
	class Label;
	class MaterialButton;
	class Panel;
	class TextBox;
	class CheckBox;
private:
	// ����� �������� ������� ����.
	class WindowObject
	{
	protected:
		std::wstring szObjectText{};
		int xPos{}, yPos{};
		int Width{}, Height{};

		virtual void SetBackgroundColor(BaseColor Color) = 0;
	};

	// ����������� ����� ��� ��������, ���������� �����.
	class TextFontBasedObject : WindowObject
	{
	private:
		std::wstring _fontName{};
		int _fontSize{};
	public:
		// ����� �������� ����� �������.
		void SetText(const wchar_t* text) { this->szObjectText = text; SendMessage(NULL, WM_PAINT, 0, 0); }

		// ����� ���������� ����� �������.
		const wchar_t* GetText() { return this->szObjectText.c_str(); }

		// ����� ������ ����� �������.
		void SetFont(const wchar_t* fontName) { this->_fontName = fontName; SendMessage(NULL, WM_PAINT, 0, 0); }

		// ����� ��������� �������� ������ �������.
		const wchar_t* GetFont() { return this->_fontName.c_str(); }

		// ����� ������ ������ ������ �������.
		void SetFontSize(const int& fontSize) { this->_fontSize = fontSize; SendMessage(NULL, WM_PAINT, 0, 0); }

		// ����� ���������� ������ ������� �������.
		int GetFontSize() { return this->_fontSize; }

		// ����� ������ X - ���������� �������.
		void SetX(const int& x) { this->xPos = x; SendMessage(NULL, WM_PAINT, 0, 0); }

		// ����� ������ Y - ���������� �������.
		void SetY(const int& y) { this->yPos = y; SendMessage(NULL, WM_PAINT, 0, 0); }

		// ����� ���������� X - ���������� �������.
		int GetX() { return this->xPos; }

		// ����� ���������� Y - ���������� �������.
		int GetY() { return this->yPos; }

		// ����� ���������� ������ �������.
		int GetWidth() { return this->Width; }

		// ����� ������������� ������ �������.
		void SetWidth(const int& width) { this->Width = width; }

		// ����� ������������� ������ �������.
		void SetHeight(const int& height) { this->Height = height; }

		// ����� ���������� ������ �������.
		int GetHeight() { return this->Height; }

		// ����� ���������� ������ ������ �������.
		int GetLen() { return this->szObjectText.size(); }
	};
public:
	// ����� �������� ����.
	class Window : private WindowObject
	{
	private:
		/*����������*/

		/*Direct2D-stuff*/
		ID2D1Factory * _pD2D1Factory = nullptr;
		ID2D1HwndRenderTarget * _pRT = nullptr;

		IDWriteFactory * _pDWriteFactory = nullptr;
		IDWriteTextFormat * _pTextFormat = nullptr;

		ID2D1SolidColorBrush * _pBlackBrush = nullptr;
		ID2D1SolidColorBrush * _pWhiteBrush = nullptr;
		ID2D1SolidColorBrush * _pColorBrush = nullptr;

		HWND _hwnd{};
		MSG _msg{};
		ParamColor WindowBackgroundColor;

		/*������ �������� �����*/
		std::vector<Shan0xUI::Label*> labelObjs;
		std::vector<Shan0xUI::MaterialButton*> buttonObjs;
		std::vector<Shan0xUI::Panel*> panelObjs;
		std::vector<Shan0xUI::TextBox*> textboxObjs;
		std::vector<Shan0xUI::CheckBox*> checkboxObjs;

		bool _bWindowMinimumSize;
		bool _bWindowMaximumSize;
		bool _bWindowFixedSize;
		int _minWidth{}, _maxWidth{}, _fixedWidth{};
		int _minHeight{}, _maxHeight{}, _fixedHeight{};

		/*������*/

		// ����� ������� ����.
		void OnWindowRender();

		// ����� ������������� Direct2D.
		void InitDirectX();

		// ����� �������� ��������, ��� ������ � Direct2D.
		void CreateDirectxResources(HWND hwnd);

		// ����� �������� ������� ������.
		HRESULT CreateDirectxBrushes();

		// ����� �������� ����.
		void CreateUiWindow();

		// ����� ������ ������� Label.
		void DrawLabelObjs();

		// ����� ������ ������� Material Button.
		void DrawMaterialButtonObjs();

		// ����� ������ ������� Panel.
		void DrawPanelObjs();
		
		// ����� ������ ������� TextBox.
		void DrawTextBoxObjs();

		// ����� ������ ������� CheckBox.
		void DrawCheckBoxObjs();

		// ����� ��������� ������� ���������.
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// ����� ��������� ������� ���������.
		static LRESULT CALLBACK ApplicationProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// ����� ��������� ������� ���, ��������� up.
		void ProcessButton_LButtonUp();

		// ����� ��������� ������� ���, ��������� down.
		void ProcessButton_LButtonDown();

		// ����� ��������� mouse-hover.
		void ProcessButton_MouseMove();

		// ����� ��������� mouse-leave.
		void ProcessButton_MouseLeave();

		//////////////////////////////////////////////

		// ������ ��������� ������� ���, ��������� up.
		void ProcessTextBox_LButtonUp();

		// ������ ��������� ������� ���, ��������� down.
		void ProcessTextBox_LButtonDown();

		// ����� ��������� mouse-hover.
		void ProcessTextBox_MouseMove();

		// ����� ��������� mouse-leave.
		void ProcessTextBox_MouseLeave();
	
		// ����� ��������� text-change.
		void ProcessTextBox_TextChanged(const wchar_t* vKey);

		//////////////////////////////////////////////

		// ������ ��������� ������� ���, ��������� up.
		void ProcessCheckBox_LButtonUp();

		// ������ ��������� ������� ���, ��������� down.
		void ProcessCheckBox_LButtonDown();

		// ����� ��������� mouse-hover.
		void ProcessCheckBox_MouseMove();

		// ����� ��������� text-change.
		void ProcessCheckBox_MouseLeave();

		// ����� ��������� state-changed.
		//void ProcessCheckBox_StateChanged();

		//////////////////////////////////////////////
	public:
		// ����� ������� ������� ���������.
		int Run();

		// ������� �����������.
		// szWindowTitle = ��������� ����,
		// nWidth = ������ ����,
		// nHeight = ������ ����,
		// bScreenCenter = ���� true - ���� ����� �� ������ ������,
		// x, y = ������� �� ������.
		Window(const wchar_t* szWindowTitle, int nWidth = 600, int nHeight = 600, bool bScreenCenter = false, int x = 0, int y = 0);

		// ����� ���������� ���������� ����.
		HWND GetHWND() { return this->_hwnd; }

		// ����� ������������� ���� ������ ���� ����.
		void SetWinOnTop(bool onTop = true);

		// ����� ������������� ���� �������
		void SetBackgroundColor(BaseColor Color);

		// ����� ������������� ������� ���� �� ������.
		void SetWinPosition(const int& x, const int& y);

		// ����� ���������� ������� ���� �� ������.
		const int* GetWinPosition();

		// ����� ������������� ������� ����.
		void SetWinSize(const int& width, const int& height);

		// ����� ���������� ������� ����.
		const int* GetWinSize();

		// ����� ������������� ����� ��������� ����.
		void SetWinText(const wchar_t* text);

		// ����� ���������� ����� ��������� ����.
		const wchar_t* GetWinText();

		// ����� ��������� �� ����� �����.
		void AddLabel(Shan0xUI::Label& label);

		// ����� ��������� �� ����� ������.
		void AddButton(Shan0xUI::MaterialButton& button);

		// ����� ��������� �� ����� ������.
		void AddPanel(Shan0xUI::Panel& panel);

		// ����� ��������� �� ����� ���� ��� �����.
		void AddTextBox(Shan0xUI::TextBox& textbox);

		// ����� ��������� �� ����� �������.
		void AddCheckBox(Shan0xUI::CheckBox& checkbox);

		// ����� '�������'/'����������' ������ � ��������� ����.
		void SetWinButtons(bool minimizeButton = true, bool maximizeButton = true);

		// ����� ������������� ����������� ������ � ������ ����.
		void SetWinMinSize(bool bEnable = false, const int& minWidth = 600, const int& minHeight = 600);

		// ����� ������������� ������������ ������ � ������ ����.
		void SetWinMaxSize(bool bEnable = false, const int& maxWidth = 600, const int& maxHeight = 600);

		// ����� ������������� ������������� ������� ����.
		void SetWinFixedSize(bool bEnable = false, const int& fixedWidth = 600, const int& fixedHeight = 600);

		// ����������� �� ���������.
		Window();

		// ���������� �� ���������.
		~Window();
	};

	// ����� �������� '�����'.
	class Label : public TextFontBasedObject
	{
	private:
		ParamColor _Color;
	public:
		// ����������� �� ���������.
		Label(const wchar_t* text = L"Label", const wchar_t* fontName = L"Arial", 
			const int& fontSize = 18, const int& x = 10, const int& y = 10, const int& width = 100, const int& height = 100);

		// ����� ������������� ���� ������.
		virtual void SetBackgroundColor(BaseColor Color);

		// ����� ���������� ���� ������.
		ParamColor GetColor() { return this->_Color; }

		// ���������� �� ���������.
		~Label();
	};

	// ����� �������� '������'.
	class MaterialButton : public TextFontBasedObject
	{
	private:
		ParamColor _bColor;
		ParamColor _bColorOnHover;
		ParamColor _bColorOnClick;

		ParamColor _fColor;
		ParamColor _fColorOnHover;
		ParamColor _fColorOnClick;

		bool _isButtonHovered;
		bool _isButtonBeginPressed;
	public:
		enum MaterialButtonStyles { CrimsonStyle };

		bool getButtonState_Hovered() { return this->_isButtonHovered; }
		void setButtonState_Hovered(bool isButtonHovered) { this->_isButtonHovered = isButtonHovered; }

		bool getButtonState_BeginPressed() { return this->_isButtonBeginPressed; }
		void setButtonState_BeginPressed(bool isButtonBeginPressed) { this->_isButtonBeginPressed = isButtonBeginPressed; }

		// ����� ���������� true, ���� ������ ��������� '���' �������.
		bool IsCursorOnButton(HWND hwnd, float dpiX, float dpiY)
		{
			RECT rc{};
			rc.left = this->GetX() * dpiX;
			rc.top = this->GetY() * dpiY + 2;
			rc.right = this->GetWidth() * dpiX - 2 + (this->GetX() / 2) * 2;
			rc.bottom = this->GetHeight() * dpiY - 2 + (this->GetY() / 2) * 2;
			POINT pt{};
			GetCursorPos(&pt);
			ScreenToClient(hwnd, &pt);
			if (PtInRect(&rc, pt))
				return true;
			else
				return false;
		}

		// ����������� �� ���������.
		MaterialButton(const wchar_t* text = L"Button", const int& x = 0, const int& y = 0, const int& width = 150, const int& height = 40);
		
		// ����� ������������� ���� material-������.
		virtual void SetBackgroundColor(BaseColor Color);

		// ����� ������������� ���� ������ material-������.
		void SetForegroundColor(BaseColor Color);

		// ����� ������������� ���� ������ material-������ ��� ���������.
		void SetForegroundColorOnHover(BaseColor Color);

		// ����� ������������� ���� ���� material-������ ��� ���������.
		void SetBackgroundColorOnHover(BaseColor Color);

		// ����� ���������� ���� ������ material-������ ��� ���������.
		ParamColor GetForegroundColorOnHover() { return this->_fColorOnHover; }

		// ����� ���������� ���� material-������ ��� ���������.
		ParamColor GetBackgroundColorOnHover() { return this->_bColorOnHover; }

		// ����� ���������� ���� ������.
		ParamColor GetForegroundColor() { return this->_fColor; }

		// ����� ���������� ���� ���� material-������.
		ParamColor GetBackgroundColor() { return this->_bColor; }

		// ����� ������������� ���� ���� material-������ ��� �����.
		void SetBackgroundColorOnClick(BaseColor Color);

		// ����� ������������� ���� ������ material-������ ��� �����.
		void SetForegroundColorOnClick(BaseColor Color);

		// ����� ���������� ���� ���� material-������ ��� �����.
		ParamColor GetBackgroundColorOnClick() { return this->_bColorOnClick; }

		// ����� ���������� ���� ������ material-������ ��� �����.
		ParamColor GetForegroundColorOnClick() { return this->_fColorOnClick; }

		// ����� ������������� ����� ��� material-������.
		void SetStyle(MaterialButtonStyles style);

		// ����� ������ MouseEvent; c.� MouseEvents
		struct
		{
		public:
			void(*onClick)();

		} Connect;

		// ���������� �� ���������.
		~MaterialButton();
	};

	// ����� �������� '������'.
	class Panel : protected WindowObject
	{
	private:
		ParamColor _bColor;
	public:

		// ����������� �� ���������.
		Panel(BaseColor BackgroundColor = BaseColor::Black, const int& x = 0, const int& y = 0, const int& width = 100, const int& height = 100);

		// ����� ������������� ���� ������� panel.
		void SetBackgroundColor(BaseColor BackgroundColor) { this->_bColor = BackgroundColor; }

		// ����� ���������� ���� ������� panel.
		ParamColor GetBackgroundColor() { return this->_bColor; }

		// ����� ������������� X �������, ������� panel.
		void SetX(const int& x) { this->xPos = x; }

		// ����� ���������� ������� X, ������� panel.
		int GetX() { return this->xPos; }
		
		// ����� ������������� Y �������, ������� panel.
		void SetY(const int& y) { this->yPos = y; }

		// ����� ���������� ������� Y, ������� panel.
		int GetY() { return this->yPos; }

		// ����� ������������� ������ ������� panel.
		void SetWidth(const int& width) { this->Width = width; }

		// ����� ���������� ������ ������� panel.
		int GetWidth() { return this->Width; }
		
		// ����� ������������� ������ ������� panel.
		void SetHeight(const int& height) { this->Height = height; }

		// ����� ���������� ������ ������� panel.
		int GetHeight() { return this->Height; }

		// ���������� �� ���������.
		~Panel();
	};

	// ����� �������� '���� ��� �����'.
	class TextBox : public TextFontBasedObject 
	{
	private:
		// background
		ParamColor _bColor;
		ParamColor _bColorOnHover;
		ParamColor _bColorOnClick;

		// border
		ParamColor _bbColor;
		ParamColor _bbColorOnHover;
		ParamColor _bbColorOnClick;

		// font
		ParamColor _fColor;
		ParamColor _fColorOnHover;
		ParamColor _fColorOnClick;

		bool _isTextBoxHovered;
		bool _isTextBoxBeginPressed;

		int _textLimit;
	public:
		bool getTextBoxState_Hovered() { return this->_isTextBoxHovered; }
		void setTextBoxState_Hovered(bool isTextBoxHovered) { this->_isTextBoxHovered = isTextBoxHovered; }

		bool getTextBoxState_BeginPressed() { return this->_isTextBoxBeginPressed; }
		void setTextBoxState_BeginPressed(bool isTextBoxBeginPressed) { this->_isTextBoxBeginPressed = isTextBoxBeginPressed; }

		// ����� ���������� true, ���� ������ ��������� '���' ����� ��� �����.
		bool IsCursorOnTextBox(HWND hwnd, float dpiX, float dpiY)
		{
			RECT rc{};
			rc.left = this->GetX() * dpiX + 2;
			rc.top = this->GetY() * dpiY + 2;
			rc.right = this->GetWidth() * dpiX - 2 + (this->GetX() / 2) * 2;
			rc.bottom = this->GetHeight() * dpiY - 2 + (this->GetY() / 2) * 2;
			POINT pt{};
			GetCursorPos(&pt);
			ScreenToClient(hwnd, &pt);
			if (PtInRect(&rc, pt))
				return true;
			else
				return false;
		}

		// ����������� �� ���������.
		TextBox(const wchar_t* text = L"TextBox", const int& x = 10, const int& y = 10, const int& width = 220, const int& height = 35);

		// ����� ������������� ���� TextBox-��������.
		virtual void SetBackgroundColor(BaseColor Color);

		// ����� ������������� ����� �� ���������� �������� � TextBox.
		void SetTextLimit(const int& textLimit = 24);

		// ����� ���������� ����� �� ���������� �������� � TextBox.
		int GetTextLimit() { return this->_textLimit; }

		// ����� ������������� ���� ������ TextBox-��������.
		void SetForegroundColor(BaseColor Color);

		// ����� ������������� ���� ������� TextBox-��������.
		void SetBorderColor(BaseColor Color);

		// ����� ������������� ���� ������� TextBox-�������� ��� ���������.
		void SetBorderColorOnHover(BaseColor Color);

		// ����� ���������� ���� ������� TextBox-�������� ��� ���������.
		ParamColor GetBorderColorOnHover() { return this->_bbColorOnHover; }

		// ����� ������������� ���� ������� TextBox-�������� ��� �����.
		void SetBorderColorOnClick(BaseColor Color);

		// ����� ���������� ���� ������� TextBox-�������� ��� �����.
		ParamColor GetBorderColorOnClick() { return this->_bbColorOnClick; }

		// ����� ���������� ���� ������� TextBox-��������.
		ParamColor GetBorderColor() { return this->_bbColor; }

		// ����� ������������� ���� ������ TextBox-�������� ��� ���������.
		void SetForegroundColorOnHover(BaseColor Color);

		// ����� ������������� ���� ���� TextBox-�������� ��� ���������.
		void SetBackgroundColorOnHover(BaseColor Color);

		// ����� ���������� ���� ������ TextBox-�������� ��� ���������.
		ParamColor GetForegroundColorOnHover() { return this->_fColorOnHover; }

		// ����� ���������� ���� TextBox-�������� ��� ���������.
		ParamColor GetBackgroundColorOnHover() { return this->_bColorOnHover; }

		// ����� ���������� ���� ������ TextBox-��������.
		ParamColor GetForegroundColor() { return this->_fColor; }

		// ����� ���������� ���� ���� TextBox-��������.
		ParamColor GetBackgroundColor() { return this->_bColor; }

		// ����� ������������� ���� ���� TextBox-�������� ��� �����.
		void SetBackgroundColorOnClick(BaseColor Color);

		// ����� ������������� ���� ������ TextBox-�������� ��� �����.
		void SetForegroundColorOnClick(BaseColor Color);

		// ����� ���������� ���� ���� TextBox-�������� ��� �����.
		ParamColor GetBackgroundColorOnClick() { return this->_bColorOnClick; }

		// ����� ���������� ���� ������ TextBox-�������� ��� �����.
		ParamColor GetForegroundColorOnClick() { return this->_fColorOnClick; }

		// ���������� �� ���������.
		~TextBox();
	};

	// ����� �������� '�������'.
	class CheckBox : public TextFontBasedObject
	{
	private:
		// background
		ParamColor _bColor;
		ParamColor _bColorOnClick;

		// border
		ParamColor _bbColor;
		ParamColor _bbColorOnHover;

		bool _isCheckBoxHovered;
		bool _isCheckBoxBeginPressed;

		bool _isChecked;
	public:
		bool getCheckBoxState_Hovered() { return this->_isCheckBoxHovered; }
		void setCheckBoxState_Hovered(bool isCheckBoxHovered) { this->_isCheckBoxHovered = isCheckBoxHovered; }

		bool getCheckBoxState_BeginPressed() { return this->_isCheckBoxBeginPressed; }
		void setCheckBoxState_BeginPressed(bool isCheckBoxBeginPressed) { this->_isCheckBoxBeginPressed = isCheckBoxBeginPressed; }

		// ����� ���������� true, ���� CheckBox ����������.
		bool getCheckBoxState_Checked() { return this->_isChecked; }

		// ����� ������������� ��������� CheckBox.
		void setCheckBoxState_Checked(bool isChecked);

		// ����� ���������� true, ���� ������ ��������� '���' ���������.
		bool IsCursorOnCheckBox(HWND hwnd, float dpiX, float dpiY)
		{
			RECT rc{};
			rc.left = this->GetX() * dpiX;
			rc.top = this->GetY() * dpiY;
			rc.right = this->GetWidth() * dpiX + (this->GetX() / 2) * 2;
			rc.bottom = this->GetHeight() * dpiY + (this->GetY() / 2) * 2;
			POINT pt{};
			GetCursorPos(&pt);
			ScreenToClient(hwnd, &pt);
			if (PtInRect(&rc, pt))
				return true;
			else
				return false;
		}

		// ����� ������������� ���� CheckBox-��������.
		virtual void SetBackgroundColor(BaseColor Color);

		// ����� ������������� ���� CheckBox-�������� ��� �����.
		void SetBackgroundColorOnClick(BaseColor Color);

		// ����� ���������� ���� CheckBox-�������� ��� �����.
		ParamColor GetBackgroundColorOnClick() { return this->_bColorOnClick; }

		// ����� ������������� ���� ������� CheckBox-�������� ��� ���������.
		void SetBorderColorOnHover(BaseColor Color);

		// ����� ���������� ���� ������� CheckBox-�������� ��� ���������.
		ParamColor GetBorderColorOnHover() { return this->_bbColorOnHover; }

		// ����� ������������� ���� ������� CheckBox-��������.
		void SetBorderColor(BaseColor Color);

		// ����� ���������� ���� ������� CheckBox-��������.
		ParamColor GetBorderColor() { return this->_bbColor; }

		// ����������� �� ���������.
		CheckBox(const wchar_t* text = L"CheckBox", const int& x = 10, const int& y = 10, const int& width = 125, const int& height = 18);

		// ����� ������ MouseEvent; c.� MouseEvents
		struct
		{
		public:
			void(*onStateChanged)(bool checkBoxState);

		} Connect;

		// ���������� �� ���������.
		~CheckBox();
	};
};