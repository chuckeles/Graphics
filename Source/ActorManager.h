#pragma once

#include <unordered_map>

#include "Actor.h"
#include "Pool.h"
#include "Singleton.h"

class ActorManager :
	public Singleton<ActorManager>
{

	typedef std::unordered_map<Actor::Id, ActorPtr> ActorMap;
	typedef Pool<Actor> ActorPool;

public:

	ActorManager();

	// create new actor or reuse old actor if possible
	ActorPtr CreateActor();
	// destroy actor or store it in pool if possible
	void DestroyActor(Actor::Id id);

	ActorPtr GetActor(Actor::Id id) const;

private:

	Actor::Id mLastId = 0;
	ActorMap mActors;
	ActorPool mPool;

};