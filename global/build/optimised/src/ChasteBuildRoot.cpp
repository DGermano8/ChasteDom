
#include "ChasteBuildRoot.hpp"

const char* ChasteBuildRootDir()
{
    return "/Users/germanod/Workspace/ChasteDom/";
}

const char* ChasteSourceRootDir()
{
    return "/Users/germanod/Workspace/ChasteDom/";
}

std::string ChasteComponentBuildDir(const std::string& rComponent)
{
    return std::string(ChasteBuildRootDir()) + rComponent + "/build/optimised/";
}

std::string ChasteBuildDirName()
{
    return "optimised";
}

std::string ChasteBuildType()
{
    return "GccOpt";
}

