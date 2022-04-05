BUILT_SOURCES = parser.h
AM_YFLAGS = -d
AM_CPPFLAGS = -DPATH_DATADIR="\"$(datadir)\"" -I"/usr/include/opencascade" -I"/usr/local/include/opencascade"
AM_CPPFLAGS += $(LIBGTK4_CPP)
AM_LDFLAGS = -lTKSTL -lTKService -lTKOpenGl -lTKV3d -lTKPrim -lTKMesh -lTKBO -lTKBRep -lTKMath -lTKernel 
AM_LDFLAGS += $(LIBGTK4_LD) -lEGL
AM_LDFLAGS += -lpthread
bin_PROGRAMS = cascad
cascad_SOURCES = ast.c builtin.c compiler.c deps.c gui.c interpreter.c lexer.l lib.c main.c parser.y strutils.c tree.c
cascad_SOURCES += ast.h backend.h builtin.h cascad.h compiler.h context.h deps.h frontend.h gui.h interpreter.h lexer.h parser_interface.h resources.h strutils.h tree.h
cascad_SOURCES += backend/occt.cpp
cascad_SOURCES += frontend/gtk4.c
cascad_SOURCES += resources/render.c resources/stl.c
