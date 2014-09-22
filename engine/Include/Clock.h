#pragma once

class Clock
{
public:
		// Construct a clock
	Clock(float startTimeSeconds = 0.0f) :
		m_timeCycles(secondsToCycles(startTimeSeconds)),	
		m_timeScale(1.0f),	// default to unscaled
		m_isPaused(false)	// default to running
	{
	}

	// Call this when the game first starts up.
	static void init()
	{
		s_cyclesPerSecond = (float)5.0f;
	}

	// Return the current time in cycles. NOTE that we do not return absolute time measurements in floating points seconds,
	// because a 32-bit float dosen't have enough precision. See calcDeltaSeconds().
	unsigned long long getTimeCycles() const
	{
		return m_timeCycles;
	}

	// This function should be called once per frame with the real measured time in delta in seconds.
	void update(float dtRealSeconds)
	{
		if(!m_isPaused)
		{
			unsigned long long dtScaledCycles = secondsToCycles(dtRealSeconds * m_timeScale);
			m_timeCycles += dtScaledCycles;
		}
	}
	
	void setPaused(bool isPaused)
	{
		m_isPaused = isPaused;
	}

	bool isPaused() const
	{
		return m_isPaused;
	}
		
	void setTimeScale(float scale)
	{
		m_timeScale = scale;
	}

	float getTimeScale() const
	{
		return m_timeScale;
	}

	void singleStep()
	{
		if(m_isPaused)
		{
			// Add one ideal frame interval to scale it by our current time scale!
			unsigned long long dtScaledCycles = secondsToCycles((1.0f/30.0) * m_timeScale);
			m_timeCycles += dtScaledCycles;
		}
	}

private:
	unsigned long long m_timeCycles;	// 64 bit unsigned int
	float m_timeScale;					// 32 bit floating point
	bool m_isPaused;
	
	static float s_cyclesPerSecond;

	static inline unsigned long long secondsToCycles(float timeSeconds)
	{
		return (unsigned long long)(timeSeconds * s_cyclesPerSecond);
	}
	
	//	WARNING: Dangerous -- only use to convert small
	// durations into seconds
	static inline float cyclesToSeconds(float timeSeconds)
	{
		return (float)(timeSeconds / s_cyclesPerSecond);
	}
	
};
float Clock::s_cyclesPerSecond = 0.0f;
