#include "Shan0xUI.h"
float dpiX{}, dpiY{};
TRACKMOUSEEVENT lpEventTrack{ sizeof(TRACKMOUSEEVENT) };
bool window_loaded = false;
std::wstring key_pressed{};

// Метод обработки оконных сообщений
LRESULT CALLBACK Shan0xUI::Window::ApplicationProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Shan0xUI::Window* pWindow{};

	if (uMsg == WM_NCCREATE)
	{
		pWindow = static_cast<Shan0xUI::Window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow)))
		{
			if (GetLastError() != 0)
				return false;
		}
	}
	else
	{
		pWindow = reinterpret_cast<Shan0xUI::Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pWindow)
	{
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

///////////////////////////////////////////////////////////////////
// Метод обработки нажатий ЛКМ, положение up.
void Shan0xUI::Window::ProcessButton_LButtonUp()
{
	if (this->buttonObjs.size() != 0)
		for (auto i = buttonObjs.begin(); i != buttonObjs.end(); i++)
		{
			if ((*i)->IsCursorOnButton(GetHWND(), dpiX, dpiY))
			{
				if ((*i)->getButtonState_BeginPressed())
				{
					SetCursor(LoadCursor(NULL, IDC_HAND));
					(*i)->setButtonState_BeginPressed(false);
					(*i)->setButtonState_Hovered(true);
					SendMessage(GetHWND(), WM_PAINT, 0, 0);
					if ((*i)->Connect.onClick != nullptr)
					{
						(*i)->Connect.onClick();
						SendMessage(GetHWND(), WM_PAINT, 0, 0);
					}
				}
			}
		}
}

// Метод обработки нажатий ЛКМ, положение down.
void Shan0xUI::Window::ProcessButton_LButtonDown()
{
	if (this->buttonObjs.size() != 0)
		for (auto i = buttonObjs.begin(); i != buttonObjs.end(); i++)
		{
			if ((*i)->getButtonState_Hovered())
			{
				SetCursor(LoadCursor(NULL, IDC_HAND));
				(*i)->setButtonState_BeginPressed(true);
				SendMessage(GetHWND(), WM_PAINT, 0, 0);
			}
		}
}

// Метод обработки mouse-hover.
void Shan0xUI::Window::ProcessButton_MouseMove()
{
	if (this->buttonObjs.size() != 0)
		for (auto i = buttonObjs.begin(); i != buttonObjs.end(); i++)
		{
			if ((*i)->IsCursorOnButton(GetHWND(), dpiX, dpiY))
			{
				(*i)->setButtonState_Hovered(true);
				SetCursor(LoadCursor(NULL, IDC_HAND));
				SendMessage(GetHWND(), WM_PAINT, 0, 0);
			}
			else
			{
				if ((*i)->getButtonState_Hovered())
				{
					(*i)->setButtonState_Hovered(false);
					SendMessage(GetHWND(), WM_PAINT, 0, 0);
				}
				else if ((*i)->getButtonState_BeginPressed())
				{
					(*i)->setButtonState_BeginPressed(false);
					SendMessage(GetHWND(), WM_PAINT, 0, 0);
				}
			}
		}
}

// Метод обработки mouse-leave.
void Shan0xUI::Window::ProcessButton_MouseLeave()
{
	if (this->buttonObjs.size() != 0)
		for (auto i = buttonObjs.begin(); i != buttonObjs.end(); i++)
		{
			(*i)->setButtonState_Hovered(false);
			(*i)->setButtonState_BeginPressed(false);
		}
	SendMessage(GetHWND(), WM_PAINT, 0, 0);
}

///////////////////////////////////////////////////////////////////

// Методы обработки нажатий ЛКМ, положение up.
void Shan0xUI::Window::ProcessTextBox_LButtonUp()
{
	if (this->textboxObjs.size() != 0)
		for (auto i = textboxObjs.begin(); i != textboxObjs.end(); i++)
		{
			if ((*i)->IsCursorOnTextBox(GetHWND(), dpiX, dpiY))
			{
				if ((*i)->getTextBoxState_BeginPressed())
				{
					SetCursor(LoadCursor(NULL, IDC_IBEAM));
					key_pressed = (*i)->GetText();
					SendMessage(GetHWND(), WM_PAINT, 0, 0);
				}
			}
		}
}

// Методы обработки нажатий ЛКМ, положение down.
void Shan0xUI::Window::ProcessTextBox_LButtonDown()
{
	if (this->textboxObjs.size() != 0)
		for (auto i = textboxObjs.begin(); i != textboxObjs.end(); i++)
		{
			if ((*i)->getTextBoxState_Hovered())
			{
				(*i)->setTextBoxState_BeginPressed(true);
				SetCursor(LoadCursor(NULL, IDC_IBEAM));
				SendMessage(GetHWND(), WM_PAINT, 0, 0);
			}
			else
				if ((*i)->getTextBoxState_BeginPressed())
				{
					key_pressed = {};
					(*i)->setTextBoxState_BeginPressed(false);
					SendMessage(GetHWND(), WM_PAINT, 0, 0);
				}
		}
}

// Метод обработки mouse-hover.
void Shan0xUI::Window::ProcessTextBox_MouseMove()
{
	if (this->textboxObjs.size() != 0)
		for (auto i = textboxObjs.begin(); i != textboxObjs.end(); i++)
		{
			if ((*i)->IsCursorOnTextBox(GetHWND(), dpiX, dpiY))
			{
				if (!(*i)->getTextBoxState_BeginPressed())
				{
					(*i)->setTextBoxState_BeginPressed(false);
					(*i)->setTextBoxState_Hovered(true);
					SetCursor(LoadCursor(NULL, IDC_IBEAM));
				}
				else if ((*i)->getTextBoxState_BeginPressed())
				{
					SetCursor(LoadCursor(NULL, IDC_IBEAM));
					(*i)->setTextBoxState_BeginPressed(true);
					(*i)->setTextBoxState_Hovered(false);
				}
				SendMessage(GetHWND(), WM_PAINT, 0, 0);
			}
			else
			{
				if ((*i)->getTextBoxState_Hovered())
				{
					(*i)->setTextBoxState_Hovered(false);
					SendMessage(GetHWND(), WM_PAINT, 0, 0);
				}
			}
		}
}

// Метод обработки mouse-leave.
void Shan0xUI::Window::ProcessTextBox_MouseLeave()
{
	if (this->textboxObjs.size() != 0)
		for (auto i = textboxObjs.begin(); i != textboxObjs.end(); i++)
		{
			(*i)->setTextBoxState_Hovered(false);
			//(*i)->setTextBoxState_BeginPressed(false);
		}
	SendMessage(GetHWND(), WM_PAINT, 0, 0);
}

// Метод обработки text-change.
void Shan0xUI::Window::ProcessTextBox_TextChanged(const wchar_t* vKey)
{
	if (this->textboxObjs.size() != 0)
		for (auto i = this->textboxObjs.begin(); i != this->textboxObjs.end(); i++)
		{
			if ((*i)->getTextBoxState_BeginPressed())
			{
					if ((int)vKey == VK_BACK && !key_pressed.empty())
					{
						if (key_pressed.size() == 0)
							key_pressed = {};

						key_pressed = key_pressed.substr(0, key_pressed.size() - 1);
						(*i)->SetText(key_pressed.c_str());
					}
					else if ((int)vKey != VK_BACK && key_pressed.length() < (*i)->GetTextLimit())
					{
						key_pressed += (wchar_t)vKey;
						(*i)->SetText(key_pressed.c_str());
					}
					SendMessage(GetHWND(), WM_PAINT, 0, 0);				
			}
		}
}

///////////////////////////////////////////////////////////////////

// Методы обработки нажатий ЛКМ, положение up.
void Shan0xUI::Window::ProcessCheckBox_LButtonUp()
{
	if (this->checkboxObjs.size() != 0)
		for (auto i = checkboxObjs.begin(); i != checkboxObjs.end(); i++)
		{
			if ((*i)->IsCursorOnCheckBox(GetHWND(), dpiX, dpiY))
			{
				if ((*i)->getCheckBoxState_BeginPressed())
				{
					if ((*i)->getCheckBoxState_Checked())
					{
						SetCursor(LoadCursor(NULL, IDC_HAND));
						(*i)->setCheckBoxState_Checked(false);
						(*i)->setCheckBoxState_BeginPressed(false);
						SendMessage(GetHWND(), WM_PAINT, 0, 0);
					}
					else
					{
						SetCursor(LoadCursor(NULL, IDC_HAND));
						(*i)->setCheckBoxState_Checked(true);
						SendMessage(GetHWND(), WM_PAINT, 0, 0);
					}
				}
			}
		}
}

// Методы обработки нажатий ЛКМ, положение down.
void Shan0xUI::Window::ProcessCheckBox_LButtonDown()
{
	if (this->checkboxObjs.size() != 0)
		for (auto i = this->checkboxObjs.begin(); i != this->checkboxObjs.end(); i++)
		{
			if ((*i)->getCheckBoxState_Hovered())
			{
				SetCursor(LoadCursor(NULL, IDC_HAND));
				(*i)->setCheckBoxState_BeginPressed(true);
				SendMessage(GetHWND(), WM_PAINT, 0, 0);
			}
		}
}

// Метод обработки mouse-hover.
void Shan0xUI::Window::ProcessCheckBox_MouseMove()
{
	if (this->checkboxObjs.size() != 0)
		for (auto i = this->checkboxObjs.begin(); i != this->checkboxObjs.end(); i++)
		{
			if ((*i)->IsCursorOnCheckBox(GetHWND(), dpiX, dpiY))
			{
				(*i)->setCheckBoxState_Hovered(true);
				SetCursor(LoadCursor(NULL, IDC_HAND));
				SendMessage(GetHWND(), WM_PAINT, 0, 0);
			}
			else
			{
				if ((*i)->getCheckBoxState_Hovered())
				{
					(*i)->setCheckBoxState_Hovered(false);
					SendMessage(GetHWND(), WM_PAINT, 0, 0);
				}
			}
		}
}

// Метод обработки text-change.
void Shan0xUI::Window::ProcessCheckBox_MouseLeave()
{
	if (this->checkboxObjs.size() != 0)
		for (auto i = this->checkboxObjs.begin(); i != this->checkboxObjs.end(); i++)
		{
			(*i)->setCheckBoxState_Hovered(false);
		}
	SendMessage(GetHWND(), WM_PAINT, 0, 0);
}

// Метод обработки state-changed.
void Shan0xUI::Window::ProcessCheckBox_StateChanged()
{
}

///////////////////////////////////////////////////////////////////

// Метод обработки оконных сообщений
LRESULT CALLBACK Shan0xUI::Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			this->_pD2D1Factory->GetDesktopDpi(&dpiX, &dpiY);
			dpiX /= 96.0f; dpiY /= 96.0f;
			this->CreateDirectxResources(hwnd);
			lpEventTrack.dwFlags = TME_LEAVE;
			lpEventTrack.hwndTrack = hwnd;
		}
		break;
		
		case WM_PAINT:
		{
			OnWindowRender();
		}
		break;
		
		case WM_CHAR:
		{
			ProcessTextBox_TextChanged(reinterpret_cast<wchar_t*>(wParam));
		}
		break;

		case WM_LBUTTONUP:
		{
			//
			ProcessButton_LButtonUp();
			//
			ProcessTextBox_LButtonUp();
			//
			ProcessCheckBox_LButtonUp();
		}
		break;

		case WM_MOUSEMOVE:
		{
			//
			ProcessButton_MouseMove();
			//
			ProcessTextBox_MouseMove();
			//
			ProcessCheckBox_MouseMove();

			TrackMouseEvent(&lpEventTrack);
		}
		break;

		case WM_LBUTTONDOWN:
		{
			//
			ProcessButton_LButtonDown();
			//
			ProcessTextBox_LButtonDown();
			//
			ProcessCheckBox_LButtonDown();
		}
		break;

		case WM_MOUSELEAVE:
		{
			//
			ProcessButton_MouseLeave();
			//
			ProcessTextBox_MouseLeave();
			//
			ProcessCheckBox_MouseLeave();
		}
		break;

		case WM_SIZE:
		{
			this->_pRT->Resize(D2D1::SizeU(LOWORD(lParam), HIWORD(lParam)));
		}
		break;

		case WM_GETMINMAXINFO:
		{
			LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
			if (this->_bWindowMinimumSize)
			{
				lpMMI->ptMinTrackSize.x = this->_minWidth;
				lpMMI->ptMinTrackSize.y = this->_minHeight;
			}
			if (this->_bWindowMaximumSize)
			{
				lpMMI->ptMaxTrackSize.x = this->_maxWidth;
				lpMMI->ptMaxTrackSize.y = this->_maxHeight;
			}
			if (this->_bWindowFixedSize)
			{
				lpMMI->ptMinTrackSize.x = this->_fixedWidth;
				lpMMI->ptMinTrackSize.y = this->_fixedHeight;
				lpMMI->ptMaxTrackSize.x = this->_fixedWidth;
				lpMMI->ptMaxTrackSize.y = this->_fixedHeight;
			}
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Метод рисует объекты Label.
void Shan0xUI::Window::DrawLabelObjs()
{
	for (auto i = this->labelObjs.begin(); i != this->labelObjs.end(); i++)
	{
		this->_pDWriteFactory->CreateTextFormat(
			(*i)->GetFont(),
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			(*i)->GetFontSize(),
			L"",
			&this->_pTextFormat);

		this->_pColorBrush->SetColor((*i)->GetColor());

		this->_pRT->DrawText((*i)->GetText(), (*i)->GetLen(), this->_pTextFormat,
			D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush);

		this->_pTextFormat->Release();
	}
}

// Метод рисует объекты Material Button.
void Shan0xUI::Window::DrawMaterialButtonObjs()
{
	for (auto i = this->buttonObjs.begin(); i != this->buttonObjs.end(); i++)
	{
		this->_pDWriteFactory->CreateTextFormat(
			(*i)->GetFont(),
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			(*i)->GetFontSize(),
			L"",
			&this->_pTextFormat);

		this->_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		this->_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		if ((*i)->getButtonState_BeginPressed())
		{
			(*i)->setButtonState_Hovered(false);
			this->_pColorBrush->SetColor((*i)->GetBackgroundColorOnClick());
			this->_pRT->FillRectangle(D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush);

			this->_pColorBrush->SetColor((*i)->GetForegroundColorOnClick());
			this->_pRT->DrawText((*i)->GetText(), (*i)->GetLen(), this->_pTextFormat,
				D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush);
		}
		else if ((*i)->getButtonState_Hovered())
		{
			this->_pColorBrush->SetColor((*i)->GetBackgroundColorOnHover());
			this->_pRT->FillRectangle(D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush);
		
			this->_pColorBrush->SetColor((*i)->GetForegroundColorOnHover());
			this->_pRT->DrawText((*i)->GetText(), (*i)->GetLen(), this->_pTextFormat,
				D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush);
		}
		else
		{
			this->_pColorBrush->SetColor((*i)->GetBackgroundColor());
			this->_pRT->DrawRectangle(D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush, 1.8f);
		
			this->_pColorBrush->SetColor((*i)->GetForegroundColor());
			this->_pRT->DrawText((*i)->GetText(), (*i)->GetLen(), this->_pTextFormat,
				D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush);
		}
		
		this->_pTextFormat->Release();
	}
}

// Метод рисует объекты Panel.
void Shan0xUI::Window::DrawPanelObjs()
{
	for (auto i = this->panelObjs.begin(); i != this->panelObjs.end(); i++)
	{
		this->_pColorBrush->SetColor((*i)->GetBackgroundColor());
		this->_pRT->FillRectangle(D2D1::RectF(static_cast<FLOAT>((*i)->GetX()), static_cast<FLOAT>((*i)->GetY()), static_cast<FLOAT>((*i)->GetWidth()), static_cast<FLOAT>((*i)->GetHeight())), this->_pColorBrush);
	}
}

// Метод рисует объекты TextBox.
void Shan0xUI::Window::DrawTextBoxObjs()
{
	for (auto i = this->textboxObjs.begin(); i != this->textboxObjs.end(); i++)
	{
		this->_pDWriteFactory->CreateTextFormat(
			(*i)->GetFont(),
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			(*i)->GetFontSize(),
			L"",
			&this->_pTextFormat);

		//this->_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		this->_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		this->_pColorBrush->SetColor((*i)->GetBackgroundColor());
		this->_pRT->FillRectangle(D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush);
		if ((*i)->getTextBoxState_BeginPressed())
		{
			this->_pColorBrush->SetColor((*i)->GetBorderColorOnClick());
			this->_pRT->DrawRectangle(D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush, 1.8f);
		}
		else if ((*i)->getTextBoxState_Hovered())
		{
			this->_pColorBrush->SetColor((*i)->GetBorderColorOnHover());
			this->_pRT->DrawRectangle(D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush, 1.8f);
		}
		else
		{
			this->_pColorBrush->SetColor((*i)->GetBorderColor());
			this->_pRT->DrawRectangle(D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()), this->_pColorBrush, 1.8f);
		}

		this->_pColorBrush->SetColor((*i)->GetForegroundColor());
		this->_pRT->DrawText(
			(*i)->GetText(), (*i)->GetLen(), this->_pTextFormat,
			D2D1::RectF((*i)->GetX() + 10, (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight()),
			this->_pColorBrush);

		this->_pTextFormat->Release();
	}
}

// Метод рисует объекты CheckBox.
void Shan0xUI::Window::DrawCheckBoxObjs()
{
	for (auto i = this->checkboxObjs.begin(); i != this->checkboxObjs.end(); i++)
	{

		this->_pDWriteFactory->CreateTextFormat(
			(*i)->GetFont(),
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			(*i)->GetFontSize(),
			L"",
			&this->_pTextFormat);

		this->_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		this->_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		this->_pColorBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		this->_pRT->DrawText((*i)->GetText(), (*i)->GetLen(), this->_pTextFormat, D2D1::RectF((*i)->GetX() + 20, (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight() + ((*i)->GetY() / 2) * 2), this->_pColorBrush);

		// debug
		//this->_pRT->DrawRectangle(D2D1::RectF((*i)->GetX(), (*i)->GetY(), (*i)->GetWidth(), (*i)->GetHeight() + ((*i)->GetY() / 2) * 2), this->_pBlackBrush, 2);
		
		if ((*i)->getCheckBoxState_BeginPressed())
		{
			this->_pColorBrush->SetColor((*i)->GetBackgroundColorOnClick());
			this->_pRT->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF((*i)->GetX(), (*i)->GetY(), 27, ((*i)->GetY() / 2) * 2 + (*i)->GetHeight()), 2, 2), this->_pColorBrush);

			// Process anim..
			this->_pColorBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
			this->_pRT->DrawLine(D2D1::Point2F((*i)->GetX() + 2, (*i)->GetY() + ((*i)->GetHeight() / 2)), D2D1::Point2F((*i)->GetX() + 7, (*i)->GetY() + ((*i)->GetHeight() / 2) + 5), this->_pColorBrush, 2.0f);
			this->_pRT->DrawLine(D2D1::Point2F((*i)->GetX() + 7, (*i)->GetY() + ((*i)->GetHeight() / 2) + 6), D2D1::Point2F((*i)->GetX() + 15, (*i)->GetY() + 4.5f), this->_pColorBrush, 2.0f);
		}
		else if ((*i)->getCheckBoxState_Hovered())
		{
			// Process anum..
			this->_pColorBrush->SetColor((*i)->GetBorderColorOnHover());
			this->_pRT->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF((*i)->GetX(), (*i)->GetY(), 27, ((*i)->GetY() / 2) * 2 + (*i)->GetHeight()), 1.5, 1.5), this->_pColorBrush, 1.8);
		}
		else
		{
			this->_pColorBrush->SetColor((*i)->GetBorderColor());
			this->_pRT->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF((*i)->GetX(), (*i)->GetY(), 27, ((*i)->GetY() / 2 ) * 2 + (*i)->GetHeight()), 1.5, 1.5), this->_pColorBrush, 1.8);
		}

		this->_pTextFormat->Release();
	}
}

