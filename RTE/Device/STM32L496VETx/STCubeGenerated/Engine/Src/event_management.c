#include <stdlib.h>
#include <string.h>
#include "event_management.h"
#include "__event_management.h"

static eventQueue_t key_queue_for_key = {0}, key_queue_for_game= {0};

static void inital_queue (eventQueue_t *queue, rt_uint8_t size);
static EventQueueStatus pop(eventQueue_t queue, key_t *key);
static EventQueueStatus push(eventQueue_t queue, const key_t key);
static rt_bool_t empty(eventQueue_t queue);

static void initial_queue (eventQueue_t *queue, rt_uint8_t size) {
	queue->front = 0;
	queue->rear = 0;
	queue->size = size;
	queue->events = (key_t *)malloc(size * sizeof(key_t));
}

static EventQueueStatus pop(eventQueue_t queue, key_t *key) {
	if(queue.front == queue.rear) {
		key = RT_NULL;
		return Event_Queue_Empty;
	} else {
		memcpy(key, &queue.events[queue.front], sizeof(key_t));
		queue.front = (queue.front + 1) % queue.size;
	}
	return Event_Queue_EOK;
}

static EventQueueStatus push(eventQueue_t queue, const key_t key) {
	if ((queue.rear + 1) % queue.size == queue.front) {
		return Event_Queue_Full;
	} else {
		memcpy(&queue.events[queue.rear], &key, sizeof(key_t));
		queue.rear = (queue.rear + 1) % queue.size;
	}
	return Event_Queue_EOK;
}

static rt_bool_t empty(eventQueue_t queue) {
	return queue.front == queue.rear ? RT_TRUE : RT_FALSE;
}

EventQueueStatus pop_key_event_from_queue(key_t *key) {
	return pop(key_queue_for_game, key);
}

EventQueueStatus push_key_event_to_queue(const key_t key) {
	return push(key_queue_for_key, key);
}

void EventProcessEntry(void *param) {
	initial_queue(&key_queue_for_key, MAX_QUEUE_SIZE);
	initial_queue(&key_queue_for_game, MAX_QUEUE_SIZE);
	
	while(1) {
		if(empty(key_queue_for_key) == RT_FALSE) {
			
		}
		rt_thread_mdelay(50);
	}
}