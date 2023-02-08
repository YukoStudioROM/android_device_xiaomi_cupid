/*
 * Copyright (C) 2023 Paranoid Android
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aidl/vendor/aospa/power/BnPowerFeature.h>
#include <android-base/file.h>
#include <android-base/logging.h>
#include <sys/ioctl.h>

#include "xiaomi_touch.h"

#define TOUCH_DEV_PATH "/dev/xiaomi-touch"
#define TOUCH_ID 0
#define TOUCH_MAGIC 'T'
#define TOUCH_IOC_SET_CUR_VALUE _IO(TOUCH_MAGIC, SET_CUR_VALUE)
#define TOUCH_IOC_GET_CUR_VALUE _IO(TOUCH_MAGIC, GET_CUR_VALUE)

namespace aidl {
namespace vendor {
namespace aospa {
namespace power {

bool setDeviceSpecificFeature(Feature feature, bool enabled) {
    switch (feature) {
        case Feature::DOUBLE_TAP: {
            int fd = open(TOUCH_DEV_PATH, O_RDWR);
            if (fd == -1) {
                LOG(WARNING) << "DT2W won't work because can't open xiaomi-touch device path";
                return false;
            }
            int buf[MAX_BUF_SIZE] = {TOUCH_ID, Touch_Doubletap_Mode, enabled ? 1 : 0};
            ioctl(fd, TOUCH_IOC_SET_CUR_VALUE, &buf);
            close(fd);
        }
            return true;
        default:
            return false;
    }
}

}  // namespace power
}  // namespace aospa
}  // namespace vendor
}  // namespace aidl
