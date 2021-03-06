Name:           chromium
Version:        35.0.1906.0
Release:        0
Summary:        Chromium ozone-wayland
License:        BSD-3-Clause
Group:          Web Framework/chromium
Url:            https://01.org/ozone-wayland
Source:         %{name}.tar
Source1:        chromium-browser.sh
Source1001:     chromium.manifest

BuildRequires:  bison
BuildRequires:  bzip2-devel
BuildRequires:  expat-devel
BuildRequires:  flex
BuildRequires:  gperf
BuildRequires:  libcap-devel
BuildRequires:  ninja
BuildRequires:  python
BuildRequires:  python-xml
BuildRequires:  perl
BuildRequires:  which
BuildRequires:  pkgconfig(alsa)
BuildRequires:  pkgconfig(aul)
BuildRequires:  pkgconfig(audio-session-mgr)
BuildRequires:  pkgconfig(cairo)
BuildRequires:  pkgconfig(capi-appfw-application)
BuildRequires:  pkgconfig(capi-location-manager)
BuildRequires:  pkgconfig(dbus-1)
BuildRequires:  pkgconfig(fontconfig)
BuildRequires:  pkgconfig(freetype2)
BuildRequires:  pkgconfig(gles20)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(haptic)
BuildRequires:  pkgconfig(icu-i18n)
BuildRequires:  pkgconfig(libdrm)
BuildRequires:  pkgconfig(libexif)
BuildRequires:  pkgconfig(libpci)
BuildRequires:  pkgconfig(libpulse)
BuildRequires:  pkgconfig(libudev)
BuildRequires:  pkgconfig(libxml-2.0)
BuildRequires:  pkgconfig(libxslt)
BuildRequires:  pkgconfig(nss)
BuildRequires:  pkgconfig(pango)
BuildRequires:  pkgconfig(pkgmgr-info)
BuildRequires:  pkgconfig(pkgmgr-parser)
BuildRequires:  pkgconfig(nspr)
BuildRequires:  pkgconfig(sensor)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(wayland-client)
BuildRequires:  pkgconfig(wayland-cursor)
BuildRequires:  pkgconfig(wayland-egl)
BuildRequires:  pkgconfig(weston)
BuildRequires:  pkgconfig(xkbcommon)

%description
# Ozone is a set of classes in Chromium for abstracting different window systems on Linux. It provides abstraction for the construction of accelerated surfaces underlying Aura UI framework, input devices assignment, and event handling.

%prep
%setup -q -n chromium

cp %{SOURCE1001} .

cp -a src/AUTHORS AUTHORS.chromium
cp -a src/LICENSE LICENSE.chromium
cp -a src/ozone/AUTHORS AUTHORS.ozone-wayland
cp -a src/ozone/LICENSE LICENSE.ozone-wayland

%build

# For ffmpeg on ia32. The original CFLAGS set by the gyp and config files in
# src/third_party/ffmpeg already pass -O2 -fomit-frame-pointer, but Tizen's
# CFLAGS end up appending -fno-omit-frame-pointer. See http://crbug.com/37246
export CFLAGS=`echo $CFLAGS | sed s,-fno-omit-frame-pointer,,g`

# Building the RPM in the GBS chroot fails with errors such as
#   /usr/lib/gcc/i586-tizen-linux/4.7/../../../../i586-tizen-linux/bin/ld:
#       failed to set dynamic section sizes: Memory exhausted
# For now, work around it by passing a GNU ld-specific flag that optimizes the
# linker for memory usage.
export LDFLAGS="${LDFLAGS} -Wl,--no-keep-memory"

# Support building in a non-standard directory, possibly outside %{_builddir}.
# Since the build root is erased every time a new build is performed, one way
# to avoid losing the build directory is to specify a location outside the
# build root to the BUILDDIR_NAME definition, such as "/var/tmp/chromium-build"
# (remember all paths are still inside the chroot):
#    gbs build --define 'BUILDDIR_NAME /some/path'
#
# The --depth and --generator-output combo is used to put all the Makefiles
# inside the build directory, and (this is the important part) keep file lists
# (generatedwith <|() in gyp) in the build directory as well, otherwise they
# will be in the source directory, erased every time and trigger an almost full
# Blink rebuild (among other smaller targets).
# We cannot always pass those flags, though, because gyp's make generator does
# not work if the --generator-output is the top-level source directory.
BUILDDIR_NAME="%{?BUILDDIR_NAME}"
if [ -z "${BUILDDIR_NAME}" ]; then
   BUILDDIR_NAME="."
