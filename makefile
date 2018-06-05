all:
	g++ main.cpp maths/Vector2.cpp maths/Matrix2.cpp game/Renderer.cpp game/Scene.cpp game/Wall.cpp system/wad.cpp system/texture.cpp system/file.cpp game/Character.cpp system/Inputs.cpp system/Controller.cpp game/World.cpp game/Sector.cpp -lSDL2

