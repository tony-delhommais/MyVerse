cmake_minimum_required(VERSION 3.8)

set(CLIENT_SOURCES
	Client/Area/Area.cpp
	Client/Area/CircleArea.cpp
	Client/Area/OrientationFixedRectangleArea.cpp

	Client/Common/Application.cpp
	Client/Common/AssetRepositoryAnalyzer.cpp
	Client/Common/Clock.cpp
	Client/Common/Debug.cpp
	Client/Common/Input.cpp
	Client/Common/RessourceManager.cpp
	Client/Common/SceneManager.cpp
	
	Client/Components/Camera/Camera.cpp
	Client/Components/Camera/CameraBuilder.cpp
	Client/Components/Camera/CameraParser.cpp

	Client/Components/MeshRenderer/MeshRenderer.cpp
	Client/Components/MeshRenderer/MeshRendererBuilder.cpp
	Client/Components/MeshRenderer/MeshRendererParser.cpp

	Client/Components/Script/Script.cpp
	Client/Components/Script/ScriptFactory.cpp

	Client/Components/Transform/Transform.cpp
	Client/Components/Transform/TransformBuilder.cpp
	Client/Components/Transform/TransformParser.cpp

	Client/Components/Component.cpp

	Client/Core/ApplicationCore.cpp
	Client/Core/InputCore.cpp
	Client/Core/RessourceManagerCore.cpp
	Client/Core/SceneManagerCore.cpp
	
	Client/Entity/EntityQuadTree/EntityQuadTree.cpp
	
	Client/Entity/Entity.cpp
	Client/Entity/EntityBuilder.cpp
	Client/Entity/EntityParser.cpp

	Client/GameScripts/Controllers/CameraController.cpp
	Client/GameScripts/Controllers/PlayerController.cpp

	Client/GameScripts/GameSettings.cpp
	Client/GameScripts/Rotation.cpp
	Client/GameScripts/SpawnTest.cpp
	
	Client/Ressources/Material/Material.cpp
	Client/Ressources/Material/MaterialBuilder.cpp
	Client/Ressources/Material/MaterialParser.cpp
	
	Client/Ressources/Mesh/Mesh.cpp
	
	Client/Ressources/Prefab/Prefab.cpp

	Client/Ressources/Scene/Scene.cpp

	Client/Ressources/Shader/Shader.cpp

	Client/Ressources/Terrain/Chunck.cpp
	Client/Ressources/Terrain/Terrain.cpp

	Client/Ressources/Texture/Texture.cpp

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
