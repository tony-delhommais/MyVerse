cmake_minimum_required(VERSION 3.8)

set(CLIENT_SOURCES
	Client/Area/Area.cpp
	Client/Area/CircleArea.cpp
	Client/Area/OrientationFixedRectangleArea.cpp

	Client/Builders/CameraBuilder.cpp
	Client/Builders/EntityBuilder.cpp
	Client/Builders/MaterialBuilder.cpp
	Client/Builders/MeshRendererBuilder.cpp
	Client/Builders/SceneBuilder.cpp
	Client/Builders/TransformBuilder.cpp

	Client/Common/Application.cpp
	Client/Common/AssetRepositoryAnalyzer.cpp
	Client/Common/Clock.cpp
	Client/Common/Debug.cpp
	Client/Common/Input.cpp
	Client/Common/RessourceManager.cpp
	
	Client/Components/Camera.cpp
	Client/Components/Component.cpp
	Client/Components/MeshRenderer.cpp
	Client/Components/Script.cpp
	Client/Components/Transform.cpp

	Client/Core/ApplicationCore.cpp
	Client/Core/InputCore.cpp
	Client/Core/RessourceManagerCore.cpp
	
	Client/Entity/Entity.cpp
	Client/Entity/EntityQuadTree.cpp

	Client/Factories/ScriptFactory.cpp

	Client/GameScripts/Controllers/CameraController.cpp
	Client/GameScripts/Controllers/PlayerController.cpp
	Client/GameScripts/GameSettings.cpp
	Client/GameScripts/Rotation.cpp
	Client/GameScripts/SpawnTest.cpp

	Client/Parser/CameraParser.cpp
	Client/Parser/EntityParser.cpp
	Client/Parser/MaterialParser.cpp
	Client/Parser/MeshRendererParser.cpp
	Client/Parser/SceneParser.cpp
	Client/Parser/TransformParser.cpp

	Client/Ressource/Terrain/Chunck.cpp
	Client/Ressource/Terrain/Terrain.cpp
	Client/Ressource/Material.cpp
	Client/Ressource/Mesh.cpp
	Client/Ressource/Prefab.cpp
	Client/Ressource/Scene.cpp
	Client/Ressource/Shader.cpp
	Client/Ressource/Texture.cpp

	Client/Utils/JsonUtils.cpp
	Client/Utils/MathUtils.cpp
	Client/Utils/Utils.cpp
)

add_executable(MyVerse "Client/Common/Client.cpp" ${CLIENT_SOURCES})

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
