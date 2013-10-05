#include "ActorManager.h"

#include "Exception.h"

SINGLETON_DEF(ActorManager);

ActorManager::ActorManager() :
	Singleton(this)
{
}

ActorPtr ActorManager::CreateActor()
{
	ActorPtr actor;
	// first try to obtain actor from pool
	actor = mPool.GetObject();
	// if not possible, allocate new one
	if (!actor)
	{
		mLastId += 1;
		actor.reset(new Actor(mLastId));
	}

	// add to map
	mActors[actor->GetId()] = actor;
	return actor;
}

void ActorManager::DestroyActor(Actor::Id id)
{
	if (mActors.count(id))
	{
		ActorPtr actor = mActors[id];
		actor->ClearComponents();
		// move to pool
		mActors.erase(id);
		mPool.AddObject(actor);
	}
	else
		THROW_ERROR("Unknown actor id " + id);
}

ActorPtr ActorManager::GetActor(Actor::Id id) const
{
	if (mActors.count(id))
		return mActors.at(id);
	else
		THROW_ERROR("Unknown actor id " + id);
}