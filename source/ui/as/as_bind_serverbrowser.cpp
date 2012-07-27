#include "ui_precompiled.h"
#include "kernel/ui_common.h"
#include "kernel/ui_main.h"

#include "as/asui.h"
#include "as/asui_local.h"

#include "datasources/ui_serverbrowser_datasource.h"

namespace ASUI {

typedef WSWUI::ServerBrowserDataSource ServerBrowserDataSource;

void PrebindServerbrowser( ASInterface *as )
{
	ASBind::Class<ServerBrowserDataSource, ASBind::class_singleref>( as->getEngine() );
}

void BindServerbrowser( ASInterface *as )
{
	ASBind::GetClass<ServerBrowserDataSource>( as->getEngine() )

		.method( &ServerBrowserDataSource::startFullUpdate, "fullUpdate" )
		.method( &ServerBrowserDataSource::startRefresh, "refresh" )
		.method( &ServerBrowserDataSource::isUpdating, "isUpdating" )
		.method( &ServerBrowserDataSource::stopUpdate, "stopUpdate" )

		;
}

void BindServerbrowserGlobal( ASInterface *as )
{
	// globals
	ASBind::Global( as->getEngine() )
		// global variables
		.var( UI_Main::Get()->getServerBrowser(), "serverBrowser" )
	;
}

}

ASBIND_TYPE( WSWUI::ServerBrowserDataSource, ServerBrowser );
