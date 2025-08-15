#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

arch = env["suffix"].split(".")[-1]
suffix = f".{env["platform"]}.{arch}"

# TODO: handle macos
csharp_build_code = os.system(f"dotnet publish src/edgar.interop.csharp --use-current-runtime -o game/edgar.godot.gdextension/bin /p:SConsSuffix={suffix}")
if csharp_build_code != 0:
    sys.exit(1)

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/edgar.interop.cpp"])

env.Append(LIBS=[f"edgar.interop.csharp{suffix}"])
env.Append(LIBPATH="game/edgar.godot.gdextension/bin")

import glob
sources = glob.glob("src/edgar.interop.cpp/**/*.cpp", recursive=True)
sources = [File(s) for s in sources]

if env["platform"] == "macos":
    library = env.SharedLibrary(
        # f"game/edgar.godot.gdextension/bin/edgar.interop.cpp.{env["platform"]}.{env["target"]}.framework/edgar.gdextension.{env["platform"]}.{env["target"]}",
        f"game/edgar.godot.gdextension/bin/edgar.interop.cpp.{env["platform"]}.framework/edgar.gdextension.{env["platform"]}",
        source=sources,
    )
else:
    library = env.SharedLibrary(
        # f"game/edgar.godot.gdextension/bin/edgar.interop.cpp{env["suffix"]}{env["SHLIBSUFFIX"]}",
        f"game/edgar.godot.gdextension/bin/edgar.interop.cpp{suffix}{env["SHLIBSUFFIX"]}",
        source=sources,
    )

Default(library)
