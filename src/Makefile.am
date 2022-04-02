BUILT_SOURCES = parser.h
AM_YFLAGS = -d
AM_CPPFLAGS = -DPATH_DATADIR="\"$(datadir)\""
bin_PROGRAMS = cascad
cascad_SOURCES = ast.c compiler.c deps.c interpreter.c lexer.l lib.c main.c parser.y strutils.c tree.c
cascad_SOURCES += ast.h cascad.h compiler.h context.h deps.h interpreter.h lexer.h parser_interface.h strutils.h tree.h
