#include "SubsystemManager.h"
#include "gamelogic/SSGravity.h"
#include "gamelogic/SSPhysics.h"
#include "gfx/SSRender.h"
#include "input/SSControllable.h"
#include "level/SSLevel.h"
#include <algorithm>



SubsystemManager& SubsystemManager::GetInstance()
{
	static SubsystemManager instance;
	return instance;
}

SubsystemManager::SubsystemManager()
{}

void SubsystemManager::Startup()
{
	// Set priorities (100 is default). Startup, Update and Shutdown priority can be defined

	// Startup priorities
	//g_SSRender.SetStartOrderPriority(100U);

	// Update priorities
	g_SSControllable	.SetUpdateOrderPriority(   5U );	// Before: Game Logic	|
	g_SSGravity			.SetUpdateOrderPriority( 110U );	// Before: Physics		| After: Input
	g_SSPhysics			.SetUpdateOrderPriority( 130U );	// Before: Rendering	| After: Gravity (Accelerations)
	g_SSRender			.SetUpdateOrderPriority( 200U );	//						| After: Everything

	// Shutdown priorities
	//g_SSRender				.SetShutdownOrderPriority(100U);
	
	// Add all subsystems here.
	AddSubsystem( &g_SSGravity		);
	AddSubsystem( &g_SSPhysics		);
	AddSubsystem( &g_SSRender		);
	AddSubsystem( &g_SSControllable	);
	AddSubsystem( &g_SSLevel		);

	StartAll();
}

void SubsystemManager::Update( const float deltaTime )
{
	for ( auto subsystem : m_UpdateOrder )
	{
		// Update every subsystem as long as it isn't paused
		if ( subsystem->IsStarted() == true && subsystem->IsPaused( ) == false )
		{
			subsystem->Update( deltaTime );
		}
	}
}

void SubsystemManager::Shutdown()
{
	for ( auto subsystem : m_ShutdownOrder )
	{
		if ( subsystem->IsStarted() )
		{
			subsystem->ShutdownFromCollection();
		}
	}
}

void SubsystemManager::AddSubsystem( Subsystem* subsystem )
{
	// Add subsystem to map only if it isn't found in it.
	auto it = m_SubsystemMap.find( subsystem->GetName( ) );
	if ( it != m_SubsystemMap.end( ) )
	{
		// Warn about it being in the map already, not standard behaviour.
		//Logger::Log( subsystem->GetName( ) + " subsystem is already added. Nothing will be done.", "SubsystemManager", LogSeverity::WARNING_MSG );
		return;
	}
	else
		m_SubsystemMap.emplace( subsystem->GetName( ), subsystem );

	if ( m_StartupOrder.empty( ) )
	{
		m_StartupOrder.push_back( subsystem );
		m_UpdateOrder.push_back( subsystem );
		m_ShutdownOrder.push_back( subsystem );
	}
	else
	{
		AddStartup( subsystem );
		AddUpdate( subsystem );
		AddShutdown( subsystem );
	}
}

void SubsystemManager::StartAll()
{
	for ( auto subsystem : m_StartupOrder )
	{
		if ( !subsystem->IsStarted() )
			subsystem->StartupFromCollection();
	}
}

bool SubsystemManager::StartSubsystem( const std::string& name )
{
	auto subsystem = m_SubsystemMap.find( name );
	if ( subsystem != m_SubsystemMap.end() )
	{
		if ( !subsystem->second->IsStarted() )
		{
			subsystem->second->StartupFromCollection();
			return true;
		}
		else
		{
			//Logger::Log( "Cannot start subsystem <" + name + ">. It is already started", "SubsystemManager", LogSeverity::WARNING_MSG );
			return false;
		}
	}
	//Logger::Log( "Cannot start subsystem <" + name + ">. No subsystem with that name exists", "SubsystemManager", LogSeverity::WARNING_MSG );
	return false;
}

void SubsystemManager::StartSubsystems( const std::vector<Subsystem*>& subsystemsToStart )
{
	for ( int i = 0; i < m_StartupOrder.size(); ++i )
	{
		for ( int j = 0; j < subsystemsToStart.size(); ++j )
		{
			if ( *m_StartupOrder[i] == *subsystemsToStart[j] )
			{
				m_StartupOrder[i]->StartupFromCollection();
				break;
			}
		}
	}
}

bool SubsystemManager::StopSubsystem( const std::string& name )
{
	auto subsystem = m_SubsystemMap.find( name );
	if ( subsystem != m_SubsystemMap.end() )
	{
		if ( subsystem->second->IsStarted() )
		{
			subsystem->second->ShutdownFromCollection();
			return true;
		}
		else
		{
			//Logger::Log( "Cannot stop subsystem <" + name + ">. It is not started", "SubsystemManager", LogSeverity::WARNING_MSG );
			return false;
		}
	}
	//Logger::Log( "Cannot stop subsystem <" + name + ">. No subsystem with that name exists", "SubsystemManager", LogSeverity::WARNING_MSG );
	return false;
}

void SubsystemManager::StopSubsystems( const std::vector<Subsystem*>& subsystemsTopStop )
{
	if ( !subsystemsTopStop.empty() )
	{
		for ( int i = 0; i < m_ShutdownOrder.size(); ++i )
		{
			for ( int j = 0; j < subsystemsTopStop.size(); ++j )
			{
				if ( *m_ShutdownOrder[i] == *subsystemsTopStop[j] )
				{
					m_ShutdownOrder[i]->ShutdownFromCollection();
					break;
				}
			}
		}
	}
}

