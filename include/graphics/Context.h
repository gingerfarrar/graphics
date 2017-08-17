#pragma once

//forward declare glfw'w window
//handling pointer type
struct GLFWwindow;

class Context
{
private:
	GLFWwindow *handle;

public:
	//pop up window
	bool init(size_t w = 800, size_t h = 600, const char *title = "Graphics");

	//update. determines fps
	bool step();
	bool getKey(int key);
	bool getMouseButton(int button);
	void getMousePosition(double &x_out, double &y_out);
	double getTime();
	//close window
	bool term();
};