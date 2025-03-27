import os

AddOption("--godot_cpp_path", dest='godot_cpp_path', type='string', action='store', metavar='DIR', help='must have a godot-cpp path')
godot_cpp_path = GetOption('godot_cpp_path')
if not godot_cpp_path:
    print("must have a godot_cpp_path")
    Exit(1)
env = SConscript(os.path.join(godot_cpp_path, "Sconstruct"))

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
