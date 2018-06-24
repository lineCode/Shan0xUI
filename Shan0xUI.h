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

// Класс GUI-библиотеки.
class Shan0xUI
{
	class Label;
	class MaterialButton;
	class Panel;
	class TextBox;
	class CheckBox;
private:
	// Класс базового объекта окна.
	class WindowObject
	{
	protected:
		std::wstring szObjectText{};
		int xPos{}, yPos{};
		int Width{}, Height{};

		virtual void SetBackgroundColor(BaseColor Color) = 0;
	};

	// Наследуемый класс для объектов, содержащих текст.
	class TextFontBasedObject : WindowObject
	{
	private:
		std::wstring _fontName{};
		int _fontSize{};
	public:
		// Метод изменяет текст объекта.
		void SetText(const wchar_t* text) { this->szObjectText = text; SendMessage(NULL, WM_PAINT, 0, 0); }

		// Метод возвращает текст объекта.
		const wchar_t* GetText() { return this->szObjectText.c_str(); }

		// Метод задает шрифт объекту.
		void SetFont(const wchar_t* fontName) { this->_fontName = fontName; SendMessage(NULL, WM_PAINT, 0, 0); }

		// Метод возврщает название шрифта объекта.
		const wchar_t* GetFont() { return this->_fontName.c_str(); }

		// Метод задает размер шрифта объекта.
		void SetFontSize(const int& fontSize) { this->_fontSize = fontSize; SendMessage(NULL, WM_PAINT, 0, 0); }

		// Метод возвращает размер шрифтра объекта.
		int GetFontSize() { return this->_fontSize; }

		// Метод задает X - координату объекта.
		void SetX(const int& x) { this->xPos = x; SendMessage(NULL, WM_PAINT, 0, 0); }

		// Метод задает Y - координату объекта.
		void SetY(const int& y) { this->yPos = y; SendMessage(NULL, WM_PAINT, 0, 0); }

		// Метод возвращает X - координату объекта.
		int GetX() { return this->xPos; }

		// Метод возвращает Y - координату объекта.
		int GetY() { return this->yPos; }

		// Метод возвращает ширину объекта.
		int GetWidth() { return this->Width; }

		// Метод устанавливает ширину объекта.
		void SetWidth(const int& width) { this->Width = width; }

		// Метод устанавливает высоту объекта.
		void SetHeight(const int& height) { this->Height = height; }

		// Метод возвращает высоту объекта.
		int GetHeight() { return this->Height; }

		// Метод возвращает длинну текста объекта.
		int GetLen() { return this->szObjectText.size(); }
	};
public:
	// Класс базового окна.
	class Window : private WindowObject
	{
	private:
		/*Переменные*/

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

		/*Списки объектов формы*/
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

		/*Методы*/

		// Метод рендера окна.
		void OnWindowRender();

		// Метод инициализации Direct2D.
		void InitDirectX();

		// Метод создания ресурсов, для работы с Direct2D.
		void CreateDirectxResources(HWND hwnd);

		// Метод создания цветных кистей.
		HRESULT CreateDirectxBrushes();

		// Метод создания окна.
		void CreateUiWindow();

		// Метод рисует объекты Label.
		void DrawLabelObjs();

		// Метод рисует объекты Material Button.
		void DrawMaterialButtonObjs();

		// Метод рисует объекты Panel.
		void DrawPanelObjs();
		
		// Метод рисует объекты TextBox.
		void DrawTextBoxObjs();

		// Метод рисует объекты CheckBox.
		void DrawCheckBoxObjs();

		// Метод обработки оконных сообщений.
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// Метод обработки оконных сообщений.
		static LRESULT CALLBACK ApplicationProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// Метод обработки нажатий ЛКМ, положение up.
		void ProcessButton_LButtonUp();

		// Метод обработки нажатий ЛКМ, положение down.
		void ProcessButton_LButtonDown();

		// Метод обработки mouse-hover.
		void ProcessButton_MouseMove();

		// Метод обработки mouse-leave.
		void ProcessButton_MouseLeave();

		//////////////////////////////////////////////

		// Методы обработки нажатий ЛКМ, положение up.
		void ProcessTextBox_LButtonUp();

