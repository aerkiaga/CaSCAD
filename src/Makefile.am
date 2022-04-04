BUILT_SOURCES = parser.h
AM_YFLAGS = -d
AM_CPPFLAGS = -DPATH_DATADIR="\"$(datadir)\"" -I"/usr/include/opencascade" -lTKernel
AM_LDFLAGS = -lTKSTL -lTKPrim -lTKMesh -lTKBO -lTKBRep -lTKMath -lTKernel 
AM_LDFLAGS += $(LIBGTK4_LD)
bin_PROGRAMS = cascad
cascad_SOURCES = ast.c builtin.c compiler.c deps.c interpreter.c lexer.l lib.c main.c parser.y strutils.c tree.c
cascad_SOURCES += ast.h builtin.h cascad.h compiler.h context.h deps.h interpreter.h lexer.h parser_interface.h strutils.h tree.h backend.h
cascad_SOURCES += backend/occt.cpp
