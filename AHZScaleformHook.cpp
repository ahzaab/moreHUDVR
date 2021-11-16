#include "skse64/GameTypes.h"
#include "skse64/GameMenus.h"
#include "skse64/ScaleFormTypes.h"
#include "skse64/ScaleFormCallbacks.h"
#include "skse64/GameRTTI.h"
#include "skse64/ScaleFormMovie.h"
#include "skse64_common/SafeWrite.h"
#include "AHZScaleformHook.h"
#include "skse64/GameMenus.h"
#include "skse64/PapyrusEvents.h"
#include <string>
#include "xbyak/xbyak.h"
#include "skse64_common/BranchTrampoline.h"

using namespace std;
bool AHZEventHandler::ahzMenuLoaded = false;
static SafeEnemyLevelDataHolder ahzTargetHandle;
static SafeWandReferenceDataHolder s_ahzWandReference;
TESObjectREFR *g_ahzTargetReference;

EventResult AHZEventHandler::ReceiveEvent(MenuOpenCloseEvent * evn, EventDispatcher<MenuOpenCloseEvent> * dispatcher)
{
   string menuName(evn->menuName.data);
   _VMESSAGE("Menu: %s", menuName.c_str());
   if ((ahzMenuLoaded == false) && (menuName == "WSEnemyMeters") && (evn->opening))
   {
      GFxMovieView *view = MenuManager::GetSingleton()->GetMovieView(&evn->menuName);
      if (view)
      {
         GFxValue hudComponent;
         GFxValue result;
         GFxValue args[2]; 

         if (!view)
         {
            _ERROR("The IMenu returned NULL. The moreHUD widgets will not be loaded.");
         }


		 GFxValue fxValue;
		 fxValue.SetBool(true);


		 view->SetVariable("_lockroot", &fxValue, 1);



         args[0].SetString("AHZEnemyLevelInstance");
         view->Invoke("getNextHighestDepth", &args[1], NULL, 0);
         view->Invoke("createEmptyMovieClip", &hudComponent, args, 2);

         if (!hudComponent.objectInterface)
         {
            _ERROR("moreHUD could not create an empty movie clip for the WSEnemyMeters. The moreHUD enemy data will not be loaded.");
            return EventResult::kEvent_Abort;
         }

         args[0].SetString("AHZEnemyLevel.swf");
         hudComponent.Invoke("loadMovie", &result, &args[0], 1);
         ahzMenuLoaded = true;
         return EventResult::kEvent_Abort;
      }
   }

   return EventResult::kEvent_Continue;
}

EventResult AHZCrosshairRefEventHandler::ReceiveEvent(SKSECrosshairRefEvent * evn, EventDispatcher<SKSECrosshairRefEvent> * dispatcher)
{
   g_ahzTargetReference = evn->crosshairRef;
   return EventResult::kEvent_Continue;
}

uintptr_t Enemy_Update_Hook_Base = 0x008AFE70;
RelocAddr<uintptr_t> Enemy_Update_Hook_Target(Enemy_Update_Hook_Base + 0x44);
bool __cdecl EnemyHealth_Update_Hook(UInt32 & refHandle, NiPointer<TESObjectREFR> &refrOut)
{
   bool result = LookupREFRByHandle(refHandle, refrOut);
   TESObjectREFR * reference = refrOut;
   if (!reference)
   {
      return result;
   }
   UInt16 npcLevel = 0;
   UInt32 isSentient = 0;
   if (reference)
   {
	   if (reference->baseForm->formType == kFormType_NPC ||
		   reference->baseForm->formType == kFormType_Character)
	   {
		   Actor * pNPC = DYNAMIC_CAST(reference, TESObjectREFR, Actor);
		   if (pNPC)
		   {
			   npcLevel = CALL_MEMBER_FN(pNPC, GetLevel)();
			   isSentient = CAHZActorInfo::IsSentient(pNPC);
		   }
	   }
   }

   ahzTargetHandle.Lock();
   ahzTargetHandle.m_data.Level = npcLevel;
   ahzTargetHandle.m_data.IsSentient = isSentient;
   ahzTargetHandle.Release();
   return result;
}
//RelocPtr<SimpleLock>		globalMenuStackLock(0x1EE4A60);
CAHZActorData GetCurrentEnemyData()
{
   CAHZActorData refr;
   ahzTargetHandle.Lock();
   refr = ahzTargetHandle.m_data;
   ahzTargetHandle.Release();
   return refr;
}

