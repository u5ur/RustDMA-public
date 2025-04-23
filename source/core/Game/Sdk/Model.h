#pragma once

class Model
{
public:

	static struct Transforms
	{
		Unity::Transform Head;
		Unity::Transform Eye;
		Unity::Transform Neck;
		Unity::Transform LShoulder;
		Unity::Transform RShoulder;
		Unity::Transform LForeArm;
		Unity::Transform RForeArm;
		Unity::Transform LHand;
		Unity::Transform RHand;
		Unity::Transform Spine;
		Unity::Transform Pelvis;
		Unity::Transform LHip;
		Unity::Transform RHip;
		Unity::Transform LKnee;
		Unity::Transform RKnee;
		Unity::Transform LFoot;
		Unity::Transform RFoot;
	};

	uint64_t Address = 0;
	uint64_t TransformsArray;
	Transforms transforms;
};