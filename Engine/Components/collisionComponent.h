#pragma once
#include "Framework/component.h"
#include "Physics/collision.h"
#include "Physics/physicsSystem.h"
#include <functional>

namespace tech
{
	class CollisionComponent : public Component, public ICollidable
	{
	public:
		using funcPtr = std::function<void(Actor*)>;
		CLASS_CLONE(CollisionComponent);

	public:
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		void SetCollisionEnter(funcPtr function) { m_enterFunction = function; }
		void SetCollisionExit(funcPtr function) { m_exitFunction = function; }

	private:
		PhysicsSystem::CollisionData data;
		funcPtr m_enterFunction;
		funcPtr m_exitFunction;
	};
}