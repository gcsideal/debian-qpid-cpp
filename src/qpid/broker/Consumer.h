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
#ifndef _Consumer_
#define _Consumer_

#include "qpid/broker/Message.h"
#include "qpid/broker/QueuedMessage.h"
#include "qpid/broker/OwnershipToken.h"

namespace qpid {
namespace broker {

class Queue;
class QueueListeners;

/**
 * Base class for consumers which represent a subscription to a queue.
 */
class Consumer
{
    const bool acquires;
    // inListeners allows QueueListeners to efficiently track if this
    // instance is registered for notifications without having to
    // search its containers
    bool inListeners;
    // the name is generated by broker and is unique within broker scope.  It is not
    // provided or known by the remote Consumer.
    const std::string name;
 public:
    typedef boost::shared_ptr<Consumer> shared_ptr;

    Consumer(const std::string& _name, bool preAcquires = true)
      : acquires(preAcquires), inListeners(false), name(_name), position(0) {}
    virtual ~Consumer(){}

    bool preAcquires() const { return acquires; }
    const std::string& getName() const { return name; }

    /**@return the position of the last message seen by this consumer */
    virtual framing::SequenceNumber getPosition() const  { return position; }

    virtual void setPosition(framing::SequenceNumber pos) { position = pos; }

    virtual bool deliver(QueuedMessage& msg) = 0;
    virtual void notify() = 0;
    virtual bool filter(boost::intrusive_ptr<Message>) { return true; }
    virtual bool accept(boost::intrusive_ptr<Message>) { return true; }
    virtual OwnershipToken* getSession() = 0;
    virtual void cancel() = 0;

    /** Returns true if the browser wants acquired as well as
     * available messages.
     */
    virtual bool browseAcquired() const { return false; };

    /** Called when the peer has acknowledged receipt of the message.
     * Not to be confused with accept() above, which is asking if
     * this consumer will consume/browse the message.
     */
    virtual void acknowledged(const QueuedMessage&) = 0;

    /** Called if queue has been deleted, if true suppress the error message.
     * Used by HA ReplicatingSubscriptions where such errors are normal.
     */
    virtual bool hideDeletedError() { return false; }

  protected:
    framing::SequenceNumber position;

  private:
    friend class QueueListeners;
};

}}


#endif
