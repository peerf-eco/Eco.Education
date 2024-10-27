LOCAL_PATH:= $(call my-dir)

#
# Eco.CalculatorC
#
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles
LOCAL_C_INCLUDES += $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../HeaderFiles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../SharedFiles
TARGET_PLATFORM := android-15
TARGET_OUT := $(LOCAL_PATH)/../../../../../BuildFiles/Android/$(TARGET_ARCH_ABI)/$(CONFIGURATION)
LOCAL_SRC_FILES := ../../../../../SourceFiles/CEcoCalculatorC.c \
../../../../../SourceFiles/CEcoCalculatorCFactory.c

ifeq ($(TARGET_LINK),0)

LOCAL_MODULE := lib4828F6552E4540E78121EBD220DC360E
LOCAL_CFLAGS := -std=c99 -DECO_LIB -DUGUID_UTILITY -DECO_ANDROID -D__ANDROID__

include $(BUILD_STATIC_LIBRARY)

else

LOCAL_MODULE := 4828F6552E4540E78121EBD220DC360E
LOCAL_CFLAGS := -std=c99 -DECO_DLL -DUGUID_UTILITY -DECO_ANDROID -D__ANDROID__

include $(BUILD_SHARED_LIBRARY)

endif