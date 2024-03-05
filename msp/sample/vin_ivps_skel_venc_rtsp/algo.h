/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#pragma once

#include "ax_global_type.h"

typedef struct _SKEL_RECT_T {
    AX_F32 fX;
    AX_F32 fY;
    AX_F32 fW;
    AX_F32 fH;
} SKEL_RECT_T;

typedef struct _SKEL_OBJECT_ITEM_T {
    SKEL_RECT_T stRect;
} SKEL_OBJECT_ITEM_T;

typedef struct _SKEL_RESULT_T {
    AX_U32 nObjectSize;
    AX_U32 nWidth;
    AX_U32 nHeight;
    SKEL_OBJECT_ITEM_T *pstObjectItems;
} SKEL_RESULT_T;