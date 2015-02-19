/*
 * Licensed under the MIT License (MIT)
 *
 * Copyright (c) 2013 AudioScience Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * system_message_queue.cpp
 *
 * System message queue implementation, which is called by System modules to queue packets.
 */

#include <Windows.h>
#include "system_message_queue.h"

namespace avdecc_lib
{
    system_message_queue::system_message_queue(int count, int size)
    {
        entry_count = count;
        entry_size = size;
        in_pos = 0;
        out_pos = 0;
        buf = (uint8_t *)calloc(entry_count, entry_size);
        space_avail = CreateSemaphore(NULL, entry_count, entry_count, NULL);
        data_avail = CreateSemaphore(NULL, 0, entry_count, NULL);
        InitializeCriticalSection(&critical_section_obj);
    }

    system_message_queue::~system_message_queue()
    {
        if(buf)
        {
            free(buf);
        }
        CloseHandle(space_avail);
        CloseHandle(data_avail);
        DeleteCriticalSection(&critical_section_obj);
    }

    bool system_message_queue::queue_push(void *thread_data)
    {
        DWORD status;
        unsigned int amount_to_grow = 256;
        status = WaitForSingleObject(space_avail, 0);

        // if timeout waiting for room in the queue, grow the queue
        if (status == WAIT_TIMEOUT)
        {
            size_t new_count = entry_count + amount_to_grow;
            uint8_t * new_buf;
            uint8_t * old_buf;
            int new_out_pos = 0;
            int old_out_pos = 0;
            int copy_count;

            new_buf = (uint8_t *)calloc(new_count, entry_size);
            if (new_buf)
            {
                // Because buf is essentially a circular buffer, have
                // to copy values carefully to the new buffer.
                // We know that the old buffer is full, so have
                // two copy operations to perform.
                EnterCriticalSection(&critical_section_obj);
                old_out_pos = out_pos;
                copy_count = entry_count - old_out_pos;
                // copy old buffer from out_pos to the end of the old buffer
                memcpy(&new_buf[0 * entry_size],
                        &buf[old_out_pos * entry_size],
                        entry_size * copy_count);
                new_out_pos = copy_count;
                old_out_pos = (old_out_pos + copy_count) % entry_count;
                copy_count = out_pos;
                // copy from start of old buffer to position out_pos
                memcpy(&new_buf[new_out_pos * entry_size],
                    &buf[0 * entry_size],
                    entry_size * copy_count);
                new_out_pos = new_out_pos + copy_count;
                out_pos = 0;
                in_pos = new_out_pos;
                old_buf = buf;
                buf = new_buf;
                entry_count = new_count;
                LeaveCriticalSection(&critical_section_obj);
                free(old_buf);
                // increase space available
                ReleaseSemaphore(space_avail, amount_to_grow, NULL);
                // use up a single entry
                WaitForSingleObject(space_avail, INFINITE);
            }
            else
            {
                // alloc failed, so wait for space in que
                WaitForSingleObject(space_avail, INFINITE);
            }
        }

        EnterCriticalSection(&critical_section_obj);
        memcpy(&buf[in_pos * entry_size], thread_data, entry_size);
        in_pos = (in_pos + 1) % entry_count;
        LeaveCriticalSection(&critical_section_obj);
        ReleaseSemaphore(data_avail, 1, NULL);
        return status != WAIT_TIMEOUT;
    }

    void system_message_queue::queue_pop_nowait(void *thread_data)
    {
        EnterCriticalSection(&critical_section_obj);
        memcpy(thread_data, &buf[out_pos * entry_size], entry_size);
        out_pos = (out_pos + 1) % entry_count;
        LeaveCriticalSection(&critical_section_obj);
        ReleaseSemaphore(space_avail, 1, NULL);
    }

    void system_message_queue::queue_pop_wait(void *thread_data)
    {
        WaitForSingleObject(data_avail, INFINITE);
        queue_pop_nowait(thread_data);
    }

    HANDLE system_message_queue::queue_data_available_object()
    {
        return data_avail;
    }
}
