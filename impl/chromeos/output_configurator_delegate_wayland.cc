// Copyright 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ozone/impl/chromeos/output_configurator_delegate_wayland.h"

namespace chromeos {

OutputConfiguratorDelegateWayland::OutputConfiguratorDelegateWayland() {
}

OutputConfiguratorDelegateWayland::~OutputConfiguratorDelegateWayland() {
}

int OutputConfiguratorDelegateWayland::InitResources() {
  NOTIMPLEMENTED();
  return 0;
}

void OutputConfiguratorDelegateWayland::HandleScreenChangeNotification(
    const base::NativeEvent& event) {
  NOTIMPLEMENTED();
}

void OutputConfiguratorDelegateWayland::GrabServer() {
  NOTIMPLEMENTED();
}

void OutputConfiguratorDelegateWayland::UngrabServer() {
  NOTIMPLEMENTED();
}

void OutputConfiguratorDelegateWayland::SyncWithServer() {
  NOTIMPLEMENTED();
}

void OutputConfiguratorDelegateWayland::SetBackgroundColor(uint32 color_argb) {
  NOTIMPLEMENTED();
}

void OutputConfiguratorDelegateWayland::ForceDPMSOn() {
  NOTIMPLEMENTED();
}

std::vector<OutputConfigurator::OutputSnapshot>
OutputConfiguratorDelegateWayland::GetOutputs() {
  std::vector<OutputConfigurator::OutputSnapshot> outputs;
  NOTIMPLEMENTED();
  return outputs;
}

void OutputConfiguratorDelegateWayland::AddOutputMode(RROutput output,
                                                   RRMode mode) {
  NOTIMPLEMENTED();
}

bool OutputConfiguratorDelegateWayland::ConfigureCrtc(RRCrtc crtc,
                                                      RRMode mode,
                                                      RROutput output,
                                                      int x,
                                                      int y) {
  NOTIMPLEMENTED();
  return false;
}

void OutputConfiguratorDelegateWayland::CreateFrameBuffer(
    int width,
    int height,
    const std::vector<OutputConfigurator::OutputSnapshot>& outputs) {
  NOTIMPLEMENTED();
}

void OutputConfiguratorDelegateWayland::ConfigureCTM(
    int touch_device_id,
    const OutputConfigurator::CoordinateTransformation& ctm) {
  NOTIMPLEMENTED();
}

void OutputConfiguratorDelegateWayland::SendProjectingStateToPowerManager(
    bool projecting) {
  NOTIMPLEMENTED();
}

bool OutputConfiguratorDelegateWayland::GetHDCPState(RROutput id,
                                                  HDCPState* state) {
  NOTIMPLEMENTED();
  return false;
}

bool OutputConfiguratorDelegateWayland::SetHDCPState(RROutput id,
                                                  HDCPState state) {
  NOTIMPLEMENTED();
  return false;
}

}  // namespace chromeos
