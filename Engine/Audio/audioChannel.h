#pragma once

namespace FMOD
{
	class Channel;
}

namespace tech
{
	class AudioChannel
	{
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* channel) : m_channel{ channel } {}

		bool IsPlaying();
		void Stop();

		void SetPitch(float pitch);
		void SetVolume(float volume);
		float GetPtich();
		float GetVolume();

	private:
		FMOD::Channel* m_channel{ nullptr };
	};
}