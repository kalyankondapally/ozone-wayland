// Copyright 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DISPLAY_OUTPUT_CONFIGURATOR_OZONE_WAYLAND_H_
#define CHROMEOS_DISPLAY_OUTPUT_CONFIGURATOR_OZONE_WAYLAND_H_

#include "chromeos/display/output_configurator_ozone.h"

namespace chromeos {

class CHROMEOS_EXPORT OutputConfiguratorOzoneWayland
    : public OutputConfiguratorOzone {
 public:
  OutputConfiguratorOzoneWayland();
  virtual ~OutputConfiguratorOzoneWayland();
  virtual void StartProcessingEvents() OVERRIDE;
  virtual void StopProcessingEvents() OVERRIDE;

protected:
 virtual OutputConfigurator::Delegate* CreateDelegate() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(OutputConfiguratorOzoneWayland);
};

}  // namespace chromeos

#endif  // CHROMEOS_DISPLAY_OUTPUT_CONFIGURATOR_OZONE_WAYLAND_H_
