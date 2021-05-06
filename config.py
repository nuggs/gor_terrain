def can_build(env, platform):
    return platform == "x11" or platform == "windows" or platform == "osx"

def configure(env):
    if env["platform"] == "x11":
        env.Append(RPATH=["."])
        env.Append(CPPFLAGS="-std=c++17")
    elif env["platform"] == "windows":
        # visual studio
        if env["CC"] == "cl":
            # do this so it doesn't complain
            env.Append(LIBS=[""])
            # if we had something to do, we'd do it here.
        # mingw(rpath might not be needed
        else:
            env.Append(RPATH=["."])
            env.Append(CPPFLAGS="-std=c++17")
    elif env["platform"] == "osx":
        env.Append(CXXFLAGS="-std=c++0x")

