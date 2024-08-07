﻿#include "Head.h"
#include "GTA5_SDK.h"
const int ReleaseVersion = 124;
const string ReleaseDate = "[2024-08-06 12:10]";
EasyGUI::EasyGUI GUI_BL_;
EasyGUI::EasyGUI_IO GUI_IO_;
BOOL MenuShowState;
//--------------------------------------------------------------------
namespace TAHack_Config_Var
{
	const string Default_Config = "1\n300\n1\n300\n0\n0\n1\n1.2\n0\n0\n1\n1\n1\n116\n1\n1\n25\n0\n11\n0\n45\n255\n230\n255\n250\n6\n1\n5\n1\n18\n0\n0\n1\n1\n25\n1\n5\n0\n1\n0\n1\n116\n1\n0\n0\n1\n117\n5\n";
	BOOL UI_Menu_Health = Variable::string_int_(System::Get_File("TAHack.cfg", 1));
	int UI_Menu_Health_Value = Variable::string_int_(System::Get_File("TAHack.cfg", 2));
	BOOL UI_Menu_Armor = Variable::string_int_(System::Get_File("TAHack.cfg", 3));
	int UI_Menu_Armor_Value = Variable::string_int_(System::Get_File("TAHack.cfg", 4));
	BOOL UI_Menu_WantedLevel = Variable::string_int_(System::Get_File("TAHack.cfg", 5));
	int UI_Menu_WantedLevel_Value = Variable::string_int_(System::Get_File("TAHack.cfg", 6));
	BOOL UI_Menu_MoveSpeed = Variable::string_int_(System::Get_File("TAHack.cfg", 7));
	float UI_Menu_MoveSpeed_Value = Variable::string_float_(System::Get_File("TAHack.cfg", 8));
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
	float UI_Legit_VehicleGravity_Value = Variable::string_float_(System::Get_File("TAHack.cfg", 35));
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
	BOOL UI_Menu_PublicSession = false;
	BOOL UI_Menu_InviteOnlySession = false;
	BOOL UI_Menu_SpawnVehicle = Variable::string_int_(System::Get_File("TAHack.cfg", 46));
	int UI_Menu_SpawnVehicle_Key = Variable::string_int_(System::Get_File("TAHack.cfg", 47));
	BOOL UI_Menu_SpawnVehicle_Button = false;
	int UI_Menu_SpawnVehicle_List = 0;
	string UI_Menu_SpawnVehicle_String = "";
	int UI_Menu_BulletType_Key = Variable::string_int_(System::Get_File("TAHack.cfg", 48));
}
using namespace TAHack_Config_Var;
//--------------------------------------------------------------------
void Thread_Menu() noexcept
{
	System::Log("Load Thread: Thread_Menu()");
	GUI_BL_.Window_Create(1440, 610, "TAHack ", true);
	while (true)
	{
		static int UI_Panel = 0; static Variable::Vector2 WindowSize = { 0 ,0 }; if (!MenuShowState)WindowSize = { 0 ,0 };
		GUI_BL_.Window_SetSize(Variable::Animation_Vec2<class CLASS_GTAMENU_ANIMATION_>(WindowSize, 3));//窗口大小动画
		if (!GUI_BL_.Window_Move() && MenuShowState)
		{
			if (UI_Settings_CustomMenuColor)GUI_BL_.GUI_BackGround(4);
			else GUI_BL_.GUI_BackGround(3);
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
				GUI_BL_.GUI_Checkbox(Block_Attributes, 7, "Move speed", UI_Menu_MoveSpeed);
				GUI_BL_.GUI_Slider<float, class GTA_Menu_4>(Block_Attributes, 8, "Value", 0, 20, UI_Menu_MoveSpeed_Value);
				GUI_BL_.GUI_Button({ Block_Attributes.x,Block_Attributes.y + 5 }, 9, "Suicide", UI_Menu_Suicide, 90);
				const auto Block_World = GUI_BL_.GUI_Block(150, 360, 220, "World");
				GUI_BL_.GUI_Checkbox(Block_World, 1, "Snow", UI_Menu_Snow);
				GUI_BL_.GUI_Checkbox(Block_World, 2, "Time", UI_Menu_Time);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_5>(Block_World, 3, "Hour", 0, 23, UI_Menu_Time_Hour);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_6>(Block_World, 4, "Minute", 0, 59, UI_Menu_Time_Minute);
				GUI_BL_.GUI_Button({ Block_World.x,Block_World.y + 5 }, 5, "Public session", UI_Menu_PublicSession, 75);
				GUI_BL_.GUI_Button({ Block_World.x,Block_World.y + 5 }, 6, "Invite only session", UI_Menu_InviteOnlySession, 60);
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
				GUI_BL_.GUI_Slider<float, class GTA_Menu_9>(Block_Vehicle, 3, "Value", 0, 300, UI_Menu_Vehicle_Gravity_Value);
				GUI_BL_.GUI_Checkbox(Block_Vehicle, 4, "Anti gravity", UI_Menu_AntiGravity);
				GUI_BL_.GUI_KeySelector<class GTA_Menu_10>(Block_Vehicle, 4, UI_Menu_AntiGravity_Key);
				const auto Block_Weapon = GUI_BL_.GUI_Block(580, 430, 120, "Weapon");
				GUI_BL_.GUI_Checkbox(Block_Weapon, 1, "One hit kill", UI_Menu_OneHitKill);
				GUI_BL_.GUI_Checkbox(Block_Weapon, 2, "Bullet type", UI_Menu_BulletType);
				GUI_BL_.GUI_KeySelector<class GTA_Menu_11>(Block_Weapon, 2, UI_Menu_BulletType_Key);
				GUI_BL_.GUI_Slider<int, class GTA_Menu_12>(Block_Weapon, 3, "Type", 0, 99, UI_Menu_BulletType_Value);
				const auto Block_SpawnVehicle = GUI_BL_.GUI_Block(1010, 30, 550, "Spawn vehicle");
				GUI_BL_.GUI_Checkbox(Block_SpawnVehicle, 1, "Enabled", UI_Menu_SpawnVehicle);
				GUI_BL_.GUI_Button_Small(Block_SpawnVehicle, 1, UI_Menu_SpawnVehicle_Button);
				GUI_BL_.GUI_KeySelector<class GTA_Menu_13>(Block_SpawnVehicle, 1, UI_Menu_SpawnVehicle_Key);
				GUI_BL_.GUI_InputText<class GTA_Menu_14>(Block_SpawnVehicle, 2, UI_Menu_SpawnVehicle_String, "Custom vehicle ID");
				GUI_BL_.GUI_List(Block_SpawnVehicle, 3, { "Oppressor Mk2","P-996 LAZER","F-160 RAIJU","Vigilante","Deveste Eight","TM-02 KHANJALI","Kuruma","Savage","Seashark","Buzzard","X80 Proto","Krieger" }, UI_Menu_SpawnVehicle_List, 17);
				GUI_BL_.GUI_Tips({ Block_Weapon.x + 10,Block_Weapon.y }, 3, "Self research. XD");
				WindowSize = { 1440 ,610 };
			}
			else if (UI_Panel == 1)//Setting
			{
				const auto Block_About = GUI_BL_.GUI_Block(150, 30, 190, "About");
				GUI_BL_.GUI_Text(Block_About, 1, "TAHack", GUI_BL_.Global_Get_EasyGUI_Color());
				GUI_BL_.GUI_Text(Block_About, 1, "            for GTA5 (External)", { 150,150,150 });
				GUI_BL_.GUI_Text(Block_About, 2, "Release date: " + ReleaseDate + " (" + to_string(ReleaseVersion) + ")", { 150,150,150 });
				GUI_BL_.GUI_Text(Block_About, 3, "Cloud offsets date: " + Offsets_Date, { 150,150,150 });
				GUI_BL_.GUI_Text(Block_About, 4, "Online version: " + SupportGameVersion, { 150,150,150 });
				GUI_BL_.GUI_Text(Block_About, 5, "Author: https://github.com/Coslly", { 150,150,150 });
				BOOL Button_AuthorLink = false;
				GUI_BL_.GUI_Button_Small({ Block_About.x + 10,Block_About.y }, 5, Button_AuthorLink);
				if (Button_AuthorLink)System::Open_Website("https://github.com/Coslly");
				const auto Block_Menu = GUI_BL_.GUI_Block(150, 240, 340, "Menu");
				GUI_BL_.GUI_Text(Block_Menu, 1, "Menu key");
				GUI_BL_.GUI_KeySelector<class GTA_Menu_15>(Block_Menu, 1, UI_Settings_MenuKey);
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
				if (Module_GTA5)GUI_BL_.GUI_Tips({ Block_Menu.x + 10,Block_Menu.y }, 7, "GTA5.exe -> " + to_string(Module_GTA5));
				else GUI_BL_.GUI_Tips({ Block_Menu.x + 10,Block_Menu.y }, 7, "GTA5 not found!!!", 0, { 200,100,100 });
				GUI_BL_.GUI_Tips({ Block_Menu.x + 10,Block_Menu.y }, 8, "If it doesn't work you can download the latest version in the Release folder.");
				WindowSize = { 580 ,610 };
			}
			else if (UI_Panel == 2)//Legit
			{
				const auto Block_Hint = GUI_BL_.GUI_Block(150, 30, 150, "What is this?");
				GUI_BL_.GUI_Text({ Block_Hint.x - 30,Block_Hint.y }, 1, "Made for your account security.", { 200,100,100 });
				GUI_BL_.GUI_Text({ Block_Hint.x - 30,Block_Hint.y }, 2, "I can make sure this is 99.9% safe. You can rest assured.", { 200,100,100 });
				GUI_BL_.GUI_Text({ Block_Hint.x - 30,Block_Hint.y }, 3, "I use it all myself. XD", { 200,100,100 });
				GUI_BL_.GUI_Text({ Block_Hint.x - 30,Block_Hint.y }, 4, "When you enable it, Menu funtion will be disabled.");
				const auto Block_Menu = GUI_BL_.GUI_Block(150, 200, 210, "Legit");
				GUI_BL_.GUI_Checkbox(Block_Menu, 1, "Enabled", UI_Legit_Enabled, GUI_BL_.Global_Get_EasyGUI_Color());
				if (UI_Legit_Enabled)
				{
					GUI_BL_.GUI_Checkbox(Block_Menu, 2, "Health lock", UI_Legit_HealthLock);
					GUI_BL_.GUI_Button_Small(Block_Menu, 2, UI_Legit_Suicide);
					GUI_BL_.GUI_Checkbox(Block_Menu, 3, "Vehicle gravity", UI_Legit_VehicleGravity);
					GUI_BL_.GUI_Slider<float, class GTA_Menu_16>(Block_Menu, 4, "Value", 0, 50, UI_Legit_VehicleGravity_Value);
					GUI_BL_.GUI_Checkbox(Block_Menu, 5, "Vehicle Anti gravity", UI_Legit_VehicleAntiGravity);
					GUI_BL_.GUI_KeySelector<class GTA_Menu_17>(Block_Menu, 5, UI_Legit_VehicleAntiGravity_Key);
					GUI_BL_.GUI_Checkbox(Block_Menu, 6, "Teleport waypoint", UI_Legit_TeleportWaypoint, { 150,100,150 });
					GUI_BL_.GUI_KeySelector<class GTA_Menu_18>(Block_Menu, 6, UI_Legit_TeleportWaypoint_Key);
				}
				WindowSize = { 580 ,440 };
			}
			GUI_BL_.Draw_GUI();
			if (true)//按钮状态
			{
				if (UI_Settings_SaveConfig)//保存参数
				{
					System::Create_File("TAHack.cfg",
						to_string(UI_Menu_Health) + "\n" +
						to_string(UI_Menu_Health_Value) + "\n" +
						to_string(UI_Menu_Armor) + "\n" +
						to_string(UI_Menu_Armor_Value) + "\n" +
						to_string(UI_Menu_WantedLevel) + "\n" +
						to_string(UI_Menu_WantedLevel_Value) + "\n" +
						to_string(UI_Menu_MoveSpeed) + "\n" +
						to_string(UI_Menu_MoveSpeed_Value) + "\n" +
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
						to_string(UI_Menu_AntiAFK) + "\n" +
						to_string(UI_Menu_SpawnVehicle) + "\n" +
						to_string(UI_Menu_SpawnVehicle_Key) + "\n" +
						to_string(UI_Menu_BulletType_Key) + "\n"
					);
				}
				if (UI_Settings_StartGTA)System::Open_Website("steam://rungameid/271590");//启动 GTA5
				if (UI_Settings_GitHubRepositories)System::Open_Website("https://github.com/Coslly/TaHack.git");//打开Github项目页面
				if (UI_Settings_Restart)System::Self_Restart();//重启程序
				if (UI_Settings_CloseMenu)exit(0);//关闭程序
			}
		}
	}
}
void Thread_Memory() noexcept
{
	System::Log("Load Thread: Thread_Memory()");
	while (true)
	{
		if (Module_GTA5)//游戏运行时时运行
		{
			if (!UI_Legit_Enabled)
			{
				if (UI_Menu_Health)Health(true, (float)UI_Menu_Health_Value);//修改生命值
				if (UI_Menu_Armor)Armor(true, (float)UI_Menu_Armor_Value);//修改护甲值
				if (UI_Menu_WantedLevel)Wanted(true, UI_Menu_WantedLevel_Value);//修改通缉星
				if (UI_Menu_NeverWanted)Wanted(true, 0);//永远不被通缉
				if (UI_Menu_MoveSpeed)MoveSpeed(true, UI_Menu_MoveSpeed_Value);//修改跑步速度
				else MoveSpeed(true, 1);//默认速度
				if (UI_Menu_God)God(true, 1);//无敌
				else God(true, 0);
				if (UI_Menu_NoRagdoll)Ragdoll(true, 1);//无布娃娃
				else Ragdoll(true, 0);
				if (UI_Menu_DisableCollision && System::Get_Key(UI_Menu_DisableCollision_Key))Collision(true, 1);//无碰撞
				else Collision(true, 0);
				if (UI_Menu_OneHitKill && (System::Get_Key(VK_LBUTTON) || System::Get_Key(VK_RBUTTON)))WeaponDamage(true, 999999);//子弹一击毙命
				else WeaponDamage(true, 50);
				if (UI_Menu_Suicide)Health(true, 0);//修改生命值实现自杀
				if (UI_Menu_TeleportWaypoint && System::Get_Key_Onest(UI_Menu_TeleportWaypoint_Key) && WayPoint().x != 64000)//传送导航点
				{
					auto to_pos = WayPoint(); to_pos.z = -255;//-255 自动计算地面坐标
					Pos(true, to_pos);
					Beep(100, 30);
				}
				if (UI_Menu_Vehicle_God)VehicleGod(true, 1);//载具无敌
				else VehicleGod(true, 0);
				if (UI_Menu_Vehicle_Gravity)VehicleGravity(true, UI_Menu_Vehicle_Gravity_Value);//载具重力(加速度灵敏)
				else VehicleGravity(true, 9.8);//地球重力9.8 (初3知识XD)
				if (UI_Menu_Time)Time(true, { UI_Menu_Time_Hour ,UI_Menu_Time_Minute });//修改全局时间
				if (UI_Menu_AntiGravity && System::Get_Key(UI_Menu_AntiGravity_Key))VehicleGravity(true, UI_Menu_Vehicle_Gravity_Value * -1);//反重力 (快速爬升)
				if (UI_Menu_BulletType && (System::Get_Key(VK_LBUTTON) || System::Get_Key(VK_RBUTTON)) && (!UI_Menu_BulletType_Key || System::Get_Key(UI_Menu_BulletType_Key)))WeaponImpactType(true, UI_Menu_BulletType_Value);//修改子弹类型
				else WeaponImpactType(true, -1);//默认子弹类型
				if (UI_Menu_PublicSession)LoadSession(0);//切换公共战局
				else if (UI_Menu_InviteOnlySession)LoadSession(11);//切换邀请战局
				if ((UI_Menu_SpawnVehicle && System::Get_Key(UI_Menu_SpawnVehicle_Key)) || UI_Menu_SpawnVehicle_Button)
				{
					if (UI_Menu_SpawnVehicle_String != "")SpawnVehicle(UI_Menu_SpawnVehicle_String);//https://www.bbfas.com/vc/#google_vignette
					else if (UI_Menu_SpawnVehicle_List == 0)SpawnVehicle("oppressor2");
					else if (UI_Menu_SpawnVehicle_List == 1)SpawnVehicle("lazer");
					else if (UI_Menu_SpawnVehicle_List == 2)SpawnVehicle("raiju");
					else if (UI_Menu_SpawnVehicle_List == 3)SpawnVehicle("vigilante");
					else if (UI_Menu_SpawnVehicle_List == 4)SpawnVehicle("deveste");
					else if (UI_Menu_SpawnVehicle_List == 5)SpawnVehicle("khanjali");
					else if (UI_Menu_SpawnVehicle_List == 6)SpawnVehicle("kuruma2");
					else if (UI_Menu_SpawnVehicle_List == 7)SpawnVehicle("savage");
					else if (UI_Menu_SpawnVehicle_List == 8)SpawnVehicle("seashark");
					else if (UI_Menu_SpawnVehicle_List == 9)SpawnVehicle("buzzard");
					else if (UI_Menu_SpawnVehicle_List == 10)SpawnVehicle("prototipo");
					else if (UI_Menu_SpawnVehicle_List == 11)SpawnVehicle("krieger");
					Beep(100, 30);
				}
			}
			else {//Legit
				if (System::Sleep_Tick<class GTA5_LegitFunc_Sleep_Class_>(300) && UI_Legit_HealthLock)//锁定血量
				{
					Health(true, 300);//血量
					Armor(true, 50);//护甲
				}
				if (UI_Legit_Suicide)Health(true, 0);//自杀
				if (UI_Legit_VehicleAntiGravity && System::Get_Key(UI_Legit_VehicleAntiGravity_Key))VehicleGravity(true, UI_Menu_Vehicle_Gravity_Value * -1);//载具反重力
				else if (UI_Legit_VehicleGravity)VehicleGravity(true, UI_Menu_Vehicle_Gravity_Value);
				else VehicleGravity(true, 9.8);
				if (System::Get_Key(VK_LBUTTON) || System::Get_Key(VK_RBUTTON))WeaponDamage(true, 999999);//子弹一击毙命
				else WeaponDamage(true, 50);
				if (UI_Legit_TeleportWaypoint && System::Get_Key_Onest(UI_Legit_TeleportWaypoint_Key) && WayPoint().x != 64000)//传送导航点
				{
					auto to_pos = WayPoint(); to_pos.z = -255;//-255 自动计算地面坐标
					Pos(true, to_pos);
					Beep(100, 30);
				}
			}
		}
		if (MenuShowState)Sleep(10);//用于更好的接收消息
		else Sleep(100);//节省CPU占用
	}
}
void Thread_Misc() noexcept
{
	System::Log("Load Thread: Thread_Misc()");
	Window::Windows RenderWindow_Var;
	const HWND Render_Window_HWND_ = RenderWindow_Var.Create_RenderBlock_Alpha(GetSystemMetrics(SM_CXSCREEN), 30, "TAHack - Watermark");//创建绘制窗口
	Window::Render Render_Var; Render_Var.CreatePaint(Render_Window_HWND_, 0, 0, GetSystemMetrics(SM_CXSCREEN), 30);
	Reload(true);//初始化刷新内存变量
	while (true)
	{
		Reload();//刷新内存变量
		if (System::Sleep_Tick<class Funtion_AntiAFK_>(5000) && !UI_Legit_Enabled && UI_Menu_AntiAFK && Window::Get_WindowEnable(GTA_mem.Get_ProcessHWND())) { System::Mouse_Move(1, 0); Sleep(1); System::Mouse_Move(-1, 0); Sleep(1); }//防止挂机踢出
		if (UI_Settings_WaterMark)
		{
			RenderWindow_Var.Set_WindowPos(0, 0);
			if (System::Sleep_Tick<class Render_Window_Sleep_Class_>(200))
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
		if (UI_Settings_ShowConsoleWindow)ShowWindow(GetConsoleWindow(), true);//显示控制台窗口
		else ShowWindow(GetConsoleWindow(), false);//隐藏控制台窗口
		if (UI_Settings_LockGameWindow && !MenuShowState)SetForegroundWindow(GTA_HWND);//锁定GTA5窗口
		GUI_IO_ = GUI_BL_.Get_IO();
		if (!UI_Settings_CustomMenuColor)GUI_IO_.GUIColor = { GUI_IO_.GUIColor_Rainbow[3],GUI_IO_.GUIColor_Rainbow[4],GUI_IO_.GUIColor_Rainbow[5] };
		Sleep(5);//CPU
	}
}
int main() noexcept
{
	system("cls");
	System::Log("Load Thread: main()");
	System::Anti_click();
	Window::Hide_ConsoleWindow();
	System::URL_READ AutoUpdate = { "cache_update" };//自动更新系统
	if (AutoUpdate.StoreMem("https://github.com/Coslly/TaHack/blob/main/TAHack/TAHack/Main.cpp?raw=true"))//版本号更新检查
	{
		auto Version = AutoUpdate.Read(3); if (Version != "") { Version.erase(0, 27); Version.erase(Version.size() - 1, 1); }
		AutoUpdate.Release();
		if (Variable::string_int_(Version) > ReleaseVersion && Window::Message_Box("TAHack Update", "A new version has been released.\nDo you want to update now?\nIt may take tens of seconds.\n", MB_YESNO | MB_ICONASTERISK) == 6)
		{
			System::Open_Website("https://github.com/Coslly/TaHack/releases/download/Release/TAHack.exe"); Beep(100, 30); exit(0);
		}
	}
	if (FindWindow(0, L"TAHack ")) { MessageBox(0, L"Already running.", L"TAHack - Error", MB_ICONERROR); exit(0); }//防止多开程序
	if (!System::Judge_File("TAHack.cfg")) { System::Create_File("TAHack.cfg", Default_Config); System::Self_Restart(); }//创建默认参数文件
	thread Thread_Menu1 = thread(Thread_Menu);
	thread Thread_Misc1 = thread(Thread_Misc);
	thread Thread_Memory1 = thread(Thread_Memory);
	while (true)
	{
		if (System::Get_Key(VK_INSERT) && System::Get_Key(VK_DELETE)) { Beep(100, 30); exit(0); }//关闭程序快捷键
		static short MenuWindowAlpha = 0;//窗口透明度动画
		if (MenuShowState)MenuWindowAlpha = MenuWindowAlpha + UI_Settings_MenuColor_A / 8;
		else MenuWindowAlpha = MenuWindowAlpha - UI_Settings_MenuColor_A / 8;
		if (MenuWindowAlpha >= UI_Settings_MenuColor_A)MenuWindowAlpha = UI_Settings_MenuColor_A;
		else if (MenuWindowAlpha <= 0)MenuWindowAlpha = 0;
		GUI_BL_.Window_SetAlpha(MenuWindowAlpha);
		if (UI_Settings_CustomMenuColor)GUI_BL_.Global_Set_EasyGUI_Color(UI_Settings_MenuColor);
		if (!System::Key_Toggle<class Class_GTAMENU_KeyHold_>(UI_Settings_MenuKey)) { GUI_BL_.Window_Show(); MenuShowState = true; }
		else { if (MenuWindowAlpha == 0)GUI_BL_.Window_Hide(); MenuShowState = false; }
		Sleep(1);
	}
}
