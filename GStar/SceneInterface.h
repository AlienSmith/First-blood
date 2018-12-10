#pragma once
namespace GStar {
	class SceneInterface {
	public:
		static SceneInterface* Instance;
		SceneInterface() {}
		virtual ~SceneInterface() {}
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Terminate() = 0;
	};
}
GStar::SceneInterface* GStar::SceneInterface::Instance = nullptr;