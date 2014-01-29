// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef OZONE_PLATFORM_OZONE_PLATFORM_WAYLAND_H_
#define OZONE_PLATFORM_OZONE_PLATFORM_WAYLAND_H_

#include "ozone/impl/desktop_factory_wayland.h"
#include "ozone/impl/ozone_display.h"
#if defined(OS_CHROMEOS)
#include "ozone/impl/chromeos/output_configurator_ozone_wayland.h"
#endif
#include "ozone/platform/ozone_export_wayland.h"
#include "ozone/ui/ime/input_method_context_factory_wayland.h"
#include "ui/events/ozone/event_factory_ozone.h"
#include "ui/ozone/ozone_platform.h"

namespace ui {

// OzonePlatform for Wayland
//
// This platform is Linux with the wayland display server.
class OzonePlatformWayland : public OzonePlatform {
 public:
  OzonePlatformWayland();
  virtual ~OzonePlatformWayland();

  virtual gfx::SurfaceFactoryOzone* GetSurfaceFactoryOzone() OVERRIDE;
  virtual ui::EventFactoryOzone* GetEventFactoryOzone() OVERRIDE;
#if defined(OS_CHROMEOS)
  virtual chromeos::OutputConfiguratorOzone* GetOutputConfiguratorOzone();
#endif
  virtual ui::InputMethodContextFactoryOzone*
      GetInputMethodContextFactoryOzone() OVERRIDE;

 private:
  ozonewayland::OzoneDisplay surface_factory_ozone_;

  // TODO(kalyan): Use EventFactoryOzone. This is a stub that does nothing.
  ui::EventFactoryOzone event_factory_ozone_;

  ozonewayland::InputMethodContextFactoryWayland input_method_context_factory_;

#if defined(TOOLKIT_VIEWS) && !defined(OS_CHROMEOS)
  ozonewayland::DesktopFactoryWayland desktop_factory_ozone_;
#endif
#if defined(OS_CHROMEOS)
  chromeos::OutputConfiguratorOzoneWayland output_configurator_;
#endif

  DISALLOW_COPY_AND_ASSIGN(OzonePlatformWayland);
};

// Constructor hook for use in ozone_platform_list.cc
OZONE_WAYLAND_EXPORT OzonePlatform* CreateOzonePlatformWayland();

}  // namespace ui

#endif  // OZONE_PLATFORM_OZONE_PLATFORM_WAYLAND_H_
