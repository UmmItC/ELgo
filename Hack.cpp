#include <iostream>
#include <Windows.h>
#include <cmath>
#include "MemMan.h"
#include "OffSets.hpp"
#include "Csgo OffSets.hpp"
#include "OT.hpp"

using namespace hazedumper;

#define KeyDOWN -32768
#define KeyUP 0

MemMan MM;

struct ft {
	bool canTBot = false, keyHeld = false;
	bool BunnHop;
	bool AnFlash;
	bool AnSmoke;
	bool GloHack;
	bool FoChange;
	bool NHand;
	bool RadarHak;
	bool ThridPersnMod;
}ftt;

int lines;

void CCursorGoto(short x, short y)
{
	COORD position = { x, y };
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout, position);
}

void CCursorGoto(POINT point)
{
	CCursorGoto(point.x, point.y);
}

void ClearPreviousLines(int lines)
{
	if (lines > 0)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO infoCon;
		GetConsoleScreenBufferInfo(handle, &infoCon);

		COORD position = infoCon.dwCursorPosition;
		position.X = 0;
		position.Y -= lines;

		SetConsoleCursorPosition(handle, position);
	}
}

void PrintStatus()
{
	ClearPreviousLines(lines);
	lines = 0;

	std::cout << ">> F1 ( TriggerBot Status : ) " << (ftt.canTBot ? "On " : "Off") <<"\tHold ALT to Trigger."<< "\n" << std::endl; lines += 2;;
	std::cout << ">> F2 ( BunnyHop Status : ) " << (ftt.BunnHop ? "On " : "Off") <<"\t\tHold Space Bar to BunnyHop."<< "\n" << std::endl; lines += 2;
	std::cout << ">> F3 ( No Flash Status : ) " << (ftt.AnFlash ? "On " : "Off") << "\n" << std::endl; lines += 2;
	std::cout << ">> F4 ( No Smoke Status : ) " << (ftt.AnSmoke ? "On " : "Off") << "\n" << std::endl; lines += 2;
	std::cout << ">> F6 ( GlowHack Status : ) " << (ftt.GloHack ? "On " : "Off") << "\n" << std::endl; lines += 2;
	std::cout << ">> NumPad0 ( No Hand Status : ) " << (ftt.NHand ? "On " : "Off") << "\n" << std::endl; lines += 2;
	std::cout << ">> NumPad1 ( Radar Hack Status : ) " << (ftt.RadarHak ? "On " : "Off") << "\n" << std::endl; lines += 2;
	std::cout << ">> NumPad2 ( Fov Changer Status : ) " << (ftt.FoChange ? "On " : "Off") << "\n" << std::endl; lines += 2;
	std::cout << ">> NumPad3 ( ThridPersonMode Status : ) " << (ftt.ThridPersnMod ? "On " : "Off") << "\n" << std::endl; lines += 2;

	/*
	CONSOLE_SCREEN_BUFFER_INFO infoCon;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &infoCon);
	CCursorGoto(0, infoCon.dwCursorPosition.Y - 2);

	static int a = 0;
	static int b = 0;

	a++;
	b--;
	*/
}

void Beginning()
{
	//result
	const int enquire = MessageBox(NULL, L"Change Setting\nYES = Recommend to open options\nNo = Constant", L"Setting", MB_YESNOCANCEL);

	switch (enquire)
	{
	case IDYES:
		ftt.canTBot = true;
		ftt.BunnHop = true;
		ftt.GloHack = true;
		ftt.RadarHak = true;
		break;
	case IDNO:
		MessageBox(NULL, L"No", L"No", MB_OK);
		break;
	case IDCANCEL:
			
		break;
	}
}

struct vector
{
	float x, y, z;
};

bool checkIfScoped()
{
	return MM.readMem<bool>(var.LocalPlayer + OS_Trigger.m_bIsScoped);
}

void setTBDelay(float distance)
{
	float delay;
	switch (var.myWeaponID)
	{
	case 262204: delay = 3; break;
	case 7: delay = 3.3; break;
	case 40: delay = 0.15; break;
	case 9: delay = 0.15; break;
	default: delay = 0;
	}
	var.tbDelay = delay * distance;
}

