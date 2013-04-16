#ifndef __Scenario_hxx
#define __Scenario_hxx

#include <World.hxx>
#include <GeneralState.hxx>
#include "ScenarioConfig.hxx"

namespace Engine
{
	class Simulation;
}

namespace Panic 
{

enum Rasters
{
	// obstacle, 1 if true, 0 if false
	eObstacles,
	// exits, 1 if true, 0 if false
	eExits
};

class Scenario: public Engine::World
{
	ScenarioConfig _config;

	void createAgents();
	void createRasters();

public:
	Scenario( Engine::Simulation &simulation, ScenarioConfig &config );
	virtual ~Scenario();
};

} // namespace Panic

#endif // __Scenario_hxx
