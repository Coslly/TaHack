#include "Head.h"
const string ReleaseDate = "[2023-07-15 13:00]";
EasyGUI::EasyGUI GUI_BL_;
BOOL MenuShowState;
//------------------------------------
BOOL UI_Menu_Health = string_int_(Get_File("TAHack.cfg", 1));
int UI_Menu_Health_Value = string_int_(Get_File("TAHack.cfg", 2));
BOOL UI_Menu_Armor = string_int_(Get_File("TAHack.cfg", 3));
int UI_Menu_Armor_Value = string_int_(Get_File("TAHack.cfg", 4));
BOOL UI_Menu_WantedLevel = string_int_(Get_File("TAHack.cfg", 5));
int UI_Menu_WantedLevel_Value = string_int_(Get_File("TAHack.cfg", 6));
BOOL UI_Menu_SpeedChanger = string_int_(Get_File("TAHack.cfg", 7));
float UI_Menu_SpeedChanger_Value = string_float_(Get_File("TAHack.cfg", 8));
BOOL UI_Menu_God = string_int_(Get_File("TAHack.cfg", 9));
BOOL UI_Menu_NoRagdoll = string_int_(Get_File("TAHack.cfg", 10));
BOOL UI_Menu_DisableCollision = string_int_(Get_File("TAHack.cfg", 11));
BOOL UI_Menu_OneHitKill = string_int_(Get_File("TAHack.cfg", 12));
BOOL UI_Menu_Suicide = false;
BOOL UI_Menu_TeleportWaypoint = string_int_(Get_File("TAHack.cfg", 13));
int UI_Menu_TeleportWaypoint_Key = string_int_(Get_File("TAHack.cfg", 14));
BOOL UI_Menu_Vehicle_God = string_int_(Get_File("TAHack.cfg", 15));
BOOL UI_Menu_Vehicle_Gravity = string_int_(Get_File("TAHack.cfg", 16));
float UI_Menu_Vehicle_Gravity_Value = string_float_(Get_File("TAHack.cfg", 17));
BOOL UI_Menu_Time = string_int_(Get_File("TAHack.cfg", 18));
int UI_Menu_Time_Hour = string_int_(Get_File("TAHack.cfg", 19));
int UI_Menu_Time_Minute = string_int_(Get_File("TAHack.cfg", 20));
int UI_Settings_MenuKey = string_int_(Get_File("TAHack.cfg", 21));
vector<int> UI_Settings_MenuColor = { string_int_(Get_File("TAHack.cfg", 22)),string_int_(Get_File("TAHack.cfg", 23)),string_int_(Get_File("TAHack.cfg", 24)) };
int UI_Settings_MenuColor_A = string_int_(Get_File("TAHack.cfg", 25));
int UI_Menu_DisableCollision_Key = string_int_(Get_File("TAHack.cfg", 26));
BOOL UI_Menu_AntiGravity = string_int_(Get_File("TAHack.cfg", 27));
int UI_Menu_AntiGravity_Key = string_int_(Get_File("TAHack.cfg", 28));
BOOL UI_Menu_BulletType = string_int_(Get_File("TAHack.cfg", 29));
int UI_Menu_BulletType_Value = string_int_(Get_File("TAHack.cfg", 30));
BOOL UI_Settings_LockGameWindow = string_int_(Get_File("TAHack.cfg", 31));
BOOL UI_Settings_SaveConfig = false;
BOOL UI_Settings_StartGTA = false;
BOOL UI_Settings_GitHubRepositories = false;
BOOL UI_Settings_Restart = false;
BOOL UI_Settings_CloseMenu = false;
//------------------------------------
BOOL UI_Legit_Enabled = string_int_(Get_File("TAHack.cfg", 32));
BOOL UI_Legit_HealthLock = string_int_(Get_File("TAHack.cfg", 33));
BOOL UI_Legit_VehicleGravity = string_int_(Get_File("TAHack.cfg", 34));
float UI_Legit_VehicleGravity_Value = string_float_(Get_File("TAHack.cfg", 35));
//------------------------------------
Memory::Memory GTA_mem;//GTA5 Memory
DWORD64 GTA_EXE_Modl;//GTA5.exe ModuleAddress
uintptr_t WorldPTR;
uintptr_t LocalPlayer;
const auto oWorldPTR = 0x257BEA0;//Need to find
const auto oWayPoint = 0x200BEB0;//Need to find 可以遍历地图光点获取，也就是get_blip，还可以直接读内存获取，有一个静态地址，没有导航点是64000（浮点），有导航点是导航点坐标
const auto TimeADDR = 0x1D89B40;//Need to find
//以下CT表里有 https://www.unknowncheats.me/forum/grand-theft-auto-v/474288-gtatunersscriptgenz-3-0-1-57-final-cut.html#post3273389
const auto pCPed = 0x8;
const auto oHealth = 0x280;
const auto pedArmor = 0x150C;
const auto pCPlayerInfo = 0x10A8;
const auto oSwimSpeed = 0x1C8;
const auto oRunSpeed = 0xD40;
const auto oWanted = 0x8D8;
const auto oGod = 0x189;
const auto oRagdoll = 0x1098;//int 32: false 1 / 0 : true
const auto pCPedWeaponManager = 0x10B8;
const auto pCWeaponInfo = 0x20;
const auto oDamage = 0xB0;
const auto pCNavigation = 0x30;
const auto oPositionX = 0x50;
const auto oPositionY = 0x54;
const auto oPositionZ = 0x58;
const auto pCVehicle = 0xD10;
const auto oVGravity = 0xC3C;
const auto oImpactType = 0x20;
const auto oImpactExplosion = 0x24;
//------------------------------------
void Thread_Menu()//Draw Menu
{
	GUI_BL_.Window_Create(1010, 520, L"TaHack for GTA5", true);
	while (1)
	{
		static int UI_Panel = 0;//Panel
		static vector<int> WindowSize = { 0 ,0 };
		if (!GUI_BL_.Window_Move())
		{
			if (!MenuShowState)WindowSize = { 0 ,0 };
			GUI_BL_.Window_SetSize({ (int)Fast_to_Slow<class GTAMEnu_Animation_1>(WindowSize[0],3),(int)Fast_to_Slow<class GTAMEnu_Animation_2>(WindowSize[1],3) });//Animation
			GUI_BL_.GUI_BackGround(1369);
			GUI_BL_.GUI_Block_Panel(20, 20, 100, GUI_BL_.Window_GetSize()[1] - 40, "", { "Menu","Settings","Legit" }, UI_Panel);
			if (UI_Panel == 0)//Menu
			{
				vector<int> Block_Attributes = GUI_BL_.GUI_Block(150, 30, 310, "Attributes");
				GUI_BL_.GUI_Checkbox(Block_Attributes, 1, "Health", UI_Menu_Health);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_1>(Block_Attributes, 2, "Value", 0, 1000, UI_Menu_Health_Value, { 100,100,100 });
				GUI_BL_.GUI_Checkbox(Block_Attributes, 3, "Armor", UI_Menu_Armor);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_2>(Block_Attributes, 4, "Value", 0, 1000, UI_Menu_Armor_Value, { 100,100,100 });
				GUI_BL_.GUI_Checkbox(Block_Attributes, 5, "Wanted Level", UI_Menu_WantedLevel);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_3>(Block_Attributes, 6, "Value", 0, 6, UI_Menu_WantedLevel_Value, { 100,100,100 });
				GUI_BL_.GUI_Checkbox(Block_Attributes, 7, "Move Speed", UI_Menu_SpeedChanger);
				GUI_BL_.GUI_Slider<float, class GTA_Menu_4>(Block_Attributes, 8, "Value", 0, 10, UI_Menu_SpeedChanger_Value, { 100,100,100 });
				GUI_BL_.GUI_Button({ Block_Attributes[0],Block_Attributes[1] + 5 }, 9, "Suicide", 90, UI_Menu_Suicide);
				vector<int> Block_World = GUI_BL_.GUI_Block(150, 360, 130, "World");
				GUI_BL_.GUI_Checkbox(Block_World, 1, "Time", UI_Menu_Time);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_5>(Block_World, 2, "Hour", 0, 23, UI_Menu_Time_Hour, { 100,100,100 });
				GUI_BL_.GUI_Slider<int, class GTA_Menu_6>(Block_World, 3, "Minute", 0, 59, UI_Menu_Time_Minute, { 100,100,100 });
				vector<int> Block_General = Block_Attributes = GUI_BL_.GUI_Block(580, 30, 150, "General");
				GUI_BL_.GUI_Checkbox(Block_General, 1, "God", UI_Menu_God);
				GUI_BL_.GUI_Checkbox(Block_General, 2, "No Ragdoll", UI_Menu_NoRagdoll);
				GUI_BL_.GUI_Checkbox(Block_General, 3, "Disable Collision", UI_Menu_DisableCollision);
				GUI_BL_.GUI_KeySelector<class GTA_Menu_7>(Block_General, 3, UI_Menu_DisableCollision_Key);
				GUI_BL_.GUI_Checkbox(Block_General, 4, "Teleport Waypoint", UI_Menu_TeleportWaypoint, { 150,100,150 });
				GUI_BL_.GUI_KeySelector<class GTA_Menu_8>(Block_General, 4, UI_Menu_TeleportWaypoint_Key);
				vector<int> Block_Vehicle = GUI_BL_.GUI_Block(580, 200, 150, "Vehicle");
				GUI_BL_.GUI_Checkbox(Block_Vehicle, 1, "God", UI_Menu_Vehicle_God);
				GUI_BL_.GUI_Checkbox(Block_Vehicle, 2, "Gravity", UI_Menu_Vehicle_Gravity);
				GUI_BL_.GUI_Slider<float, class GTA_Menu_9>(Block_Vehicle, 3, "Value", 0, 100, UI_Menu_Vehicle_Gravity_Value, { 100,100,100 });
				GUI_BL_.GUI_Checkbox(Block_Vehicle, 4, "AntiGravity", UI_Menu_AntiGravity);
				GUI_BL_.GUI_KeySelector<class GTA_Menu_10>(Block_Vehicle, 4, UI_Menu_AntiGravity_Key);
				vector<int> Block_Weapon = GUI_BL_.GUI_Block(580, 370, 120, "Weapon");
				GUI_BL_.GUI_Checkbox(Block_Weapon, 1, "One Hit Kill", UI_Menu_OneHitKill);
				GUI_BL_.GUI_Checkbox(Block_Weapon, 2, "Bullet Type", UI_Menu_BulletType);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_11>(Block_Weapon, 3, "Type", 0, 99, UI_Menu_BulletType_Value, { 100,100,100 });
				GUI_BL_.GUI_Tips({ Block_Weapon[0] + 10,Block_Weapon[1] }, 3, "Self Research. XD");
				WindowSize = { 1010 ,520 };
			}
			else if (UI_Panel == 1)//Settings
			{
				vector<int> Block_Settings = GUI_BL_.GUI_Block(150, 30, GUI_BL_.Window_GetSize()[1] - 60, "Settings");
				GUI_BL_.GUI_Text(Block_Settings, 1, "TaHack", GUI_BL_.Global_Get_EasyGUI_Color());
				GUI_BL_.GUI_Text(Block_Settings, 1, "            for GTA5 (External)", { 150,150,150 });
				GUI_BL_.GUI_Text(Block_Settings, 2, "Release Date: " + ReleaseDate, { 150,150,150 });
				GUI_BL_.GUI_Text(Block_Settings, 3, "Online Version: 1.67", { 150,150,150 });
				GUI_BL_.GUI_Checkbox(Block_Settings, 4, "Lock Game Window", UI_Settings_LockGameWindow);
				GUI_BL_.GUI_Text(Block_Settings, 5, "Menu Key");
				GUI_BL_.GUI_KeySelector<class GTA_Menu_12>(Block_Settings, 5, UI_Settings_MenuKey);
				GUI_BL_.GUI_Text(Block_Settings, 6, "Menu Color");
				GUI_BL_.GUI_ColorSelector(Block_Settings, 6, UI_Settings_MenuColor);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_13>(Block_Settings, 7, "Alpha", 200, 255, UI_Settings_MenuColor_A);
				GUI_BL_.GUI_Button(Block_Settings, 8, "SaveConfig", 85, UI_Settings_SaveConfig);
				GUI_BL_.GUI_Button(Block_Settings, 9, "Start GTA5", 85, UI_Settings_StartGTA);
				GUI_BL_.GUI_Button(Block_Settings, 10, "GitHub Repositories", 65, UI_Settings_GitHubRepositories);
				GUI_BL_.GUI_Button(Block_Settings, 11, "Restart", 95, UI_Settings_Restart);
				GUI_BL_.GUI_Button(Block_Settings, 12, "Close", 100, UI_Settings_CloseMenu);
				GUI_BL_.GUI_Tips({ Block_Settings[0] + 10,Block_Settings[1] }, 8, "If you want to reset the default config you can delete TAHack.cfg in the same folder.");
				GUI_BL_.GUI_Tips({ Block_Settings[0] + 10,Block_Settings[1] }, 10, "If it doesn't work you can download the latest version in the Release folder.");
				if (UI_Settings_SaveConfig)//Save Config
				{
					Found_File("TAHack.cfg", to_string(UI_Menu_Health) + "\n" + to_string(UI_Menu_Health_Value) + "\n" + to_string(UI_Menu_Armor) + "\n" + to_string(UI_Menu_Armor_Value) + "\n" + to_string(UI_Menu_WantedLevel) + "\n" + to_string(UI_Menu_WantedLevel_Value) + "\n" + to_string(UI_Menu_SpeedChanger) + "\n" + to_string(UI_Menu_SpeedChanger_Value) + "\n" + to_string(UI_Menu_God) + "\n" + to_string(UI_Menu_NoRagdoll) + "\n" + to_string(UI_Menu_DisableCollision) + "\n" + to_string(UI_Menu_OneHitKill) + "\n" + to_string(UI_Menu_TeleportWaypoint) + "\n" + to_string(UI_Menu_TeleportWaypoint_Key) + "\n" + to_string(UI_Menu_Vehicle_God) + "\n" + to_string(UI_Menu_Vehicle_Gravity) + "\n" + to_string(UI_Menu_Vehicle_Gravity_Value) + "\n" + to_string(UI_Menu_Time) + "\n" + to_string(UI_Menu_Time_Hour) + "\n" + to_string(UI_Menu_Time_Minute) + "\n" + to_string(UI_Settings_MenuKey) + "\n" + to_string(UI_Settings_MenuColor[0]) + "\n" + to_string(UI_Settings_MenuColor[1]) + "\n" + to_string(UI_Settings_MenuColor[2]) + "\n" + to_string(UI_Settings_MenuColor_A) + "\n" + to_string(UI_Menu_DisableCollision_Key) + "\n" + to_string(UI_Menu_AntiGravity) + "\n" + to_string(UI_Menu_AntiGravity_Key) + "\n" + to_string(UI_Menu_BulletType) + "\n" + to_string(UI_Menu_BulletType_Value) + "\n" + to_string(UI_Settings_LockGameWindow) + "\n" + to_string(UI_Legit_Enabled) + "\n" + to_string(UI_Legit_HealthLock) + "\n" + to_string(UI_Legit_VehicleGravity) + "\n" + to_string(UI_Legit_VehicleGravity_Value) + "\n");
					Beep(100, 30);
				}
				if (UI_Settings_StartGTA)//Start GTA5
				{
					system("start steam://rungameid/271590");
					Beep(100, 30);
				}
				if (UI_Settings_GitHubRepositories)//Open GitHubRepositories
				{
					system("start https://github.com/Coslly/TaHack.git");
					Beep(100, 30);
				}
				if (UI_Settings_Restart)//RestartSelf
				{
					Beep(100, 30);
					TCHAR szPath[MAX_PATH];
					GetModuleFileName(NULL, szPath, MAX_PATH);
					STARTUPINFO StartInfo;
					PROCESS_INFORMATION procStruct;
					memset(&StartInfo, 0, sizeof(STARTUPINFO));
					StartInfo.cb = sizeof(STARTUPINFO);
					if (!CreateProcess((LPCTSTR)szPath, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &StartInfo, &procStruct));
					CloseHandle(procStruct.hProcess);
					CloseHandle(procStruct.hThread);
					exit(0);//Close
				}
				if (UI_Settings_CloseMenu)//Close
				{
					Beep(100, 30);
					exit(0);
				}
				WindowSize = { 580 ,460 };
			}
			else if (UI_Panel == 2)//Legit
			{
				vector<int> Block_Hint = GUI_BL_.GUI_Block(150, 30, 150, "What is this?");
				GUI_BL_.GUI_Text({ Block_Hint[0] - 30,Block_Hint[1] }, 1, "Made for your account security.", { 200,100,100 });
				GUI_BL_.GUI_Text({ Block_Hint[0] - 30,Block_Hint[1] }, 2, "I can make sure this is 99.99% safe. You can rest assured.", { 200,100,100 });
				GUI_BL_.GUI_Text({ Block_Hint[0] - 30,Block_Hint[1] }, 3, "I use it all myself. XD", { 200,100,100 });
				GUI_BL_.GUI_Text({ Block_Hint[0] - 30,Block_Hint[1] }, 4, "When you enable it, Menu funtion will be disabled.");
				vector<int> Block_Menu = GUI_BL_.GUI_Block(150, 200, 160, "Legit");
				GUI_BL_.GUI_Checkbox(Block_Menu, 1, "Enabled", UI_Legit_Enabled, GUI_BL_.Global_Get_EasyGUI_Color());
				GUI_BL_.GUI_Checkbox(Block_Menu, 2, "HealthLock", UI_Legit_HealthLock);
				GUI_BL_.GUI_Checkbox(Block_Menu, 3, "VehicleGravity", UI_Legit_VehicleGravity);
				GUI_BL_.GUI_Slider<float, class GTA_Menu_14>(Block_Menu, 4, "Value", 9.8, 50, UI_Legit_VehicleGravity_Value, { 100,100,100 });
				WindowSize = { 580 ,390 };
			}
			GUI_BL_.Draw_GUI();
		}
	}
}
void Thread_Memory()//Memory
{
	while (1)
	{
		if (Sleep_Tick<class GTA5_Address_Update_Sleep_>(3000))//每3秒刷新地址
		{
			GTA_mem.Get_ProcessID(FindWindow(NULL, L"Grand Theft Auto V"));
			GTA_EXE_Modl = GTA_mem.Get_ModuleAddress(L"GTA5.exe");
			WorldPTR = GTA_mem.Read<uintptr_t>(GTA_EXE_Modl + oWorldPTR); LocalPlayer = WorldPTR + pCPed;
		}
		if (GTA_EXE_Modl)//游戏加载完成
		{
			if (!UI_Legit_Enabled)
			{
				if (UI_Menu_Health)GTA_mem.Write_Level<float>(LocalPlayer, { oHealth }, (float)UI_Menu_Health_Value);//修改生命值
				if (UI_Menu_Armor)GTA_mem.Write_Level<float>(LocalPlayer, { pedArmor }, (float)UI_Menu_Armor_Value);//修改护甲值
				if (UI_Menu_WantedLevel)GTA_mem.Write_Level<int>(LocalPlayer, { pCPlayerInfo,oWanted }, UI_Menu_WantedLevel_Value);//修改通缉星
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
				if (UI_Menu_DisableCollision && GetAsyncKeyState(UI_Menu_DisableCollision_Key) & 0x8000)//无碰撞（穿墙）
				{
					GTA_mem.Write_Level<float>(LocalPlayer, { 0x30,0x10,0x20,0x70,0x0,0x2c }, -1);
					GTA_mem.Write_Level<int>(LocalPlayer, { oRagdoll }, 1);
				}
				else GTA_mem.Write_Level<float>(LocalPlayer, { 0x30,0x10,0x20,0x70,0x0,0x2c }, 0.25);
				if (UI_Menu_OneHitKill)GTA_mem.Write_Level<float>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oDamage }, 999999);//子弹一击毙命
				else GTA_mem.Write_Level<float>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oDamage }, 40);
				if (UI_Menu_Suicide)GTA_mem.Write_Level<float>(LocalPlayer, { oHealth }, 0);//修改生命值实现自杀
				if (UI_Menu_TeleportWaypoint && Get_Key_Onest(UI_Menu_TeleportWaypoint_Key) && GTA_mem.Read<float>(GTA_EXE_Modl + oWayPoint) != 64000)//传送导航点
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
					GTA_mem.Write<int>(GTA_EXE_Modl + TimeADDR + 0x10, UI_Menu_Time_Hour);
					GTA_mem.Write<int>(GTA_EXE_Modl + TimeADDR + 0x14, UI_Menu_Time_Minute);
				}
				if (UI_Menu_AntiGravity && (GetAsyncKeyState(UI_Menu_AntiGravity_Key) & 0x8000))GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,oVGravity }, -50);//反重力 (快速爬升)
				if (UI_Menu_BulletType && ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000)))//修改子弹类型
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
				if (Sleep_Tick<class GTA5_LegitFunc_Sleep_>(500))//每0.5秒修改一次(减少cpu占用)
				{
					if (UI_Legit_HealthLock)GTA_mem.Write_Level<float>(LocalPlayer, { oHealth }, 300);//锁定生命值
					if (UI_Legit_VehicleGravity)GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,oVGravity }, UI_Legit_VehicleGravity_Value);//载具重力
				}
			}
		}
		if (MenuShowState)Sleep(3);//用于更好的接收消息
		else Sleep(100);//节省CPU占用
	}
}
int main()//Main thread
{
	ShowWindow(GetConsoleWindow(), false);//HideConsoleWindow
	Sleep(100);//Fix RestartBug
	if (FindWindow(NULL, L"TaHack for GTA5"))//Prevent multiple openings
	{
		MessageBox(NULL, L"Already running.", L"Error", MB_ICONERROR);
		exit(0);
	}
	if (_access("TAHack.cfg", 0) == -1)//Create parameter file if not found
	{
		Found_File("TAHack.cfg", "0\n1000\n0\n1000\n1\n0\n1\n1.5\n1\n1\n1\n1\n1\n116\n1\n1\n20\n1\n11\n0\n45\n255\n255\n255\n250\n9\n1\n6\n1\n0\n0\n1\n1\n1\n25\n");//DefaultConfig
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		STARTUPINFO StartInfo;
		PROCESS_INFORMATION procStruct;
		memset(&StartInfo, 0, sizeof(STARTUPINFO));
		StartInfo.cb = sizeof(STARTUPINFO);
		if (!CreateProcess((LPCTSTR)szPath, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &StartInfo, &procStruct));//RestartSelf
		CloseHandle(procStruct.hProcess);
		CloseHandle(procStruct.hThread);
		Beep(100, 100);
		exit(0);//Close
	}
	thread Thread_Menu1 = thread(Thread_Menu);
	thread Thread_Memory1 = thread(Thread_Memory);
	while (1)
	{
		ShowWindow(GetConsoleWindow(), false);//HideConsoleWindow
		static short MenuWindowAlpha = 0;//Animation Alpha
		if (MenuShowState)MenuWindowAlpha = MenuWindowAlpha + UI_Settings_MenuColor_A / 10;
		else MenuWindowAlpha = MenuWindowAlpha - UI_Settings_MenuColor_A / 10;
		if (MenuWindowAlpha >= UI_Settings_MenuColor_A)MenuWindowAlpha = UI_Settings_MenuColor_A;
		else if (MenuWindowAlpha <= 0)MenuWindowAlpha = 0;
		GUI_BL_.Window_SetAlpha(MenuWindowAlpha);//SetWindow AlphaColor
		GUI_BL_.Global_Set_EasyGUI_Color(UI_Settings_MenuColor);
		if (!Key_Toggle<class Class_GTAMENU_KeyHold_>(UI_Settings_MenuKey))
		{
			GUI_BL_.Window_Show();
			MenuShowState = true;
		}
		else {
			if (MenuWindowAlpha == 0)GUI_BL_.Window_Hide();
			MenuShowState = false;
		}
		if (UI_Settings_LockGameWindow && !MenuShowState)SetForegroundWindow(FindWindow(NULL, L"Grand Theft Auto V"));//Show GTA5 Window
		if ((GetAsyncKeyState(VK_INSERT) & 0x8000) && (GetAsyncKeyState(VK_DELETE) & 0x8000))//Close Key
		{
			Beep(100, 30);
			exit(0);
		}
		Sleep(1);
	}
}