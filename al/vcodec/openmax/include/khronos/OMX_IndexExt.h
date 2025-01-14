/*
 * Copyright (c) 2010 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/** @file OMX_IndexExt.h - OpenMax IL version 1.1.2
 * The OMX_IndexExt header file contains extensions to the definitions
 * for both applications and components .
 */

#ifndef OMX_IndexExt_h
#define OMX_IndexExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully
 */
#include <OMX_Index.h>

/** Khronos standard extension indices.

This enum lists the current Khronos extension indices to OpenMAX IL.
*/
typedef enum OMX_INDEXEXTTYPE {

  /* Component parameters and configurations */
  OMX_IndexExtComponentStartUnused = OMX_IndexKhronosExtensions + 0x00100000,
  OMX_IndexConfigCallbackRequest, /**< reference: OMX_CONFIG_CALLBACKREQUESTTYPE
                                   */
  OMX_IndexConfigCommitMode,      /**< reference: OMX_CONFIG_COMMITMODETYPE */
  OMX_IndexConfigCommit,          /**< reference: OMX_CONFIG_COMMITTYPE */

  /* Port parameters and configurations */
  OMX_IndexExtPortStartUnused = OMX_IndexKhronosExtensions + 0x00200000,

  /* Audio parameters and configurations */
  OMX_IndexExtAudioStartUnused = OMX_IndexKhronosExtensions + 0x00400000,
  OMX_IndexParamAudioAndroidAc3, /**< reference: OMX_AUDIO_PARAM_ANDROID_AC3TYPE
                                  */
  OMX_IndexParamAudioAndroidOpus,            /**< reference:
                                                OMX_AUDIO_PARAM_ANDROID_OPUSTYPE */
  OMX_IndexParamAudioAndroidAacPresentation, /**< reference:
                                                OMX_AUDIO_PARAM_ANDROID_AACPRESENTATIONTYPE
                                              */
  OMX_IndexParamAudioAndroidEac3,            /**< reference:
                                                OMX_AUDIO_PARAM_ANDROID_EAC3TYPE */
  OMX_IndexParamAudioProfileQuerySupported,  /**< reference:
                                                OMX_AUDIO_PARAM_ANDROID_PROFILETYPE
                                              */

  /* Image parameters and configurations */
  OMX_IndexExtImageStartUnused = OMX_IndexKhronosExtensions + 0x00500000,

  /* Video parameters and configurations */
  OMX_IndexExtVideoStartUnused = OMX_IndexKhronosExtensions + 0x00600000,
  OMX_IndexParamNalStreamFormatSupported, /**< reference:
                                             OMX_NALSTREAMFORMATTYPE */
  OMX_IndexParamNalStreamFormat, /**< reference: OMX_NALSTREAMFORMATTYPE */
  OMX_IndexParamNalStreamFormatSelect, /**< reference: OMX_NALSTREAMFORMATTYPE
                                        */
  OMX_IndexParamVideoVp8, /**< reference: OMX_VIDEO_PARAM_VP8TYPE */
  OMX_IndexConfigVideoVp8ReferenceFrame,     /**< reference:
                                                OMX_VIDEO_VP8REFERENCEFRAMETYPE */
  OMX_IndexConfigVideoVp8ReferenceFrameType, /**< reference:
                                                OMX_VIDEO_VP8REFERENCEFRAMEINFOTYPE
                                              */
  OMX_IndexParamVideoAndroidVp8Encoder,      /**< reference:
                                                OMX_VIDEO_PARAM_ANDROID_VP8ENCODERTYPE
                                              */
  OMX_IndexParamVideoHevc,     /**< reference: OMX_VIDEO_PARAM_HEVCTYPE */
  OMX_IndexParamSliceSegments, /**< reference: OMX_VIDEO_SLICESEGMENTSTYPE */
  OMX_IndexConfigAndroidIntraRefresh,          /**< reference:
                                                  OMX_VIDEO_CONFIG_ANDROID_INTRAREFRESHTYPE
                                                */
  OMX_IndexParamAndroidVideoTemporalLayering,  /**< reference:
                                                  OMX_VIDEO_PARAM_ANDROID_TEMPORALLAYERINGTYPE
                                                */
  OMX_IndexConfigAndroidVideoTemporalLayering, /**< reference:
                                                  OMX_VIDEO_CONFIG_ANDROID_TEMPORALLAYERINGTYPE
                                                */

  /* Image & Video common configurations */
  OMX_IndexExtCommonStartUnused = OMX_IndexKhronosExtensions + 0x00700000,

  /* Other configurations */
  OMX_IndexExtOtherStartUnused = OMX_IndexKhronosExtensions + 0x00800000,
  OMX_IndexConfigAutoFramerateConversion, /**< reference: OMX_CONFIG_BOOLEANTYPE
                                           */
  OMX_IndexConfigPriority,                /**< reference: OMX_PARAM_U32TYPE */
  OMX_IndexConfigOperatingRate, /**< reference: OMX_PARAM_U32TYPE in Q16 format
                                   for video and in Hz for audio */
  OMX_IndexParamConsumerUsageBits, /**< reference: OMX_PARAM_U32TYPE */

  /* Time configurations */
  OMX_IndexExtTimeStartUnused = OMX_IndexKhronosExtensions + 0x00900000,

  OMX_IndexExtMax = 0x7FFFFFFF
} OMX_INDEXEXTTYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_IndexExt_h */
/* File EOF */
