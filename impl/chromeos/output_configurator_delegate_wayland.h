// Copyright 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef OZONE_IMPL_OUTPUT_CONFIGURATOR_DELEGATE_WAYLAND_H_
#define OZONE_IMPL_OUTPUT_CONFIGURATOR_DELEGATE_WAYLAND_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chromeos/display/output_configurator.h"

namespace chromeos {

class OutputConfiguratorDelegateWayland : public OutputConfigurator::Delegate {
 public:
  OutputConfiguratorDelegateWayland();
  virtual ~OutputConfiguratorDelegateWayland();

  // OutputConfigurator::Delegate overrides:
  virtual int InitResources() OVERRIDE;
  virtual void HandleScreenChangeNotification(
      const base::NativeEvent& event) OVERRIDE;
  virtual void GrabServer() OVERRIDE;
  virtual void UngrabServer() OVERRIDE;
  virtual void SyncWithServer() OVERRIDE;
  virtual void SetBackgroundColor(uint32 color_argb) OVERRIDE;
  virtual void ForceDPMSOn() OVERRIDE;
  virtual std::vector<OutputConfigurator::OutputSnapshot> GetOutputs() OVERRIDE;
  virtual void AddOutputMode(RROutput output, RRMode mode) OVERRIDE;
  virtual bool ConfigureCrtc(
      RRCrtc crtc,
      RRMode mode,
      RROutput output,
      int x,
      int y) OVERRIDE;
  virtual void CreateFrameBuffer(
      int width,
      int height,
      const std::vector<OutputConfigurator::OutputSnapshot>& outputs) OVERRIDE;
  virtual void ConfigureCTM(
      int touch_device_id,
      const OutputConfigurator::CoordinateTransformation& ctm) OVERRIDE;
  virtual void SendProjectingStateToPowerManager(bool projecting) OVERRIDE;
  virtual bool GetHDCPState(RROutput id, HDCPState* state) OVERRIDE;
  virtual bool SetHDCPState(RROutput id, HDCPState state) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(OutputConfiguratorDelegateWayland);
};

}  // namespace chromeos

#endif  // OZONE_IMPL_OUTPUT_CONFIGURATOR_DELEGATE_WAYLAND_H_