void getMyWeapon()
{
	int weapon = MM.readMem<int>(var.LocalPlayer + OS_Trigger.m_hActiveWeapon);
	int weaponEntity = MM.readMem<int>(var.GameModule + OS_Trigger.dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);
	if (weaponEntity != NULL)
		var.myWeaponID = MM.readMem<int>(weaponEntity + OS_Trigger.m_iItemDefinitionIndex);
}

float getDistance(uintptr_t entity)
{
	vector myLocation = MM.readMem<vector>(var.LocalPlayer + OS_Trigger.m_vecOrigin);
	vector enemyLocation = MM.readMem<vector>(entity + OS_Trigger.m_vecOrigin);

	float distance = sqrt(pow(myLocation.x - enemyLocation.x, 2) + pow(myLocation.y - enemyLocation.y, 2) + pow(myLocation.z - enemyLocation.z, 2)) * 0.0254;
	var.vDelay = distance * 4;
	std::cout << myLocation.x;
	std::cout << myLocation.y;
	std::cout << myLocation.z;

	return sqrt(pow(myLocation.x - enemyLocation.x, 2) + pow(myLocation.y - enemyLocation.y, 2) + pow(myLocation.z - enemyLocation.z, 2)) * 0.0254;
}

/*
void getDistance(DWORD entity)
{
	vector myLocation = MM.readMem<vector>(var.LocalPlayer + OS.m_vecOrigin);
	vector enemyLocation = MM.readMem<vector>(entity + OS.m_vecOrigin);

	float distance = sqrt(pow(myLocation.x - enemyLocation.x, 2) + pow(myLocation.y - enemyLocation.y, 2) + pow(myLocation.z - enemyLocation.z, 2)) * 0.0254;
	var.vDelay = distance * 3.3;
	std::cout << myLocation.x;
	std::cout << myLocation.y;
	std::cout << myLocation.z;
}
*/

void shoot()
{
	Sleep(var.vDelay);
	MM.writeMem<int>(var.GameModule + OS_Trigger.dwForceAttack, 5);
	Sleep(20);
	MM.writeMem<int>(var.GameModule + OS_Trigger.dwForceAttack, 4);

	int weapon = MM.readMem<int>(var.LocalPlayer + OS_Trigger.m_hActiveWeapon);
	int weaponEntity = MM.readMem<int>(var.GameModule + OS_Trigger.dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);
	if (weaponEntity != NULL)
		var.myWeaponID = MM.readMem<int>(weaponEntity + OS_Trigger.m_iItemDefinitionIndex);
}

bool checkTBot()
{
	int crosshair = MM.readMem<int>(var.LocalPlayer + OS_Trigger.m_iCrosshairId);
	if (crosshair != 0 && crosshair < 64 && GetAsyncKeyState(VK_MENU))
	{
		uintptr_t entity = MM.readMem<uintptr_t>(var.GameModule + OS_Trigger.dwEntityList + ((crosshair - 1) * 0x10));
		int eTeam = MM.readMem<int>(entity + OS_Trigger.m_iTeamNum);
		int eHealth = MM.readMem<int>(entity + OS_Trigger.m_iHealth);
		if (eTeam != var.Team && eHealth > 0)
		{
			float distance = getDistance(entity);
			getMyWeapon();
			setTBDelay(distance);
			if (var.myWeaponID == 40 || var.myWeaponID == 9)
				return checkIfScoped();
			else
				return true;
		}
		else
			return false;
	}
	else
		return false;
}

void handleTBot()
{
	if (checkTBot() && GetAsyncKeyState(VK_MENU))
		shoot();
}

bool BunnyHop()
{
	var.Flags = MM.readMem<BYTE>(var.LocalPlayer + OS_BunnyHop.m_fFlags);
	if (GetAsyncKeyState(VK_SPACE) && var.Flags & (1 << 0))
		MM.writeMem<uintptr_t>(var.GameModule + OS_BunnyHop.dwForceJump, 6);
	Sleep(1);
	return false;
}

