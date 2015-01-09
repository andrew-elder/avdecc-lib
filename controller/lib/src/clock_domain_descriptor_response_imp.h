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
 * clock_domain_descriptor_response_imp.h
 *
 * CLOCK DOMAIN descriptor response implementation class
 */

#pragma once

#include "clock_domain_descriptor_response.h"
#include "jdksavdecc_aem_descriptor.h"

namespace avdecc_lib
{
    class clock_domain_descriptor_response_imp : public clock_domain_descriptor_response
    {
    private:
        std::vector<uint16_t> clk_src_vec; // Store clock sources in a vector
        uint8_t * buffer;
        ssize_t position;
        size_t frame_size;
        /**
         * Store the Clock Sources of the CLOCK DOMAIN object.
         */
        void store_clock_sources();

    public:
        clock_domain_descriptor_response_imp(const uint8_t *frame, size_t frame_len, ssize_t pos);
        virtual ~clock_domain_descriptor_response_imp();

        uint8_t * STDCALL object_name();
        uint16_t STDCALL localized_description();
        uint16_t STDCALL clock_source_index();
        uint16_t clock_sources_offset();
        uint16_t STDCALL clock_sources_count();
        uint16_t STDCALL get_clock_source_by_index(size_t clk_src_index);
    };
}
