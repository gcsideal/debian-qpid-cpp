/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
#ifndef _DtxManager_
#define _DtxManager_

#include <boost/ptr_container/ptr_map.hpp>
#include "qpid/broker/DtxBuffer.h"
#include "qpid/broker/DtxWorkRecord.h"
#include "qpid/broker/TransactionalStore.h"
#include "qpid/framing/amqp_types.h"
#include "qpid/framing/Xid.h"
#include "qpid/sys/Mutex.h"
#include "qpid/ptr_map.h"

namespace qpid {
namespace broker {

class DtxManager{
    typedef boost::ptr_map<std::string, DtxWorkRecord> WorkMap;

    struct DtxCleanup : public sys::TimerTask
    {
        DtxManager& mgr;
        const std::string& xid;

        DtxCleanup(uint32_t timeout, DtxManager& mgr, const std::string& xid);
        void fire();
    };

    WorkMap work;
    TransactionalStore* store;
    qpid::sys::Mutex lock;
    qpid::sys::Timer* timer;

    void remove(const std::string& xid);
    DtxWorkRecord* createWork(const std::string& xid);

public:
    DtxManager(sys::Timer&);
    ~DtxManager();
    void start(const std::string& xid, DtxBuffer::shared_ptr work);
    void join(const std::string& xid, DtxBuffer::shared_ptr work);
    void recover(const std::string& xid, std::auto_ptr<TPCTransactionContext> txn, DtxBuffer::shared_ptr work);
    bool prepare(const std::string& xid);
    bool commit(const std::string& xid, bool onePhase);
    void rollback(const std::string& xid);
    void setTimeout(const std::string& xid, uint32_t secs);
    uint32_t getTimeout(const std::string& xid);
    void timedout(const std::string& xid);
    void setStore(TransactionalStore* store);
    void setTimer(sys::Timer& t) { timer = &t; }

    // Used by cluster for replication.
    template<class F> void each(F f) const {
        for (WorkMap::const_iterator i = work.begin(); i != work.end(); ++i)
            f(*ptr_map_ptr(i));
    }
    DtxWorkRecord* getWork(const std::string& xid);
    bool exists(const std::string& xid);
    static std::string convert(const framing::Xid& xid);
    static framing::Xid convert(const std::string& xid);
};

}
}

#endif
