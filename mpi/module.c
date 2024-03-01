/*
 * Copyright 2022-2023 SPACEMIT. All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file.
 *
 * @Author: David(qiang.fu@spacemit.com)
 * @Date: 2023-01-11 10:27:53
 * @LastEditTime: 2024-01-11 09:40:19
 * @Description: dlopen the video codec library dynamicly
 */

#define ENABLE_DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "module.h"
#include "v4l2_utils.h"
#include "log.h"

#include <linux/videodev2.h>

struct _MppModule {
    U8    so_path[MAX_PATH_LENGTH];
    void    *load_so;
};

#define FIND_PLUGIN(TYPE, type, name) \
S32 find_##type##_plugin(U8 *path) \
{ \
    if (0 == access("/usr/lib/lib"#name".so", F_OK)) \
    { \
        debug("yeah! we have "#name" plugin---------------"); \
        U8 *tmp = "/usr/lib/lib"#name".so"; \
        S32 len = strlen(tmp);  \
        memcpy(path, tmp, len); \
        path[len] = '\0';  \
        return 1; \
    } \
 \
    if (0 == access("/usr/local/lib/lib"#name".so", F_OK)) \
    { \
        debug("yeah! have "#name" plugin---------------"); \
        U8 *tmp = "/usr/local/lib/lib"#name".so"; \
        S32 len = strlen(tmp);  \
        memcpy(path, tmp, len); \
        path[len] = '\0';  \
        return 1; \
    } \
 \
    return 0; \
} \

FIND_PLUGIN(OPENH264, openh264, soft_openh264)
FIND_PLUGIN(SFOMX, sfomx, sfomxil_plugin)
FIND_PLUGIN(SFENC, sfenc, sfenc_plugin)
FIND_PLUGIN(SFDEC, sfdec, sfdec_plugin)
FIND_PLUGIN(FFMPEG, ffmpeg, ffmpegcodec)
FIND_PLUGIN(V4L2, v4l2, v4l2_standard_codec)
FIND_PLUGIN(FAKEDEC, fakedec, fake_dec_plugin)
FIND_PLUGIN(V4L2_LINLONV5V7, v4l2_linlonv5v7, v4l2_linlonv5v7_codec)
FIND_PLUGIN(K1_V2D, k1_v2d, v2d_plugin)
FIND_PLUGIN(K1_JPU, k1_jpu, jpu_plugin)

#define CHECK_LIBRARY(TYPE, type, name, path1, path2) \
S32 check_##type() \
{ \
    if ((0 == access("/usr/lib/lib"#name".so", F_OK)) || \
            (0 == access("/usr/local/lib/lib"#name".so", F_OK)) || \
            (0 == access("/usr/lib/riscv64-linux-gnu/lib"#name".so", F_OK)) || \
            (0 == access("/usr/lib/riscv64-linux-gnu/lib"#name".so.7", F_OK)) || \
            (0 == access(#path1"/lib"#name".so", F_OK)) || \
            (0 == access(#path2"/lib"#name".so", F_OK))) \
    { \
        debug("yeah! have "#type"---------------"); \
        return 1; \
    } \
\
    return 0; \
} \

CHECK_LIBRARY(SFOMX, sfomx, sf-omx-il, /, /)
CHECK_LIBRARY(SFENC, sfenc, sfenc, /, /)
CHECK_LIBRARY(SFDEC, sfdec, sfdec, /, /)
CHECK_LIBRARY(FFMPEG, ffmpeg, avcodec, /usr/lib/ffmpeg, /usr/local/lib/ffmpeg)
CHECK_LIBRARY(OPENH264, openh264, openh264, /usr/lib/x86_64-linux-gnu, /usr/local/lib/x86_64-linux-gnu)
CHECK_LIBRARY(FAKEDEC, fakedec, c, /, /)
CHECK_LIBRARY(K1_V2D, k1_v2d, v2d, /, /)
CHECK_LIBRARY(K1_JPU, k1_jpu, jpu, /, /)

#define CHECKCODEC_BY_TYPE(TYPE, type) \
{ \
    if(check_##type()) \
    { \
        if(find_##type##_plugin(module->so_path)) \
        { \
            debug("++++++++++ "#TYPE" (%s)", module->so_path); \
            module->load_so = dlopen(module->so_path, RTLD_LAZY | RTLD_LOCAL); \
            debug("++++++++++ open (%s) success !", module->so_path); \
        } \
        else \
        { \
            error("can not find "#type" plugin, please check!"); \
            free(module); \
            return NULL; \
        } \
    } \
    else \
    { \
        error("can not find "#type", please check!"); \
        free(module); \
        return NULL; \
    } \
} \

/**
 * @description: dlopen the video codec library by codec_type
 * @param {MppCodecType} codec_type : input, the codec need to be opened
 * @return {MppModule*} : the module context
 */
MppModule*  module_init(MppCodecType codec_type)
{
    debug("++++++++++++++++++++++++++++++++++ module init, codec type = %d", codec_type);
    MppModule *module = (MppModule*)malloc(sizeof(MppModule));

#if 0
    //for test
    U8 buffer[2000];
    getcwd(buffer, 2000);
    debug("the buffer is (%s)", buffer);
#endif

    if(CODEC_OPENH264 == codec_type)
    {
        CHECKCODEC_BY_TYPE(OPENH264, openh264);
    }
    else if(CODEC_FFMPEG == codec_type)
    {
        CHECKCODEC_BY_TYPE(FFMPEG, ffmpeg);
    }
    else if(CODEC_SFDEC == codec_type)
    {
        CHECKCODEC_BY_TYPE(SFDEC, sfdec);
    }
    else if(CODEC_SFENC == codec_type)
    {
        CHECKCODEC_BY_TYPE(SFENC, sfenc);
    }
    else if(CODEC_SFOMX == codec_type)
    {
        CHECKCODEC_BY_TYPE(SFOMX, sfomx);
    }
    else if(CODEC_V4L2 == codec_type)
    {
        CHECKCODEC_BY_TYPE(V4L2, v4l2);
    }
    else if(CODEC_FAKEDEC == codec_type)
    {
        CHECKCODEC_BY_TYPE(FAKEDEC, fakedec);
    }
    else if(CODEC_V4L2_LINLONV5V7 == codec_type)
    {
        CHECKCODEC_BY_TYPE(V4L2_LINLONV5V7, v4l2_linlonv5v7);
    }
    else if(CODEC_K1_V2D == codec_type)
    {
        CHECKCODEC_BY_TYPE(K1_V2D, k1_v2d);
    }
    else if(CODEC_K1_JPU == codec_type)
    {
        CHECKCODEC_BY_TYPE(K1_JPU, k1_v2d);
    }
    else
    {
        error("need auto detect load_so");
    }

    return module;
}

MppModule* module_auto_init() {
    MppModule *module_tmp = NULL;
    module_tmp = module_init(CODEC_V4L2);
    if(module_tmp) {
        debug("auto select V4L2 codec");
        return module_tmp;
    }

    module_tmp = module_init(CODEC_SFOMX);
        if(module_tmp) {
        debug("auto select starfice openmax codec");
        return module_tmp;
    }

    error("can not find suitable codec, please check!");
    return NULL;
}

/**
 * @description: close the module
 * @param {MppModule*} module : input, the module need to be closed
 * @return {*}
 */
void module_destory(MppModule *module)
{
    debug("+++++++++++++++++++++++++++++++++++++++++++++++++++ module destory");
    if (module->load_so)
    {
        dlclose(module->load_so);
        module->load_so = NULL;
    }

    free(module);
}

/**
 * @description: get the so path from the module
 * @param {MppModule*} module : the module opened
 * @return {void*} : the path string pointer
 */
void* module_get_so_path(MppModule *module)
{
    if(!module)
    {
        error("module is NULL, please check!");
        return NULL;
    }

    return module->load_so;
}