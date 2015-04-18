#pragma once
#include "Subsystem.h"


#define DELTA_FPS_60 0.01666667f
#define DELTA_FPS_30 (DELTA_FPS_60 * 2)
#define DELTA_TIME_STEP DELTA_FPS_30
#define g_SubsystemManager	SubsystemManager::GetInstance()

class SubsystemManager
{
public:
	static SubsystemManager&		GetInstance();	// Added so all components with same UID easily can be removed.

	void							Startup					( );
	void							Update					( const float deltaTIme );
	void							Shutdown				( );
	void							AddSubsystem			( Subsystem* subsystem );

	void							StartAll				( );
	bool							StartSubsystem			( const std::string& name );
	void							StartSubsystems			( const std::vector<Subsystem*>& subsystemsToStart );

	bool							StopSubsystem			( const std::string& name );
	void							StopSubsystems			( const std::vector<Subsystem*>& subsystemsTopStop );

	void 							Restart 				( );
	void							RestartSubsystem		( const std::string& subsystemName );

	void 							PauseSubsystem			( const std::string& subsystemName );
	void 							UnpauseSubsystem		( const std::string& subsystemName );

	const std::vector<Subsystem*>*	GetUpdateCollection		( ) const;

	void							SetSimulationFramerate	( const unsigned int simulationFPS );
	unsigned int					GetSimulationFramerate	( ) const;

	void 							PrintStartupOrder 		( ) const;
	void 							PrintUpdateOrder 		( ) const;
	void 							PrintShutdownOrder 		( ) const;
	void							PrintStartedSubsystems	( ) const;
	void							PrintUnstartedSubsystems( ) const;

private:
									SubsystemManager();

	void							AddStartup				( Subsystem* subsystem );
	void							AddUpdate				( Subsystem* subsystem );
	void							AddShutdown				( Subsystem* subsystem );

	void 							PrintOrder 				( const std::vector<Subsystem*>& orderToPrint ) const;

	std::vector<Subsystem*>				m_StartupOrder;			// List of subsystems ordered in startup order.
	std::vector<Subsystem*>				m_UpdateOrder;			// List of subsystems ordered in update order.
	std::vector<Subsystem*>				m_ShutdownOrder;		// List of subsystems ordered in shutdown order.

	std::map<std::string, Subsystem*>		m_SubsystemMap;			// Maps subsystem names to subsystem pointers

	unsigned int					m_SimFPS = 60;
};