// Метод рендера окна
void Shan0xUI::Window::OnWindowRender()
{
	this->_pRT->BeginDraw();
	this->_pRT->Clear(ParamColor(this->WindowBackgroundColor));

	if (this->panelObjs.size() != 0)
		DrawPanelObjs();

	if (this->textboxObjs.size() != 0)
		DrawTextBoxObjs();

	if (this->checkboxObjs.size() != 0)
		DrawCheckBoxObjs();

	if (this->labelObjs.size() != 0)
		DrawLabelObjs();

	if (this->buttonObjs.size() != 0)
		DrawMaterialButtonObjs();

	this->_pRT->EndDraw();
}

// Метод устанавливает цвет окна(клиентской области)
void Shan0xUI::Window::SetBackgroundColor(BaseColor Color)
{
	this->WindowBackgroundColor = Color;
	SendMessage(this->_hwnd, WM_PAINT, 0, 0);
}

// Метод устанавливает позицию окна на экране.
void Shan0xUI::Window::SetWinPosition(const int & x, const int & y)
{
	this->xPos = x;
	this->yPos = y;

	SetWindowPos(GetHWND(), NULL, x, y, this->Width, this->Height, NULL);
}

// Метод возвращает позицию окна на экране.
const int * Shan0xUI::Window::GetWinPosition()
{
	return new int[2]{ this->xPos, this->yPos };
}

