#ifndef QPID_FRAMING_AMQP_ALLOPERATIONS_H
#define QPID_FRAMING_AMQP_ALLOPERATIONS_H
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


#include <sstream> 
#include "qpid/framing/ProtocolVersion.h"
#include "qpid/framing/amqp_structs.h"

namespace qpid {
namespace framing {

class AMQMethodBody;

class AMQP_AllOperations {
  public:
    class Invoker;              // Declared in AllInvoker

    virtual ~AMQP_AllOperations() {}

    virtual ProtocolVersion getVersion() const = 0;

    // Inner classes
    // ==================== class ConnectionHandler ====================
    class ConnectionHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        ConnectionHandler(){};
        virtual ~ConnectionHandler() {}
        // Protocol methods
    
    virtual void start(const FieldTable& serverProperties,
    const Array& mechanisms,
    const Array& locales) = 0;
    
    virtual void startOk(const FieldTable& clientProperties,
    const std::string& mechanism,
    const std::string& response,
    const std::string& locale) = 0;
    
    virtual void secure(const std::string& challenge) = 0;
    
    virtual void secureOk(const std::string& response) = 0;
    
    virtual void tune(uint16_t channelMax,
    uint16_t maxFrameSize,
    uint16_t heartbeatMin,
    uint16_t heartbeatMax) = 0;
    
    virtual void tuneOk(uint16_t channelMax,
    uint16_t maxFrameSize,
    uint16_t heartbeat) = 0;
    
    virtual void open(const std::string& virtualHost,
    const Array& capabilities,
    bool insist) = 0;
    
    virtual void openOk(const Array& knownHosts) = 0;
    
    virtual void redirect(const std::string& host,
    const Array& knownHosts) = 0;
    
    virtual void heartbeat(    ) = 0;
    
    virtual void close(uint16_t replyCode,
    const std::string& replyText) = 0;
    
    virtual void closeOk(    ) = 0;
    }; // class ConnectionHandler
    
    
    // ==================== class SessionHandler ====================
    class SessionHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        SessionHandler(){};
        virtual ~SessionHandler() {}
        // Protocol methods
    
    virtual void attach(const std::string& name,
    bool force) = 0;
    
    virtual void attached(const std::string& name) = 0;
    
    virtual void detach(const std::string& name) = 0;
    
    virtual void detached(const std::string& name,
    uint8_t code) = 0;
    
    virtual void requestTimeout(uint32_t timeout) = 0;
    
    virtual void timeout(uint32_t timeout) = 0;
    
    virtual void commandPoint(const SequenceNumber& commandId,
    uint64_t commandOffset) = 0;
    
    virtual void expected(const SequenceSet& commands,
    const Array& fragments) = 0;
    
    virtual void confirmed(const SequenceSet& commands,
    const Array& fragments) = 0;
    
    virtual void completed(const SequenceSet& commands,
    bool timelyReply) = 0;
    
    virtual void knownCompleted(const SequenceSet& commands) = 0;
    
    virtual void flush(bool expected,
    bool confirmed,
    bool completed) = 0;
    
    virtual void gap(const SequenceSet& commands) = 0;
    }; // class SessionHandler
    
    
    // ==================== class ExecutionHandler ====================
    class ExecutionHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        ExecutionHandler(){};
        virtual ~ExecutionHandler() {}
        // Protocol methods
    
    virtual void sync(    ) = 0;
    
    virtual void result(const SequenceNumber& commandId,
    const std::string& value) = 0;
    
