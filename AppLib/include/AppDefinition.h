#ifndef APP_DEFINITION_H
#define APP_DEFINITION_H

struct AppDefinition
{
	static const char * problemDatasetName;
	static const char * solutionDatasetName;
};

enum class AppBehaviour { create_empty, check, solved, solve };

#endif
