#pragma once
#include <SDL.h>

class InputHandler {
public:
	static InputHandler* Instance() {
		if (input_instance == 0) {
			input_instance = new InputHandler();
		}
		return input_instance;
	}

	bool isKeyDown(SDL_Scancode key);
	void KeyUp();
	void KeyDown();
	void update();
	void clean();
	void handleEvent();

	const Uint8* m_keystates;

	//new add
	bool GetMouseButtonDown();
	bool GetMouseButtonUp();
	bool GetLeftMouseButtonState();
	void Reset();
	SDL_Point GetMousePosition();
	bool m_MouseBottonDown;
	bool m_MouseButtonUp;
	SDL_Point m_MousePosition;

private:
	//InputHandler();
	//~InputHandler(){}
	bool m_MouseButtonLeft;
	static InputHandler* input_instance;
};

