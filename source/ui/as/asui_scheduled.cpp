#include "ui_precompiled.h"
#include "kernel/ui_common.h"
#include "kernel/ui_main.h"

#include "as/asui.h"
#include "as/asui_local.h"
#include "as/asui_scheduled.h"

namespace ASUI
{

ScheduledFunction::ScheduledFunction()
	: any( NULL ), sched( 0 )
{

}

ScheduledFunction::ScheduledFunction( asIScriptFunction *func, unsigned int delay, bool intervalled, CScriptAnyInterface *any, FunctionCallScheduler *sched )
	: any( any ), sched( sched ), start( trap::Milliseconds() ), delay( delay ), intervalled( intervalled )
{
	if( any ) {
		funcPtr2 = ASBind::CreateFunctionPtr( func, funcPtr2 );
		if( funcPtr2.isValid() ) {
			func->AddRef();
		}
		any->AddRef();
	}
	else {
		funcPtr = ASBind::CreateFunctionPtr( func, funcPtr );
		if( funcPtr.isValid() ) {
			func->AddRef();
		}
	}

	/* TODO: intervalled function should be called right away? */
}

ScheduledFunction::~ScheduledFunction()
{
	if( any ) {
		if( funcPtr2.isValid() ) {
			funcPtr2.release();
		}
		any->Release();
	}
	else {
		if( funcPtr.isValid() ) {
			funcPtr.release();
		}
	}
}

bool ScheduledFunction::run()
{
	unsigned int now = trap::Milliseconds();

	if( funcPtr.isValid() || funcPtr2.isValid() )
	{
		// call function
		if( now >= ( start + delay ) )
		{
			bool res = intervalled;

			try {
				if( funcPtr2.isValid() ) {
					funcPtr2.setContext( sched->getAS()->getContext() );
					res = funcPtr2( any );
				}
				else {
					funcPtr.setContext( sched->getAS()->getContext() );
					res = funcPtr();
				}
			} catch( ASBind::Exception & ) {
				Com_Printf( S_COLOR_RED "SheduledFunction: Failed to call function %s\n", funcPtr.getName() );
			}

			if( !res )
				return false;	// stop this madness

			// push start time forwards
			// FIXME: push until now in case of big gaps between run()
			start += delay;
		}
	}

	// signal for keep going
	return true;
}

//============================================================

FunctionCallScheduler::FunctionCallScheduler( ASInterface *asmodule )
	: asmodule( asmodule ), counter( 0 )
{
	// assert( asmodule != 0 );
}

FunctionCallScheduler::~FunctionCallScheduler()
{

}

void FunctionCallScheduler::init( ASInterface *_asmodule )
{
	asmodule = _asmodule;
}

// runs all active functions
void FunctionCallScheduler::update( void )
{
	for( FunctionMap::iterator it = functions.begin(); it!= functions.end(); )
	{
		if( !it->second.run() )
			functions.erase( it++ );
		else
			it++;
	}
}

void FunctionCallScheduler::shutdown( void )
{
	for( FunctionMap::iterator it = functions.begin(); it!= functions.end(); )
	{
		functions.erase( it++ );
	}
}

int FunctionCallScheduler::setTimeout( asIScriptFunction *func, unsigned int ms )
{
	// I'm not entirely sure why this is NOT needed
//	func->AddRef();
	functions[counter] = ScheduledFunction( func, ms, false, NULL, this );
	return counter++;
}

int FunctionCallScheduler::setInterval( asIScriptFunction *func, unsigned int ms )
{
	// I'm not entirely sure why this is NOT needed
//	func->AddRef();
	functions[counter] = ScheduledFunction( func, ms, true, NULL, this );
	return counter++;
}

int FunctionCallScheduler::setTimeout( asIScriptFunction *func, unsigned int ms, CScriptAnyInterface &any )
{
	any.AddRef();

	// I'm not entirely sure why this is NOT needed
//	func->AddRef();
	functions[counter] = ScheduledFunction( func, ms, false, &any, this );
	return counter++;
}

int FunctionCallScheduler::setInterval( asIScriptFunction *func, unsigned int ms, CScriptAnyInterface &any )
{
	any.AddRef();

	// I'm not entirely sure why this is NOT needed
//	func->AddRef();
	functions[counter] = ScheduledFunction( func, ms, true, &any, this );
	return counter++;
}

void FunctionCallScheduler::clearTimeout( int id )
{
	removeFunction( id );
}

void FunctionCallScheduler::clearInterval( int id )
{
	removeFunction( id );
}

void FunctionCallScheduler::removeFunction( int id )
{
	FunctionMap::iterator it = functions.find( id );
	if( it != functions.end() ) {
		functions.erase( it );
	}
}

}
