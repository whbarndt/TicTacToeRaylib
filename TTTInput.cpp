#include "TTTInput.hpp"

Input::Input() {};

// Function for updating the mouse position
void Input::UpdateMousePosition(Window *window, Time *time)
{
    position = GetScreenToWorld2D(GetMousePosition(), window->camera);
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool Input::IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

// Function for drawing the text box
void Input::DrawTextBox()
{
    DrawRectangleRec(tb.textBox, LIGHTGRAY);
    if (tb.mouseOnText) DrawRectangleLines(tb.textBox.x, tb.textBox.y, tb.textBox.width, tb.textBox.height, RED);
    else DrawRectangleLines(tb.textBox.x, tb.textBox.y, tb.textBox.width, tb.textBox.height, DARKGRAY);

    DrawText(tb.choice, tb.textBox.x + 5, tb.textBox.y + 8, 40, MAROON);

    if (tb.mouseOnText)
    {
        if (tb.letterCount < 2)
        {
            // Draw blinking underscore char
            if (((tb.framesCounter / 20) % 2) == 0) DrawText("_", tb.textBox.x + 8 + MeasureText(tb.choice, 40), tb.textBox.y + 12, 40, MAROON);
        }
    }
}

// Function to update the text box
void Input::UpdateTextBox()
{
    if (CheckCollisionPointRec(GetMousePosition(), tb.textBox)) tb.mouseOnText = true;
    else tb.mouseOnText = false;

    if (tb.mouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (tb.letterCount < 2))
            {
                tb.choice[tb.letterCount] = (char)key;
                tb.letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            tb.letterCount--;
            if (tb.letterCount < 0) tb.letterCount = 0;
            tb.choice[tb.letterCount] = '\0';
        }
    }
    else if (GetMouseCursor() != MOUSE_CURSOR_DEFAULT) SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (tb.mouseOnText) tb.framesCounter++;
    else tb.framesCounter = 0;
}

// Function that updates all inputs
void Input::UpdateInput(Window *window, Time *time)
{
    UpdateMousePosition(window, time);
    UpdateTextBox();
    IsAnyKeyPressed();
}