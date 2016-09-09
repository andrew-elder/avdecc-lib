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
 * stream_output_get_tx_connection_response_imp.cpp
 *
 * STREAM output get tx state response implementation
 */

#include "enumeration.h"
#include "log_imp.h"
#include "stream_output_get_tx_connection_response_imp.h"
#include "util.h"

namespace avdecc_lib
{
stream_output_get_tx_connection_response_imp::stream_output_get_tx_connection_response_imp(uint8_t * frame, size_t frame_len, ssize_t pos)
{
    m_position = pos;
    m_size = frame_len;
    m_frame = (uint8_t *)malloc(m_size * sizeof(uint8_t));
    memcpy(m_frame, frame, m_size);
}

stream_output_get_tx_connection_response_imp::~stream_output_get_tx_connection_response_imp()
{
    free(m_frame);
}

uint64_t STDCALL stream_output_get_tx_connection_response_imp::get_tx_connection_stream_id()
{
    jdksavdecc_eui64 stream_id;
    stream_id = jdksavdecc_common_control_header_get_stream_id(m_frame, m_position);
    return jdksavdecc_eui64_convert_to_uint64(&stream_id);
}

uint16_t STDCALL stream_output_get_tx_connection_response_imp::get_tx_connection_talker_unique_id()
{
    return jdksavdecc_acmpdu_get_talker_unique_id(m_frame, m_position);
}

uint16_t STDCALL stream_output_get_tx_connection_response_imp::get_tx_connection_listener_unique_id()
{
    return jdksavdecc_acmpdu_get_listener_unique_id(m_frame, m_position);
}

uint64_t STDCALL stream_output_get_tx_connection_response_imp::get_tx_connection_stream_dest_mac()
{
    jdksavdecc_eui48 stream_dest_mac;
    stream_dest_mac = jdksavdecc_acmpdu_get_stream_dest_mac(m_frame, m_position);
    return jdksavdecc_eui48_convert_to_uint64(&stream_dest_mac);
}

uint16_t STDCALL stream_output_get_tx_connection_response_imp::get_tx_connection_connection_count()
{
    return jdksavdecc_acmpdu_get_connection_count(m_frame, m_position);
}

uint16_t STDCALL stream_output_get_tx_connection_response_imp::get_tx_connection_stream_vlan_id()
{
    return jdksavdecc_acmpdu_get_stream_vlan_id(m_frame, m_position);
}

uint64_t STDCALL stream_output_get_tx_connection_response_imp::get_tx_connection_listener_entity_id()
{
    jdksavdecc_eui64 listener_entity_id;
    listener_entity_id = jdksavdecc_acmpdu_get_listener_entity_id(m_frame, m_position);
    return jdksavdecc_eui64_convert_to_uint64(&listener_entity_id);
}
}