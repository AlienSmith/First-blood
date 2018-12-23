#pragma once
#include"Component.h"
#include"Vector3.h"
class Object;
namespace GStar {
	class LightComponent :public Component {
	public:
		const static float DistanceLimit;
		const static float SpotLightLimit;
		const static char TypeWord() {
			return LIGHT_WORD;
		}
		bool Initialize();
		bool Update();
		bool Terminate();
		LightComponent() :Component(LIGHT_WORD) {}
	private:
		Vector3 direction;
		Vector3 LightColor;
		Object* my_object;
		float Intensity;
		//Concentration > 0 For Spot light
		// = 0 for point light
		// < 0 for ambient Light
		float Conentration;
	};

}