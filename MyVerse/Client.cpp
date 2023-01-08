//
// Created by Tony on 29/06/2022.
//

#include "ApplicationCore.h"

int main(int argc, char *argv[])
{
	Client::ApplicationCore& app = Client::ApplicationCore::instance();

	if (app.Initialize())
	{
		app.RenderLoop();
	}

	app.Clear();

	return 0;
}