		// Методы обработки нажатий ЛКМ, положение down.
		void ProcessTextBox_LButtonDown();

		// Метод обработки mouse-hover.
		void ProcessTextBox_MouseMove();

		// Метод обработки mouse-leave.
		void ProcessTextBox_MouseLeave();
	
		// Метод обработки text-change.
		void ProcessTextBox_TextChanged(const wchar_t* vKey);

		//////////////////////////////////////////////

		// Методы обработки нажатий ЛКМ, положение up.
		void ProcessCheckBox_LButtonUp();

		// Методы обработки нажатий ЛКМ, положение down.
		void ProcessCheckBox_LButtonDown();

		// Метод обработки mouse-hover.
		void ProcessCheckBox_MouseMove();

		// Метод обработки text-change.
		void ProcessCheckBox_MouseLeave();

		// Метод обработки state-changed.
		//void ProcessCheckBox_StateChanged();

		//////////////////////////////////////////////
	public:
		// Метод запуска оконной процедуры.
		int Run();

		// Базовый конструктор.
		// szWindowTitle = заголовок окна,
		// nWidth = ширина окна,
		// nHeight = высота окна,
		// bScreenCenter = если true - окно будет по центру экрана,
		// x, y = позиция на экране.
		Window(const wchar_t* szWindowTitle, int nWidth = 600, int nHeight = 600, bool bScreenCenter = false, int x = 0, int y = 0);

		// Метод возвращает дескриптор окна.
		HWND GetHWND() { return this->_hwnd; }

		// Метод устанавливает окно поверх всех окон.
		void SetWinOnTop(bool onTop = true);

		// Метод устанавливает цвет объекта
		void SetBackgroundColor(BaseColor Color);

		// Метод устанавливает позицию окна на экране.
		void SetWinPosition(const int& x, const int& y);

		// Метод возвращает позицию окна на экране.
		const int* GetWinPosition();

		// Метод устанавливает размеры окна.
		void SetWinSize(const int& width, const int& height);

		// Метод возвращает размеры окна.
		const int* GetWinSize();

		// Метод устанавливает текст заголовка окна.
		void SetWinText(const wchar_t* text);

		// Метод возвращает текст заголовка окна.
		const wchar_t* GetWinText();

		// Метод добавляет на форму текст.
		void AddLabel(Shan0xUI::Label& label);

		// Метод добавляет на форму кнопку.
		void AddButton(Shan0xUI::MaterialButton& button);

		// Метод добавляет на форму панель.
		void AddPanel(Shan0xUI::Panel& panel);

		// Метод добавляет на форму поле для ввода.
		void AddTextBox(Shan0xUI::TextBox& textbox);

		// Метод добавляет на форму чекбокс.
		void AddCheckBox(Shan0xUI::CheckBox& checkbox);

		// Метод 'убирает'/'показывает' кнопки в заголовке окна.
		void SetWinButtons(bool minimizeButton = true, bool maximizeButton = true);

		// Метод устанавливают минимальную ширину и высоту окна.
		void SetWinMinSize(bool bEnable = false, const int& minWidth = 600, const int& minHeight = 600);

		// Метод устанавливают максимальную ширину и высоту окна.
		void SetWinMaxSize(bool bEnable = false, const int& maxWidth = 600, const int& maxHeight = 600);

		// Метод устанавливает фиксированные размеры окна.
		void SetWinFixedSize(bool bEnable = false, const int& fixedWidth = 600, const int& fixedHeight = 600);

		// Конструктор по умолчанию.
		Window();

		// Деструктор по умолчанию.
		~Window();
	};

	// Класс элемента 'текст'.
	class Label : public TextFontBasedObject
	{
	private:
		ParamColor _Color;
	public:
		// Конструктор по умолчанию.
		Label(const wchar_t* text = L"Label", const wchar_t* fontName = L"Arial", 
			const int& fontSize = 18, const int& x = 10, const int& y = 10, const int& width = 100, const int& height = 100);

		// Метод устанавливает цвет текста.
		virtual void SetBackgroundColor(BaseColor Color);

		// Метод возвращает цвет текста.
		ParamColor GetColor() { return this->_Color; }

		// Деструктор по умолчанию.
		~Label();
	};

	// Класс элемента 'кнопка'.
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

