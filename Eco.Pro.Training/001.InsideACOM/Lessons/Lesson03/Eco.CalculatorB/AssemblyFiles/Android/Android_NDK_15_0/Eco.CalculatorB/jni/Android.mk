LOCAL_PATH:= $(call my-dir)

#
# Eco.CalculatorB
#
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../HeaderFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../SharedFiles
TARGET_PLATFORM := android-15
TARGET_OUT := $(LOCAL_PATH)/../../../../../BuildFiles/Android/$(TARGET_ARCH_ABI)/$(CONFIGURATION)
LOCAL_SRC_FILES := ../../../../../SourceFiles/CEcoCalculatorB.c \
../../../../../SourceFiles/CEcoCalculatorBFactory.c

ifeq ($(TARGET_LINK),0)

LOCAL_MODULE := libAE202E543CE54550899603BD70C62565
LOCAL_CFLAGS := -std=c99 -DECO_LIB -DUGUID_UTILITY -DECO_ANDROID -D__ANDROID__

include $(BUILD_STATIC_LIBRARY)

else

LOCAL_MODULE := AE202E543CE54550899603BD70C62565
LOCAL_CFLAGS := -std=c99 -DECO_DLL -DUGUID_UTILITY -DECO_ANDROID -D__ANDROID__

include $(BUILD_SHARED_LIBRARY)

endif