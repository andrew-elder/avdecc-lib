/*
 * Licensed under the MIT License (MIT)
 *
 * Copyright (c) 2014 AudioScience Inc.
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
 * stream_output_get_stream_info_response_imp.h
 *
 * STREAM OUTPUT get stream info response implementation class
 */

#pragma once

#include "stream_output_get_stream_info_response.h"
#include "jdksavdecc_aem_command.h"

namespace avdecc_lib
{
    class stream_output_get_stream_info_response_imp : public stream_output_get_stream_info_response
    {
    private:
        uint8_t * m_frame;
        size_t m_size;
        ssize_t m_position;
    public:
        stream_output_get_stream_info_response_imp(uint8_t *frame, size_t frame_len, ssize_t pos);
        virtual ~stream_output_get_stream_info_response_imp();
        
        uint64_t STDCALL get_stream_format_stream_format();
        uint32_t STDCALL get_stream_info_flags();
        uint64_t STDCALL get_stream_info_stream_format();
        uint64_t STDCALL get_stream_info_stream_id();
        uint32_t STDCALL get_stream_info_msrp_accumulated_latency();
        uint64_t STDCALL get_stream_info_stream_dest_mac();
        uint8_t STDCALL get_stream_info_msrp_failure_code();
        uint64_t STDCALL get_stream_info_msrp_failure_bridge_id();
        uint16_t STDCALL get_stream_info_stream_vlan_id();
    };
}
