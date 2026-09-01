wrapper_icd = custom_target(
  'wrapper_icd',
  input: [vk_icd_gen, vk_api_xml],
  output: 'wrapper_icd.@0@.json'.format(host_machine.cpu()),
  command: [
    prog_python,
    '@INPUT0@',
    '--api-version', '1.3',
    '--xml', '@INPUT1@',
    '--icd-lib-path', join_paths(get_option('prefix'), get_option('libdir')),
    '--icd-filename', 'libvulkan_wrapper.so',
    '--out', '@OUTPUT@',
  ],
  build_by_default: true,
  install_dir: with_vulkan_icd_dir,
  install: true,
)

wrapper_entrypoints = custom_target(
  'wrapper_entrypoints',
  input: [vk_entrypoints_gen, vk_api_xml],
  output: ['wrapper_entrypoints.h', 'wrapper_entrypoints.c'],
  command: [
    prog_python,
    '@INPUT0@',
    '--xml', '@INPUT1@',
    '--proto',
    '--weak',
    '--beta', with_vulkan_beta.to_string(),
    '--out-h', '@OUTPUT0@',
    '--out-c', '@OUTPUT1@',
    '--prefix', 'wrapper',
  ],
  depend_files: vk_entrypoints_gen_depend_files,
)

wrapper_trampolines_gen = files('vk_wrapper_trampolines_gen.py')

wrapper_trampolines = custom_target(
  'wrapper_trampolines',
  input: [wrapper_trampolines_gen, vk_api_xml],
  output: ['wrapper_trampolines.c', 'wrapper_trampolines.h'],
  command: [
    prog_python,
    '@INPUT0@',
    '--xml', '@INPUT1@',
    '--out-c', '@OUTPUT0@',
    '--out-h', '@OUTPUT1@',
    '--beta', with_vulkan_beta.to_string(),
  ],
  depend_files: vk_dispatch_trampolines_gen_depend_files,
)

wrapper_features_gen = files('vk_wrapper_features_gen.py')

wrapper_features = custom_target(
  'vk_wrapper_features',
  input: [wrapper_features_gen, vk_api_xml],
  output: ['wrapper_features.c'],
  command: [
    prog_python,
    '@INPUT0@',
    '--xml', '@INPUT1@',
    '--out-c', '@OUTPUT0@',
    '--beta', with_vulkan_beta.to_string(),
  ],
  depend_files: vk_physical_device_features_gen_depend_files,
)

wrapper_files = files(
  'wrapper_device.c',
  'wrapper_device_memory.c',
  'wrapper_instance.c',
  'wrapper_physical_device.c',
)

wrapper_deps = [
  idep_vulkan_lite_runtime,
  idep_vulkan_util,
  idep_vulkan_wsi,
]
if not with_wrapper_hybris
  # In hybris mode the AHardwareBuffer entry points come from libahb-wrapper
  # (proxying the Android driver through libhybris); linking the android_stub
  # DSOs would both add unusable DT_NEEDED entries and shadow the real
  # implementations with stub no-ops.
  wrapper_deps += dep_android
endif

wrapper_extra_deps = []
wrapper_c_args = []
if with_wrapper_hybris
  # hybris_dlopen/hybris_dlsym live in libhybris-common; the AHardwareBuffer
  # entry points used by the WSI come from libahb-wrapper (which proxies them
  # to the Android libandroid.so through hybris).
  wrapper_c_args += '-DWRAPPER_USE_HYBRIS'
  wrapper_extra_deps += [
    cc.find_library('hybris-common', required: true),
    cc.find_library('ahb-wrapper', required: true),
  ]
endif

libvulkan_wrapper = shared_library(
  'vulkan_wrapper',
  [wrapper_entrypoints, wrapper_trampolines, wrapper_features, wrapper_files],
  include_directories: [
    inc_include,
    inc_src,
  ],
  c_args: wrapper_c_args,
  dependencies: [wrapper_deps, vulkan_wsi_deps, wrapper_extra_deps],
  gnu_symbol_visibility: 'hidden',
  install: true,
)
