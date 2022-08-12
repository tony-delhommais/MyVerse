cmake_minimum_required(VERSION 3.8)

set(ENGINE_SOURCES
	Core/Area/Area.cpp
	Core/Area/CircleArea.cpp
	Core/Area/OrientationFixedRectangleArea.cpp

	Core/Common/Application.cpp
	Core/Common/AssetRepositoryAnalyzer.cpp
	Core/Common/Clock.cpp
	Core/Common/Debug.cpp
	Core/Common/Input.cpp

	Core/Components/Component.cpp
	Core/Components/Camera.cpp
	Core/Components/MeshRenderer.cpp
	Core/Components/Script.cpp

	Core/CoreClass/ApplicationCore.cpp
	Core/CoreClass/InputCore.cpp
	Core/CoreClass/RessourceManagerCore.cpp

	Core/Entity/Entity.cpp
	Core/Entity/EntityQuadTree.cpp

	Core/Factories/ScriptFactory.cpp

	Core/Managers/RessourceManager.cpp

	Core/Ressource/Terrain/Chunck.cpp
	Core/Ressource/Terrain/Terrain.cpp
	Core/Ressource/Material.cpp
	Core/Ressource/Mesh.cpp
	Core/Ressource/Prefab.cpp
	Core/Ressource/Scene.cpp
	Core/Ressource/Shader.cpp
	Core/Ressource/Texture.cpp

	Core/Utils/JsonUtils.cpp
	Core/Utils/MathUtils.cpp
	Core/Utils/Utils.cpp
)

set(CLIENT_SOURCES
	Client/Scripts/GameSettings.cpp
	Client/Scripts/PlayerMovementController.cpp
	Client/Scripts/Rotation.cpp
	Client/Scripts/SpawnTest.cpp
)

add_executable(MyVerse "Client/Client.cpp" ${ENGINE_SOURCES} ${CLIENT_SOURCES})

set_property(TARGET MyVerse PROPERTY CXX_STANDARD 20)

if(WIN32)
	target_link_libraries(MyVerse
		grpc++
		glad
		glfw
		opengl32
	)
else()
	target_link_libraries(MyVerse
		grpc++
		glad
		glfw
		OpenGL
	)
endif()

target_include_directories(MyVerse PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)

target_compile_definitions(MyVerse PRIVATE PROJECT_SETTINGS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../resources/ProjectSettings/")
target_compile_definitions(MyVerse PRIVATE ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../resources/Assets/")
