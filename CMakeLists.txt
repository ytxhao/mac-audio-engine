cmake_minimum_required(VERSION 3.19)
project(mac_audio_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE on)
#set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa -framework AppKit -framework CoreData -framework Foundation -framework AVFoundation -framework AudioToolbox -framework AVFAudio -framework CoreAudio -framework CoreAudiokit")
#set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa -framework AppKit
# -framework CoreData
# -framework Foundation
# -framework AVFoundation
# -framework AudioToolbox
# -framework AVFAudio
# -framework CoreAudio
# -framework CoreAudiokit")

add_compile_options(-x objective-c++)
add_definitions(-DWEBRTC_POSIX -DWEBRTC_MAC)
include_directories(src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include)
set(PATH_TO_THIRDPARTY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libs)

set(SRC
        main.cpp
        src/api/task_queue/task_queue_base.cc
        src/api/task_queue/default_task_queue_factory_gcd.cc
        src/rtc_base/checks.cc
        src/rtc_base/event.cc
        src/rtc_base/logging.cc
        src/rtc_base/platform_thread.cc
        src/rtc_base/platform_thread_types.cc
        src/rtc_base/string_encode.cc
        src/rtc_base/string_to_number.cc
        src/rtc_base/string_utils.cc
        src/rtc_base/system_time.cc
        src/rtc_base/time_utils.cc
        src/rtc_base/task_queue.cc
        src/rtc_base/zero_memory.cc
        src/rtc_base/task_queue_gcd.cc
        src/rtc_base/task_utils/pending_task_safety_flag.cc
        src/rtc_base/strings/string_builder.cc
        src/rtc_base/synchronization/mutex.cc
        src/rtc_base/synchronization/yield.cc
        src/rtc_base/synchronization/yield_policy.cc
        src/rtc_base/synchronization/sequence_checker_internal.cc
        src/rtc_base/system/gcd_helpers.m
        src/rtc_base/system/warn_current_thread_is_deadlocked.cc
        src/modules/audio_device/audio_device_buffer.cc
        src/modules/audio_device/audio_device_generic.cc
        src/modules/audio_device/mac/audio_device_mac.cc
        src/modules/audio_device/mac/audio_mixer_manager_mac.cc
        )
add_executable(mac_audio_engine ${SRC})

#add_library(libabsl STATIC IMPORTED)
#set_property(TARGET absl PROPERTY IMPORTED_LOCATION ${PATH_TO_THIRDPARTY}/absl/libabsl.a)

target_link_libraries(mac_audio_engine
        ${PATH_TO_THIRDPARTY}/absl/libabsl.a
        ${PATH_TO_THIRDPARTY}/portaudio/libportaudio.a
        "-framework Cocoa"
        "-framework AppKit"
        "-framework CoreData"
        "-framework Foundation"
        "-framework AVFoundation"
        "-framework AudioToolbox"
        "-framework AVFAudio"
        "-framework CoreAudio"
        "-framework CoreAudiokit")