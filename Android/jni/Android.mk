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
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := PlatformCore-Android-Shared
LOCAL_SRC_FILES := Sources/ILData.cpp Sources/ILHash.cpp Sources/ILLinkedList.cpp Sources/ILList.cpp Sources/ILMap.cpp Sources/ILMessage.cpp Sources/ILMessageHub.cpp Sources/ILNumber.cpp Sources/ILObject.cpp Sources/ILReleasePool.cpp Sources/ILReleasePoolDelegate.cpp Sources/ILRunLoop.cpp Sources/ILSet.cpp Sources/ILSource.cpp Sources/ILString.cpp Sources/ILThreadTarget.cpp Sources/ILTime.cpp Sources/ILTimer.cpp

include $(BUILD_SHARED_LIBRARY)


# include $(CLEAR_VARS)
# 
# LOCAL_MODULE    := PlatformCore-Android-Static
# LOCAL_SRC_FILES := Sources/ILData.cpp Sources/ILHash.cpp Sources/ILLinkedList.cpp Sources/ILList.cpp Sources/ILMap.cpp Sources/ILMessage.cpp Sources/ILMessageHub.cpp Sources/ILNumber.cpp Sources/ILObject.cpp Sources/ILReleasePool.cpp Sources/ILReleasePoolDelegate.cpp Sources/ILRunLoop.cpp Sources/ILSet.cpp Sources/ILSource.cpp Sources/ILString.cpp Sources/ILThreadTarget.cpp Sources/ILTime.cpp Sources/ILTimer.cpp
# 
# include $(BUILD_STATIC_LIBRARY)
