#include "AzurEngine.h"

#include <iostream>

class Sandbox : public AzurEngine::Application
{
public:
	Sandbox()
	{
		std::cout << "Hello from Sandbox Project!!\n";
	}

	~Sandbox()
	{

	}
};

AzurEngine::Application* AzurEngine::CreateApplication()
{
	return new Sandbox();
}