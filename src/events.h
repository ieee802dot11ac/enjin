/**
 * @file events.h
 * @author ieee 802.11ac
 * @brief Events, senders, and receivers.
 * @version 0.1
 * @date 2024-09-16
 * 
 */

#pragma once

#include <cstddef>
#include <stdint.h>

enum class EventType {
    kNoType
};

struct Event {
    EventType type;
    size_t id;
    void* data;
};

class EventRecv {
    EventRecv() {}
    virtual ~EventRecv() {}
    virtual void PushEvent(Event* e);
    virtual Event* PopEvent();
};

class EventSend {
    EventSend();
    virtual ~EventSend() {}
    virtual void Trigger(EventType type);
};
