﻿/**
 * Tencent is pleased to support the open source community by making Tars available.
 *
 * Copyright (C) 2016THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except 
 * in compliance with the License. You may obtain a copy of the License at
 *
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed 
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the 
 * specific language governing permissions and limitations under the License.
 */

#ifndef _Http2Imp_H_
#define _Http2Imp_H_

#include "servant/Application.h"
#include "util/tc_spin_lock.h"
#include "util/tc_http2.h"

/**
 *
 *
 */
class Http2Imp : public Servant
{
public:
    /**
     *
     */
    virtual ~Http2Imp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

    /**
     *
     */
    int doRequest(TarsCurrentPtr current, vector<char> &buffer);

    /**
     * close connection
     */    
    int doClose(TarsCurrentPtr current);

    static TC_Http2Server *getHttp2(uint32_t uid)
    {
        TC_LockT<TC_SpinLock> lock(_mutex);

        auto it = _http2.find(uid);

        if(it != _http2.end())
        {
            return it->second;
        }
        return NULL;
    }

    static void addHttp2(uint32_t uid, TC_Http2Server* ptr)
    {
        TC_LockT<TC_SpinLock> lock(_mutex);

        _http2[uid] = ptr;
    }

    static void delHttp2(uint32_t uid)
    {
        TC_LockT<TC_SpinLock> lock(_mutex);

        auto it = _http2.find(uid);

        if(it != _http2.end())
        {
            _http2.erase(it);
        }
    }
    
protected:

    static TC_SpinLock _mutex;

    static unordered_map<int32_t, TC_Http2Server*> _http2;
};
/////////////////////////////////////////////////////
#endif
