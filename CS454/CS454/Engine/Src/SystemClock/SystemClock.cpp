#include  "../../../Engine/Include/Util/SystemClock.h"

#include "SDL_timer.h"

SystemClock SystemClock::singleton;

uint64_t SystemClock::milli_secs(void) const {
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
uint64_t SystemClock::micro_secs(void) const {
	return std::chrono::duration_cast<std::chrono::microseconds>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
uint64_t SystemClock::nano_secs(void) const {
	return std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

SystemClock::SystemClock()
{
	Reset();
	mTimeScale = 1.0f;
    mElapsedTicks = 0;
    mDeltaTime = 0.0f;
}


void SystemClock::Reset()
{
	mStartTicks = SDL_GetTicks();
	
}

float SystemClock::GetDeltaTime()
{
	return mDeltaTime;
}

void SystemClock::SetTimeScale(float t)
{
	mTimeScale = t;
}

void SystemClock::Update()
{
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = mElapsedTicks * 0.001f;
}



uint64_t GetSystemTime(void) {
	return SystemClock::Get().milli_secs();
}
