#pragma once

#include <unordered_map>

#include "Actor.h"
#include "Pool.h"
#include "Singleton.h"

class ActorManager :
	public Singleton<ActorManager>
{

	typedef std::unordered_map<ActorId, ActorPtr> ActorMap;
	typedef Pool<Actor> ActorPool;

public:

	ActorManager();

	// create new actor or reuse old actor if possible
	ActorPtr CreateActor();
	// destroy actor or store it in pool if possible
	void DestroyActor(ActorId id);

	ActorPtr GetActor(ActorId id) const;

private:

	ActorId mLastId;
	ActorMap mActors;
	ActorPool mPool;

};