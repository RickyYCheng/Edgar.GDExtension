#!/usr/bin/env python
import os
import sys

os.system("dotnet publish src/edgar.interop.csharp --use-current-runtime -o game/bin")

env = SConscript("godot-cpp/SConstruct")

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/edgar.interop.cpp"])

sources = Glob("src/edgar.interop.cpp/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        f"game/bin/Edgar.Interop.Cpp.{env["platform"]}.{env["target"]}.framework/edgar.gdextension.{env["platform"]}.{env["target"]}",
        source=sources,
    )
else:
    library = env.SharedLibrary(
        f"game/bin/Edgar.Interop.Cpp{env["suffix"]}{env["SHLIBSUFFIX"]}",
        source=sources,
    )

env.Append(LIBS=["Edgar.Interop.CSharp"])
env.Append(LIBPATH="game/bin")

Default(library)
