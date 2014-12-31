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
 * locale_descriptor_response_imp.h
 *
 * LOCALE descriptor response implementation class
 */

#pragma once

#include "locale_descriptor_response.h"
#include "jdksavdecc_aem_command.h"
#include "jdksavdecc_aem_descriptor.h"

namespace avdecc_lib
{
    class locale_descriptor_response_imp : public locale_descriptor_response
    {
    private:
        uint8_t * buffer;
        ssize_t position;
        size_t frame_size;
    public:
        locale_descriptor_response_imp(const uint8_t *frame, size_t frame_len, ssize_t pos);
        virtual ~locale_descriptor_response_imp();

        uint8_t * STDCALL locale_identifier();
        uint16_t STDCALL number_of_strings();
        uint16_t STDCALL base_strings();
    };
}
