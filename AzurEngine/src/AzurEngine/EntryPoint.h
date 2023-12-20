#pragma once

#include "Application.h"

int main(int argc, char* argv[])
{
	AzurEngine::app = AzurEngine::CreateApplication();

	int result = AzurEngine::app->Start();

	delete AzurEngine::app;

	return result;
}