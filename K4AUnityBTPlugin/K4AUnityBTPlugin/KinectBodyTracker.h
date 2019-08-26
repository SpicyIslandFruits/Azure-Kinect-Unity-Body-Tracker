#pragma once
#include <thread>
#include <k4a/k4a.h>
#include <k4abt.h>

#define K4ABT_MAX_BODY 6

typedef void(*DebugLogFuncPtr)(const char*);

class KinectBodyTracker
{
public:

	typedef struct Body {
		k4abt_body_t body;
		k4a_float2_t calibratedJointPoints[K4ABT_JOINT_COUNT];
	} Body;

	void Start();
	void Stop();
	void SetDebugLogFunction(DebugLogFuncPtr fp);

	Body bodies[K4ABT_MAX_BODY];
	unsigned long* color = nullptr;
	uint64_t colorTimestamp;
	unsigned short* depth = nullptr;
	uint64_t depthTimestamp;
	unsigned short* transformedDepth = nullptr;
	uint64_t transformedDepthTimestamp;

private:
	void DebugLog(const char* message);

	k4a_device_t device;
	k4abt_tracker_t tracker;
	bool isRunning;
	std::thread workerThread;
	DebugLogFuncPtr debugPrintFunction = nullptr;
};

