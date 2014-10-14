# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# keep a reference to the JNI source dir
TOP_LOCAL_PATH := $(call my-dir)

# initialise the makefile
include $(CLEAR_VARS)

# setup the source files
LOCAL_SRC_FILES := AndroidMain.cpp

LOCAL_SRC_FILES += math/Matrix.cpp

LOCAL_SRC_FILES += core/CoreEngine.cpp
LOCAL_SRC_FILES += core/TimeManager.cpp
LOCAL_SRC_FILES += core/SavedState.cpp

LOCAL_SRC_FILES += opengl/GLUtils.cpp
LOCAL_SRC_FILES += opengl/GLEngine.cpp
LOCAL_SRC_FILES += opengl/GLES2Renderer.cpp

LOCAL_SRC_FILES += render/Shader.cpp
LOCAL_SRC_FILES += render/Geometry.cpp
LOCAL_SRC_FILES += render/Model.cpp
LOCAL_SRC_FILES += render/Square.cpp
LOCAL_SRC_FILES += render/Camera.cpp
LOCAL_SRC_FILES += render/Environment.cpp

LOCAL_SRC_FILES += behavior/BehaviorEngine.cpp
LOCAL_SRC_FILES += behavior/BehavioralObject.cpp

LOCAL_SRC_FILES += component/Transform.cpp

# configure the module
LOCAL_PATH := $(TOP_LOCAL_PATH)
LOCAL_MODULE    := nativesandbox

# libs dependencies
LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := android_native_app_glue

# C++ features support (C++ exceptions, RTTI and STL classes)
# stlport_static and gnustl_static both provides the same features
# gnustl is under the GPLv3 license
APP_STL := stlport_static

# enable exceptions
LOCAL_CPP_FEATURES := rtti exceptions

# Version dependant configuration
ifeq ($(APP_OPTIM),release)
    # Release version optimisation : hide symbols
	LOCAL_CPPFLAGS += -fvisibility=hidden
	LOCAL_CFLAGS += -fvisibility=hidden
else
    # Enable Logs
    LOCAL_CPPFLAGS += -DLOGCAT
    LOCAL_CFLAGS += -DLOGCAT
endif


include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
