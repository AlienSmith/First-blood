#pragma once
#include"Component.h"
#include"Vector3.h"
#include"TransformComponent.h"
class Object;
namespace GStar {
	enum Lighttype {DIRECTIONAL = 0, POINT =1, SPOT=2};
	struct LightInfo {
		Vector3 ambient;
		Vector3 diffuse;
		Vector3 specular;

		TransformComponent* my_transform;
		Lighttype my_type;

		float constant;
		float linear;
		float quadratic;
		//This value suggests the concentration level of the spot light

		float anglecutOff;
		float inneranglecutOff;
		float distancecutoff;
		LightInfo(Lighttype type, TransformComponent* component) :my_transform(component), my_type(type) {}
	};
	//This component will not be added on the Object
	class LightComponent {
	public:
		const static float DistanceLimit;
		const static float SpotLightLimit;
		LightComponent(Lighttype type, TransformComponent* component):
		my_info(type, component) {
			if (type == Lighttype::DIRECTIONAL) {
				CleananglecutOff();
				Cleanconstance();
			}
			else if (type == Lighttype::POINT) {
				CleananglecutOff();
			}
		}
		inline void SetIntensity(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular) {
			my_info.ambient = ambient;
			my_info.diffuse = diffuse;
			my_info.specular = specular;
		}
		//Both angle cutoff is for spot light set them to 0.0f if it is not a spot light
		inline void SetcutOff(float distancecutoff, float anglecutoff,float inneranglecutoff) {
			my_info.distancecutoff = distancecutoff;
			my_info.anglecutOff = anglecutoff;
			my_info.inneranglecutOff = inneranglecutoff;
		}
		inline void SetTransform( TransformComponent* component) {
			my_info.my_transform = component;
		}
		//concnetration is for the focus of the spot light leave it as 0.0f if it is not a spot light
		inline void SetActivateConsts(float constant, float linear, float qudratic) {
			my_info.linear = linear;
			my_info.constant = constant;
			my_info.quadratic = qudratic;
		}inline void SetType(Lighttype ltype) {
			my_info.my_type = ltype;
			if (ltype == Lighttype::DIRECTIONAL) {
				CleananglecutOff();
				Cleanconstance();
			}
			else if (ltype == Lighttype::POINT) {
				CleananglecutOff();
			}
		}
		//Read only
		inline const LightInfo& Getlightinfo() const {
			return my_info;
		}
		inline void CleananglecutOff() {
			my_info.inneranglecutOff = 0.0f;
			my_info.anglecutOff = 0.0f;
		}inline void Cleanconstance() {
			my_info.distancecutoff = 0.0f;
			my_info.linear = 0.0f;
			my_info.constant = 0.0f;
			my_info.quadratic = 0.0f;
		}
	private:
		LightInfo my_info;
	};

}