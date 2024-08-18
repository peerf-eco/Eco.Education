LOCAL_PATH:= $(call my-dir)

#
# Eco.List1
#
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../HeaderFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../SharedFiles
TARGET_PLATFORM := android-15
TARGET_OUT := $(LOCAL_PATH)/../../../../../BuildFiles/Android/$(TARGET_ARCH_ABI)/$(CONFIGURATION)
LOCAL_SRC_FILES := ../../../../../SourceFiles/CEcoList1.c \
../../../../../SourceFiles/CEcoList1Factory.c

ifeq ($(TARGET_LINK),0)

LOCAL_MODULE := lib53884AFC93C448ECAA929C8D3A562281
LOCAL_CFLAGS := -std=c99 -DECO_LIB -DECO_ANDROID -DUGUID_UTILITY -D__ANDROID__

include $(BUILD_STATIC_LIBRARY)

else

LOCAL_MODULE := 53884AFC93C448ECAA929C8D3A562281
LOCAL_CFLAGS := -std=c99 -DECO_DLL -DECO_ANDROID -DUGUID_UTILITY -D__ANDROID__
LOCAL_LDLIBS := -latomic

include $(BUILD_SHARED_LIBRARY)

endif