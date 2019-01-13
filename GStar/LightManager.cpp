//include Shader.h after light manager would lead to error.
#include "Shader.h"
#include "LightManager.h"
#include <string>
#include "GLError.h"
namespace GStar {
	LightManager* LightManager::instance = nullptr;
	MyString LightManager::prePhix;
	MyString LightManager::afterPhix[12];
	void LightManager::WriteToShader(const Shader * const shader)
	{	
		int count = 0;
		this->Lights.Resetcurrent();
		while (Lights.HasNext()) {
			_writeToShader(shader, Lights.GetNext()->Getlightinfo(), count);
			check_gl_error();
			count++;
			Lights.Move();
		}
		float a = 0;
		shader->setInt("numlights", count);
	}

	void LightManager::Initialize()
	{
		check_gl_error();
		LightManager::prePhix = MyString("light[");
		LightManager::afterPhix[0] = MyString("].position");
		LightManager::afterPhix[1] = MyString("].ambient");
		LightManager::afterPhix[2] = MyString("].diffuse");
		LightManager::afterPhix[3] = MyString("].specular");
		LightManager::afterPhix[4] = MyString("].lighttype");

		LightManager::afterPhix[5] = MyString("].lightDirection");

		LightManager::afterPhix[6] = MyString("].constant");
		LightManager::afterPhix[7] = MyString("].linear");
		LightManager::afterPhix[8] = MyString("].quadratic");
		LightManager::afterPhix[9] = MyString("].distancecutoff");

		LightManager::afterPhix[10] = MyString("].anglecutoff");
		LightManager::afterPhix[11] = MyString("].inneranglecutoff");
		
	}

	void LightManager::_writeToShader(const Shader * const shader, const GStar::LightInfo& info, int index)
	{
		MyString sindex = MyString::inttostring(index);
		shader->setVec3(prePhix+ sindex +afterPhix[0], info.my_transform->GetTransform());
		shader->setVec3(prePhix + sindex + afterPhix[1], info.ambient);
		shader->setVec3(prePhix + sindex + afterPhix[2], info.diffuse);
		shader->setVec3(prePhix + sindex + afterPhix[3], info.specular);
		shader->setInt(prePhix + sindex + afterPhix[4], info.my_type);
		//Point out to light
		if (info.my_type != Lighttype::POINT) {
			GStar::Vector3 temp = info.my_transform->GetForWardVector();
			temp.Normalize();
			temp *= -1.0f;
			shader->setVec3(prePhix + sindex + afterPhix[5], temp);
		}
		if (info.my_type != Lighttype::DIRECTIONAL) {
			shader->setFloat(prePhix + sindex + afterPhix[6], info.constant);
			shader->setFloat(prePhix + sindex + afterPhix[7], info.linear);
			shader->setFloat(prePhix + sindex + afterPhix[8], info.quadratic);
			shader->setFloat(prePhix + sindex + afterPhix[9], info.distancecutoff);
			if (info.my_type == Lighttype::SPOT) {
				shader->setFloat(prePhix + sindex + afterPhix[10], info.anglecutOff);
				shader->setFloat(prePhix + sindex + afterPhix[11], info.inneranglecutOff);
			}
		}
	}
	
}