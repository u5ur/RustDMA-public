#include "Unity.h"

namespace Unity {

	uint64_t Camera::GetMain()
	{
		uint64_t TypeInfo = mem.Read<uint64_t>(mem.BaseAddress + offsets::MainCamera);
		if (!TypeInfo) return 0;

		uint64_t StaticFields = mem.Read<uint64_t>(TypeInfo + 0xB8);
		if (!StaticFields) return 0;

		uint64_t Cameras = mem.Read<uint64_t>(StaticFields + offsets::MainCamera1);
		if (!Cameras) return 0;

		return mem.Read<uint64_t>(Cameras + 0x10);
	}

	Vector2 Camera::WorldToScreen(Vector3 world_pos)
	{
		Vector3 trans_vec{ this->ViewMatrix._14, this->ViewMatrix._24, this->ViewMatrix._34 };
		Vector3 right_vec{ this->ViewMatrix._11, this->ViewMatrix._21, this->ViewMatrix._31 };
		Vector3 up_vec{ this->ViewMatrix._12, this->ViewMatrix._22, this->ViewMatrix._32 };

		float w = trans_vec.Dot(world_pos) + this->ViewMatrix._44;
		if (w < 0.1f) return {};

		float y = up_vec.Dot(world_pos) + this->ViewMatrix._42;
		float x = right_vec.Dot(world_pos) + this->ViewMatrix._41;

		return Vector2((1920 / 2) * (1.f + x / w), (1080 / 2) * (1.f - y / w));
	}
}