// Метод устанавливает размеры окна.
void Shan0xUI::Window::SetWinSize(const int & width, const int & height)
{
	this->Width = width;
	this->Height = height;

	SetWindowPos(GetHWND(), NULL, this->xPos, this->yPos, width, height, NULL);
}

// Метод возвращает размеры окна.
const int * Shan0xUI::Window::GetWinSize()
{
	return new int[2]{ this->Width, this->Height};
}

// Метод устанавливает текст заголовка окна.
void Shan0xUI::Window::SetWinText(const wchar_t * text)
{
	this->szObjectText = text;

	SetWindowText(GetHWND(), text);
}

// Метод возвращает текст заголовка окна.
const wchar_t * Shan0xUI::Window::GetWinText()
{
	return this->szObjectText.c_str();
}

// Метод запуска оконной процедуры
int Shan0xUI::Window::Run()
{
	while (GetMessage(&this->_msg, NULL, 0, 0))
	{
		TranslateMessage(&this->_msg);
		DispatchMessage(&this->_msg);
	}
	return static_cast<int>(this->_msg.wParam);
}

// Метод создания окна
void Shan0xUI::Window::CreateUiWindow()
{
	InitDirectX();

	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpfnWndProc = ApplicationProc;
	wc.lpszClassName = this->szObjectText.c_str();
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error, while registering window class", L"Shan0xUI", MB_ICONERROR);
	}

	this->_hwnd = CreateWindow(
		this->szObjectText.c_str(),
		this->szObjectText.c_str(),
		WS_OVERLAPPEDWINDOW,
		this->xPos,
		this->yPos,
		this->Width,
		this->Height,
		NULL, NULL, NULL, this
	);
	ShowWindow(this->_hwnd, SW_SHOW);
	UpdateWindow(this->_hwnd);
}

