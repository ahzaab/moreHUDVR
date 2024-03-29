#pragma once
#include "skse64/PapyrusEvents.h"
#include "AHZActorInfo.h"

//void AHZInstallEnemyHealthUpdateHook();
//void AHZInstallWandLookupREFRByHandle();

void AHZScaleformHooks_Commit();

CAHZActorData GetCurrentEnemyData();
TESObjectREFR * GetCurrentWandReference();
extern TESObjectREFR *g_ahzTargetReference;
class AHZEventHandler : public BSTEventSink <MenuOpenCloseEvent> {
public:
	static bool ahzMenuLoaded;
   EventResult ReceiveEvent(MenuOpenCloseEvent * evn, EventDispatcher<MenuOpenCloseEvent> * dispatcher);
};

class AHZCrosshairRefEventHandler : public BSTEventSink <SKSECrosshairRefEvent>
{
   EventResult ReceiveEvent(SKSECrosshairRefEvent * evn, EventDispatcher<SKSECrosshairRefEvent> * dispatcher);
};


class SafeEnemyLevelDataHolder: public SafeDataHolder<CAHZActorData>
{
public:
   SafeEnemyLevelDataHolder() {};
   ~SafeEnemyLevelDataHolder() {};
};

class SafeWandReferenceDataHolder : public SafeDataHolder<TESObjectREFR *>
//class SafeWandReferenceDataHolder : public SafeDataHolder<NiPointer<TESObjectREFR>*>
{
public:
	SafeWandReferenceDataHolder() { m_data = nullptr; };
	~SafeWandReferenceDataHolder() {};
};