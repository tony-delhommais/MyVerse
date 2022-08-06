//
// Created by Tony on 29/06/2022.
//

#include "Core/CoreClass/ApplicationCore.h"

int main(int argc, char *argv[])
{
    Core::ApplicationCore& app = Core::ApplicationCore::instance();

    if (app.Initialize())
    {
        app.RenderLoop();
    }

    app.Clear();

    return 0;
}
