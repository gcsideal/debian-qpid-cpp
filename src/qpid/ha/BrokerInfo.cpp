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

#include "BrokerInfo.h"
#include "qpid/amqp_0_10/Codecs.h"
#include "qpid/Exception.h"
#include "qpid/log/Statement.h"
#include "qpid/framing/FieldTable.h"
#include "qpid/framing/FieldValue.h"
#include <iostream>
#include <iterator>
#include <sstream>

namespace qpid {
namespace ha {

namespace {
std::string SYSTEM_ID="system-id";
std::string HOST_NAME="host-name";
std::string PORT="port";
std::string STATUS="status";
}

using types::Uuid;
using types::Variant;
using framing::FieldTable;

BrokerInfo::BrokerInfo(const std::string& host, uint16_t port_, const types::Uuid& id) :
    hostName(host), port(port_), systemId(id)
{
    updateLogId();
}

void BrokerInfo::updateLogId() {
    std::ostringstream o;
    o << hostName << ":" << port;
    logId = o.str();
}

FieldTable BrokerInfo::asFieldTable() const {
    Variant::Map m = asMap();
    FieldTable ft;
    amqp_0_10::translate(m, ft);
    return ft;
}

Variant::Map BrokerInfo::asMap() const {
    Variant::Map m;
    m[SYSTEM_ID] = systemId;
    m[HOST_NAME] = hostName;
    m[PORT] = port;
    m[STATUS] = status;
    return m;
}

void BrokerInfo::assign(const FieldTable& ft) {
    Variant::Map m;
    amqp_0_10::translate(ft, m);
    assign(m);
}

namespace {
const Variant& get(const Variant::Map& m, const std::string& k) {
    Variant::Map::const_iterator i = m.find(k);
    if (i == m.end()) throw Exception(
        QPID_MSG("Missing field '" << k << "' in broker information"));
    return i->second;
}
}

void BrokerInfo::assign(const Variant::Map& m) {
    systemId = get(m, SYSTEM_ID).asUuid();
    hostName = get(m, HOST_NAME).asString();
    port = get(m, PORT).asUint16();
    status = BrokerStatus(get(m, STATUS).asUint8());
    updateLogId();
}

std::ostream& operator<<(std::ostream& o, const BrokerInfo& b) {
    return o << b.getHostName() << ":" << b.getPort() << "("
             << printable(b.getStatus()) << ")";
}

std::ostream& operator<<(std::ostream& o, const BrokerInfo::Set& infos) {
    std::ostream_iterator<BrokerInfo> out(o, " ");
    copy(infos.begin(), infos.end(), out);
    return o;
}

std::ostream& operator<<(std::ostream& o, const BrokerInfo::Map::value_type& v) {
    return o << v.second;
}

std::ostream& operator<<(std::ostream& o, const BrokerInfo::Map& infos) {
    std::ostream_iterator<BrokerInfo::Map::value_type> out(o, " ");
    copy(infos.begin(), infos.end(), out);
    return o;
}

}}
