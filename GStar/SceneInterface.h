#pragma once
/*To use the customization of GStar  
1.inheritant this class for Secene setup and put and instance in SceneInterface::Instance;
2.inheritant InterfaceComponent and add them to the Object for Control of indivisual Object;
*/
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