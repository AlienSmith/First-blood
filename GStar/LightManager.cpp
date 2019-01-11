//include Shader.h after light manager would lead to error.
#include "Shader.h"
#include "LightManager.h"
namespace GStar {
	LightManager* LightManager::instance = nullptr;
	void LightManager::WriteToShader(const Shader * const shader) const
	{	
		shader->setVec3("light[0].position", LightManager::Instance()->GetLightPosition());
		shader->setVec3("light[0].ambient", LightManager::Instance()->GetLightInfo().ambient);
		shader->setVec3("light[0].diffuse", LightManager::Instance()->GetLightInfo().diffuse);
		shader->setVec3("light[0].specular", LightManager::Instance()->GetLightInfo().specular);
		shader->setInt("light[0].lighttype", LightManager::Instance()->GetLightInfo().my_type);
		//Point out to light
		if (LightManager::Instance()->GetLightInfo().my_type != Lighttype::POINT) {
			GStar::Vector3 temp = LightManager::Instance()->GetLightInfo().my_transform->GetForWardVector();
			temp.Normalize();
			temp *= -1.0f;
			shader->setVec3("light[0].lightDirection", temp);
		}
		if (LightManager::Instance()->GetLightInfo().my_type != Lighttype::DIRECTIONAL) {
			shader->setFloat("light[0].constant", LightManager::Instance()->GetLightInfo().constant);
			shader->setFloat("light[0].linear", LightManager::Instance()->GetLightInfo().linear);
			shader->setFloat("light[0].quadratic", LightManager::Instance()->GetLightInfo().quadratic);
			shader->setFloat("light[0].distancecutoff", LightManager::Instance()->GetLightInfo().distancecutoff);
			if (LightManager::Instance()->GetLightInfo().my_type == Lighttype::SPOT) {
				shader->setFloat("light[0].anglecutoff", LightManager::Instance()->GetLightInfo().anglecutOff);
				shader->setFloat("light[0].inneranglecutoff", LightManager::Instance()->GetLightInfo().inneranglecutOff);
			}
		}
	}
	
}