bool No_Flash(float NFF)
{
	var.NF = MM.readMem<int>(var.LocalPlayer + OS_NoFlash.m_flFlashDuration);
	if (var.NF > 0)
	{
		MM.writeMem<int>(var.LocalPlayer + OS_NoFlash.m_flFlashDuration, 0);
	}

	Sleep(1);
	return false;
}

bool No_Smoke()
{


	return false;
}

bool FovChange()
{
	var.Fov = MM.readMem<int>(var.LocalPlayer + OS_Fov.m_iFOVStart);
	//var.Scope = MM.readMem<int>(var.LocalPlayer + OS_Fov.m_bIsScoped);
	MM.writeMem<int>(var.LocalPlayer + OS_Fov.m_iFOV, 115);

	return false;
}

struct ClrRender
{
	BYTE red, green, blue;
};

ClrRender clrEnemy;
ClrRender clrTeam;

void SetBrightness()
{
	float brightness = 5.0f;

	clrTeam.green = 0;
	clrTeam.blue = 150;
	clrTeam.red = 0;

	clrEnemy.red = 150;
	clrEnemy.green = 0;
	clrEnemy.blue = 0;

	int ptr = MM.readMem<int>(var.engineModule + OS_Brightness.model_ambient_min);
	int xorptr = *(int*)&brightness ^ ptr;
	MM.writeMem<int>(var.engineModule + OS_Brightness.model_ambient_min, xorptr);
}

