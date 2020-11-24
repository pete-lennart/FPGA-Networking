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

#include "IPPacketHandler.hpp"

Optional<axis_word> IPPacketHandler::get_payload(
    const Optional<axis_word> &word, const Addresses &loc, Status &status) {
#pragma HLS INLINE

  if (!word.is_valid) {
    return NOTHING;
  }

  switch (this->cnt) {
  case 0:
    this->ip_pkt_ihl = word.value.data(3, 0);
    this->cnt = 1;
    return NOTHING;
    break;
  case 1:
    this->cnt = 2;
    return NOTHING;
    break;
  case 2:
    this->cnt = 3;
    return NOTHING;
    break;
  case 3:
    this->cnt = 4;
    return NOTHING;
    break;
  case 4:
    this->cnt = 5;
    return NOTHING;
    break;
  case 5:
    this->cnt = 6;
    return NOTHING;
    break;
  case 6:
    this->cnt = 7;
    return NOTHING;
    break;
  case 7:
    this->cnt = 8;
    return NOTHING;
    break;
  case 8:
    this->cnt = 9;
    return NOTHING;
    break;
  case 9:
    this->ip_pkt_protocol = word.value.data;
    this->cnt = 10;
    return NOTHING;
    break;
  case 10:
    this->cnt = 11;
    return NOTHING;
    break;
  case 11:
    this->cnt = 12;
    return NOTHING;
    break;
  case 12:
    this->ip_pkt_src_ip_addr(31, 24) = word.value.data;
    this->cnt = 13;
    return NOTHING;
    break;
  case 13:
    this->ip_pkt_src_ip_addr(23, 16) = word.value.data;
    this->cnt = 14;
    return NOTHING;
    break;
  case 14:
    this->ip_pkt_src_ip_addr(15, 8) = word.value.data;
    this->cnt = 15;
    return NOTHING;
    break;
  case 15:
    this->ip_pkt_src_ip_addr(7, 0) = word.value.data;
    this->cnt = 16;
    return NOTHING;
    break;
  case 16:
    this->ip_pkt_dst_ip_addr(31, 24) = word.value.data;
    this->cnt = 17;
    return NOTHING;
    break;
  case 17:
    this->ip_pkt_dst_ip_addr(23, 16) = word.value.data;
    this->cnt = 18;
    return NOTHING;
    break;
  case 18:
    this->ip_pkt_dst_ip_addr(15, 8) = word.value.data;
    this->cnt = 19;
    return NOTHING;
    break;
  case 19:
    this->ip_pkt_dst_ip_addr(7, 0) = word.value.data;
    this->cnt = 20;
    return NOTHING;
    break;
  default:
    if (loc.ip_addr != ip_pkt_dst_ip_addr) {
      status.set_bad_ip_addr();
    }
    if (this->cnt >= this->ip_pkt_ihl * 4) {
      word.value.user(79, 48) = this->ip_pkt_src_ip_addr;
      switch (this->ip_pkt_protocol) {
      case UDP:
        return this->udpPacketHandler.get_payload(
            word, loc, status, this->ip_pkt_src_ip_addr);
        break;
      default:
        status.set_bad_ip_protocol();
        return NOTHING;
      }
    }
    return NOTHING;
    break;
  }
}

void IPPacketHandler::reset() {
  this->udpPacketHandler.reset();
  this->cnt = 0;
}
