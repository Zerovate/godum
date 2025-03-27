import os

env = SConscript("E:/Project/Perforce/3rdparty/godot-cpp/Sconstruct")

VariantDir('build', 'src', duplicate=0)

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

env.Append(CPPDEFINES=["GODUM_GDEXTENSION"])

env.Append(CPPPATH=["src"])

def getSubdirs(path:str):
    result = ["build"]
    for root, folders, _ in os.walk(path):
        for folder in folders:
            result.append(os.path.join("build", folder))
    return result

sources = Glob("*.cpp")
for path in getSubdirs("src"):
    sources += Glob(os.path.join(path, "*.cpp"))

library = env.SharedLibrary(
    "bin/godum{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
    source=sources,
)

Default(library)
