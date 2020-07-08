/*
 * Copyright (c) 2020, Peter Lehnhardt
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ETH_OUT_HPP
#define ETH_OUT_HPP
#pragma once

#include "../utils/Addresses.hpp"
#include "../utils/axis_word.hpp"
#include "../utils/checksums/CRC32.hpp"
#include "../utils/checksums/Checksum.hpp"
#include "../utils/constants.hpp"
#include <ap_int.h>
#include <hls_stream.h>

const int MIN_UDP_PAYLOAD_BYTE_SIZE = 18;
const int UDP_PKT_HEADER_BYTE_SIZE = 8;
const int MIN_UDP_PKT_BYTE_SIZE = 26;
const int IP_PKT_HEADER_BYTE_SIZE = 20;
const int MIN_IP_PKT_BYTE_SIZE = 46;

void eth_out(hls::stream<axis_word> &data_in,
             ap_uint<2> &txd,
             ap_uint<1> &txen,
             const Addresses &loc);

#endif
