#include "playerComponent.h"
#include "audioComponent.h"
#include "physicsComponent.h"
#include "collisionComponent.h"
#include "Math/mathUtils.h"
#include "Framework/actor.h"

namespace tech
{
	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}

	void PlayerComponent::Initialize()
	{
		auto component = m_owner->GetComponent<CollisionComponent>();

		if (component)
		{
			component->SetCollisionEnter(std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1));
			component->SetCollisionExit(std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1));
		}
	}

	void PlayerComponent::Update()
	{
		// movement
		Vector2 direction = Vector2::ZERO;
		if (tech::g_inputSystem.GetKeyDown(tech::key_left))
		{
			direction = Vector2::LEFT;
		}

		if (tech::g_inputSystem.GetKeyDown(tech::key_right))
		{
			direction = Vector2::RIGHT;
		}

		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(direction * speed);
		}

		// jump
		if (tech::g_inputSystem.GetKeyState(tech::key_space) == InputSystem::State::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::UP * 300);
			}
		}

		if (tech::g_inputSystem.GetKeyDown(tech::key_up))
		{
			// currently null
		}
	}

	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		std::cout << "player has entered the building\n";
	}

	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		std::cout << "player has left the building\n";
	}
}