void SubsystemManager::Restart()
{
	//Logger::Log( "Restarting subsystems.", "SubsystemManager", LogSeverity::DEBUG_MSG );
	Shutdown();
	//Logger::Log( "Subsystems shut down.", "SubsystemManager", LogSeverity::DEBUG_MSG );
	//Logger::Log( "Starting subsystems.", "SubsystemManager", LogSeverity::DEBUG_MSG );
	Startup();
	//Logger::Log( "Subsystems started.", "SubsystemManager", LogSeverity::DEBUG_MSG );
}

void SubsystemManager::RestartSubsystem( const std::string& subsystemName )
{
	auto subsystemToRestart = m_SubsystemMap.find(subsystemName);
	if ( subsystemToRestart == m_SubsystemMap.end() )
	{
		//Logger::Log( "Tried to restart non existant subsystem: " + subsystemName, "SubsystemManager", LogSeverity::WARNING_MSG );
	}
	else
	{
		if ( subsystemToRestart->second->IsStarted() )
		{
			subsystemToRestart->second->ShutdownFromCollection();
			subsystemToRestart->second->StartupFromCollection();
		}
		else
		{
			//Logger::Log( "Tried to restart non-started subsystem. Nothing will happen", "SubsystemManager", LogSeverity::DEBUG_MSG );
		}
	}
}

void SubsystemManager::PauseSubsystem( const std::string& subsystemName )
{
	auto it = m_SubsystemMap.find( subsystemName );
	if ( it == m_SubsystemMap.end( ) )
		std::cout << "Tried to pause non existant subsystem: "  << subsystemName << std::endl;//Logger::Log( "Tried to pause non existant subsystem: " + subsystemName, "SubsystemManager", LogSeverity::WARNING_MSG );
	else
		it->second->Pause( );
}

void SubsystemManager::UnpauseSubsystem( const std::string& subsystemName )
{
	auto it = m_SubsystemMap.find( subsystemName );
	if ( it == m_SubsystemMap.end( ) )
		std::cout << "Tried to unpause non existant subsystem: "  << subsystemName << std::endl;//Logger::Log( "Tried to unpause non existant subsystem: " + subsystemName, "SubsystemManager", LogSeverity::WARNING_MSG );
	else
		it->second->Unpause( );
}

const std::vector<Subsystem*>* SubsystemManager::GetUpdateCollection() const
{
	return &m_UpdateOrder;
}

void SubsystemManager::SetSimulationFramerate( const unsigned int simulationFPS )
{
	if ( m_SimFPS < 1024U )
		m_SimFPS = simulationFPS;
	else
		m_SimFPS = 1024U;
}

unsigned int SubsystemManager::GetSimulationFramerate() const
{
	return m_SimFPS;
}

void SubsystemManager::PrintStartupOrder() const
{
	PrintOrder( m_StartupOrder );
}

void SubsystemManager::PrintUpdateOrder() const
{
	PrintOrder( m_UpdateOrder );	
}

void SubsystemManager::PrintShutdownOrder() const
{
	PrintOrder( m_ShutdownOrder );	
}

void SubsystemManager::PrintStartedSubsystems() const
{
	//Logger::GetStream() << "Printing started subsystems in update order." << std::endl;

	int index = 0;
	for ( auto& subsystem : m_UpdateOrder )
	{
		if ( subsystem->IsStarted() )
		{
			//Logger::GetStream() << index++ << ": " << subsystem->GetName() << std::endl;
		}
	}
}

void SubsystemManager::PrintUnstartedSubsystems() const
{
	//Logger::GetStream() << "Printing unstarted subsystems in startup order." << std::endl;

	int index = 0;
	for ( auto& subsystem : m_StartupOrder )
	{
		if ( !subsystem->IsStarted() )
		{
			//Logger::GetStream() << index++ << ": " << subsystem->GetName() << std::endl;
		}
	}
}

// Used by std::lower_bound to insert new subsystems in correct startup order.
bool CompareStartup( const Subsystem* lhs, const Subsystem* rhs )
{
	return lhs->GetStartOrderPriority( ) < rhs->GetStartOrderPriority( );
}

void SubsystemManager::AddStartup( Subsystem* subsystem )
{
	auto it = std::lower_bound( m_StartupOrder.begin( ), m_StartupOrder.end( ), subsystem, CompareStartup );
	m_StartupOrder.insert( it, subsystem );
}

// Used by std::lower_bound to insert new subsystems in correct update order.
bool CompareUpdate( const Subsystem* lhs, const Subsystem* rhs )
{
	return lhs->GetUpdateOrderPriority( ) < rhs->GetUpdateOrderPriority( );
}

void SubsystemManager::AddUpdate( Subsystem* subsystem )
{
	auto it = std::lower_bound( m_UpdateOrder.begin( ), m_UpdateOrder.end( ), subsystem, CompareUpdate );
	m_UpdateOrder.insert( it, subsystem );
}

// Used by std::lower_bound to insert new subsystems in correct shutdown order.
bool CompareShutdown( const Subsystem* lhs, const Subsystem* rhs ) // TODOJM: Shouldn't this be a private member function?
{
	return lhs->GetShutdownOrderPriority( ) < rhs->GetShutdownOrderPriority( );
}

void SubsystemManager::AddShutdown( Subsystem* subsystem )
{
	auto it = std::lower_bound( m_ShutdownOrder.begin( ), m_ShutdownOrder.end( ), subsystem, CompareShutdown );
	m_ShutdownOrder.insert( it, subsystem );
}

void SubsystemManager::PrintOrder( const std::vector<Subsystem*>& orderToPrint ) const
{
	int index = 0;
	for ( auto& subsystem : orderToPrint )
	{
		//Logger::GetStream() << index++ << ": " << subsystem->GetName() << std::endl;
	}
}
