/*
Copyright (C) 2012 Victor Luchits

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef _FTLIB_PUBLIC_H_
#define _FTLIB_PUBLIC_H_

// ftlib_public.h - font provider subsystem

#define	FTLIB_API_VERSION			1

//===============================================================

struct shader_s;
struct qfontface_s;

//
// functions provided by the main engine
//
typedef struct
{
	// drops to console a client game error
	void ( *Error )( const char *msg );

	// console messages
	void ( *Print )( const char *msg );

	// console variable interaction
	cvar_t *( *Cvar_Get )( const char *name, const char *value, int flags );
	cvar_t *( *Cvar_Set )( const char *name, const char *value );
	void ( *Cvar_SetValue )( const char *name, float value );
	cvar_t *( *Cvar_ForceSet )( const char *name, const char *value );      // will return 0 0 if not found
	float ( *Cvar_Value )( const char *name );
	const char *( *Cvar_String )( const char *name );

	int ( *Cmd_Argc )( void );
	char *( *Cmd_Argv )( int arg );
	char *( *Cmd_Args )( void );        // concatenation of all argv >= 1

	void ( *Cmd_AddCommand )( const char *name, void ( *cmd )( void ) );
	void ( *Cmd_RemoveCommand )( const char *cmd_name );
	void ( *Cmd_ExecuteText )( int exec_when, const char *text );
	void ( *Cmd_Execute )( void );
	void ( *Cmd_SetCompletionFunc )( const char *cmd_name, char **( *completion_func )( const char *partial ) );

	// files will be memory mapped read only
	// the returned buffer may be part of a larger pak file,
	// or a discrete file from anywhere in the quake search path
	// a -1 return means the file does not exist
	// NULL can be passed for buf to just determine existance
	int ( *FS_FOpenFile )( const char *filename, int *filenum, int mode );
	int ( *FS_Read )( void *buffer, size_t len, int file );
	int ( *FS_Write )( const void *buffer, size_t len, int file );
	int ( *FS_Print )( int file, const char *msg );
	int ( *FS_Tell )( int file );
	int ( *FS_Seek )( int file, int offset, int whence );
	int ( *FS_Eof )( int file );
	int ( *FS_Flush )( int file );
	void ( *FS_FCloseFile )( int file );
	qboolean ( *FS_RemoveFile )( const char *filename );
	int ( *FS_GetFileList )( const char *dir, const char *extension, char *buf, size_t bufsize, int start, int end );
	qboolean ( *FS_IsUrl )( const char *url );

	// clock
	unsigned int	( *Milliseconds )( void );
	quint64			( *Microseconds )( void );

	// renderer
	struct shader_s *( *R_RegisterPic )( const char *name );
	struct shader_s * ( *R_RegisterRawPic )( const char *name, int width, int height, qbyte *data );
	void ( *R_DrawStretchPic )( int x, int y, int w, int h, float s1, float t1, float s2, float t2, const vec4_t color, const struct shader_s *shader );
	void ( *R_SetScissorRegion )( int x, int y, int w, int h );
	void ( *R_GetScissorRegion )( int *x, int *y, int *w, int *h );

	// managed memory allocation
	struct mempool_s *( *Mem_AllocPool )( const char *name, const char *filename, int fileline );
	void *( *Mem_Alloc )( struct mempool_s *pool, int size, const char *filename, int fileline );
	void ( *Mem_Free )( void *data, const char *filename, int fileline );
	void ( *Mem_FreePool )( struct mempool_s **pool, const char *filename, int fileline );
	void ( *Mem_EmptyPool )( struct mempool_s *pool, const char *filename, int fileline );

	void *( *LoadLibrary )( const char *name, dllfunc_t *funcs );
	void ( *UnloadLibrary )( void **lib );
} ftlib_import_t;

//
// functions exported by the cinematics subsystem
//
typedef struct
{
	// if API is different, the dll cannot be used
	int ( *API )( void );

	// the init function will be called at each restart
	qboolean ( *Init )( qboolean verbose );
	void ( *Shutdown )( qboolean verbose );

	// core functions
	void ( *PrecacheFonts )( qboolean verbose );
	struct qfontface_s *( *RegisterFont )( const char *family, qfontstyle_t style, unsigned int size );
	void ( *TouchFont )( struct qfontface_s *qfont );
	void ( *FreeFonts )( qboolean verbose );

	// drawing functions
	size_t ( *FontHeight )( struct qfontface_s *font );
	size_t ( *StringWidth )( const char *str, struct qfontface_s *font, size_t maxlen );
	size_t ( *StrlenForWidth )( const char *str, struct qfontface_s *font, size_t maxwidth );
	void ( *DrawRawChar )( int x, int y, qwchar num, struct qfontface_s *font, vec4_t color );
	void ( *DrawClampString )( int x, int y, const char *str, int xmin, int ymin, int xmax, int ymax, struct qfontface_s *font, vec4_t color );
	size_t ( *DrawRawString )( int x, int y, const char *str, size_t maxwidth, struct qfontface_s *font, vec4_t color );
} ftlib_export_t;

#endif
