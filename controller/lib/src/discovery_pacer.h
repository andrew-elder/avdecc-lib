/*
* Licensed under the MIT License (MIT)
*
* Copyright (c) 2015 AudioScience Inc.
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
* discovery pacer.h
*
* This class supports pacing the rate at which background enumeration sends packets.
*
*/

#pragma once

#include "timer.h"

namespace avdecc_lib
{
    class discovery_pacer
    {
    public:
        static discovery_pacer& getInstance() {
            // The only instance
            // Guaranteed to be lazy initialized
            // Guaranteed that it will be destroyed correctly
            static discovery_pacer instance;
            return instance;
        }

        bool ok_to_send_packet(void) {
            if (m_packets_per_second < 0)
                return true;
            if (m_packets_available > 0)
            {
                m_packets_available--;
                return true;
            }
            else
            {
                return false;
            }
        };

        void set_packets_per_second(int pps, int tick_rate_ms)
        {
            if (m_packets_per_second < 0)
            {
                m_timestamp = timer::clk_convert_to_ms(timer::clk_monotonic());
            }
            m_packets_per_second = pps;
            m_packets_per_tick = pps * 1000 / tick_rate_ms;
            // never go as low as zero packets per tick
            if (0 == m_packets_per_tick)
                m_packets_per_tick = 1;
        };

        void tick(void)
        {
            uint32_t the_time = timer::clk_convert_to_ms(timer::clk_monotonic());
            if (the_time != m_timestamp)
            {
                m_packets_available += (m_packets_per_second * 1000) / (the_time - m_timestamp);
                if (m_packets_available > m_packets_per_tick)
                    m_packets_available = m_packets_per_tick;
            }
            m_timestamp = the_time;
        };

    private:
        // Private Constructor
        discovery_pacer(){ m_packets_per_second = -1; };    // by default pacing is disabled
        // Stop the compiler generating methods of copy the object
        discovery_pacer(discovery_pacer const& copy);            // Not Implemented
        discovery_pacer& operator=(discovery_pacer const& copy); // Not Implemented

        int m_packets_per_second;  // -1 implies no pacing
        int m_packets_per_tick;    // packets per timer tick
        int m_packets_available;   // current packets available to send
        uint32_t m_timestamp;      // last timestamp


    };
}