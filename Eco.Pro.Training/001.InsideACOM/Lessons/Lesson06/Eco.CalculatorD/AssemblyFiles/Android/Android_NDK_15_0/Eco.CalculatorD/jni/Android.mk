LOCAL_PATH:= $(call my-dir)

#
# Eco.CalculatorD
#
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../HeaderFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../SharedFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../../Lesson02/Eco.CalculatorA/SharedFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../../../Lesson03/Eco.CalculatorB/SharedFiles
TARGET_PLATFORM := android-15
TARGET_OUT := $(LOCAL_PATH)/../../../../../BuildFiles/Android/$(TARGET_ARCH_ABI)/$(CONFIGURATION)
LOCAL_SRC_FILES := ../../../../../SourceFiles/CEcoCalculatorD.c \
../../../../../SourceFiles/CEcoCalculatorDFactory.c

ifeq ($(TARGET_LINK),0)

LOCAL_MODULE := lib3A8E44677E82475CB4A3719ED8397E61
LOCAL_CFLAGS := -std=c99 -DECO_LIB -DUGUID_UTILITY -DECO_ANDROID -D__ANDROID__

include $(BUILD_STATIC_LIBRARY)

else

LOCAL_MODULE := 3A8E44677E82475CB4A3719ED8397E61
LOCAL_CFLAGS := -std=c99 -DECO_DLL -DUGUID_UTILITY -DECO_ANDROID -D__ANDROID__

include $(BUILD_SHARED_LIBRARY)

endif