bool GlowHack()
{
	CKing.GlowObject = MM.readMem<uintptr_t>(var.GameModule + hazedumper::signatures::dwGlowObjectManager);
	CKing.GlowCount = MM.readMem<int>(var.GameModule + hazedumper::signatures::dwGlowObjectManager + 0xC);

	CKing.myteam = MM.readMem<int>(var.LocalPlayer + hazedumper::netvars::m_iTeamNum);

	for (int i = 0; i < CKing.GlowCount; ++i)
	{
		CKing.entity = MM.readMem<int>(CKing.GlowObject + 0x38 * i);

		uintptr_t one = MM.readMem<uintptr_t>(CKing.entity + 0x8);
		uintptr_t two = MM.readMem<uintptr_t>(one + 0x8);
		uintptr_t three = MM.readMem<uintptr_t>(two + 0x1);

		int ClassID = MM.readMem<int>(three + 0x14);

		int entityHealth = MM.readMem<int>(CKing.entity + hazedumper::netvars::m_iHealth);
		int entityTeam = MM.readMem<int>(CKing.entity + hazedumper::netvars::m_iTeamNum);

		Glow = MM.readMem<CGlow>(CKing.GlowObject + (i * 0x38) + 0x4);

		Glow.a = 0.7f;
		Glow.m_bRenderWhenOccluded = true;
		Glow.m_bRenderWhenUnoccluded = false;

		switch (ClassID)
		{
		case 38: //Player
			if (CKing.myteam == entityTeam)
			{
				Glow.r = tg.r;
				Glow.g = tg.g;
				Glow.b = tg.b;
				Glow.a = tg.a;
			}

			else
			{
				//Glow.r = entityHealth / -var.maxHealth + 1;
				//Glow.g = entityHealth / var.maxHealth;
				Glow.r = 1.0f;
				Glow.g = 0.0f;
				Glow.b = 0.0f;
				Glow.a = 1.0f;
			}break;

			/* Not Shooting */
		case 105: // Knife
			Glow.r = 1.0f;
			Glow.g = 1.0f;
			Glow.b = 1.0f;
			Glow.a = 0.5f;
			break;
		case 32: // bomb (not planted)
			Glow.r = 1.0f;
			Glow.g = 0.0f;
			Glow.b = 0.0f;
			Glow.a = 1.0f;
			break;
		case 126: // bomb (planted)
			Glow.r = 1.0f;
			Glow.g = 0.0f;
			Glow.b = 0.0f;
			Glow.a = 1.0f;
			break;
		case 263: // Zeus (taser)
			Glow.r = 1.0f;
			Glow.g = 1.0f;
			Glow.b = 1.0f;
			Glow.a = 0.5f;
			break;
		case 51: // Defuse kit (defuser)
			Glow.r = 0.0f;
			Glow.g = 0.0f;
			Glow.b = 1.0f;
			Glow.a = 1.0f;
			break;
		case 102: // Healthshot
			Glow.r = 0.0f;
			Glow.g = 0.0f;
			Glow.b = 1.0f;
			Glow.a = 1.0f;
			break;
		case 110: // Molotov
			Glow.r = 1.0f;
			Glow.g = 0.5f;
			Glow.b = 0.0f;
			Glow.a = 0.5f;
			break;
		case 45: // Decoy
			Glow.r = 1.0f;
			Glow.g = 1.0f;
			Glow.b = 1.0f;
			Glow.a = 0.5f;
			break;
		case 75: // Flashbang
			Glow.r = 0.0f;
			Glow.g = 1.0f;
			Glow.b = 1.0f;
			Glow.a = 0.5f;
			break;
		case 94: // HEGrenade
			Glow.r = 1.0f;
			Glow.g = 0.0f;
			Glow.b = 0.0f;
			Glow.a = 0.5f;
			break;
		case 152: // Smoke
			Glow.r = 1.0f;
			Glow.g = 0.0f;
			Glow.b = 1.0f;
			Glow.a = 0.5f;
			break;
		case 97: // Incendiary
			Glow.r = 1.0f;
			Glow.g = 0.5f;
			Glow.b = 0.0f;
			Glow.a = 0.5f;
			break;
		case 148: // Tactical Awareness Grenade
			Glow.r = 0.0f;
			Glow.g = 1.0f;
			Glow.b = 1.0f;
			Glow.a = 0.5f;
			break;
		case 28: // Breachcharge
			Glow.r = 1.0f;
			Glow.g = 0.0f;
			Glow.b = 0.0f;
			Glow.a = 0.5f;
			break;
		case 109: // Axe; Hammer; Spanner (Wrench)
			Glow.r = OtherGlow.r;
			Glow.g = OtherGlow.g;
			Glow.b = OtherGlow.b;
			Glow.a = OtherGlow.a;
			break;
		case 168: // Tablet
			Glow.r = OtherGlow.r;
			Glow.g = OtherGlow.g;
			Glow.b = OtherGlow.b;
			Glow.a = OtherGlow.a;
			break;
		case 48: // Turret
			Glow.r = OtherGlow.r;
			Glow.g = OtherGlow.g;
			Glow.b = OtherGlow.b;
			Glow.a = OtherGlow.a;
			break;
		case 47: // Amazon Drone
			Glow.r = OtherGlow.r;
			Glow.g = OtherGlow.g;
			Glow.b = OtherGlow.b;
			Glow.a = OtherGlow.a;
			break;
		case 103: // Danger Zone Money
			Glow.r = OtherGlow.r;
			Glow.g = OtherGlow.g;
			Glow.b = OtherGlow.b;
			Glow.a = OtherGlow.a;
			break;
		case 123: // Loot Crate
			Glow.r = OtherGlow.r;
			Glow.g = OtherGlow.g;
			Glow.b = OtherGlow.b;
			Glow.a = OtherGlow.a;
			break;
		case 34: // Chicken
			Glow.r = OtherGlow.r;
			Glow.g = OtherGlow.g;
			Glow.b = OtherGlow.b;
			Glow.a = OtherGlow.a;
			break;
				// PISTOLS // 
		case 241: // Glock
			Glow.r = pistolGlow.r;
			Glow.g = pistolGlow.g;
			Glow.b = pistolGlow.b;
			Glow.a = pistolGlow.a;
			break;
		case 242: // USP-S; P2000
			Glow.r = pistolGlow.r;
			Glow.g = pistolGlow.g;
			Glow.b = pistolGlow.b;
			Glow.a = pistolGlow.a;
			break;
		case 254: // P250; CZ75
			Glow.r = pistolGlow.r;
			Glow.g = pistolGlow.g;
			Glow.b = pistolGlow.b;
			Glow.a = pistolGlow.a;
			break;
		case 235: // Duals
			Glow.r = pistolGlow.r;
			Glow.g = pistolGlow.g;
			Glow.b = pistolGlow.b;
			Glow.a = pistolGlow.a;
			break;
		case 264: // TEC-9
			Glow.r = pistolGlow.r;
			Glow.g = pistolGlow.g;
			Glow.b = pistolGlow.b;
			Glow.a = pistolGlow.a;
			break;
		case 237: // Fiveseven
			Glow.r = pistolGlow.r;
			Glow.g = pistolGlow.g;
			Glow.b = pistolGlow.b;
			Glow.a = pistolGlow.a;
			break;
		case 44: // Deagle; revolver
			Glow.r = pistolGlow.r;
			Glow.g = pistolGlow.g;
			Glow.b = pistolGlow.b;
			Glow.a = pistolGlow.a;
			break;

			// HEAVY //
		case 247: // MAG-7
			Glow.r = heavyGlow.r;
			Glow.g = heavyGlow.g;
			Glow.b = heavyGlow.b;
			Glow.a = heavyGlow.a;
			break;
		case 252: // Nova
			Glow.r = heavyGlow.r;
			Glow.g = heavyGlow.g;
			Glow.b = heavyGlow.b;
			Glow.a = heavyGlow.a;
			break;
		case 256: // Sawed-Off
			Glow.r = heavyGlow.r;
			Glow.g = heavyGlow.g;
			Glow.b = heavyGlow.b;
			Glow.a = heavyGlow.a;
			break;
		case 268: // XM1014
			Glow.r = heavyGlow.r;
			Glow.g = heavyGlow.g;
			Glow.b = heavyGlow.b;
			Glow.a = heavyGlow.a;
			break;
		case 243: // M249
			Glow.r = heavyGlow.r;
			Glow.g = heavyGlow.g;
			Glow.b = heavyGlow.b;
			Glow.a = heavyGlow.a;
			break;
		case 251: // Negev
			Glow.r = heavyGlow.r;
			Glow.g = heavyGlow.g;
			Glow.b = heavyGlow.b;
			Glow.a = heavyGlow.a;
			break;

			// SMGs //
		case 246: // MAC-10
			Glow.r = Submachinegun.r;
			Glow.g = Submachinegun.g;
			Glow.b = Submachinegun.b;
			Glow.a = Submachinegun.a;
			break;
		case 250: // MP9
			Glow.r = Submachinegun.r;
			Glow.g = Submachinegun.g;
			Glow.b = Submachinegun.b;
			Glow.a = Submachinegun.a;
			break;
		case 249: // MP7
			Glow.r = Submachinegun.r;
			Glow.g = Submachinegun.g;
			Glow.b = Submachinegun.b;
			Glow.a = Submachinegun.a;
			break;
		case 266: // UMP
			Glow.r = Submachinegun.r;
			Glow.g = Submachinegun.g;
			Glow.b = Submachinegun.b;
			Glow.a = Submachinegun.a;
			break;
		case 255: // P90
			Glow.r = Submachinegun.r;
			Glow.g = Submachinegun.g;
			Glow.b = Submachinegun.b;
			Glow.a = Submachinegun.a;
			break;
		case 231: // Bizon
			Glow.r = Submachinegun.r;
			Glow.g = Submachinegun.g;
			Glow.b = Submachinegun.b;
			Glow.a = Submachinegun.a;
			break;

			// Rifles //
		case 240: // Galil
			Glow.r = rifleGlow.r;
			Glow.g = rifleGlow.g;
			Glow.b = rifleGlow.b;
			Glow.a = rifleGlow.a;
			break;
		case 236: // Famas
			Glow.r = rifleGlow.r;
			Glow.g = rifleGlow.g;
			Glow.b = rifleGlow.b;
			Glow.a = rifleGlow.a;
			break;
		case 1: // AK-47
			Glow.r = rifleGlow.r;
			Glow.g = rifleGlow.g;
			Glow.b = rifleGlow.b;
			Glow.a = rifleGlow.a;
			break;
		case 245: // M4A4; M421-S
			Glow.r = rifleGlow.r;
			Glow.g = rifleGlow.g;
			Glow.b = rifleGlow.b;
			Glow.a = rifleGlow.a;
			break;
		case 261: // SG553
			Glow.r = rifleGlow.r;
			Glow.g = rifleGlow.g;
			Glow.b = rifleGlow.b;
			Glow.a = rifleGlow.a;
			break;
		case 228: // AUG
			Glow.r = rifleGlow.r;
			Glow.g = rifleGlow.g;
			Glow.b = rifleGlow.b;
			Glow.a = rifleGlow.a;
			break;

			// SNIPERS //
		case 262: // SSG 08 (Scout)
			Glow.r = sniperGlow.r;
			Glow.g = sniperGlow.g;
			Glow.b = sniperGlow.b;
			Glow.a = sniperGlow.a;
			break;
		case 229: // AWP
			Glow.r = sniperGlow.r;
			Glow.g = sniperGlow.g;
			Glow.b = sniperGlow.b;
			Glow.a = sniperGlow.a;
			break;
		case 257: // SCAR-20
			Glow.r = sniperGlow.r;
			Glow.g = sniperGlow.g;
			Glow.b = sniperGlow.b;
			Glow.a = sniperGlow.a;
			break;
		case 238: // G3SG1
			Glow.r = sniperGlow.r;
			Glow.g = sniperGlow.g;
			Glow.b = sniperGlow.b;
			Glow.a = sniperGlow.a;
			break;
		default:
			Glow.m_bRenderWhenOccluded = false;
			break;
		}
		MM.writeMem<CGlow>(CKing.GlowObject + (i * 0x38) + 0x4, Glow);
	}

	return false;
}

