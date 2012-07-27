#ifndef __UI_ROCKETMODULE_H__
#define __UI_ROCKETMODULE_H__

#include "kernel/ui_systeminterface.h"
#include "kernel/ui_fileinterface.h"
#include "kernel/ui_renderinterface.h"
#include "kernel/ui_keyconverter.h"

namespace WSWUI
{
	// RocketModule contains details and interface to libRocket
	class RocketModule
	{
		// some typical Rocket shortcuts
		typedef Rocket::Core::Element Element;
		typedef Rocket::Core::Event Event;

	public:
		RocketModule( int vidWidth, int vidHeight );
		~RocketModule();

		// pre-initialization
		// bool initRocket( int vidWidth, int vidHeight );
		// void shutdownRocket();

		// post-initialization
		void registerCustoms();

		// cursor functions
		void loadCursor( const String& rmlCursor );
		void showCursor( void );
		void hideCursor( void );

		// system events
		void mouseMove( int mousex, int mousey );
		void textInput( qwchar c );
		void keyEvent( int key, bool pressed );

		Rocket::Core::ElementDocument *loadDocument( const char *filename, bool show=false );
		void closeDocument( Rocket::Core::ElementDocument *doc );

		// called from ElementInstancer after it instances an element, set up default
		// attributes, properties, events etc..
		void registerElementDefaults( Rocket::Core::Element *);

		// GET/SET Submodules
		UI_SystemInterface *getSystemInterface() { return system; }
		UI_FileInterface *getFileInterface() { return files; }
		UI_RenderInterface *getRenderInterface() { return render; }

		// you shouldnt need to use this
		Rocket::Core::Context *getContext() { return context; }

	private:
		void preloadFonts( const char *ext );

		void registerElement( const char *tag, Rocket::Core::ElementInstancer* );
		void registerFontEffect( const char *name, Rocket::Core::FontEffectInstancer *);
		void registerDecorator( const char *name, Rocket::Core::DecoratorInstancer *);
		void registerEventInstancer( Rocket::Core::EventInstancer *);
		void registerEventListener( Rocket::Core::EventListenerInstancer *);

		bool rocketInitialized;

		UI_SystemInterface *system;
		UI_FileInterface *files;
		UI_RenderInterface *render;

		Rocket::Core::Context *context;

		// hold this so we can unref these in the end
		std::list<Rocket::Core::ElementInstancer*> elementInstancers;
	};
}

#endif // __UI_ROCKETMODULE_H__