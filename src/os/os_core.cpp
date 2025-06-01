#include "os_core.h"
#include <os/os_inc.h>
#include <string.h>

internal struct
{
  OS_Event events[OS_EVENT_QUEUE_CAPACITY];
  size_t head;
  size_t tail;
} g_event_queue = {{}, 0, 0};

OS_Event *_os_new_event()
{
  OS_Event* event = g_event_queue.events + g_event_queue.head;
  g_event_queue.head = (g_event_queue.head + 1) % OS_EVENT_QUEUE_CAPACITY;
  ENGINE_ASSERT(g_event_queue.head != g_event_queue.tail);
  memset(event, 0, sizeof(OS_Event));
  return event;
}

//void os_event_hook(OS_Handle& window) => os specifc

bool os_next_event(OS_Event *event)
{
  memset(event, 0, sizeof(OS_Event));

  if (g_event_queue.head != g_event_queue.tail) {
    *event = g_event_queue.events[g_event_queue.tail];
    g_event_queue.tail = (g_event_queue.tail + 1) % OS_EVENT_QUEUE_CAPACITY;
  }

  return event->type != OS_Event_None;
}

void os_event_reset(OS_Event *event)
{
  // in case the event has heap allocated data in it
  memset(event, 0, sizeof(OS_Event));
}