// Метод создания цветных кистей
HRESULT Shan0xUI::Window::CreateDirectxBrushes()
{
	HRESULT hr = this->_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->_pBlackBrush);
	if (!SUCCEEDED(hr))
		return hr;

	hr = this->_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &this->_pWhiteBrush);
	if (!SUCCEEDED(hr))
		return hr;

	hr = this->_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::WhiteSmoke), &this->_pColorBrush);
	return hr;
}

// Метод создания ресурсов, для работы с Direct2D
void Shan0xUI::Window::CreateDirectxResources(HWND hwnd)
{
	RECT rcClient{};
	GetClientRect(hwnd, &rcClient);
	HRESULT hr = this->_pD2D1Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rcClient.right - rcClient.left, rcClient.bottom - rcClient.top)), &this->_pRT);
	if (!SUCCEEDED(hr))
		ExitProcess(-1);

	hr = CreateDirectxBrushes();
	if (!SUCCEEDED(hr))
		ExitProcess(-1);
}

// Метод инициализации Direct2D
void Shan0xUI::Window::InitDirectX()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->_pD2D1Factory);
	if (!SUCCEEDED(hr))
		ExitProcess(-1);

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(this->_pDWriteFactory), reinterpret_cast<IUnknown**>(&this->_pDWriteFactory));
	if (!SUCCEEDED(hr))
		ExitProcess(-1);
}

