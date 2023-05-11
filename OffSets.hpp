#include <iostream>
#include <Windows.h>
#include <cmath>
#include "Csgo OffSets.hpp"


struct offsets_Trigger
{
	uintptr_t dwForceAttack = hazedumper::signatures::dwForceAttack;
	uintptr_t dwEntityList = hazedumper::signatures::dwEntityList;
	uintptr_t m_iCrosshairId = hazedumper::netvars::m_iCrosshairId;
	uintptr_t m_iTeamNum = hazedumper::netvars::m_iTeamNum;
	uintptr_t m_iHealth = hazedumper::netvars::m_iHealth;

	//recoil control
	uintptr_t m_vecOrigin = hazedumper::netvars::m_vecOrigin;

	//Weapon
	uintptr_t m_iItemDefinitionIndex = hazedumper::netvars::m_iItemDefinitionIndex;
	uintptr_t m_hActiveWeapon = hazedumper::netvars::m_hActiveWeapon;
	uintptr_t m_bIsScoped = hazedumper::netvars::m_bIsScoped;

	//knife
	uintptr_t dwForceAttack2 = hazedumper::signatures::dwForceAttack2;

} OS_Trigger;

struct offset_localplayer
{
	uintptr_t dwLocalPlayer = hazedumper::signatures::dwLocalPlayer;

}localplayer;

struct offset_BunnyHop
{
	//BunnyHop
	uintptr_t dwForceJump = hazedumper::signatures::dwForceJump;
	uintptr_t m_fFlags = hazedumper::netvars::m_fFlags;

}OS_BunnyHop;

struct offset_Fov
{
	//Fov
	uintptr_t m_iFOV = hazedumper::netvars::m_iFOV;
	uintptr_t m_iFOVStart = hazedumper::netvars::m_iFOVStart;

} OS_Fov;

struct offset_NoFlash
{
	//No Flash
	uintptr_t m_flFlashMaxAlpha = hazedumper::netvars::m_flFlashMaxAlpha;
	uintptr_t m_flFlashDuration = hazedumper::netvars::m_flFlashDuration;

} OS_NoFlash;

struct offset_RadarHack
{
	uintptr_t dwEntityList = hazedumper::signatures::dwEntityList;
	uintptr_t m_bSpotted = hazedumper::netvars::m_bSpotted;
}OS_RadarHack;

struct offset_GlowHack
{
	uintptr_t dwEntityList = hazedumper::signatures::dwEntityList;
	uintptr_t dwGlowObjectManager = hazedumper::signatures::dwGlowObjectManager;
	uintptr_t m_iGlowIndex = hazedumper::netvars::m_iGlowIndex;
	uintptr_t m_iTeamNum = hazedumper::netvars::m_iTeamNum;
	uintptr_t m_iHealth = hazedumper::netvars::m_iHealth;
	uintptr_t m_bIsDefusing = hazedumper::netvars::m_bIsDefusing;
	uintptr_t m_clrRender = hazedumper::netvars::m_clrRender;

}OS_GlowHack;

struct offset_No_Hand
{
	uintptr_t n_hand = 0x258;

}OS_NoHand;

struct offset_Brightness
{
	uintptr_t model_ambient_min = hazedumper::signatures::model_ambient_min;
}OS_Brightness;

struct offset_testWeapon
{
	uintptr_t dwEntityList = hazedumper::signatures::dwEntityList;
	uintptr_t dwGlowObjectManager = hazedumper::signatures::dwGlowObjectManager;
}OS_testWeapon;

struct offset_ThridPerson
{
	uintptr_t PersonMode = hazedumper::netvars::m_iObserverMode;
	uintptr_t Prso = hazedumper::netvars::m_thirdPersonViewAngles;
}OS_ThridPerson;

struct offset_Defusing
{
	uintptr_t Defusing = hazedumper::netvars::m_bIsDefusing;
	uintptr_t entity;
	int entitygg;
}OS_defusingg;

struct Glowing
{
	uintptr_t GlowObject;
	int GlowCount;
	int myteam;
	int entity;
} CKing;

struct CGlow
{
	float r;
	float g;
	float b;
	float a;
	uint8_t unk1[16];
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloom;
	uint8_t unk2[10];
}Glow;

struct TeamGlow
{
	float r = 0.0f;
	float g = 0.0f;
	float b = 1.0f;
	float a = 1.0f;
} tg;

struct PistolGlow
{
	float r = 0.0f;
	float g = 0.250f;
	float b = 0.719f;
	float a = 1.0f;
} pistolGlow;

struct SniperGlow
{
	float r = 0.398f;
	float g = 0.0f;
	float b = 0.797f;
	float a = 1.0f;
} sniperGlow;

struct SmgGlow
{
	float r = 1.0f;
	float g = 0.3f;
	float b = 0.0f;
	float a = 1.0f;
} Submachinegun;

struct RifleGlow
{
	float r = 0.600f;
	float g = 0.231f;
	float b = 0.1f;
	float a = 1.0f;
} rifleGlow;

struct HeavyGlow
{
	float r = 0.0f;
	float g = 0.797f;
	float b = 0.0f;
	float a = 1.0f;
} heavyGlow;

struct Other
{
	float r = 0.21f;
	float g = 0.50f;
	float b = 0.0f;
	float a = 1.0f;
}OtherGlow;

struct variables
{
	uintptr_t LocalPlayer;
	uintptr_t GameModule;
	uintptr_t engineModule;
	uintptr_t Process;
	uintptr_t glowObject;
	int Team;
	BYTE Flags;
	int vDelay;
	int NF;

	int Fov;
	int Scope;

	//CheckScoped
	int tbDelay;
	int myWeaponID;

	float maxHealth = 120.0f;
} var;