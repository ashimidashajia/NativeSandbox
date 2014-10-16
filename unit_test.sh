#!/bin/sh

# assume we are int the project's root folder 

# build the application
ndk-build -C app/src/main/


# copy built libraries into the device
adb push app/src/main/libs/armeabi-v7a/libnativesandbox.so /data/local/tmp/
adb push app/src/main/libs/armeabi-v7a/nativesandbox_unittest /data/local/tmp/

# launch the executable unit test
adb shell "LD_LIBRARY_PATH=/data/local/tmp /data/local/tmp/nativesandbox_unittest"
