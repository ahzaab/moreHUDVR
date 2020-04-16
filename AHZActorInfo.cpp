#include "AHZActorInfo.h"


typedef  UInt32 (__fastcall *GET_ACTOR_IS_SENTIENT)(Actor *theActor);
RelocAddr<GET_ACTOR_IS_SENTIENT>pGetActorIsSentient(0x0060F1D0);

typedef  UInt32 (__fastcall *GET_ACTOR_SOUL_TYPE)(UInt32 level, UInt8 isSetient);
RelocAddr<GET_ACTOR_SOUL_TYPE>pGetActorSoulType(0x003D0FC0);


UInt32 CAHZActorInfo::IsSentient(Actor *actor)
{
	return pGetActorIsSentient(actor);
}

UInt32 CAHZActorInfo::GetSoulType(UInt16 actorLevel, UInt8 isActorSentient)
{
	UInt32 type = pGetActorSoulType(actorLevel, isActorSentient);
	return type;
}
