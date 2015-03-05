LOCAL_PATH:=$(call my-dir)
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)
$(call import-module.android/native_app_glue)