		// Метод возвращает true, если курсор находится 'над' кнопкой.
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

		// Конструктор по умолчанию.
		MaterialButton(const wchar_t* text = L"Button", const int& x = 0, const int& y = 0, const int& width = 150, const int& height = 40);
		
		// Метод устанавливает цвет material-кнопки.
		virtual void SetBackgroundColor(BaseColor Color);

		// Метод устанавливает цвет текста material-кнопки.
		void SetForegroundColor(BaseColor Color);

		// Метод устанавливает цвет текста material-кнопки при наведении.
		void SetForegroundColorOnHover(BaseColor Color);

		// Метод устанавливает цвет фона material-кнопки при наведении.
		void SetBackgroundColorOnHover(BaseColor Color);

		// Метод возвращает цвет текста material-кнопки при наведении.
		ParamColor GetForegroundColorOnHover() { return this->_fColorOnHover; }

		// Метод возвращает цвет material-кнопки при наведении.
		ParamColor GetBackgroundColorOnHover() { return this->_bColorOnHover; }

		// Метод возвращает цвет текста.
		ParamColor GetForegroundColor() { return this->_fColor; }

		// Метод возвращает цвет фона material-кнопки.
		ParamColor GetBackgroundColor() { return this->_bColor; }

		// Метод устанавливает цвет фона material-кнопки при клике.
		void SetBackgroundColorOnClick(BaseColor Color);

		// Метод устанавливает цвет текста material-кнопки при клике.
		void SetForegroundColorOnClick(BaseColor Color);

		// Метод возвращает цвет фона material-кнопки при клике.
		ParamColor GetBackgroundColorOnClick() { return this->_bColorOnClick; }

		// Метод возвращает цвет текста material-кнопки при клике.
		ParamColor GetForegroundColorOnClick() { return this->_fColorOnClick; }

		// Метод устанавливает стиль для material-кнопки.
		void SetStyle(MaterialButtonStyles style);

		// Метод задает MouseEvent; c.м MouseEvents
		struct
		{
		public:
			void(*onClick)();

		} Connect;

