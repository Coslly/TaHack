﻿#include "Head.h"
namespace GTA5_SDK//GTA5作弊开发助手
{
	HWND GTA_HWND = 0;
	System::Memory GTA_mem = { "GTA5.exe" };//GTA5 Memory
	uintptr_t Module_GTA5 = GTA_mem.Get_Module("GTA5.exe");//GTA5.exe ModuleAddress
	namespace GTA5_Offsets//内存偏移量
	{
		uintptr_t WorldPTR, GlobalPTR, LocalPlayer;//动态基址 (基本)
		const auto oWorldPTR = 0x2593320, oGlobalPTR = 0x2EF59A0;
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
		const auto oPosition = 0x50;
		const auto pCVehicle = 0xD10;
		const auto oVGravity = 0xC8C;
		const auto oImpactType = 0x20;
		const auto oImpactExplosion = 0x24;
		const auto oSessionSwitchType = 1575032;
		const auto oSessionSwitchState = 1574589;
	}
	using namespace GTA5_Offsets;
	namespace Base//基础内存
	{
		template<class Global_CLASS>
		void Set_GlobalValue(uintptr_t Index, Global_CLASS Value) noexcept//写入全局地址
		{
			const auto GlobalAddress = GTA_mem.Read<uintptr_t>(Module_GTA5 + oGlobalPTR + (8 * (Index >> 0x12 & 0x3F))) + (8 * (Index & 0x3FFFF));
			GTA_mem.Write<Global_CLASS>(GlobalAddress, Value);
		}
		//---------------------------------------------------------------------------------------------------
		float Health(BOOL Set = false, float SetValue = 0) noexcept//生命值
		{
			if (Set)GTA_mem.Write_Level<float>(LocalPlayer, { oHealth }, SetValue);
			return GTA_mem.Read_Level<float>(LocalPlayer, { oHealth });
		}
		float Armor(BOOL Set = false, float SetValue = 0) noexcept//护甲值
		{
			if (Set)GTA_mem.Write_Level<float>(LocalPlayer, { pedArmor }, SetValue);
			return GTA_mem.Read_Level<float>(LocalPlayer, { pedArmor });
		}
		int Wanted(BOOL Set = false, int SetValue = 0) noexcept//通缉等级 (星级)
		{
			if (SetValue < 0)SetValue = 0; else if (SetValue > 6)SetValue = 6;//防止过量崩溃
			if (Set)GTA_mem.Write_Level<int>(LocalPlayer, { pCPlayerInfo,oWanted }, SetValue);
			return GTA_mem.Read_Level<int>(LocalPlayer, { pCPlayerInfo,oWanted });
		}
		float MoveSpeed(BOOL Set = false, float SetValue = 1) noexcept//移动速度
		{
			if (Set)
			{
				GTA_mem.Write_Level<float>(LocalPlayer, { pCPlayerInfo,oRunSpeed }, SetValue);//跑步
				GTA_mem.Write_Level<float>(LocalPlayer, { pCPlayerInfo,oSwimSpeed }, SetValue);//游泳
			}
			return GTA_mem.Read_Level<float>(LocalPlayer, { pCPlayerInfo,oWanted });
		}
		BOOL God(BOOL Set = false, BOOL SetValue = 0) noexcept//无敌
		{
			if (Set)GTA_mem.Write_Level<BOOL>(LocalPlayer, { oGod }, SetValue);
			return GTA_mem.Read_Level<BOOL>(LocalPlayer, { oGod });
		}
		BOOL Ragdoll(BOOL Set = false, BOOL SetValue = 0) noexcept//布娃娃效果
		{
			if (Set)GTA_mem.Write_Level<BOOL>(LocalPlayer, { oRagdoll }, SetValue);
			return GTA_mem.Read_Level<BOOL>(LocalPlayer, { oRagdoll });
		}
		BOOL Collision(BOOL Set = false, BOOL SetValue = 0) noexcept//碰撞效果 (穿墙)
		{
			if (Set)
			{
				if (SetValue)
				{
					GTA_mem.Write_Level<float>(LocalPlayer, { 0x30,0x10,0x20,0x70,0x0,0x2c }, -1);
					GTA_mem.Write_Level<BOOL>(LocalPlayer, { oRagdoll }, 1);
				}
				else  GTA_mem.Write_Level<float>(LocalPlayer, { 0x30,0x10,0x20,0x70,0x0,0x2c }, 0.25);
			}
			return GTA_mem.Read_Level<float>(LocalPlayer, { 0x30,0x10,0x20,0x70,0x0,0x2c });
		}
		float WeaponDamage(BOOL Set = false, float SetValue = 50) noexcept//手持武器伤害
		{
			if (Set)GTA_mem.Write_Level<float>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oDamage }, SetValue);
			return GTA_mem.Read_Level<float>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oDamage });
		}
		int WeaponImpactType(BOOL Set = false, int SetValue = -1) noexcept//武器子弹类型
		{
			if (SetValue < -1)SetValue = -1; else if (SetValue > 99)SetValue = 99;//防止过量崩溃
			if (Set)
			{
				if (SetValue == -1)GTA_mem.Write_Level<int>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oImpactType }, 3);//默认状态
				else GTA_mem.Write_Level<int>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oImpactType }, 5);//特殊子弹状态 2-3-5
				GTA_mem.Write_Level<int>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oImpactExplosion }, SetValue);//子弹类型
			}
			return GTA_mem.Read_Level<int>(LocalPlayer, { pCPedWeaponManager,pCWeaponInfo,oImpactExplosion });
		}
		Variable::Vector3 WayPoint(BOOL Set = false, Variable::Vector3 SetValue = { 0,0,-255 }) noexcept//导航点 单值浮点64000代表无导航点
		{
			if (Set)GTA_mem.Write<Variable::Vector3>(Module_GTA5 + oWayPoint, SetValue);
			return GTA_mem.Read<Variable::Vector3>(Module_GTA5 + oWayPoint);
		}
		Variable::Vector3 Pos(BOOL Set = false, Variable::Vector3 SetValue = { 0,0,-255 }) noexcept//坐标
		{
			if (Set)
			{
				if (GTA_mem.Read_Level<BOOL>(LocalPlayer, { 0xE32 }))GTA_mem.Write_Level<Variable::Vector3>(LocalPlayer, { pCVehicle,pCNavigation,oPosition }, SetValue);//当人物在载具内
				else GTA_mem.Write_Level<Variable::Vector3>(LocalPlayer, { pCNavigation,oPosition }, SetValue);
			}
			return GTA_mem.Read_Level<Variable::Vector3>(LocalPlayer, { pCVehicle,pCNavigation,oPosition });
		}
		BOOL VehicleGod(BOOL Set = false, BOOL SetValue = 0) noexcept//载具无敌
		{
			if (Set)GTA_mem.Write_Level<BOOL>(LocalPlayer, { pCVehicle,oGod }, SetValue);
			return GTA_mem.Read_Level<BOOL>(LocalPlayer, { pCVehicle,oGod });
		}
		float VehicleGravity(BOOL Set = false, float SetValue = 9.8) noexcept//载具重力
		{
			if (Set)GTA_mem.Write_Level<float>(LocalPlayer, { pCVehicle,oVGravity }, SetValue);
			return GTA_mem.Read_Level<float>(LocalPlayer, { pCVehicle,oVGravity });
		}
		Variable::Vector2 Time(BOOL Set = false, Variable::Vector2 SetValue = { 0,0 }) noexcept//时间 (小时,分钟)
		{
			if (Set)GTA_mem.Write<Variable::Vector2>(Module_GTA5 + TimeADDR, SetValue);
			return GTA_mem.Read<Variable::Vector2>(Module_GTA5 + TimeADDR);
		}
		void LoadSession(int SessionID = 0) noexcept//切换战局
		{
			///  0, 公共战局
			///  1, 创建公共战局
			///  2, 私人帮会战局
			///  3, 帮会战局
			///  6, 私人好友战局
			///  9, 加入好友
			/// 10, 单人战局
			/// 11, 仅限邀请战局
			/// 12, 加入帮会伙伴
			Set_GlobalValue<int>(oSessionSwitchType, SessionID);
			Set_GlobalValue<int>(oSessionSwitchState, 1);
			Sleep(200);
			Set_GlobalValue<int>(oSessionSwitchState, 0);
		}
	}
	using namespace Base;
	BOOL Reload() noexcept//刷新偏移量和内存变量
	{
		if (System::Sleep_Tick<class GTA5_SDK_Address_Update_Sleep_Class_>(5000))
		{
			GTA_mem = { "GTA5.exe" };
			GTA_HWND = GTA_mem.Get_ProcessHWND();
			Module_GTA5 = GTA_mem.Get_Module("GTA5.exe");
			WorldPTR = GTA_mem.Read<uintptr_t>(Module_GTA5 + oWorldPTR), GlobalPTR = GTA_mem.Read<uintptr_t>(Module_GTA5 + oGlobalPTR);
			LocalPlayer = WorldPTR + pCPed;
		}
	}
}
using namespace GTA5_SDK;