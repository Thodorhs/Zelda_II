#pragma once
#include <chrono>
class SystemClock final {
private:
	std::chrono::high_resolution_clock clock;
	static SystemClock singleton;
	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;
public:
	SystemClock();
	static auto Get(void) -> SystemClock& { return singleton; }
	uint64_t milli_secs(void) const;
	uint64_t micro_secs(void) const;
	uint64_t nano_secs(void) const;
	void Reset();
	float GetDeltaTime();

	void SetTimeScale(float t);
	float GetTimeScale();
	void Update();
};

uint64_t GetSystemTime(void);