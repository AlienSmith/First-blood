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

	void LightManager::_writeToShader(const Shader * const shader, const GStar::LightInfo& info, int index) const
	{
		shader->setVec3("light[0].position", info.my_transform->GetTransform());
		shader->setVec3("light[0].ambient", info.ambient);
		shader->setVec3("light[0].diffuse", info.diffuse);
		shader->setVec3("light[0].specular", info.specular);
		shader->setInt("light[0].lighttype", info.my_type);
		//Point out to light
		if (info.my_type != Lighttype::POINT) {
			GStar::Vector3 temp = info.my_transform->GetForWardVector();
			temp.Normalize();
			temp *= -1.0f;
			shader->setVec3("light[0].lightDirection", temp);
		}
		if (info.my_type != Lighttype::DIRECTIONAL) {
			shader->setFloat("light[0].constant", info.constant);
			shader->setFloat("light[0].linear", info.linear);
			shader->setFloat("light[0].quadratic", info.quadratic);
			shader->setFloat("light[0].distancecutoff", info.distancecutoff);
			if (info.my_type == Lighttype::SPOT) {
				shader->setFloat("light[0].anglecutoff", info.anglecutOff);
				shader->setFloat("light[0].inneranglecutoff", info.inneranglecutOff);
			}
		}
	}
	
}