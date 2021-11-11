#include <iostream>
#include <Foundation/Foundation.h>
#include "modules/audio_device/mac/audio_device_mac.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    NSLog(@"main in");

    auto *audioDeviceMac = new webrtc::AudioDeviceMac();
    audioDeviceMac->Init();

    NSLog(@"main out");
    return 0;
}