    virtual void exception(uint16_t errorCode,
    const SequenceNumber& commandId,
    uint8_t classCode,
    uint8_t commandCode,
    uint8_t fieldIndex,
    const std::string& description,
    const FieldTable& errorInfo) = 0;
    }; // class ExecutionHandler
    
    
    // ==================== class MessageHandler ====================
    class MessageHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        MessageHandler(){};
        virtual ~MessageHandler() {}
        // Protocol methods
    
    virtual void accept(const SequenceSet& transfers) = 0;
    
    virtual void reject(const SequenceSet& transfers,
    uint16_t code,
    const std::string& text) = 0;
    
    virtual void release(const SequenceSet& transfers,
    bool setRedelivered) = 0;
    
    virtual MessageAcquireResult acquire(const SequenceSet& transfers) = 0;
    
    virtual MessageResumeResult resume(const std::string& destination,
    const std::string& resumeId) = 0;
    
    virtual void subscribe(const std::string& queue,
    const std::string& destination,
    uint8_t acceptMode,
    uint8_t acquireMode,
    bool exclusive,
    const std::string& resumeId,
    uint64_t resumeTtl,
    const FieldTable& arguments) = 0;
    
    virtual void cancel(const std::string& destination) = 0;
    
    virtual void setFlowMode(const std::string& destination,
    uint8_t flowMode) = 0;
    
    virtual void flow(const std::string& destination,
    uint8_t unit,
    uint32_t value) = 0;
    
    virtual void flush(const std::string& destination) = 0;
    
    virtual void stop(const std::string& destination) = 0;
    }; // class MessageHandler
    
    
    // ==================== class TxHandler ====================
    class TxHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        TxHandler(){};
        virtual ~TxHandler() {}
        // Protocol methods
    
    virtual void select(    ) = 0;
    
    virtual void commit(    ) = 0;
    
    virtual void rollback(    ) = 0;
    }; // class TxHandler
    
    
    // ==================== class DtxHandler ====================
    class DtxHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        DtxHandler(){};
        virtual ~DtxHandler() {}
        // Protocol methods
    
    virtual void select(    ) = 0;
    
    virtual XaResult start(const Xid& xid,
    bool join,
    bool resume) = 0;
    
    virtual XaResult end(const Xid& xid,
    bool fail,
    bool suspend) = 0;
    
    virtual XaResult commit(const Xid& xid,
    bool onePhase) = 0;
    
    virtual void forget(const Xid& xid) = 0;
    
    virtual DtxGetTimeoutResult getTimeout(const Xid& xid) = 0;
    
    virtual XaResult prepare(const Xid& xid) = 0;
    
    virtual DtxRecoverResult recover(    ) = 0;
    
    virtual XaResult rollback(const Xid& xid) = 0;
    
    virtual void setTimeout(const Xid& xid,
    uint32_t timeout) = 0;
    }; // class DtxHandler
    
    
    // ==================== class ExchangeHandler ====================
    class ExchangeHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        ExchangeHandler(){};
        virtual ~ExchangeHandler() {}
        // Protocol methods
    
    virtual void declare(const std::string& exchange,
    const std::string& type,
    const std::string& alternateExchange,
    bool passive,
    bool durable,
    bool autoDelete,
    const FieldTable& arguments) = 0;
    
    virtual void delete_(const std::string& exchange,
    bool ifUnused) = 0;
    
    virtual ExchangeQueryResult query(const std::string& name) = 0;
    
    virtual void bind(const std::string& queue,
    const std::string& exchange,
    const std::string& bindingKey,
    const FieldTable& arguments) = 0;
    
    virtual void unbind(const std::string& queue,
    const std::string& exchange,
    const std::string& bindingKey) = 0;
    
    virtual ExchangeBoundResult bound(const std::string& exchange,
    const std::string& queue,
    const std::string& bindingKey,
    const FieldTable& arguments) = 0;
    }; // class ExchangeHandler
    
    
    // ==================== class QueueHandler ====================
    class QueueHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        QueueHandler(){};
        virtual ~QueueHandler() {}
        // Protocol methods
    
    virtual void declare(const std::string& queue,
    const std::string& alternateExchange,
    bool passive,
    bool durable,
    bool exclusive,
    bool autoDelete,
    const FieldTable& arguments) = 0;
    
    virtual void delete_(const std::string& queue,
    bool ifUnused,
    bool ifEmpty) = 0;
    
    virtual void purge(const std::string& queue) = 0;
    
    virtual QueueQueryResult query(const std::string& queue) = 0;
    }; // class QueueHandler
    
    
    // ==================== class FileHandler ====================
    class FileHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        FileHandler(){};
        virtual ~FileHandler() {}
        // Protocol methods
    
    virtual void qos(uint32_t prefetchSize,
    uint16_t prefetchCount,
    bool global) = 0;
    
    virtual void qosOk(    ) = 0;
    
    virtual void consume(const std::string& queue,
    const std::string& consumerTag,
    bool noLocal,
    bool noAck,
    bool exclusive,
    bool nowait,
    const FieldTable& arguments) = 0;
    
    virtual void consumeOk(const std::string& consumerTag) = 0;
    
    virtual void cancel(const std::string& consumerTag) = 0;
    
    virtual void open(const std::string& identifier,
    uint64_t contentSize) = 0;
    
    virtual void openOk(uint64_t stagedSize) = 0;
    
    virtual void publish(const std::string& exchange,
    const std::string& routingKey,
    bool mandatory,
    bool immediate,
    const std::string& identifier) = 0;
    
    virtual void deliver(const std::string& consumerTag,
    uint64_t deliveryTag,
    bool redelivered,
    const std::string& exchange,
    const std::string& routingKey,
    const std::string& identifier) = 0;
    
    virtual void ack(uint64_t deliveryTag,
    bool multiple) = 0;
    
    virtual void reject(uint64_t deliveryTag,
    bool requeue) = 0;
    }; // class FileHandler
    
    
    // ==================== class StreamHandler ====================
    class StreamHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        StreamHandler(){};
        virtual ~StreamHandler() {}
        // Protocol methods
    
    virtual void qos(uint32_t prefetchSize,
    uint16_t prefetchCount,
    uint32_t consumeRate,
    bool global) = 0;
    
    virtual void qosOk(    ) = 0;
    
    virtual void consume(const std::string& queue,
    const std::string& consumerTag,
    bool noLocal,
    bool exclusive,
    bool nowait,
    const FieldTable& arguments) = 0;
    
    virtual void consumeOk(const std::string& consumerTag) = 0;
    
    virtual void cancel(const std::string& consumerTag) = 0;
    }; // class StreamHandler
    
    
    // ==================== class ClusterHandler ====================
    class ClusterHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        ClusterHandler(){};
        virtual ~ClusterHandler() {}
        // Protocol methods
    
    virtual void updateRequest(const std::string& url) = 0;
    
    virtual void updateOffer(uint64_t updatee) = 0;
    
    virtual void retractOffer(uint64_t updatee) = 0;
    
    virtual void initialStatus(uint32_t version,
    bool active,
    const Uuid& clusterId,
    uint8_t storeState,
    const Uuid& shutdownId,
    const std::string& firstConfig,
    const Array& urls) = 0;
    
    virtual void ready(const std::string& url) = 0;
    
    virtual void configChange(const std::string& members,
    const std::string& joined,
    const std::string& left) = 0;
    
    virtual void errorCheck(uint8_t type,
    const SequenceNumber& frameSeq) = 0;
    
    virtual void timerWakeup(const std::string& name) = 0;
    
    virtual void timerDrop(const std::string& name) = 0;
    
    virtual void shutdown(const Uuid& shutdownId) = 0;
    
    virtual void deliverToQueue(const std::string& queue,
    const std::string& message) = 0;
    
    virtual void clock(uint64_t time) = 0;
    }; // class ClusterHandler
    
    
    // ==================== class ClusterConnectionHandler ====================
    class ClusterConnectionHandler {
        // Constructors and destructors
      public:
        class Invoker;              // Declared in AllInvoker
          
        ClusterConnectionHandler(){};
        virtual ~ClusterConnectionHandler() {}
        // Protocol methods
    
    virtual void announce(const std::string& managementId,
    uint32_t ssf,
    const std::string& authid,
    bool nodict,
    const std::string& username,
    const std::string& initialFrames) = 0;
    
    virtual void deliverClose(    ) = 0;
    
    virtual void deliverDoOutput(uint32_t limit) = 0;
    
    virtual void abort(    ) = 0;
    
    virtual void shadowSetUser(const std::string& userId) = 0;
    
    virtual void shadowPrepare(const std::string& managementId) = 0;
    
    virtual void consumerState(const std::string& name,
    bool blocked,
    bool notifyEnabled,
    const SequenceNumber& position,
    uint32_t usedMsgCredit,
    uint32_t usedByteCredit,
    uint32_t deliveryCount) = 0;
    
    virtual void deliveryRecord(const std::string& queue,
    const SequenceNumber& position,
    const std::string& tag,
    const SequenceNumber& id,
    bool acquired,
    bool accepted,
    bool cancelled,
    bool completed,
    bool ended,
    bool windowing,
    bool enqueued,
    uint32_t credit) = 0;
    
    virtual void txStart(    ) = 0;
    
    virtual void txAccept(const SequenceSet& commands) = 0;
    
    virtual void txDequeue(const std::string& queue) = 0;
    
    virtual void txEnqueue(const std::string& queue) = 0;
    
    virtual void txPublish(const Array& queues,
    bool delivered) = 0;
    
    virtual void txEnd(    ) = 0;
    
    virtual void accumulatedAck(const SequenceSet& commands) = 0;
    
    virtual void outputTask(uint16_t channel,
    const std::string& name) = 0;
    
    virtual void dtxStart(const std::string& xid,
    bool ended,
    bool suspended,
    bool failed,
    bool expired) = 0;
    
    virtual void dtxEnd(    ) = 0;
    
    virtual void dtxAck(    ) = 0;
    
    virtual void dtxBufferRef(const std::string& xid,
    uint32_t index,
    bool suspended) = 0;
    
    virtual void dtxWorkRecord(const std::string& xid,
    bool prepared,
    uint32_t timeout) = 0;
    
    virtual void sessionState(const SequenceNumber& replayStart,
    const SequenceNumber& commandPoint,
    const SequenceSet& sentIncomplete,
    const SequenceNumber& expected,
    const SequenceNumber& received,
    const SequenceSet& unknownCompleted,
    const SequenceSet& receivedIncomplete,
    bool dtxSelected) = 0;
    
    virtual void shadowReady(uint64_t memberId,
    uint64_t connectionId,
    const std::string& managementId,
    const std::string& userName,
    const std::string& fragment,
    uint32_t sendMax) = 0;
    
    virtual void membership(const FieldTable& joiners,
    const FieldTable& members,
    const SequenceNumber& frameSeq) = 0;
    
    virtual void retractOffer(    ) = 0;
    
    virtual void queuePosition(const std::string& queue,
    const SequenceNumber& position) = 0;
    
    virtual void exchange(const std::string& encoded) = 0;
    
    virtual void addQueueListener(const std::string& queue,
    uint32_t consumer) = 0;
    
    virtual void managementSetupState(uint64_t objectNum,
    uint16_t bootSequence,
    const Uuid& brokerId,
    const std::string& vendor,
    const std::string& product,
    const std::string& instance) = 0;
    
    virtual void config(const std::string& encoded) = 0;
    
    virtual void queueFairshareState(const std::string& queue,
    uint8_t position,
    uint8_t count) = 0;
    
    virtual void queueObserverState(const std::string& queue,
    const std::string& observerId,
    const FieldTable& state) = 0;
    
    virtual void clock(uint64_t time) = 0;
    
    virtual void queueDequeueSincePurgeState(const std::string& queue,
    uint32_t dequeueSincePurge) = 0;
    
    virtual void internalState(const std::string& type,
    const std::string& name,
    const FieldTable& state) = 0;
    }; // class ClusterConnectionHandler
    
    

    // Method handler get methods

    virtual ConnectionHandler* getConnectionHandler() = 0;
    virtual SessionHandler* getSessionHandler() = 0;
    virtual ExecutionHandler* getExecutionHandler() = 0;
    virtual MessageHandler* getMessageHandler() = 0;
    virtual TxHandler* getTxHandler() = 0;
    virtual DtxHandler* getDtxHandler() = 0;
    virtual ExchangeHandler* getExchangeHandler() = 0;
    virtual QueueHandler* getQueueHandler() = 0;
    virtual FileHandler* getFileHandler() = 0;
    virtual StreamHandler* getStreamHandler() = 0;
    virtual ClusterHandler* getClusterHandler() = 0;
    virtual ClusterConnectionHandler* getClusterConnectionHandler() = 0;
}; /* class AMQP_AllOperations */
}}
#endif  /*!QPID_FRAMING_AMQP_ALLOPERATIONS_H*/
