project('prospero-headers', 'c', 'cpp',
    version: '1.0',
)

prospero_public_includes = include_directories('include')

prospero_headers_dep = declare_dependency(
    include_directories: prospero_public_includes,
)

meson.override_dependency('prospero-headers', prospero_headers_dep)