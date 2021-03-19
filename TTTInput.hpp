#pragma once
#include "TTTRender.hpp"
#include "TTTTime.hpp"

class Input
{
public:
	struct TextBox
	{
		char choice[2] = "\0";
		int letterCount = 0;
		Rectangle textBox = { 1500 / 2 - 250, 450, 450, 50 };
		bool mouseOnText = false;
		int framesCounter = 0;

		TextBox() {};
		TextBox(Rectangle _textBox) : textBox(_textBox) {};
	};

	Vector2 position = { 0 };

	Input();

	// Two TextBoxes for each menu
	TextBox tb;

	void UpdateMousePosition(Window *window, Time *time);
	bool IsAnyKeyPressed();
	void DrawTextBox();
	void UpdateTextBox();
	void UpdateInput(Window *window, Time *time);
};