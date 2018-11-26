#include "ShaderComponent.h"
#include "ShaderManger.h"
#include "ConsolePrint.h"
bool GStar::ShaderComponent::Initialize(const ShaderParameters & parameters)
{
	my_shader = ShaderManager::Instance()->GetShader(parameters);
	if (my_shader) {
		return true;
	}
	DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Shader Component failed to initialize");
	return false;
}
