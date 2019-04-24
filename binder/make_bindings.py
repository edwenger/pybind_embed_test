import glob
import os
import sys
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

# === Compiler settings
pybind_dir = f'{os.getcwd()}/../../binder/build/pybind11'
binder_source = f'{os.getcwd()}/../../binder/source'


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
               '--config config.cfg '  # for detailed binding instructions
               f' {all_includes_fn} -- -std=c++11 '

               # for Mac
               '-stdlib=libc++ '
               f'-I{gcc_include} '
               f'-DGCC_INSTALL_PREFIX {gcc_include} '
               f'-I{gcc_x64_include} '

               # for Binder
               f'-I{pybind_include} '
               f'-I{python_include} '

               f'-I{this_project_source} -DNDEBUG -v').split()
    print(' '.join(command))
    ret = subprocess.call(command)
    sources_to_compile = []
    with open(f'{bindings_dir}/{python_module_name}.sources', 'r') as fh:
        for line in fh:
            sources_to_compile.append(line.strip())
    return sources_to_compile


def compile_sources(sources_to_compile):
    og_dir = os.getcwd()
    os.chdir(bindings_dir)
    lines_to_write = []
    lines_to_write.append('cmake_minimum_required(VERSION 3.0)')
    lines_to_write.append(f'project({python_module_name})')

    compiled_sources = []
    include_directories = []
    for include_dir in [binder_source, this_project_source,
                        # gcc_include, gcc_x64_include,
                        pybind_include, get_python_inc()]:
        lines_to_write.append(f'include_directories({include_dir})')

    lines_to_write.append('set(CMAKE_CXX_STANDARD 11)')
    lines_to_write.append('set(CMAKE_CXX_STANDARD_REQUIRED ON)')

    # lines_to_write.append('set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE ON)') # -fPIC
    # lines_to_write.append('add_definitions(-DNDEBUG)')
    # lines_to_write.append('add_definitions(-DGCC_INSTALL_PREFIX)')

    # Link against pybind11 (after making local symlink)
    os.symlink(pybind_dir, 'pybind11')  # we've already chdir into bindings_dir
    lines_to_write.append('add_subdirectory(pybind11)')
    lines_to_write.append(f'add_library({python_module_name} SHARED')
    for source in sources_to_compile:
        lines_to_write.append(f'\t{source}')
    lines_to_write.append(')')
    lines_to_write.append(f'target_link_libraries({python_module_name} PRIVATE pybind11::module)')

    lines_to_write.append(f'set_target_properties({python_module_name} PROPERTIES PREFIX "" SUFFIX ".so")')

    with open('CMakeLists.txt', 'w') as f:
        for line in lines_to_write:
            f.write(f'{line}\n')

    # Compile from cmake file
    subprocess.call('cmake -DCMAKE_C_COMPILER=/usr/local/bin/gcc-8 -DCMAKE_CXX_COMPILER=/usr/local/bin/gcc-8 -G Ninja'.split())
    subprocess.call('ninja')

    # Test module from compiled .so in local directory
    sys.path.append('.')
    if python_module_name == 'test_binder':
        sys.stdout.flush()
        print('Testing Python lib...')
        import test_binder
        # test_obj = test_struct.testers.test_my_struct()
        # print(test_obj.an_int)
        # if use_pybind_stl:
        #     print(test_obj.a_vector)


def main():
    all_includes_fn =  make_all_includes()
    sources_to_compile = make_bindings_code(all_includes_fn)
    compile_sources(sources_to_compile)


if __name__ == '__main__':
    main()
