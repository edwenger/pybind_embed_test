import glob
import os
# import sys
import shutil
import subprocess
from distutils.sysconfig import get_python_inc


# === Project includes settings
this_project_source = f'{os.getcwd()}/..'
include_subdirectories = ['core', 'model']

# === Binder settings
binder_executable = glob.glob(
    f'{os.getcwd()}/../../binder/build/llvm-4.0.0/build_4.0.0*/bin/binder')[0]

# GCC includes (Binder defaults to /usr/include/c++/v1)
# From Xcode, Mac has /usr/include/c++/4.2.1/
# Homebrew will install one that supports C++11
gcc_include = '/usr/local/Cellar/gcc/8.3.0_1/include/c++/8.3.0'
gcc_x64_include = os.path.join(gcc_include, 'x86_64-apple-darwin17.7.0')

# More include paths required by inclusion of
# <pybind11/embed.h> from all_cmake_includes.hpp
pybind_include = f'{os.getcwd()}/../../binder/build/pybind11/include'
python_include = get_python_inc()

# Binder output settings
bindings_dir = 'cmake_bindings'
python_module_name = 'test_binder'
this_project_namespace_to_bind = ' '.join(include_subdirectories)

# binder_source = f'{os.getcwd()}/../../binder/source'
# use_pybind_stl = True
# #use_pybind_stl = False


def make_all_includes():
    all_includes = []
    all_include_filename = 'all_cmake_includes.hpp'
    for subdir in include_subdirectories:
        prefix = f'{this_project_source}/{subdir}'
        for filename in (glob.glob(f'{prefix}/**/*.hpp', recursive=True)+
                         glob.glob(f'{prefix}/**/*.cpp', recursive=True)+
                         glob.glob(f'{prefix}/**/*.h', recursive=True)+
                         glob.glob(f'{prefix}/**/*.cc', recursive=True)+
                         glob.glob(f'{prefix}/**/*.c', recursive=True)):
            with open(filename, 'r') as fh:
                for line in fh:
                    if line.startswith('#include'):
                        all_includes.append(line.strip())
    all_includes = list(set(all_includes))
    with open(all_include_filename, 'w') as fh:
        for include in all_includes:
            fh.write(f'{include}\n')
    return all_include_filename


def make_bindings_code(all_includes_fn):
    shutil.rmtree(bindings_dir, ignore_errors=True)
    os.mkdir(bindings_dir)
    command = (f'{binder_executable} --root-module {python_module_name} '
               f'--prefix {os.getcwd()}/{bindings_dir}/ '
               f'--bind {this_project_namespace_to_bind} '
               # + ('--config config.cfg ' if use_pybind_stl else '') +
               f' {all_includes_fn} -- -std=c++11 '
               '-stdlib=libc++ '
               f'-I{gcc_include} '
               f'-I{pybind_include} '
               f'-I{python_include} '
               f'-DGCC_INSTALL_PREFIX {gcc_include} '
               f'-I{gcc_x64_include} '
               f'-I{this_project_source} -DNDEBUG -v').split()
    print(' '.join(command))
    ret = subprocess.call(command)
    sources_to_compile = []
    with open(f'{bindings_dir}/{python_module_name}.sources', 'r') as fh:
        for line in fh:
            sources_to_compile.append(line.strip())
    return sources_to_compile


def main():
    all_includes_fn =  make_all_includes()
    sources_to_compile = make_bindings_code(all_includes_fn)
    # compile_sources(sources_to_compile)


if __name__ == '__main__':
    main()
