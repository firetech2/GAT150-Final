#include "modelComponent.h"
#include "Framework/actor.h"
#include "Renderer/model.h"

namespace tech
{
	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		std::string model_name;
		READ_DATA(value, model_name);

		m_model = g_resourceManager.Get<Model>(model_name);
		return true;
	}
	
	void tech::ModelComponent::Update()
	{
		//
	}

	void tech::ModelComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->GetTransform());
	}


}
