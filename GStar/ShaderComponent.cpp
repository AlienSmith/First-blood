#include "ShaderComponent.h"
#include "ShaderManger.h"
#include "ConsolePrint.h"
#include "Shader.h"
#include "Scene.h"
#include "UpdateObject.h"
bool GStar::ShaderComponent::Initialize(const ShaderParameters & parameters)
{
	my_shader = ShaderManager::Instance()->GetShader(parameters);
	if (my_shader) {
		return true;
	}
	DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Shader Component failed to initialize");
	return false;
}

bool GStar::ShaderComponent::Update() const
{
	my_shader->use();
	my_shader->setFloat("offset", 0.1);
	my_shader->setInt("texture1", 0);
	my_shader->setInt("texture2", 1);
	my_shader->setMat4("view", Scene::Create()->getview(), GL_FALSE);
	my_shader->setMat4("projection", Scene::Create()->getProjection(), GL_FALSE);	
	my_shader->setMat4("model", UpdateObject::OUT_Instance->GetTransformComponent()->getModel(), GL_FALSE);
	glDrawArrays(GL_TRIANGLES, 0, UpdateObject::OUT_Instance->GetMeshComponent()->GetMeshInfo().TriangleIndex());
	
	return true;
}