bool NoHand()
{
	MM.readMem<int>(var.LocalPlayer + OS_NoHand.n_hand);
	MM.writeMem<int>(var.LocalPlayer + OS_NoHand.n_hand, 0);

	return false;
}

bool RadarHack()
{
	for (short int i = 0; i < 64; i++)
	{
		uintptr_t entity = MM.readMem<uintptr_t>(var.GameModule + OS_RadarHack.dwEntityList + i * 0x10);
		if (entity != NULL)
			MM.writeMem<bool>(entity + OS_RadarHack.m_bSpotted, true);
	}
	Sleep(1);

	return false;
}

bool ThridPersonMode()
{
	MM.writeMem<int>(var.LocalPlayer + OS_ThridPerson.PersonMode, 1);
	//MM.writeMem<int>(var.LocalPlayer + OS_ThridPerson.Prso, 2);
	return false;
}

void CheckGame()
{
	HWND hwnd = FindWindowA(0, ("Counter-Strike: Global Offensive - Direct3D 9"));
	system("color e");
	while (hwnd == NULL)
	{
		Sleep(1);
		hwnd = FindWindowA(0, ("Counter-Strike: Global Offensive - Direct3D 9"));
		ClearPreviousLines(lines);
		lines = 0;
		std::cout << "Waiting you open csgo..." << std::endl; lines += 1;
		if (hwnd != NULL)
			break;
	}
	MessageBoxA(0, "Csgo Found !", "Found", MB_OK);
	system("cls");
	std::cout << "Loading ." << std::endl;
	system("color c");
	Sleep(1000);
	system("cls");
	std::cout << "Loading .." << std::endl;
	Sleep(2000);
	system("cls");
	std::cout << "Loading ..." << std::endl;
	Sleep(2410);
	system("cls");
	system("color b");
}