		// Деструктор по умолчанию.
		~MaterialButton();
	};

	// Класс элемента 'панель'.
	class Panel : protected WindowObject
	{
	private:
		ParamColor _bColor;
	public:

		// Конструктор по умолчанию.
		Panel(BaseColor BackgroundColor = BaseColor::Black, const int& x = 0, const int& y = 0, const int& width = 100, const int& height = 100);

		// Метод устанавливает цвет объекта panel.
		void SetBackgroundColor(BaseColor BackgroundColor) { this->_bColor = BackgroundColor; }

		// Метод возвращает цвет объекта panel.
		ParamColor GetBackgroundColor() { return this->_bColor; }

		// Метод устанавливает X позицию, объекта panel.
		void SetX(const int& x) { this->xPos = x; }

		// Метод возвращает позицию X, объекта panel.
		int GetX() { return this->xPos; }
		
		// Метод устанавливает Y позицию, объекта panel.
		void SetY(const int& y) { this->yPos = y; }

		// Метод возвращает позицию Y, объекта panel.
		int GetY() { return this->yPos; }

		// Метод устанавливает ширину объекта panel.
		void SetWidth(const int& width) { this->Width = width; }

		// Метод возвращает ширину объекта panel.
		int GetWidth() { return this->Width; }
		
		// Метод устанавливает высоту объекта panel.
		void SetHeight(const int& height) { this->Height = height; }

		// Метод возвращает высоту объекта panel.
		int GetHeight() { return this->Height; }

		// Деструктор по умолчанию.
		~Panel();
	};

	// Класс элемента 'поле для ввода'.
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

		// Метод возвращает true, если курсор находится 'над' полем для ввода.
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

		// Конструктор по умолчанию.
		TextBox(const wchar_t* text = L"TextBox", const int& x = 10, const int& y = 10, const int& width = 220, const int& height = 35);

		// Метод устанавливает цвет TextBox-элемента.
		virtual void SetBackgroundColor(BaseColor Color);

		// Метод устанавливает лимит на количество символов в TextBox.
		void SetTextLimit(const int& textLimit = 24);

		// Метод возвращает лимит на количество символов в TextBox.
		int GetTextLimit() { return this->_textLimit; }

		// Метод устанавливает цвет текста TextBox-элемента.
		void SetForegroundColor(BaseColor Color);

		// Метод устанавливает цвет обводки TextBox-элемента.
		void SetBorderColor(BaseColor Color);

		// Метод устанавливает цвет обводки TextBox-элемента при наведении.
		void SetBorderColorOnHover(BaseColor Color);

		// Метод возвращает цвет обводки TextBox-элемента при наведении.
		ParamColor GetBorderColorOnHover() { return this->_bbColorOnHover; }

		// Метод устанавливает цвет обводки TextBox-элемента при клике.
		void SetBorderColorOnClick(BaseColor Color);

		// Метод возвращает цвет обводки TextBox-элемента при клике.
		ParamColor GetBorderColorOnClick() { return this->_bbColorOnClick; }

		// Метод возвращает цвет обводки TextBox-элемента.
		ParamColor GetBorderColor() { return this->_bbColor; }

		// Метод устанавливает цвет текста TextBox-элемента при наведении.
		void SetForegroundColorOnHover(BaseColor Color);

		// Метод устанавливает цвет фона TextBox-элемента при наведении.
		void SetBackgroundColorOnHover(BaseColor Color);

		// Метод возвращает цвет текста TextBox-элемента при наведении.
		ParamColor GetForegroundColorOnHover() { return this->_fColorOnHover; }

		// Метод возвращает цвет TextBox-элемента при наведении.
		ParamColor GetBackgroundColorOnHover() { return this->_bColorOnHover; }

		// Метод возвращает цвет текста TextBox-элемента.
		ParamColor GetForegroundColor() { return this->_fColor; }

		// Метод возвращает цвет фона TextBox-элемента.
		ParamColor GetBackgroundColor() { return this->_bColor; }

		// Метод устанавливает цвет фона TextBox-элемента при клике.
		void SetBackgroundColorOnClick(BaseColor Color);

		// Метод устанавливает цвет текста TextBox-элемента при клике.
		void SetForegroundColorOnClick(BaseColor Color);

		// Метод возвращает цвет фона TextBox-элемента при клике.
		ParamColor GetBackgroundColorOnClick() { return this->_bColorOnClick; }

		// Метод возвращает цвет текста TextBox-элемента при клике.
		ParamColor GetForegroundColorOnClick() { return this->_fColorOnClick; }

		// Деструктор по умолчанию.
		~TextBox();
	};

	// Класс элемента 'чекбокс'.
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

		// Метод возвращает true, если CheckBox установлен.
		bool getCheckBoxState_Checked() { return this->_isChecked; }

		// Метод устанавливает положение CheckBox.
		void setCheckBoxState_Checked(bool isChecked);

		// Метод возвращает true, если курсор находится 'над' чекбоксом.
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

		// Метод устанавливает цвет CheckBox-элемента.
		virtual void SetBackgroundColor(BaseColor Color);

		// Метод устанавливает цвет CheckBox-элемента при клике.
		void SetBackgroundColorOnClick(BaseColor Color);

		// Метод возвращает цвет CheckBox-элемента при клике.
		ParamColor GetBackgroundColorOnClick() { return this->_bColorOnClick; }

		// Метод устанавливает цвет обводки CheckBox-элемента при наведении.
		void SetBorderColorOnHover(BaseColor Color);

		// Метод возвращает цвет обводки CheckBox-элемента при наведении.
		ParamColor GetBorderColorOnHover() { return this->_bbColorOnHover; }

		// Метод устанавливает цвет обводки CheckBox-элемента.
		void SetBorderColor(BaseColor Color);

		// Метод возвращает цвет обводки CheckBox-элемента.
		ParamColor GetBorderColor() { return this->_bbColor; }

		// Конструктор по умолчанию.
		CheckBox(const wchar_t* text = L"CheckBox", const int& x = 10, const int& y = 10, const int& width = 125, const int& height = 18);

		// Метод задает MouseEvent; c.м MouseEvents
		struct
		{
		public:
			void(*onStateChanged)(bool checkBoxState);

		} Connect;

		// Деструктор по умолчанию.
		~CheckBox();
	};
};