else
   GYP_EXTRA_FLAGS="--depth=. --generator-output=${BUILDDIR_NAME}"
fi

# Change src/ so that we can pass "." to --depth below, otherwise we would need
# to pass "src" to it, but this confuses the gyp make generator, that expects
# to be called from the root source directory.
cd src

# --no-parallel is added because chroot does not mount a /dev/shm, this will
# cause python multiprocessing.SemLock error.
#https://github.com/01org/ozone-wayland/issues/147

export GYP_GENERATORS=ninja
./build/gyp_chromium \
--no-parallel \
-Duse_ash=0 \
-Duse_ozone=1 \
-Dchromeos=0 \
-Ddisable_nacl=1 \
-Dpython_ver=2.7 \
-Duse_aura=1 \
-Duse_x11=0 \
-Duse_cups=0 \
-Duse_gconf=0 \
-Duse_kerberos=0 \
-Duse_system_bzip2=1 \
-Duse_system_icu=0 \
-Duse_system_libexif=1 \
-Duse_system_libxml=1 \
-Duse_system_nspr=1 \
-Denable_xi21_mt=1 \
-Duse_xi2_mt=0 \
-Dtarget_arch=ia32 \
-Duse_alsa=0 \
-Duse_gnome_keyring=0 \
-Dlogging_like_official_build=1 \
-Dtracing_like_official_build=1 \
-Drelease_unwind_tables=0 \
-Dlinux_dump_symbols=0 \
-Denable_ozone_wayland_vkb=1

ninja %{?_smp_mflags} -C out/Release chrome

%install
# Support building in a non-standard directory, possibly outside %{_builddir}.
# Since the build root is erased every time a new build is performed, one way
# to avoid losing the build directory is to specify a location outside the
# build root to the BUILDDIR_NAME definition, such as "/var/tmp/chromium-build"
# (remember all paths are still inside the chroot):
#    gbs build --define 'BUILDDIR_NAME /some/path'
BUILDDIR_NAME="%{?BUILDDIR_NAME}"
if [ -z "${BUILDDIR_NAME}" ]; then
   BUILDDIR_NAME="."
fi

# Since BUILDDIR_NAME can be either a relative path or an absolute one, we need
# to cd into src/ so that it means the same thing in the build and install
# stages: during the former, a relative location refers to a place inside src/,
# whereas during the latter a relative location by default would refer to a
# place one directory above src/. If BUILDDIR_NAME is an absolute path, this is
# irrelevant anyway.
cd src

# Binaries.
install -p -D %{SOURCE1} %{buildroot}%{_bindir}/chromium-browser
install -p -D ${BUILDDIR_NAME}/out/Release/chrome %{buildroot}%{_libdir}/chromium/chrome
cp -R ${BUILDDIR_NAME}/out/Release/locales %{buildroot}%{_libdir}/chromium/

# Workaround to avoid eu-strip error.
strip %{buildroot}%{_libdir}/chromium/chrome

# Supporting libraries and resources.
install -p -D ${BUILDDIR_NAME}/out/Release/libffmpegsumo.so %{buildroot}%{_libdir}/chromium/libffmpegsumo.so
strip %{buildroot}%{_libdir}/chromium/libffmpegsumo.so
install -p -D ${BUILDDIR_NAME}/out/Release/resources.pak %{buildroot}%{_libdir}/chromium/resources.pak
install -p -D ${BUILDDIR_NAME}/out/Release/chrome_100_percent.pak %{buildroot}%{_libdir}/chromium/chrome_100_percent.pak
install -p -D ${BUILDDIR_NAME}/out/Release/icudtl.dat %{buildroot}%{_libdir}/chromium/icudtl.dat

%files
%manifest %{name}.manifest
%license AUTHORS.chromium LICENSE.chromium AUTHORS.ozone-wayland LICENSE.ozone-wayland
%{_bindir}/chromium-browser
%{_libdir}/chromium/libffmpegsumo.so
%{_libdir}/chromium/chrome
%{_libdir}/chromium/resources.pak
%{_libdir}/chromium/chrome_100_percent.pak
%{_libdir}/chromium/icudtl.dat
%{_libdir}/chromium/locales/*
