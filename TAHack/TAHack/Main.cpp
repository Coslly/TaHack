#include "Head.h"
const float ReleaseVersion = 256;
const string ReleaseDate = "[2024-03-01 12:00]";
EasyGUI::EasyGUI GUI_BL_;
EasyGUI::EasyGUI_IO GUI_IO_;
BOOL MenuShowState;
//--------------------------------------------------------------------
namespace TAHack_Config_Var
{
	const string Default_Config = "0\n1000\n0\n1000\n0\n0\n1\n1.5\n1\n1\n1\n1\n1\n116\n1\n1\n25\n1\n11\n0\n45\n255\n230\n255\n250\n9\n1\n5\n1\n66\n0\n1\n1\n1\n25\n1\n5\n1\n1\n0\n1\n116\n1\n0\n1\n";
	BOOL UI_Menu_Health = Variable::string_int_(System::Get_File("TAHack.cfg", 1));
	int UI_Menu_Health_Value = Variable::string_int_(System::Get_File("TAHack.cfg", 2));
	BOOL UI_Menu_Armor = Variable::string_int_(System::Get_File("TAHack.cfg", 3));
	int UI_Menu_Armor_Value = Variable::string_int_(System::Get_File("TAHack.cfg", 4));
	BOOL UI_Menu_WantedLevel = Variable::string_int_(System::Get_File("TAHack.cfg", 5));
	int UI_Menu_WantedLevel_Value = Variable::string_int_(System::Get_File("TAHack.cfg", 6));
	BOOL UI_Menu_SpeedChanger = Variable::string_int_(System::Get_File("TAHack.cfg", 7));
	float UI_Menu_SpeedChanger_Value = Variable::string_float_(System::Get_File("TAHack.cfg", 8));
	BOOL UI_Menu_God = Variable::string_int_(System::Get_File("TAHack.cfg", 9));
	BOOL UI_Menu_NoRagdoll = Variable::string_int_(System::Get_File("TAHack.cfg", 10));
	BOOL UI_Menu_DisableCollision = Variable::string_int_(System::Get_File("TAHack.cfg", 11));
	BOOL UI_Menu_OneHitKill = Variable::string_int_(System::Get_File("TAHack.cfg", 12));
	BOOL UI_Menu_Suicide = false;
	BOOL UI_Menu_TeleportWaypoint = Variable::string_int_(System::Get_File("TAHack.cfg", 13));
	int UI_Menu_TeleportWaypoint_Key = Variable::string_int_(System::Get_File("TAHack.cfg", 14));
	BOOL UI_Menu_Vehicle_God = Variable::string_int_(System::Get_File("TAHack.cfg", 15));
	BOOL UI_Menu_Vehicle_Gravity = Variable::string_int_(System::Get_File("TAHack.cfg", 16));
	float UI_Menu_Vehicle_Gravity_Value = Variable::string_float_(System::Get_File("TAHack.cfg", 17));
	BOOL UI_Menu_Time = Variable::string_int_(System::Get_File("TAHack.cfg", 18));
	int UI_Menu_Time_Hour = Variable::string_int_(System::Get_File("TAHack.cfg", 19));
	int UI_Menu_Time_Minute = Variable::string_int_(System::Get_File("TAHack.cfg", 20));
	int UI_Settings_MenuKey = Variable::string_int_(System::Get_File("TAHack.cfg", 21));
	Variable::Vector4 UI_Settings_MenuColor = { Variable::string_int_(System::Get_File("TAHack.cfg", 22)),Variable::string_int_(System::Get_File("TAHack.cfg", 23)),Variable::string_int_(System::Get_File("TAHack.cfg", 24)),Variable::string_int_(System::Get_File("TAHack.cfg", 25)) };
	int UI_Settings_MenuColor_A = Variable::string_int_(System::Get_File("TAHack.cfg", 25));
	int UI_Menu_DisableCollision_Key = Variable::string_int_(System::Get_File("TAHack.cfg", 26));
	BOOL UI_Menu_AntiGravity = Variable::string_int_(System::Get_File("TAHack.cfg", 27));
	int UI_Menu_AntiGravity_Key = Variable::string_int_(System::Get_File("TAHack.cfg", 28));
	BOOL UI_Menu_BulletType = Variable::string_int_(System::Get_File("TAHack.cfg", 29));
	int UI_Menu_BulletType_Value = Variable::string_int_(System::Get_File("TAHack.cfg", 30));
	BOOL UI_Settings_LockGameWindow = Variable::string_int_(System::Get_File("TAHack.cfg", 31));
	BOOL UI_Settings_SaveConfig = false;
	BOOL UI_Settings_StartGTA = false;
	BOOL UI_Settings_GitHubRepositories = false;
	BOOL UI_Settings_Restart = false;
	BOOL UI_Settings_CloseMenu = false;
	BOOL UI_Legit_Enabled = Variable::string_int_(System::Get_File("TAHack.cfg", 32));
	BOOL UI_Legit_HealthLock = Variable::string_int_(System::Get_File("TAHack.cfg", 33));
	BOOL UI_Legit_VehicleGravity = Variable::string_int_(System::Get_File("TAHack.cfg", 34));
	int UI_Legit_VehicleGravity_Value = Variable::string_int_(System::Get_File("TAHack.cfg", 35));
	BOOL UI_Legit_VehicleAntiGravity = Variable::string_int_(System::Get_File("TAHack.cfg", 36));
	int UI_Legit_VehicleAntiGravity_Key = Variable::string_int_(System::Get_File("TAHack.cfg", 37));
	BOOL UI_Menu_NeverWanted = Variable::string_int_(System::Get_File("TAHack.cfg", 38));
	BOOL UI_Legit_Suicide = false;
	BOOL UI_Settings_CustomMenuColor = Variable::string_int_(System::Get_File("TAHack.cfg", 39));
	BOOL UI_Settings_ShowConsoleWindow = Variable::string_int_(System::Get_File("TAHack.cfg", 40));
	BOOL UI_Legit_TeleportWaypoint = Variable::string_int_(System::Get_File("TAHack.cfg", 41));
	int UI_Legit_TeleportWaypoint_Key = Variable::string_int_(System::Get_File("TAHack.cfg", 42));
	BOOL UI_Settings_WaterMark = Variable::string_int_(System::Get_File("TAHack.cfg", 43));
	BOOL UI_Menu_Snow = Variable::string_int_(System::Get_File("TAHack.cfg", 44));
	BOOL UI_Menu_AntiAFK = Variable::string_int_(System::Get_File("TAHack.cfg", 45));
}
namespace TAHack_Offsets
{
	System::Memory GTA_mem = { "" };//GTA5 Memory
	HWND GTA_HWND;//GTA5 WindowHWND
	DWORD64 GTA_EXE_Modl;//GTA5.exe ModuleAddress
	uintptr_t WorldPTR;
	uintptr_t LocalPlayer;
	const auto oWorldPTR = 0x2593320;
	const auto oWayPoint = 0x2022DE0;//可以遍历地图光点获取，也就是get_blip，还可以直接读内存获取，有一个静态地址，没有导航点是64000（浮点），有导航点是导航点坐标
	const auto TimeADDR = 0x1DA0250;//可以通过手机时间一个一个筛选
	//以下CT表里有 https://www.unknowncheats.me/forum/grand-theft-auto-v/474288-gtatunersscriptgenz-3-0-1-57-final-cut.html#post3273389
	const auto pCPed = 0x8;
	const auto oHealth = 0x280;
	const auto pedArmor = 0x150C;
	const auto pCPlayerInfo = 0x10A8;
	const auto oSwimSpeed = 0x1C8;
	const auto oRunSpeed = 0xD40;
	const auto oWanted = 0x8D8;
	const auto oGod = 0x189;
	const auto oRagdoll = 0x1098;
	const auto pCPedWeaponManager = 0x10B8;
	const auto pCWeaponInfo = 0x20;
	const auto oDamage = 0xB0;
	const auto pCNavigation = 0x30;
	const auto oPositionX = 0x50;
	const auto oPositionY = 0x54;
	const auto oPositionZ = 0x58;
	const auto pCVehicle = 0xD10;
	const auto oVGravity = 0xC8C;
	const auto oImpactType = 0x20;
	const auto oImpactExplosion = 0x24;
}
using namespace TAHack_Config_Var;
using namespace TAHack_Offsets;
//--------------------------------------------------------------------
void Thread_Menu() noexcept
{
	System::Log("Load Thread: Thread_Menu()");
	GUI_BL_.Window_Create(1010, 580, "TAHack ", true);
	while (1)
	{
		static int UI_Panel = 0; static vector<int> WindowSize = { 0 ,0 }; if (!MenuShowState)WindowSize = { 0 ,0 };
		GUI_BL_.Window_SetSize({ (int)Variable::Animation<class GTAMEnu_Animation_1>(WindowSize[0], 2.5),(int)Variable::Animation<class GTAMEnu_Animation_2>(WindowSize[1], 2.5) });//Animation
		if (!GUI_BL_.Window_Move() && MenuShowState)
		{
			if (UI_Settings_CustomMenuColor)GUI_BL_.GUI_BackGround(1369);
			else GUI_BL_.GUI_BackGround(1368);
			GUI_BL_.GUI_Block_Panel(20, 20, 100, GUI_BL_.Window_GetSize().y - 40, "", { "Menu","Setting","Legit" }, UI_Panel);
			if (UI_Panel == 0)//Menu
			{
				const auto Block_Attributes = GUI_BL_.GUI_Block(150, 30, 310, "Attributes");
				GUI_BL_.GUI_Checkbox(Block_Attributes, 1, "Health", UI_Menu_Health);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_1>(Block_Attributes, 2, "Value", 0, 1000, UI_Menu_Health_Value);
				GUI_BL_.GUI_Checkbox(Block_Attributes, 3, "Armor", UI_Menu_Armor);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_2>(Block_Attributes, 4, "Value", 0, 1000, UI_Menu_Armor_Value);
				GUI_BL_.GUI_Checkbox(Block_Attributes, 5, "Wanted level", UI_Menu_WantedLevel);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_3>(Block_Attributes, 6, "Value", 0, 6, UI_Menu_WantedLevel_Value);
				GUI_BL_.GUI_Checkbox(Block_Attributes, 7, "Move speed", UI_Menu_SpeedChanger);
				GUI_BL_.GUI_Slider<float, class GTA_Menu_4>(Block_Attributes, 8, "Value", 0, 10, UI_Menu_SpeedChanger_Value);
				GUI_BL_.GUI_Button({ Block_Attributes.x,Block_Attributes.y + 5 }, 9, "Suicide", UI_Menu_Suicide, 90);
				const auto Block_World = GUI_BL_.GUI_Block(150, 360, 160, "World");
				GUI_BL_.GUI_Checkbox(Block_World, 1, "Snow", UI_Menu_Snow);
				GUI_BL_.GUI_Checkbox(Block_World, 2, "Time", UI_Menu_Time);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_5>(Block_World, 3, "Hour", 0, 23, UI_Menu_Time_Hour);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_6>(Block_World, 4, "Minute", 0, 59, UI_Menu_Time_Minute);
				const auto Block_General = GUI_BL_.GUI_Block(580, 30, 210, "General");
				GUI_BL_.GUI_Checkbox(Block_General, 1, "God", UI_Menu_God);
				if (UI_Menu_WantedLevel)UI_Menu_NeverWanted = 0;
				GUI_BL_.GUI_Checkbox(Block_General, 2, "Never wanted", UI_Menu_NeverWanted);
				GUI_BL_.GUI_Checkbox(Block_General, 3, "No ragdoll", UI_Menu_NoRagdoll);
				GUI_BL_.GUI_Checkbox(Block_General, 4, "Disable collision", UI_Menu_DisableCollision);
				GUI_BL_.GUI_KeySelector<class GTA_Menu_7>(Block_General, 4, UI_Menu_DisableCollision_Key);
				GUI_BL_.GUI_Checkbox(Block_General, 5, "Teleport waypoint", UI_Menu_TeleportWaypoint, { 150,100,150 });
				GUI_BL_.GUI_KeySelector<class GTA_Menu_8>(Block_General, 5, UI_Menu_TeleportWaypoint_Key);
				GUI_BL_.GUI_Checkbox(Block_General, 6, "Anti-AFK", UI_Menu_AntiAFK);
				const auto Block_Vehicle = GUI_BL_.GUI_Block(580, 260, 150, "Vehicle");
				GUI_BL_.GUI_Checkbox(Block_Vehicle, 1, "God", UI_Menu_Vehicle_God);
				GUI_BL_.GUI_Checkbox(Block_Vehicle, 2, "Gravity", UI_Menu_Vehicle_Gravity);
				GUI_BL_.GUI_Slider<float, class GTA_Menu_9>(Block_Vehicle, 3, "Value", 0, 100, UI_Menu_Vehicle_Gravity_Value);
				GUI_BL_.GUI_Checkbox(Block_Vehicle, 4, "Anti gravity", UI_Menu_AntiGravity);
				GUI_BL_.GUI_KeySelector<class GTA_Menu_10>(Block_Vehicle, 4, UI_Menu_AntiGravity_Key);
				const auto Block_Weapon = GUI_BL_.GUI_Block(580, 430, 120, "Weapon");
				GUI_BL_.GUI_Checkbox(Block_Weapon, 1, "One hit kill", UI_Menu_OneHitKill);
				GUI_BL_.GUI_Checkbox(Block_Weapon, 2, "Bullet type", UI_Menu_BulletType);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_11>(Block_Weapon, 3, "Type", 0, 99, UI_Menu_BulletType_Value);
				GUI_BL_.GUI_Tips({ Block_Weapon.x + 10,Block_Weapon.y }, 3, "Self research. XD");
				WindowSize = { 1010 ,580 };
			}
			else if (UI_Panel == 1)//Setting
			{
				const auto Block_About = GUI_BL_.GUI_Block(150, 30, 160, "About");
				GUI_BL_.GUI_Text(Block_About, 1, "TAHack", GUI_BL_.Global_Get_EasyGUI_Color());
				GUI_BL_.GUI_Text(Block_About, 1, "            for GTA5 (External)", { 150,150,150 });
				GUI_BL_.GUI_Text(Block_About, 2, "Release date: " + ReleaseDate, { 150,150,150 });
				GUI_BL_.GUI_Text(Block_About, 3, "Online version: 1.68", { 150,150,150 });
				GUI_BL_.GUI_Text(Block_About, 4, "Author: https://github.com/Coslly", { 150,150,150 });
				BOOL Button_AuthorLink = false;
				GUI_BL_.GUI_Button_Small({ Block_About.x + 10,Block_About.y }, 4, Button_AuthorLink);
				if (Button_AuthorLink)System::Open_Website("https://github.com/Coslly");
				const auto Block_Menu = GUI_BL_.GUI_Block(150, 210, 340, "Menu");
				GUI_BL_.GUI_Text(Block_Menu, 1, "Menu key");
				GUI_BL_.GUI_KeySelector<class GTA_Menu_12>(Block_Menu, 1, UI_Settings_MenuKey);
				GUI_BL_.GUI_Checkbox(Block_Menu, 2, "Menu color", UI_Settings_CustomMenuColor);
				GUI_BL_.GUI_ColorSelector_a(Block_Menu, 2, UI_Settings_MenuColor);
				if (UI_Settings_MenuColor.a < 200)UI_Settings_MenuColor.a = 200; UI_Settings_MenuColor_A = UI_Settings_MenuColor.a;
				GUI_BL_.GUI_Checkbox(Block_Menu, 3, "Watermark", UI_Settings_WaterMark);
				GUI_BL_.GUI_Checkbox(Block_Menu, 4, "Lock game window", UI_Settings_LockGameWindow);
				GUI_BL_.GUI_Checkbox(Block_Menu, 5, "Show console window [Debug]", UI_Settings_ShowConsoleWindow);
				GUI_BL_.GUI_Button(Block_Menu, 6, "Save config", UI_Settings_SaveConfig, 80);
				GUI_BL_.GUI_Button(Block_Menu, 7, "Start GTA5", UI_Settings_StartGTA, 85);
				GUI_BL_.GUI_Button(Block_Menu, 8, "GitHub repositories", UI_Settings_GitHubRepositories, 65);
				GUI_BL_.GUI_Button(Block_Menu, 9, "Restart", UI_Settings_Restart, 95);
				GUI_BL_.GUI_Button(Block_Menu, 10, "Close", UI_Settings_CloseMenu, 100);
				GUI_BL_.GUI_Tips({ Block_Menu.x + 10,Block_Menu.y }, 6, "If you want to reset the default config you can delete TAHack.cfg in the same folder.");
				if (GTA_EXE_Modl)GUI_BL_.GUI_Tips({ Block_Menu.x + 10,Block_Menu.y }, 7, "GTA5.exe -> " + to_string(GTA_EXE_Modl));
				else GUI_BL_.GUI_Tips({ Block_Menu.x + 10,Block_Menu.y }, 7, "GTA5 not found!!!", { 200,100,100 });
				GUI_BL_.GUI_Tips({ Block_Menu.x + 10,Block_Menu.y }, 8, "If it doesn't work you can download the latest version in the Release folder.");
				WindowSize = { 580 ,580 };
			}
			else if (UI_Panel == 2)//Legit
			{
				const auto Block_Hint = GUI_BL_.GUI_Block(150, 30, 150, "What is this?");
				GUI_BL_.GUI_Text({ Block_Hint.x - 30,Block_Hint.y }, 1, "Made for your account security.", { 200,100,100 });
				GUI_BL_.GUI_Text({ Block_Hint.x - 30,Block_Hint.y }, 2, "I can make sure this is 99.99% safe. You can rest assured.", { 200,100,100 });
				GUI_BL_.GUI_Text({ Block_Hint.x - 30,Block_Hint.y }, 3, "I use it all myself. XD", { 200,100,100 });
				GUI_BL_.GUI_Text({ Block_Hint.x - 30,Block_Hint.y }, 4, "When you enable it, Menu funtion will be disabled.");
				const auto Block_Menu = GUI_BL_.GUI_Block(150, 200, 210, "Legit");
				GUI_BL_.GUI_Checkbox(Block_Menu, 1, "Enabled", UI_Legit_Enabled, GUI_BL_.Global_Get_EasyGUI_Color());
				GUI_BL_.GUI_Checkbox(Block_Menu, 2, "Health lock", UI_Legit_HealthLock);
				GUI_BL_.GUI_Button_Small(Block_Menu, 2, UI_Legit_Suicide);
				GUI_BL_.GUI_Checkbox(Block_Menu, 3, "Vehicle gravity", UI_Legit_VehicleGravity);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_14>(Block_Menu, 4, "Value", 0, 50, UI_Legit_VehicleGravity_Value);
				GUI_BL_.GUI_Checkbox(Block_Menu, 5, "Vehicle Anti gravity", UI_Legit_VehicleAntiGravity);
				GUI_BL_.GUI_KeySelector<class GTA_Menu_15>(Block_Menu, 5, UI_Legit_VehicleAntiGravity_Key);
				GUI_BL_.GUI_Checkbox(Block_Menu, 6, "Teleport waypoint", UI_Legit_TeleportWaypoint, { 150,100,150 });
				GUI_BL_.GUI_KeySelector<class GTA_Menu_16>(Block_Menu, 6, UI_Legit_TeleportWaypoint_Key);
				WindowSize = { 580 ,440 };
			}
			GUI_BL_.Draw_GUI();
		}
	}
}
void Thread_Memory() noexcept
{
	System::Log("Load Thread: Thread_Memory()");
	while (1)
	{
		if (GTA_EXE_Modl)//游戏加载完成
		{
			if (!UI_Legit_Enabled)
			{
				if (UI_Menu_Health)GTA_mem.Write_Level<float>(LocalPlayer, { oHealth }, (float)UI_Menu_Health_Value);//修改生命值
				if (UI_Menu_Armor)GTA_mem.Write_Level<float>(LocalPlayer, { pedArmor }, (float)UI_Menu_Armor_Value);//修改护甲值
				if (UI_Menu_WantedLevel)GTA_mem.Write_Level<int>(LocalPlayer, { pCPlayerInfo,oWanted }, UI_Menu_WantedLevel_Value);//修改通缉星
				if (UI_Menu_NeverWanted)GTA_mem.Write_Level<int>(LocalPlayer, { pCPlayerInfo,oWanted }, 0);//永远不被通缉
				if (UI_Menu_SpeedChanger)//修改跑步速度
				{
					GTA_mem.Write_Level<float>(LocalPlayer, { pCPlayerInfo,oRunSpeed }, UI_Menu_SpeedChanger_Value);//跑步速度
					GTA_mem.Write_Level<float>(LocalPlayer, { pCPlayerInfo,oSwimSpeed }, UI_Menu_SpeedChanger_Value);//游泳速度
				}
				else {
					GTA_mem.Write_Level<float>(LocalPlayer, { pCPlayerInfo,oRunSpeed }, 1);
					GTA_mem.Write_Level<float>(LocalPlayer, { pCPlayerInfo,oSwimSpeed }, 1);
				}
				if (UI_Menu_God)GTA_mem.Write_Level<int>(LocalPlayer, { oGod }, 1);//无敌
				else GTA_mem.Write_Level<int>(LocalPlayer, { oGod }, 0);
				if (UI_Menu_NoRagdoll)GTA_mem.Write_Level<int>(LocalPlayer, { oRagdoll }, 1);//无布娃娃
				else GTA_mem.Write_Level<int>(LocalPlayer, { oRagdoll }, 0);
				if (UI_Menu_DisableCollision && System::Get_Key(UI_Menu_DisableCollision_Key))//无碰撞（穿墙）
				{
					GTA_mem.Write_Level<float>(LocalPlayer, { 0x30,0x10,0x20,0x70,0x0,0x2c }, -1);
					GTA_mem.Write_Level<int>(LocalPlayer, { oRagdoll }, 1);
				}
				else GTA_mem.Write_Level<float>(LocalPlayer, { 0x30,0x10,0x20,0x70,0x0,0x2c }, 0.25);
				if (UI_Menu_OneHitKill && (System::Get_Key(VK_LBUTTON) || System::Get_Key(VK_RBUTTON)))GTA_mem.Write_Level<float>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oDamage }, 999999);//子弹一击毙命
				else GTA_mem.Write_Level<float>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oDamage }, 30);
				if (UI_Menu_Suicide)GTA_mem.Write_Level<float>(LocalPlayer, { oHealth }, 0);//修改生命值实现自杀
				if (UI_Menu_TeleportWaypoint && System::Get_Key_Onest(UI_Menu_TeleportWaypoint_Key) && GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint) != 64000)//传送导航点
				{
					if (GTA_mem.Read_Level<BOOL>(LocalPlayer, { 0xE32 }))//当人物在载具内
					{
						GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,pCNavigation,oPositionX }, GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint));
						GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,pCNavigation,oPositionY }, GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint + 4));
						GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,pCNavigation,oPositionZ }, -255);
					}
					else {
						GTA_mem.Write_Level<float>(LocalPlayer, { pCNavigation,oPositionX }, GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint));
						GTA_mem.Write_Level<float>(LocalPlayer, { pCNavigation,oPositionY }, GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint + 4));
						GTA_mem.Write_Level<float>(LocalPlayer, { pCNavigation,oPositionZ }, -255);
					}
					Beep(100, 50);
				}
				if (UI_Menu_Vehicle_God)GTA_mem.Write_Level<int>(LocalPlayer, { pCVehicle,oGod }, 1);//载具无敌
				else GTA_mem.Write_Level<int>(LocalPlayer, { pCVehicle,oGod }, 0);
				if (UI_Menu_Vehicle_Gravity)GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,oVGravity }, UI_Menu_Vehicle_Gravity_Value);//载具重力(加速度灵敏)
				else GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,oVGravity }, 9.8);//地球重力9.8 (初3知识XD)
				if (UI_Menu_Time)//修改全局时间
				{
					GTA_mem.Write<int>(GTA_EXE_Modl + TimeADDR, UI_Menu_Time_Hour);
					GTA_mem.Write<int>(GTA_EXE_Modl + TimeADDR + 4, UI_Menu_Time_Minute);
				}
				if (UI_Menu_AntiGravity && System::Get_Key(UI_Menu_AntiGravity_Key))GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,oVGravity }, UI_Menu_Vehicle_Gravity_Value * -1);//反重力 (快速爬升)
				if (UI_Menu_BulletType && (System::Get_Key(VK_LBUTTON) || System::Get_Key(VK_RBUTTON)))//修改子弹类型
				{
					GTA_mem.Write_Level<int>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oImpactType }, 5);//状态 2-3-5
					GTA_mem.Write_Level<int>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oImpactExplosion }, UI_Menu_BulletType_Value);//子弹类型 -1~99 -1是默认子弹
				}
				else {
					GTA_mem.Write_Level<int>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oImpactType }, 3);//默认状态
					GTA_mem.Write_Level<int>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oImpactExplosion }, -1);//默认子弹类型
				}
			}
			else {//Legit
				if (System::Sleep_Tick<class GTA5_LegitFunc_Sleep_Class_>(300) && UI_Legit_HealthLock)//锁定血量
				{
					GTA_mem.Write_Level<float>(LocalPlayer, { oHealth }, 300);//血量
					GTA_mem.Write_Level<float>(LocalPlayer, { pedArmor }, 50);//护甲
				}
				if (UI_Legit_Suicide)GTA_mem.Write_Level<float>(LocalPlayer, { oHealth }, 0);//自杀
				if (UI_Legit_VehicleAntiGravity && System::Get_Key(UI_Legit_VehicleAntiGravity_Key))GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,oVGravity }, UI_Legit_VehicleGravity_Value * -1);//载具反重力
				else if (UI_Legit_VehicleGravity)GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,oVGravity }, UI_Legit_VehicleGravity_Value);
				else GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,oVGravity }, 9.8);
				if (System::Get_Key(VK_LBUTTON) || System::Get_Key(VK_RBUTTON))GTA_mem.Write_Level<float>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oDamage }, 999999);//子弹一击毙命
				else GTA_mem.Write_Level<float>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oDamage }, 30);
				if (UI_Legit_TeleportWaypoint && System::Get_Key_Onest(UI_Legit_TeleportWaypoint_Key) && GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint) != 64000)//传送导航点
				{
					if (GTA_mem.Read_Level<BOOL>(LocalPlayer, { 0xE32 }))//当人物在载具内
					{
						GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,pCNavigation,oPositionX }, GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint));
						GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,pCNavigation,oPositionY }, GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint + 4));
						GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,pCNavigation,oPositionZ }, -255);
					}
					else {
						GTA_mem.Write_Level<float>(LocalPlayer, { pCNavigation,oPositionX }, GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint));
						GTA_mem.Write_Level<float>(LocalPlayer, { pCNavigation,oPositionY }, GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint + 4));
						GTA_mem.Write_Level<float>(LocalPlayer, { pCNavigation,oPositionZ }, -255);
					}
					Beep(100, 50);
				}
			}
		}
		if (MenuShowState)Sleep(3);//用于更好的接收消息
		else Sleep(50);//节省CPU占用
	}
}
void Thread_Misc() noexcept
{
	System::Log("Load Thread: Thread_Misc()");
	Window::Windows RenderWindow_Var;
	const HWND Render_Window_HWND_ = RenderWindow_Var.Create_RenderBlock_Alpha(GetSystemMetrics(SM_CXSCREEN), 30, "TAHack Render");//Create RenderWindow
	Window::Render Render_Var; Render_Var.CreatePaint(Render_Window_HWND_, 0, 0, GetSystemMetrics(SM_CXSCREEN), 30);
	while (1)
	{
		if (System::Sleep_Tick<class GTA5_Address_Update_Sleep_Class_>(3500))//Reload Offsets
		{
			GTA_mem = { "GTA5.exe" };
			GTA_HWND = GTA_mem.Get_ProcessHWND();
			GTA_EXE_Modl = GTA_mem.Get_Module("GTA5.exe");
			WorldPTR = GTA_mem.Read<uintptr_t>(GTA_EXE_Modl + oWorldPTR); LocalPlayer = WorldPTR + pCPed;
		}
		if (UI_Settings_WaterMark)
		{
			RenderWindow_Var.Set_WindowPos(0, 0);
			if (System::Sleep_Tick<class Render_Window_Sleep_Class_>(200))//Sleep no in thread.
			{
				const auto Menu_Color = GUI_IO_.GUIColor;
				const string WaterMark_String = "TAHack | " + System::Time_String();
				const short WaterMark_String_Size = strlen(WaterMark_String.c_str()) * 5.4;
				const Variable::Vector2 WaterMark_Pos = { Window::Get_Resolution().x - WaterMark_String_Size - 5,5 };
				Render_Var.Render_SolidRect(0, 0, 9999, 9999, { 0,0,0 });
				Render_Var.RenderA_SolidRect(WaterMark_Pos.x, WaterMark_Pos.y, WaterMark_String_Size, 15, { 1,1,1,150 });
				Render_Var.RenderA_GradientRect(WaterMark_Pos.x, WaterMark_Pos.y, WaterMark_String_Size / 2, 2, { Menu_Color.r / 2, Menu_Color.g / 2, Menu_Color.b / 2,255 }, { Menu_Color.r, Menu_Color.g, Menu_Color.b,255 });
				Render_Var.RenderA_GradientRect(WaterMark_Pos.x + WaterMark_String_Size / 2, WaterMark_Pos.y, WaterMark_String_Size / 2, 2, { Menu_Color.r, Menu_Color.g, Menu_Color.b,255 }, { Menu_Color.r / 2, Menu_Color.g / 2, Menu_Color.b / 2,255 });
				Render_Var.Render_String(WaterMark_Pos.x + 3, WaterMark_Pos.y + 2, WaterMark_String, "Small Fonts", 12, { 255,255,255 });
				Render_Var.DrawPaint();
				RenderWindow_Var.Fix_inWhile();
			}
		}
		else RenderWindow_Var.Set_WindowPos(9999, 9999);
		if (UI_Settings_ShowConsoleWindow)ShowWindow(GetConsoleWindow(), true);//ShowConsoleWindow
		else ShowWindow(GetConsoleWindow(), false);//HideConsoleWindow
		if (UI_Settings_LockGameWindow && !MenuShowState)SetForegroundWindow(GTA_HWND);//Lock GTA5 Window
		if (UI_Settings_SaveConfig)//Save Config
		{
			System::Create_File("TAHack.cfg",
				to_string(UI_Menu_Health) + "\n" +
				to_string(UI_Menu_Health_Value) + "\n" +
				to_string(UI_Menu_Armor) + "\n" +
				to_string(UI_Menu_Armor_Value) + "\n" +
				to_string(UI_Menu_WantedLevel) + "\n" +
				to_string(UI_Menu_WantedLevel_Value) + "\n" +
				to_string(UI_Menu_SpeedChanger) + "\n" +
				to_string(UI_Menu_SpeedChanger_Value) + "\n" +
				to_string(UI_Menu_God) + "\n" +
				to_string(UI_Menu_NoRagdoll) + "\n" +
				to_string(UI_Menu_DisableCollision) + "\n" +
				to_string(UI_Menu_OneHitKill) + "\n" +
				to_string(UI_Menu_TeleportWaypoint) + "\n" +
				to_string(UI_Menu_TeleportWaypoint_Key) + "\n" +
				to_string(UI_Menu_Vehicle_God) + "\n" +
				to_string(UI_Menu_Vehicle_Gravity) + "\n" +
				to_string(UI_Menu_Vehicle_Gravity_Value) + "\n" +
				to_string(UI_Menu_Time) + "\n" +
				to_string(UI_Menu_Time_Hour) + "\n" +
				to_string(UI_Menu_Time_Minute) + "\n" +
				to_string(UI_Settings_MenuKey) + "\n" +
				to_string(UI_Settings_MenuColor.r) + "\n" +
				to_string(UI_Settings_MenuColor.g) + "\n" +
				to_string(UI_Settings_MenuColor.b) + "\n" +
				to_string(UI_Settings_MenuColor_A) + "\n" +
				to_string(UI_Menu_DisableCollision_Key) + "\n" +
				to_string(UI_Menu_AntiGravity) + "\n" +
				to_string(UI_Menu_AntiGravity_Key) + "\n" +
				to_string(UI_Menu_BulletType) + "\n" +
				to_string(UI_Menu_BulletType_Value) + "\n" +
				to_string(UI_Settings_LockGameWindow) + "\n" +
				to_string(UI_Legit_Enabled) + "\n" +
				to_string(UI_Legit_HealthLock) + "\n" +
				to_string(UI_Legit_VehicleGravity) + "\n" +
				to_string(UI_Legit_VehicleGravity_Value) + "\n" +
				to_string(UI_Legit_VehicleAntiGravity) + "\n" +
				to_string(UI_Legit_VehicleAntiGravity_Key) + "\n" +
				to_string(UI_Menu_NeverWanted) + "\n" +
				to_string(UI_Settings_CustomMenuColor) + "\n" +
				to_string(UI_Settings_ShowConsoleWindow) + "\n" +
				to_string(UI_Legit_TeleportWaypoint) + "\n" +
				to_string(UI_Legit_TeleportWaypoint_Key) + "\n" +
				to_string(UI_Settings_WaterMark) + "\n" +
				to_string(UI_Menu_Snow) + "\n" +
				to_string(UI_Menu_AntiAFK) + "\n"
			);
		}
		if (UI_Settings_StartGTA)System::Open_Website("steam://rungameid/271590");//Start GTA5
		if (UI_Settings_GitHubRepositories)System::Open_Website("https://github.com/Coslly/TaHack.git");//Open GitHubRepositories
		if (UI_Settings_Restart)System::Self_Restart();//RestartSelf
		if (UI_Settings_CloseMenu)exit(0);//Close
		GUI_IO_ = GUI_BL_.Get_IO();
		if (!UI_Settings_CustomMenuColor)GUI_IO_.GUIColor = { GUI_IO_.GUIColor_Rainbow[3],GUI_IO_.GUIColor_Rainbow[4],GUI_IO_.GUIColor_Rainbow[5] };
		Sleep(1);//CPU
	}
}
int main() noexcept
{
	System::URL_READ AutoUpdate = {"cache_update"};//Auto Update Service
	if (AutoUpdate.StoreMem("https://github.com/Coslly/TaHack/blob/main/TAHack/TAHack/Main.cpp?raw=true"))
	{
		auto Version = AutoUpdate.Read(2);
		Version.erase(0, 30);//Erase variable name
		Version.erase(Version.size() - 1, 1);//Erase suffix
		if (Variable::string_float_(Version) > ReleaseVersion && Window::Message_Box("TaHack Update", "A new version has been released.\nDo you want to update now?\n"))
		{
			System::DownloadToPath("https://github.com/Coslly/TaHack/releases/download/Release/TAHack.exe", System::Rand_String(10) + ".exe");
		}
		AutoUpdate.Release();
	}
	system("cls");//Clear text
	System::Log("Load Thread: main()");
	System::Anti_click();//Console not selected.
	Window::Hide_ConsoleWindow();
	Sleep(200);//Fix RestartBug
	if (FindWindow(NULL, L"TAHack ")) { MessageBox(NULL, L"Already running.", L"Error", MB_ICONERROR); exit(0); }//Prevent multiple openings
	if (!System::Judge_File("TAHack.cfg")) { System::Create_File("TAHack.cfg", Default_Config); System::Self_Restart(); }//Create Default Config
	thread Thread_Menu1 = thread(Thread_Menu);
	thread Thread_Misc1 = thread(Thread_Misc);
	Sleep(10);
	thread Thread_Memory1 = thread(Thread_Memory);
	while (1)
	{
		if (System::Get_Key(VK_INSERT) && System::Get_Key(VK_DELETE)) { Beep(100, 30); exit(0); }//Close Key
		static short MenuWindowAlpha = 0;//Animation Alpha
		if (MenuShowState)MenuWindowAlpha = MenuWindowAlpha + UI_Settings_MenuColor_A / 8;
		else MenuWindowAlpha = MenuWindowAlpha - UI_Settings_MenuColor_A / 8;
		if (MenuWindowAlpha >= UI_Settings_MenuColor_A)MenuWindowAlpha = UI_Settings_MenuColor_A;
		else if (MenuWindowAlpha <= 0)MenuWindowAlpha = 0;
		GUI_BL_.Window_SetAlpha(MenuWindowAlpha);//SetWindow AlphaColor
		if (UI_Settings_CustomMenuColor)GUI_BL_.Global_Set_EasyGUI_Color(UI_Settings_MenuColor);
		if (!System::Key_Toggle<class Class_GTAMENU_KeyHold_>(UI_Settings_MenuKey)) { GUI_BL_.Window_Show(); MenuShowState = true; }
		else { if (MenuWindowAlpha == 0)GUI_BL_.Window_Hide(); MenuShowState = false; }
		Sleep(1);
	}
}