// Базовый конструктор.
// szWindowTitle = заголовок окна,
// nWidth = ширина окна,
// nHeight = высота окна,
// x, y = позиция на экране.
Shan0xUI::Window::Window(const wchar_t* szWindowTitle, int nWidth, int nHeight, bool bScreenCenter, int x, int y)
{
	this->szObjectText = szWindowTitle;
	this->Width = nWidth;
	this->Height = nHeight;
	this->WindowBackgroundColor = BaseColor(BaseColor::White);
	if (bScreenCenter)
	{
		this->xPos = (GetSystemMetrics(SM_CXSCREEN) - nWidth)  / 2;
		this->yPos = (GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;
	}
	else
	{
		this->xPos = x;
		this->yPos = y;
	}

	CreateUiWindow();
}

// Конструктор по умолчанию.
Shan0xUI::Window::Window()
{
	this->szObjectText = {L"Form"};
	this->Width = { 600 };
	this->Height = { 600 };
	this->xPos = { 0 };
	this->yPos = { 0 };
	this->WindowBackgroundColor = BaseColor(BaseColor::White);

	CreateUiWindow();
}

// Деструктор по умолчанию.
Shan0xUI::Window::~Window()
{
	this->_pBlackBrush->Release();
	this->_pWhiteBrush->Release();
	this->_pColorBrush->Release();
	this->_pRT->Release();
	this->_pD2D1Factory->Release();
}

// Метод добавляет на форму текст.
void Shan0xUI::Window::AddLabel(Shan0xUI::Label& label)
{
	this->labelObjs.push_back(&label);
	SendMessage(this->_hwnd, WM_PAINT, 0, 0);
}

// Метод добавляет на форму кнопку.
void Shan0xUI::Window::AddButton(Shan0xUI::MaterialButton& button)
{
	this->buttonObjs.push_back(&button);
	SendMessage(this->_hwnd, WM_PAINT, 0, 0);
}

// Метод добавляет на форму панель.
void Shan0xUI::Window::AddPanel(Shan0xUI::Panel& panel)
{
	this->panelObjs.push_back(&panel);
	SendMessage(this->_hwnd, WM_PAINT, 0, 0);
}

// Метод добавляет на форму поле для ввода.
void Shan0xUI::Window::AddTextBox(Shan0xUI::TextBox & textbox)
{
	this->textboxObjs.push_back(&textbox);
	SendMessage(this->_hwnd, WM_PAINT, 0, 0);
}

// Метод добавляет на форму чекбокс.
void Shan0xUI::Window::AddCheckBox(Shan0xUI::CheckBox & checkbox)
{
	this->checkboxObjs.push_back(&checkbox);
	SendMessage(this->_hwnd, WM_PAINT, 0, 0);
}

// Метод 'убирает'/'показывает' кнопки в заголовке окна.
void Shan0xUI::Window::SetWinButtons(bool minimizeButton, bool maximizeButton)
{
	LONG_PTR dwNewLong = GetWindowLongPtr(GetHWND(), GWL_STYLE);
	if (minimizeButton && !maximizeButton)
	{
		SetWindowLongPtr(GetHWND(), GWL_STYLE, dwNewLong&~WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
	}
	else if (!minimizeButton && maximizeButton)
	{
		SetWindowLongPtr(GetHWND(), GWL_STYLE, dwNewLong&~WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	}
	else if (!minimizeButton && !maximizeButton)
	{
		SetWindowLongPtr(GetHWND(), GWL_STYLE, dwNewLong&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX);
	}
	else if (minimizeButton && maximizeButton)
	{
		SetWindowLongPtr(GetHWND(), GWL_STYLE, dwNewLong | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	}
}

// Метод устанавливают минимальную ширину и высоту окна.
void Shan0xUI::Window::SetWinMinSize(bool bEnable, const int& minWidth, const int& minHeight)
{
	if (bEnable)
	{
		this->_minWidth = minWidth;
		this->_minHeight = minHeight;
		this->_bWindowMinimumSize = true;
	}
	else
	{
		this->_bWindowMinimumSize = false;
		this->_minWidth = 0;
		this->_minHeight = 0;
	}
}

// Метод устанавливают максимальную ширину и высоту окна.
void Shan0xUI::Window::SetWinMaxSize(bool bEnable, const int& maxWidth, const int& maxHeight)
{
	if (bEnable)
	{
		this->_maxWidth = maxWidth;
		this->_maxHeight = maxHeight;
		this->_bWindowMaximumSize = true;
	}
	else
	{
		this->_bWindowMaximumSize = false;
		this->_maxWidth = 0;
		this->_maxHeight = 0;
	}
}

// Метод устанавливает фиксированные размеры окна.
void Shan0xUI::Window::SetWinFixedSize(bool bEnable, const int & fixedWidth, const int & fixedHeight)
{
	if (bEnable)
	{
		this->_fixedWidth = fixedWidth;
		this->_fixedHeight = fixedHeight;
		this->_bWindowFixedSize = true;
	}
	else
	{
		this->_bWindowFixedSize = false;
		this->_fixedWidth = 0;
		this->_fixedHeight = 0;
	}
}

// Конструктор по умолчанию.
Shan0xUI::Label::Label(const wchar_t* text, 
	const wchar_t* fontName, const int& fontSize, const int& x, const int& y, const int& width, const int& height)
{
	this->SetText(text);
	this->SetFont(fontName);
	this->SetFontSize(fontSize);
	this->SetWidth(width);
	this->SetHeight(height);
	this->SetX(x);
	this->SetY(y);
}

// Деструктор по умолчанию.
Shan0xUI::Label::~Label()
{
}

// Конструктор по умолчанию.
Shan0xUI::MaterialButton::MaterialButton(const wchar_t* text, const int& x, const int& y, const int& width, const int& height)
{
	this->SetText(text);
	this->SetFont(L"Verdana");
	this->SetFontSize(14);

	this->SetBackgroundColor(BaseColor::LightGray);
	this->SetForegroundColor(BaseColor::LightGray);

	this->SetForegroundColorOnHover(BaseColor::LightGray);
	this->SetBackgroundColorOnHover(BaseColor::DarkGray);
	
	this->SetBackgroundColorOnClick(BaseColor::Gray);
	
	this->SetWidth(width);
	this->SetHeight(height);
	this->SetX(x);
	this->SetY(y);
	this->Connect.onClick = nullptr;
	this->setButtonState_Hovered(false);
	this->setButtonState_BeginPressed(false);
}

// Метод устанавливает цвет кнопки.
void Shan0xUI::MaterialButton::SetBackgroundColor(BaseColor Color)
{
	this->_bColor = Color;
}

// Метод устанавливает цвет текста material-кнопки.
void Shan0xUI::MaterialButton::SetForegroundColor(BaseColor Color)
{
	this->_fColor = Color;
}

// Метод устанавливает цвет фона material-кнопки при наведении.
void Shan0xUI::MaterialButton::SetBackgroundColorOnHover(BaseColor Color)
{
	this->_bColorOnHover = Color;
}

// Метод устанавливает цвет текста material-кнопки при наведении.
void Shan0xUI::MaterialButton::SetForegroundColorOnHover(BaseColor Color)
{
	this->_fColorOnHover = Color;
}

// Метод устанавливает цвет фона material-кнопки при клике.
void Shan0xUI::MaterialButton::SetBackgroundColorOnClick(BaseColor Color)
{
	this->_bColorOnClick = Color;
}

// Метод устанавливает цвет текста material-кнопки при клике.
void Shan0xUI::MaterialButton::SetForegroundColorOnClick(BaseColor Color)
{
	this->_fColorOnClick = Color;
}

// Метод устанавливает стиль для material-кнопки.
void Shan0xUI::MaterialButton::SetStyle(MaterialButtonStyles style)
{
	if (style == CrimsonStyle)
	{
		this->SetBackgroundColor(BaseColor::Crimson);
		this->SetForegroundColor(BaseColor::Crimson);
		this->SetBackgroundColorOnHover(BaseColor::Crimson);
		this->SetForegroundColorOnHover(BaseColor::White);
		this->SetForegroundColorOnClick(BaseColor::GhostWhite);
		this->SetBackgroundColorOnClick(BaseColor::DarkRed);
	}
}

// Метод устанавливает цвет текста.
void Shan0xUI::Label::SetBackgroundColor(BaseColor Color)
{
	this->_Color = Color;
}

// Деструктор по умолчанию.
Shan0xUI::MaterialButton::~MaterialButton()
{
}

// Конструктор по умолчанию.
Shan0xUI::Panel::Panel(BaseColor BackgroundColor, const int & x, const int & y, const int & width, const int & height)
{
	this->_bColor = BackgroundColor;
	this->xPos = x;
	this->yPos = y;
	this->Width = width;
	this->Height = height;
}

// Деструктор по умолчанию.
Shan0xUI::Panel::~Panel()
{
}

// Конструктор по умолчанию.
Shan0xUI::TextBox::TextBox(const wchar_t * text, const int & x, const int & y, const int & width, const int & height)
{
	this->SetText(text);
	this->SetFont(L"Verdana");
	this->SetFontSize(14);
	this->SetX(x);
	this->SetY(y);
	this->SetWidth(width);
	this->SetHeight(height);

	this->SetTextLimit(24);

	this->SetBackgroundColor(BaseColor::White);
	this->SetBackgroundColorOnClick(BaseColor::White);
	this->SetBackgroundColorOnHover(BaseColor::White);

	this->SetForegroundColor(BaseColor::Black);
	this->SetForegroundColorOnClick(BaseColor::Black);
	this->SetForegroundColorOnHover(BaseColor::Black);

	this->SetBorderColor(BaseColor::Black);
	this->SetBorderColorOnClick(BaseColor::LightBlue);
	this->SetBorderColorOnHover(BaseColor::Gray);

	this->setTextBoxState_Hovered(false);
	this->setTextBoxState_BeginPressed(false);
}

// Метод устанавливает цвет TextBox-элемента.
void Shan0xUI::TextBox::SetBackgroundColor(BaseColor Color)
{
	this->_bColor = Color;
}

// Метод устанавливает лимит на количество символов в TextBox.
void Shan0xUI::TextBox::SetTextLimit(const int & textLimit)
{
	this->_textLimit = textLimit;
}

// Метод устанавливает цвет текста TextBox-элемента.
void Shan0xUI::TextBox::SetForegroundColor(BaseColor Color)
{
	this->_fColor = Color;
}

// Метод устанавливает цвет обводки TextBox-элемента.
void Shan0xUI::TextBox::SetBorderColor(BaseColor Color)
{
	this->_bbColor = Color;
}

// Метод устанавливает цвет обводки TextBox-элемента при наведении.
void Shan0xUI::TextBox::SetBorderColorOnHover(BaseColor Color)
{
	this->_bbColorOnHover = Color;
}

// Метод устанавливает цвет обводки TextBox-элемента при клике.
void Shan0xUI::TextBox::SetBorderColorOnClick(BaseColor Color)
{
	this->_bbColorOnClick = Color;
}

// Метод устанавливает цвет текста TextBox-элемента при наведении.
void Shan0xUI::TextBox::SetForegroundColorOnHover(BaseColor Color)
{
	this->_fColorOnHover = Color;
}

// Метод устанавливает цвет фона TextBox-элемента при наведении.
void Shan0xUI::TextBox::SetBackgroundColorOnHover(BaseColor Color)
{
	this->_bColorOnHover = Color;
}

// Метод устанавливает цвет фона TextBox-элемента при клике.
void Shan0xUI::TextBox::SetBackgroundColorOnClick(BaseColor Color)
{
	this->_bColorOnClick = Color;
}

// Метод устанавливает цвет текста TextBox-элемента при клике.
void Shan0xUI::TextBox::SetForegroundColorOnClick(BaseColor Color)
{
	this->_fColorOnClick = Color;
}

// Деструктор по умолчанию.
Shan0xUI::TextBox::~TextBox()
{
}

void Shan0xUI::CheckBox::setCheckBoxState_Checked(bool isChecked)
{
	this->_isChecked = isChecked;
}

// Метод устанавливает цвет CheckBox-элемента при клике.
void Shan0xUI::CheckBox::SetBackgroundColor(BaseColor Color)
{
	this->_bColor = Color;
}

// Метод устанавливает цвет CheckBox-элемента при клике.
void Shan0xUI::CheckBox::SetBackgroundColorOnClick(BaseColor Color)
{
	this->_bColorOnClick = Color;
}

// Метод устанавливает цвет обводки CheckBox-элемента при наведении.
void Shan0xUI::CheckBox::SetBorderColorOnHover(BaseColor Color)
{
	this->_bbColorOnHover = Color;
}

// Метод устанавливает цвет обводки CheckBox-элемента.
void Shan0xUI::CheckBox::SetBorderColor(BaseColor Color)
{
	this->_bbColor = Color;
}

// Конструктор по умолчанию.
Shan0xUI::CheckBox::CheckBox(const wchar_t * text, const int & x, const int & y, const int & width, const int & height)
{
	this->SetText(text);
	this->SetX(x);
	this->SetY(y);
	this->SetWidth(width);
	this->SetHeight(height);
	this->SetFont(L"Arial");
	this->SetFontSize(14);

	this->SetBackgroundColor(BaseColor::White);
	this->SetBackgroundColorOnClick(BaseColor::Aqua);

	this->SetBorderColor(BaseColor::DarkGray);
	this->SetBorderColorOnHover(BaseColor::Aqua);

	this->setCheckBoxState_Hovered(false);
	this->setCheckBoxState_BeginPressed(false);
}

// Деструктор по умолчанию.
Shan0xUI::CheckBox::~CheckBox()
{
}
