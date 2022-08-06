set(ENGINE_SOURCES
        Core/Area/Area.cpp
        Core/Area/CircleArea.cpp
        Core/Area/OrientationFixedRectangleArea.cpp

        Core/Components/Component.cpp
        Core/Components/Camera.cpp
        Core/Components/MeshRenderer.cpp
        Core/Components/Script.cpp

        Core/CoreClasse/ApplicationCore.cpp
        Core/CoreClasse/InputCore.cpp
        Core/CoreClasse/RessourceManagerCore.cpp

        Core/Entity/Entity.cpp
        Core/Entity/EntityQuadTree.cpp

        Core/Factories/ScriptFactory.cpp

        Core/Managers/RessourceManager.cpp

        Core/Rendering/Scene.cpp

        Core/Ressource/Material.cpp
        Core/Ressource/Mesh.cpp
        Core/Ressource/Prefab.cpp
        Core/Ressource/Shader.cpp
        Core/Ressource/Texture.cpp

        Core/Utils/JsonUtils.cpp
        Core/Utils/MathUtils.cpp
        Core/Utils/Utils.cpp

        Core/Application.cpp
        Core/AssetRepositoryAnalyzer.cpp
        Core/Clock.cpp
        Core/Debug.cpp
        Core/Input.cpp
        )

set(CLIENT_SOURCES
        Client/Scripts/GameSettings.cpp
        Client/Scripts/PlayerMovementController.cpp
        Client/Scripts/Rotation.cpp
        Client/Scripts/SpawnTest.cpp
        )

add_executable(MyVerse Client/main.cpp ${ENGINE_SOURCES} ${CLIENT_SOURCES})

target_link_libraries(MyVerse
        glad
        glfw
        #grpc++
        opengl32
        )

target_include_directories(MyVerse PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        )

target_compile_definitions(MyVerse PRIVATE RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../resources")