void Control()
{
	if (GetAsyncKeyState(VK_F1) & 1) //TriggerBot
	{
		var.Team = MM.readMem<int>(var.LocalPlayer + OS_Trigger.m_iTeamNum);
		ftt.canTBot = !ftt.canTBot;
	}

	if (GetAsyncKeyState(VK_XBUTTON1) == KeyDOWN && !ftt.keyHeld)
	{
		ftt.keyHeld = true;
		ftt.canTBot = true;
	}
	if (GetAsyncKeyState(VK_XBUTTON1) == KeyUP && ftt.keyHeld)
	{
		ftt.keyHeld = false;
		ftt.canTBot = false;
	}

	if (ftt.canTBot)
		handleTBot();

	if (GetAsyncKeyState(VK_F2) & 1) //BunnyHop
	{
		ftt.BunnHop = !ftt.BunnHop;
	}

	if (ftt.BunnHop)
		BunnyHop();

	if (GetAsyncKeyState(VK_F3) & 1) //No Flash
	{
		ftt.AnFlash = !ftt.AnFlash;
	}

	if (ftt.AnFlash)
		No_Flash(ftt.AnFlash);

	if (GetAsyncKeyState(VK_F4) & 1) //No Smoke
	{
		ftt.AnSmoke = !ftt.AnSmoke;
	}

	if (ftt.AnSmoke)
		No_Smoke();

	if (GetAsyncKeyState(VK_F6) & 1) //GlowHack
	{
		ftt.GloHack = !ftt.GloHack;
	}

	if (ftt.GloHack)
		GlowHack();

	if (GetAsyncKeyState(VK_NUMPAD0) & 1) //No Hand
	{
		ftt.NHand = !ftt.NHand;
	}

	if (ftt.NHand)
		NoHand();

	if (GetAsyncKeyState(VK_NUMPAD1) & 1) //RadarHack
	{
		ftt.RadarHak = !ftt.RadarHak;
	}

	if (ftt.RadarHak)
		RadarHack();

	if (GetAsyncKeyState(VK_NUMPAD2) & 1) //FovChange
	{
		ftt.FoChange = !ftt.FoChange;
	}

	if (ftt.FoChange)
		FovChange();

	if (GetAsyncKeyState(VK_NUMPAD3) & 1) //ThridPersonMode
	{
		ftt.ThridPersnMod = !ftt.ThridPersnMod;
	}

	if (ftt.ThridPersnMod)
		ThridPersonMode();
}

