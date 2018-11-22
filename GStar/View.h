#pragma once
//This class manage how indivisual object are transformed from the model to the world space
class Scene;
class View {
public:
	void Update();
	View(const Scene* const scene) :my_scene(scene) {}
	View(const View& other) = delete;
	View& operator = (const View& i_other) = delete;
private:
	const Scene* const my_scene;
	void CleanScreen();
};