/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2021, Delft Robotics Institute
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of the Delft Robotics Institute, nor the names
 *    of its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \author G.A. vd. Hoorn (TU Delft Robotics Institute)
 */

#include <string>
#ifdef ROS
#include "motoman_driver/simple_message/motoman_write_mregister.h"
#include "motoman_driver/simple_message/motoman_write_mregister_reply.h"
#include "simple_message/shared_types.h"
#include "simple_message/log_wrapper.h"
#endif

#ifdef MOTOPLUS
#include "motoman_write_mregister.h"        // NOLINT(build/include)
#include "motoman_write_mregister_reply.h"  // NOLINT(build/include)
#include "shared_types.h"                   // NOLINT(build/include)
#include "log_wrapper.h"                    // NOLINT(build/include)
#endif

using industrial::shared_types::shared_int;
namespace WriteMRegisterReplyResultCodes = motoman::simple_message::io_ctrl_reply::WriteMRegisterReplyResultCodes;

namespace motoman
{
namespace simple_message
{
namespace io_ctrl_reply
{

WriteMRegisterReply::WriteMRegisterReply(void)
{
  this->init();
}
WriteMRegisterReply::~WriteMRegisterReply(void)
{
}

void WriteMRegisterReply::init()
{
  // TODO( ): is success a good initial value?
  this->init(WriteMRegisterReplyResultCodes::SUCCESS);
}

void WriteMRegisterReply::init(WriteMRegisterReplyResultCode result_code)
{
  this->setResultCode(result_code);
}

std::string WriteMRegisterReply::getResultString(shared_int result_code)
{
  switch (result_code)
  {
  case WriteMRegisterReplyResultCodes::READ_ADDRESS_INVALID:
     return "Illegal address for read: outside permitted range on this controller, "
            "see documentation (" + std::to_string(WriteMRegisterReplyResultCodes::READ_ADDRESS_INVALID) + ")";
  case WriteMRegisterReplyResultCodes::WRITE_ADDRESS_INVALID:
     return "Illegal address for write: outside permitted range on this controller, "
            "see documentation (" + std::to_string(WriteMRegisterReplyResultCodes::WRITE_ADDRESS_INVALID) + ")";
  case WriteMRegisterReplyResultCodes::WRITE_VALUE_INVALID:
     return "Illegal value for the type of IO element addressed "
            "(" + std::to_string(WriteMRegisterReplyResultCodes::WRITE_VALUE_INVALID) + ")";
  case WriteMRegisterReplyResultCodes::READ_API_ERROR:
     return "The MotoPlus function MpReadIO returned -1. No further information is available "
            "(" + std::to_string(WriteMRegisterReplyResultCodes::READ_API_ERROR) + ")";
  case WriteMRegisterReplyResultCodes::WRITE_API_ERROR:
     return "The MotoPlus function MpWriteIO returned -1. No further information is available ";
            "(" + std::to_string(WriteMRegisterReplyResultCodes::WRITE_API_ERROR) + ")";
  case WriteMRegisterReplyResultCodes::SUCCESS:
    return "Success";
  default:
    return "Unknown";
  }
}

void WriteMRegisterReply::copyFrom(WriteMRegisterReply &src)
{
  this->setResultCode(src.getResultCode());
}

bool WriteMRegisterReply::operator==(WriteMRegisterReply &rhs)
{
  bool rslt = this->result_code_ == rhs.result_code_;

  return rslt;
}

bool WriteMRegisterReply::load(industrial::byte_array::ByteArray *buffer)
{
  LOG_COMM("Executing WriteMRegisterReply load");

  if (!buffer->load(this->result_code_))
  {
    LOG_ERROR("Failed to load WriteMRegisterReply result_code");
    return false;
  }

  LOG_COMM("WriteMRegisterReply data successfully loaded");
  return true;
}

bool WriteMRegisterReply::unload(industrial::byte_array::ByteArray *buffer)
{
  LOG_COMM("Executing WriteMRegisterReply unload");

  if (!buffer->unload(this->result_code_))
  {
    LOG_ERROR("Failed to unload WriteMRegisterReply result_code");
    return false;
  }

  LOG_COMM("WriteMRegisterReply data successfully unloaded");
  return true;
}

}  // namespace io_ctrl_reply
}  // namespace simple_message
}  // namespace motoman
