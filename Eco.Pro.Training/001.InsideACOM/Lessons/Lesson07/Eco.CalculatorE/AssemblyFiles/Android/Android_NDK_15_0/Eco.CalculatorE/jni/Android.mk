LOCAL_PATH:= $(call my-dir)

#
# Eco.CalculatorE
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
LOCAL_SRC_FILES := ../../../../../SourceFiles/CEcoCalculatorE.c \
../../../../../SourceFiles/CEcoCalculatorEFactory.c

ifeq ($(TARGET_LINK),0)

LOCAL_MODULE := lib872FEF1DE3314B87AD44D1E7C232C2F0
LOCAL_CFLAGS := -std=c99 -DECO_LIB -DUGUID_UTILITY -DECO_ANDROID -D__ANDROID__

include $(BUILD_STATIC_LIBRARY)

else

LOCAL_MODULE := 872FEF1DE3314B87AD44D1E7C232C2F0
LOCAL_CFLAGS := -std=c99 -DECO_DLL -DUGUID_UTILITY -DECO_ANDROID -D__ANDROID__

include $(BUILD_SHARED_LIBRARY)

endif