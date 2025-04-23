#pragma once
#include <Memory.h>
#include "Math.h"
#include "Offsets.h"

#define TEST_BITD(value, bit) ((value) & (1U << (bit)))

namespace Unity
{

#include "Enums.h"
#include "Structs.h"

	class Camera
	{
	public:

		uint64_t Address = 0;
		Vector3 Location = {};
		Matrix4x4 ViewMatrix = {};

		static uint64_t GetMain();

		Vector2 WorldToScreen(Vector3 world_pos);
	};

	class TransformAccess {
	public:
		uintptr_t addr;
		int index;
		operator bool() const { return addr != 0; }
	};

	class TRSX {
	public:
		Vector3 t;
	private:
		char pad_000C[4];
	public:
		Vector4 q;
		Vector3 s;
	private:
		char pad_0014[4];
	};

	class Transform 
	{
	public:

		static constexpr int MAX = 300;
		TRSX trs[MAX];
		int parents[MAX];

		uintptr_t addr{}, internal_addr{}, localTransforms{}, parentIndices{};
		TransformAccess access;

		void Update(VMMDLL_SCATTER_HANDLE handle)
		{
			if (!handle || !localTransforms || !parentIndices || access.index < 0 || access.index >= MAX) return;
			int count = access.index + 1;
			mem.AddScatterRead(handle, localTransforms, trs, count * sizeof(TRSX));
			mem.AddScatterRead(handle, parentIndices, parents, count * sizeof(int));
		}

		Vector3 GetPosition() 
		{
			if (access.index < 0 || access.index >= MAX) return Vector3();

			Vector3 worldPos = trs[access.index].t;
			int index = parents[access.index];
			int max = 0;

			while (index >= 0 && index < MAX) {
				if (max++ > 30) break;

				auto& parent = trs[index];

				worldPos = parent.q * worldPos;
				worldPos = worldPos * parent.s;
				worldPos = worldPos + parent.t;

				index = parents[index];
			}

			return worldPos;
		}
	};
}