int main(void)
{
	//Process
	SetConsoleTitle(L"Csgo MHack v0.1");

	//int procID = MM.getProcess("csgo.exe");
	//var.GameModule = MM.getModule(procID, "client_panorama.dll");

	//var.LocalPlayer = MM.readMem<DWORD>(var.GameModule + OS.dwLocalPlayer);

	//LocalPlayer
	//if (var.LocalPlayer == NULL)
		//while (var.LocalPlayer == NULL)
			//var.LocalPlayer = MM.readMem<DWORD>(var.GameModule + OS.dwLocalPlayer);

	::wh();

	CheckGame();

	::Be();

	Beginning();

	var.Process = MM.getProcess(L"csgo.exe");
	var.GameModule = MM.getModule(var.Process, L"client_panorama.dll");
	var.engineModule = MM.getModule(var.Process, L"engine.dll");


	SetBrightness();

	system("color 07");
	std::cout <<"-------------------------------------------------------------------------------\n\n";
	std::cout << "------------------------------------------------------------------------------\n\n";
	std::cout << "------------------------------------------------------------------------------\n\n";
	std::cout << "---------------------------------[Csgo Cheat v2.0]----------------------------\n\n";
	std::cout << "------------------------------------------------------------------------------\n\n";
	std::cout << "------------------------------------------------------------------------------\n\n";
	std::cout << "------------------------------------------------------------------------------\n\n";


	SetConsoleTextAttribute(Font, FOREGROUND_RED | FOREGROUND_INTENSITY);
	while (true)
	{
		var.LocalPlayer = MM.readMem<uintptr_t>(var.GameModule + localplayer.dwLocalPlayer);
		int crosshair = MM.readMem<int>(var.LocalPlayer + OS_Trigger.m_iCrosshairId);

		Control();

		PrintStatus();

		Sleep(1);
	}
	return 0;
}