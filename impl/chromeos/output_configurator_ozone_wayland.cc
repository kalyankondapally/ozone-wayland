// Copyright 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ozone/impl/chromeos/output_configurator_ozone_wayland.h"
#include "ozone/impl/chromeos/output_configurator_delegate_wayland.h"

#include "base/message_loop/message_pump_ozone.h"

namespace chromeos {

OutputConfiguratorOzoneWayland::OutputConfiguratorOzoneWayland()
    : OutputConfiguratorOzone() {
}

OutputConfiguratorOzoneWayland::~OutputConfiguratorOzoneWayland() {

}

void OutputConfiguratorOzoneWayland::StartProcessingEvents() {
  base::MessagePumpOzone::Current()->AddObserver(this);
}

void OutputConfiguratorOzoneWayland::StopProcessingEvents() {
  base::MessagePumpOzone::Current()->RemoveObserver(this);
}

OutputConfigurator::Delegate* OutputConfiguratorOzoneWayland::CreateDelegate() {
  return new OutputConfiguratorDelegateWayland();
}

}  // namespace chromeos
