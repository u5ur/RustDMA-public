#pragma once
#include <Memory.h>
#include "sdk.h"

static Unity::Camera Camera;
static std::vector<BasePlayer> Players;
static std::mutex playersMutex;

static std::vector<BasePlayer> GetPlayers(VMMDLL_SCATTER_HANDLE handle)
{
	auto PlayerList = BasePlayer::GetPlayerList();
	if (!PlayerList) return {};

	auto Size = mem.Read<uint32_t>(PlayerList + 0x10);
	if (Size <= 0 || Size >= 10000) return {};

	auto List = mem.Read<uint64_t>(PlayerList + 0x18);
	if (!List) return {};

	std::vector<BasePlayer> Players(Size);
	for (int i = 0; i < Size; i++)
	{
		if (!List) continue;
		if (i == 0)  Players[i].IsLocalPlayer = true;
		mem.AddScatterRead(handle, List + (0x20 + (i * sizeof(uint64_t))), &Players[i].Address, sizeof(uint64_t));
	}
	mem.ExecuteScatterRead(handle);

	for (auto& player : Players)
	{
		if (!player.Address) continue;
		mem.AddScatterRead(handle, player.Address + offsets::DisplayName, &player.DisplayNamePtr, sizeof(uint64_t));
		mem.AddScatterRead(handle, player.Address + 0xC8, &player.model.Address, sizeof(uint64_t));
	}
	mem.ExecuteScatterRead(handle);

	for (auto& player : Players)
	{
		if (!player.model.Address) continue;
		mem.AddScatterRead(handle, player.model.Address + 0x50, &player.model.TransformsArray, sizeof(uint64_t));
		mem.AddScatterRead(handle, player.DisplayNamePtr, &player.DisplayName, sizeof(Unity::String));
	}
	mem.ExecuteScatterRead(handle);

	int BoneIndicies[] = { 47, 49, 46, 24, 55, 25, 56, 26, 57, 22, 19, 1, 13, 2, 14, 3, 15 };

	for (auto& player : Players)
	{
		if (!player.model.TransformsArray) continue;

		for (int i = 0; i < sizeof(Model::Transforms) / sizeof(Unity::Transform); i++)
		{
			Unity::Transform* transform = &((Unity::Transform*)&player.model.transforms)[i];
			mem.AddScatterRead(handle, player.model.TransformsArray + 0x20 + (BoneIndicies[i] * 0x8), &transform->addr, sizeof(uint64_t));
		}
	}
	mem.ExecuteScatterRead(handle);

	for (auto& player : Players)
	{
		if (!player.model.TransformsArray) continue;

		for (int i = 0; i < sizeof(Model::Transforms) / sizeof(Unity::Transform); i++)
		{
			Unity::Transform* transform = &((Unity::Transform*)&player.model.transforms)[i];
			mem.AddScatterRead(handle, transform->addr + 0x10, &transform->internal_addr, sizeof(uint64_t));
		}
	}
	mem.ExecuteScatterRead(handle);

	for (auto& player : Players)
	{
		for (int i = 0; i < sizeof(Model::Transforms) / sizeof(Unity::Transform); i++)
		{
			Unity::Transform* transform = &((Unity::Transform*)&player.model.transforms)[i];
			mem.AddScatterRead(handle, transform->internal_addr + 0x38, &transform->access, sizeof(Unity::TransformAccess));
		}
	}
	mem.ExecuteScatterRead(handle);

	for (auto& player : Players)
	{
		for (int i = 0; i < sizeof(Model::Transforms) / sizeof(Unity::Transform); i++)
		{
			Unity::Transform* transform = &((Unity::Transform*)&player.model.transforms)[i];
			mem.AddScatterRead(handle, transform->access.addr + 0x18, &transform->localTransforms, sizeof(uint64_t));
			mem.AddScatterRead(handle, transform->access.addr + 0x20, &transform->parentIndices, sizeof(uint64_t));
		}
	}
	mem.ExecuteScatterRead(handle);

	return Players;
}

static void UpdateLoop()
{
	static auto handle = mem.CreateScatterHandle();

	auto LastUpdate = std::chrono::steady_clock::now();
	std::vector<BasePlayer> CachedPlayers;

	while (true)
	{
		auto now = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(now - LastUpdate).count() >= 1)
		{
			Camera.Address = Unity::Camera::GetMain();
			CachedPlayers = GetPlayers(handle);
			LastUpdate = now;
		}

		Vector3 TempLocation;
		Matrix4x4 TempView;
		mem.AddScatterRead(handle, Camera.Address + 0x454, &TempLocation, sizeof(Vector3));
		mem.AddScatterRead(handle, Camera.Address + 0x30C, &TempView, sizeof(Matrix4x4));

		for (auto& player : CachedPlayers)
		{
			for (int i = 0; i < sizeof(Model::Transforms) / sizeof(Unity::Transform); i++)
			{
				Unity::Transform* transform = &((Unity::Transform*)&player.model.transforms)[i];
				transform->Update(handle);
			}
		}

		mem.ExecuteScatterRead(handle);

		{
			std::lock_guard<std::mutex> lock(playersMutex);
			Players = CachedPlayers;
			Camera.Location = TempLocation;
			Camera.ViewMatrix = TempView;
		}

		Sleep(1);
	}

	mem.CloseScatterHandle(handle);
}

