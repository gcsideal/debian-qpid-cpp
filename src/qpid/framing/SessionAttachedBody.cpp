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

///
/// This file was automatically generated from the AMQP specification.
/// Do not edit.
///


#include "qpid/framing/SessionAttachedBody.h"
#include "qpid/framing/Buffer.h"

using namespace qpid::framing;

void SessionAttachedBody::setName(const std::string& _name) {
    name = _name;
    flags |= (1 << 8);
    if (name.size() >= 65536) throw IllegalArgumentException("Value for name is too large");
}
const std::string& SessionAttachedBody::getName() const { return name; }
bool SessionAttachedBody::hasName() const { return flags & (1 << 8); }
void SessionAttachedBody::clearNameFlag() { flags &= ~(1 << 8); }

void SessionAttachedBody::encodeStructBody(Buffer& buffer) const
{
    buffer.putShort(flags);
    if (flags & (1 << 8))
        buffer.putMediumString(name);
}

void SessionAttachedBody::encode(Buffer& buffer) const
{
    encodeStructBody(buffer);
}

void SessionAttachedBody::decodeStructBody(Buffer& buffer, uint32_t /*size*/)
{
    flags = buffer.getShort();
    if (flags & (1 << 8))
        buffer.getMediumString(name);
}

void SessionAttachedBody::decode(Buffer& buffer, uint32_t /*size*/)
{
    decodeStructBody(buffer);
}

uint32_t SessionAttachedBody::bodySize() const
{
    uint32_t total = 0;
    total += 2;
    if (flags & (1 << 8))
        total += 2 + name.size();
    return total;
}

uint32_t SessionAttachedBody::encodedSize() const {
    uint32_t total = bodySize();
    return total;
}

void SessionAttachedBody::print(std::ostream& out) const
{
    out << "{SessionAttachedBody: ";
    if (flags & (1 << 8))
        out << "name=" << name << "; ";
    out << "}";
}
