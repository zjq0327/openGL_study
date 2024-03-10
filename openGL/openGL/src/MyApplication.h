#pragma once

#include"Application.h"
#include"Shader.h"

class MyApplication : public Application {
public:
	MyApplication();

protected:
	virtual void loop();

private:
	Shader shader;
	unsigned int VBO, VAO, EBO;
};