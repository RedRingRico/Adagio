#include <iostream>
#include <GitVersion.hpp>

const char *g_pBuild =
#if defined BUILD_RELEASE
"Release";
#elif defined BUILD_DEBUG
"Debug";
#elif defined BUILD_PROFILE
"Profile";
#else
"UNKNOWN";
#warning Unknown build
#endif

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "Adagio [" << g_pBuild << "]" << std::endl;
	std::cout << "Build Information" << std::endl;
	std::cout << "\tBuild:       " << GIT_BUILD_VERSION << std::endl;
	std::cout << "\tCommit date: " << GIT_COMMITTERDATE << std::endl;
	std::cout << "\tBranch:      " << GIT_BRANCH << std::endl;
	std::cout << "\tTag:         " << GIT_TAG_NAME << std::endl;
	return 0;
}