void AHZInstallEnemyHealthUpdateHook()
{
   //struct EnemyHealth_Code : Xbyak::CodeGenerator {
   //    EnemyHealth_Code(void * buf, UInt64 funcAddr) : Xbyak::CodeGenerator(4096, buf)
   //   {
   //      Xbyak::Label retnLabel;
   //      Xbyak::Label funcLabel;
   //      Xbyak::Label LookupREFRByHandleLbl;

   //      // Call original code and use the same signature as LookupREFRByHandle to pass the object ref to the hooked
   //      // function
   //      //call(LookupREFRByHandle);
   //      call(ptr[rip + LookupREFRByHandleLbl]);

   //      // Call our function (Same signature as LookupREFRByHandle)
   //      call(ptr[rip + funcLabel]);

   //      // Jump back from the Trampoline
   //      jmp(ptr[rip + retnLabel]);

   //      L(funcLabel);
   //      dq(funcAddr);

   //      L(LookupREFRByHandleLbl);
   //      dq(LookupREFRByHandle.GetUIntPtr());

   //      L(retnLabel);
   //      dq(Enemy_Update_Hook_Target.GetUIntPtr() + 5);
   //   }
   //};

   //void * codeBuf = g_localTrampoline.StartAlloc();
   //EnemyHealth_Code code(codeBuf, (uintptr_t)EnemyHealth_Update_Hook);
   //g_localTrampoline.EndAlloc(code.getCurr());

   //_VMESSAGE("g_localTrampoline, EnemyHealth_Update_Hook Size: %d", code.getSize());

   //g_branchTrampoline.Write5Branch(Enemy_Update_Hook_Target.GetUIntPtr(), uintptr_t(code.getCode()));

    g_branchTrampoline.Write5Call(Enemy_Update_Hook_Target.GetUIntPtr(), uintptr_t(EnemyHealth_Update_Hook));

   _VMESSAGE("g_branchTrampoline, Enemy_Update_Hook_Target Size: %d", 14); 
}


RelocAddr<uintptr_t> kHook_Wand_LookupREFRByHandle_Enter(0x0053EC60 + 0x7F);
//void Hook_Wand_LookupREFRByHandle(UInt32 & refHandle, NiPointer<TESObjectREFR> &refrOut)
//{
////bool result = LookupREFRByHandle(refHandle, refrOut);
//
//	//;TESObjectREFR * reference = refrOut->m_pObject;
//
//    //_VMESSAGE("reference", 14);
//
//	s_ahzWandReference.Lock();
//	s_ahzWandReference.m_data = refrOut;
//    //s_ahzWandReference.m_data = reference;
//	s_ahzWandReference.Release();
//}
bool __cdecl  Hook_Wand_LookupREFRByHandle(UInt32& refHandle, NiPointer<TESObjectREFR>& refrOut)
{
    bool result = LookupREFRByHandle(refHandle, refrOut);

        //;TESObjectREFR * reference = refrOut->m_pObject;

        //_VMESSAGE("reference", 14);

    s_ahzWandReference.Lock();
    s_ahzWandReference.m_data = refrOut;
    //s_ahzWandReference.m_data = reference;
    s_ahzWandReference.Release();

    return result;
}

//RelocPtr<SimpleLock>		globalMenuStackLock(0x1EE4A60);
TESObjectREFR * GetCurrentWandReference()
{
	TESObjectREFR* refr;
	s_ahzWandReference.Lock();
	refr = s_ahzWandReference.m_data;
    //if (s_ahzWandReference.m_data == nullptr) {
    //    refr = nullptr;
    //}
    //else {
    //    refr = s_ahzWandReference.m_data->get();
    //}
	s_ahzWandReference.Release();
	return refr;
}

void AHZInstallWandLookupREFRByHandle()
{
	//struct WandUpdate_Code : Xbyak::CodeGenerator {
 //       WandUpdate_Code(void * buf, UInt64 funcAddr) : Xbyak::CodeGenerator(4096, buf)
	//	{
	//		Xbyak::Label retnLabel;
	//		Xbyak::Label funcLabel;
 //           Xbyak::Label LookupREFRByHandleLbl;

	//		// Call original code and use the same signature as LookupREFRByHandle to pass the object ref to the hooked
	//		// function
	//		//call(LookupREFRByHandle);
 //           call(ptr[rip + LookupREFRByHandleLbl]);

	//		// Call our function (Same signature as LookupREFRByHandle)
	//		call(ptr[rip + funcLabel]);

	//		// Jump back from the Trampoline
	//		jmp(ptr[rip + retnLabel]);

	//		L(funcLabel);
	//		dq(funcAddr);

 //           L(LookupREFRByHandleLbl);
 //           dq(LookupREFRByHandle.GetUIntPtr());

	//		L(retnLabel);
	//		dq(kHook_Wand_LookupREFRByHandle_Enter.GetUIntPtr() + 5);
	//	}
	//};

	//void * codeBuf = g_localTrampoline.StartAlloc();
 //   WandUpdate_Code code(codeBuf, (uintptr_t)Hook_Wand_LookupREFRByHandle);
	//g_localTrampoline.EndAlloc(code.getCurr());
 //   
 //   _VMESSAGE("g_localTrampoline, Hook_Wand_LookupREFRByHandle Size: %d", code.getSize());

	//g_branchTrampoline.Write5Branch(kHook_Wand_LookupREFRByHandle_Enter.GetUIntPtr(), uintptr_t(code.getCode()));

    g_branchTrampoline.Write5Call(kHook_Wand_LookupREFRByHandle_Enter.GetUIntPtr(), uintptr_t(Hook_Wand_LookupREFRByHandle));

    _VMESSAGE("g_branchTrampoline, Hook_Wand_LookupREFRByHandle Size: %d", 14);
}

void SetupFixedString(const char* constString, char * buffer, UInt32 bufferSize)
{
	memset(buffer, 0, bufferSize);
	UInt32 len = strlen(constString);
	memcpy_s(buffer, bufferSize, constString, len);
}

void AHZScaleformHooks_Commit()
{
    AHZInstallEnemyHealthUpdateHook();
    AHZInstallWandLookupREFRByHandle();
}
