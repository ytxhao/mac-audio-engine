#include <iostream>
#include <Foundation/Foundation.h>
#include "modules/audio_device/mac/audio_device_mac.h"
#include "modules/audio_device/audio_device_buffer.h"
#include "api/task_queue/default_task_queue_factory.h"
#include "modules/audio_device/audio_device_generic.h"
//#define NDEBUG
using namespace webrtc;

class AudioTransportCallback : public AudioTransport{
     int32_t RecordedDataIsAvailable(const void* audioSamples,
                                            const size_t nSamples,
                                            const size_t nBytesPerSample,
                                            const size_t nChannels,
                                            const uint32_t samplesPerSec,
                                            const uint32_t totalDelayMS,
                                            const int32_t clockDrift,
                                            const uint32_t currentMicLevel,
                                            const bool keyPressed,
                                            uint32_t& newMicLevel) {

     };  // NOLINT

    // Implementation has to setup safe values for all specified out parameters.
     int32_t NeedMorePlayData(const size_t nSamples,
                                     const size_t nBytesPerSample,
                                     const size_t nChannels,
                                     const uint32_t samplesPerSec,
                                     void* audioSamples,
                                     size_t& nSamplesOut,  // NOLINT
                                     int64_t* elapsed_time_ms,
                                     int64_t* ntp_time_ms) {

    }// NOLINT

    // Method to pull mixed render audio data from all active VoE channels.
    // The data will not be passed as reference for audio processing internally.
     void PullRenderData(int bits_per_sample,
                                int sample_rate,
                                size_t number_of_channels,
                                size_t number_of_frames,
                                void* audio_data,
                                int64_t* elapsed_time_ms,
                                int64_t* ntp_time_ms) {

     }
};
#define AUDIO_DEVICE_ID (0u)
int main() {
    std::cout << "Hello, World!" << std::endl;
    NSLog(@"main in");
    RTC_LOG(LS_VERBOSE) << "main test!";
    std::unique_ptr<webrtc::TaskQueueFactory> task_queue_factory_;
    task_queue_factory_ = webrtc::CreateDefaultTaskQueueFactory();
    webrtc::AudioDeviceBuffer audio_device_buffer_(task_queue_factory_.get());
    audio_device_buffer_.SetRecordingSampleRate(48000);
    audio_device_buffer_.SetRecordingChannels(2);
    audio_device_buffer_.SetPlayoutSampleRate(48000);
    audio_device_buffer_.SetPlayoutChannels(2);

    std::unique_ptr<AudioDeviceGeneric> audio_device_;
    audio_device_.reset(new AudioDeviceMac());
    audio_device_->AttachAudioBuffer(&audio_device_buffer_);
//--------------------
    AudioDeviceGeneric::InitStatus status = audio_device_->Init();
    if (status != AudioDeviceGeneric::InitStatus::OK) {
        RTC_LOG(LS_ERROR) << "Audio device initialization failed.";
        return -1;
    }
//--------------------
    audio_device_->SetPlayoutDevice(0);
//--------------------
    audio_device_->SetRecordingDevice(AUDIO_DEVICE_ID);
    audio_device_->InitSpeaker();
//--------------------
    {
        bool isAvailable = false;
        if (audio_device_->StereoPlayoutIsAvailable(isAvailable) == -1) {
            return -1;
        }
        RTC_LOG(INFO) << "output: " << isAvailable;
    }

//--------------------
    {
        bool enable = false;
        if (audio_device_->PlayoutIsInitialized()) {
            RTC_LOG(LERROR)
            << "unable to set stereo mode while playing side is initialized";
            return -1;
        }
        if (audio_device_->SetStereoPlayout(enable)) {
            RTC_LOG(WARNING) << "stereo playout is not supported";
            return -1;
        }
        int8_t nChannels(1);
        if (enable) {
            nChannels = 2;
        }
        audio_device_buffer_.SetPlayoutChannels(nChannels);
    }
//--------------------
    audio_device_->InitMicrophone();
//--------------------
    {
        bool isAvailable = false;
        if (audio_device_->StereoRecordingIsAvailable(isAvailable) == -1) {
            return -1;
        }
        RTC_LOG(INFO) << "output: " << isAvailable;
    }
//--------------------
    {
        bool enable = false;
        if (audio_device_->RecordingIsInitialized()) {
            RTC_LOG(WARNING)
            << "unable to set stereo mode after recording is initialized";
            return -1;
        }
        if (audio_device_->SetStereoRecording(enable) == -1) {
            if (enable) {
                RTC_LOG(WARNING) << "failed to enable stereo recording";
            }
            return -1;
        }
        int8_t nChannels(1);
        if (enable) {
            nChannels = 2;
        }
        audio_device_buffer_.SetRecordingChannels(nChannels);
    }

    auto *audioTransportCallback = new AudioTransportCallback();
    //-----------------
    {
        audio_device_buffer_.RegisterAudioCallback(audioTransportCallback);
    }
//-----------------
    {
        bool isAvailable = audio_device_->BuiltInAECIsAvailable();
        RTC_LOG(INFO) << "output: " << isAvailable;
    }
    //-----------
    {
        bool isAvailable = audio_device_->BuiltInAGCIsAvailable();
        RTC_LOG(INFO) << "output: " << isAvailable;
    }
    //----------------
    {
        bool isAvailable = audio_device_->BuiltInNSIsAvailable();
        RTC_LOG(INFO) << "output: " << isAvailable;
    }
    //----------
    {
        bool isAvailable = audio_device_->BuiltInAECIsAvailable();
        RTC_LOG(INFO) << "output: " << isAvailable;
    }

//    //----------
//    audio_device_->Playing();
//    //---
//    {
//        if (audio_device_->PlayoutIsInitialized()) {
//            return 0;
//        }
//        int32_t result = audio_device_->InitPlayout();
//        RTC_LOG(INFO) << "output: " << result;
//    }
//    //------------
//    {
//        audio_device_buffer_.StartPlayout();
//#if defined(WEBRTC_ANDROID)
//        audio_device_->SetAudioMode(audio_mode_);
//#endif // WEBRTC_ANDROID
//        int32_t result = audio_device_->StartPlayout();
//        RTC_LOG(INFO) << "output: " << result;
//    }

    {
        bool isAvailable = audio_device_->BuiltInAECIsAvailable();
        RTC_LOG(INFO) << "output: " << isAvailable;
    }
    {
        bool isAvailable = audio_device_->BuiltInAGCIsAvailable();
        RTC_LOG(INFO) << "output: " << isAvailable;
    }

    audio_device_->PlayoutIsInitialized();
    {
        if (audio_device_->RecordingIsInitialized()) {
            return 0;
        }
        int32_t result = audio_device_->InitRecording();
        RTC_LOG(INFO) << "output: " << result;
    }

    {
        audio_device_buffer_.StartRecording();
        int32_t result = audio_device_->StartRecording();
        RTC_LOG(INFO) << "output: " << result;
    }

    std::string cmd;
    bool isCancel = false;
    while (!isCancel)
    {

//        std::cout << "1.录制人声" << std::endl;
//        std::cout << "2.录制人声并播放音乐" << std::endl;
//        std::cout << "请输入:";
//        std::getline(std::cin, cmd);
        if (!std::cin.eof()) {
//            std::cout << "cmd:"<<cmd<<std::endl;
        } else {
            isCancel = true;
        }
    }
    NSLog(@"main out");
    return 0;
}
