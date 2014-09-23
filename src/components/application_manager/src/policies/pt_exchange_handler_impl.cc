﻿/*
 Copyright (c) 2013, Ford Motor Company
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following
 disclaimer in the documentation and/or other materials provided with the
 distribution.

 Neither the name of the Ford Motor Company nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#include "application_manager/policies/pt_exchange_handler_impl.h"

#include "utils/logger.h"
#include "application_manager/policies/policy_handler.h"
#include "application_manager/policies/policy_retry_sequence.h"

namespace policy {

CREATE_LOGGERPTR_GLOBAL(logger_, "PolicyHandler")

PTExchangeHandlerImpl::PTExchangeHandlerImpl(PolicyHandler* handler)
    : policy_handler_(handler),
      retry_sequence_("RetrySequence", new RetrySequence(handler)) {
  DCHECK(policy_handler_);
  LOG4CXX_INFO(logger_, "Exchan created");
}

PTExchangeHandlerImpl::~PTExchangeHandlerImpl() {
  Stop();
  policy_handler_ = NULL;
}

void PTExchangeHandlerImpl::Start() {
  sync_primitives::AutoLock locker(retry_sequence_lock_);
  LOG4CXX_INFO(logger_, "Exchan started");

  if (retry_sequence_.is_running()) {
    retry_sequence_.stop();
  }

  PolicyManager* policy_manager = policy_handler_->policy_manager();
  if (policy_manager) {
    policy_manager->ResetRetrySequence();
  }
  retry_sequence_.start();
}

void PTExchangeHandlerImpl::Stop() {
  sync_primitives::AutoLock locker(retry_sequence_lock_);
  if (retry_sequence_.is_running()) {
    retry_sequence_.stop();
  }
}

}  //  namespace policy
