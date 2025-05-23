
#include "InputSystem.h"
#include "Util.h"

namespace Input {

	std::list<int> currentkeys;
	std::list<int> pressedkeys;
	std::list<int> Releasedkeys;
	std::list<int> CurrentMouseKeys;
	std::list<int> MousePressed;
	std::list<int> MouseReleased;


	//in my case it its getting the state of the key that was pressed or not 
	bool Input::getKey(const int& keycode)
	{
		if (glfwGetKey(Window::m_mywindow, keycode) == GLFW_PRESS)
		{
			return true;
		}

		return false;
	}
	//geting the state of mouse clicked 
	bool Input::getMouseKey(const int& keycode)
	{
		if (glfwGetMouseButton(Window::m_mywindow, keycode) == GLFW_PRESS)
		{
			return true;
		}

		return false;
	}
	
	// updates the lists where  i store the states of keys that was
	// pressed/released 	
	void Input::Update()
	{
		FillStates(false, NUM_MOUSEKEYCODES, MousePressed, MouseReleased);
		FillStates(true, NUM_KEYCODES, pressedkeys, Releasedkeys);
		FillCurrents(true, NUM_KEYCODES, currentkeys);
		FillCurrents(false, NUM_MOUSEKEYCODES, CurrentMouseKeys);
	
	}





	// to get position of the mouse when it clicked 
	void Input::FillStates(bool iskeyboard, const int& allkeycode, std::list<int>& Pressedkey, std::list<int>& Releasedkeys)
	{

		if (iskeyboard == false)
		{

			//released 
			Releasedkeys.clear();
			for (int i = 0; i < allkeycode; i++)
			{
				if (!getMouseKey(i) && UTils::Contains(CurrentMouseKeys, i))
				{
					Releasedkeys.emplace_back(i);
				}
			}


			//pressed
			Pressedkey.clear();
			for (int i = 0; i < allkeycode; i++)
			{
				if (getMouseKey(i) && !UTils::Contains(CurrentMouseKeys, i))
				{
					Pressedkey.emplace_back(i);
				}
			}

		}
		else if (iskeyboard == true)
		{
			//released
			Releasedkeys.clear();
			for (int i = 0; i < allkeycode; i++)
			{
				if (!getKey(i) && UTils::Contains(currentkeys, i))
				{
					Releasedkeys.emplace_back(i);
				}
			}
			//pressed
			Pressedkey.clear();
			for (int i = 0; i < allkeycode; i++)
			{
				if (getKey(i) && !UTils::Contains(currentkeys, i))
				{
					Pressedkey.emplace_back(i);
				}
			}
		}


	}

	void Input::FillCurrents(bool iskeyboard, const int& allkeycodes, std::list<int>& currents)
	{
		if (iskeyboard == true)
		{
			currents.clear();
			for (int i = 0; i < allkeycodes; i++)
			{
				if (getKey(i))
				{
					currents.emplace_back(i);
				}
			}
		}
		else if (iskeyboard == false)
		{
			currents.clear();
			for (int i = 0; i < allkeycodes; i++)
			{
				if (getMouseKey(i))
				{
					currents.emplace_back(i);
				}
			}
		}
	}

	bool Input::getStates(bool isMouse, bool ispressed, const int& keycodes)
	{
		if (isMouse == true)
		{	//mouse
			if (ispressed == true) {
				if (UTils::Contains(MousePressed, keycodes))
				{
					return true;
				}

			}
			else if (ispressed == false)
			{
				if (UTils::Contains(MouseReleased, keycodes))
				{
					return true;
				}

			}
		}
		else
		{
			//keyboard
			if (ispressed == true) {
				if (UTils::Contains(pressedkeys, keycodes))
				{
					return true;
				}

			}
			else if (ispressed == false)
			{
				if (UTils::Contains(Releasedkeys, keycodes))
				{
					return true;
				}

			}

		}
		return false;



	}
}
