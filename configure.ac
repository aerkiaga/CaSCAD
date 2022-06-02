AC_PREREQ([2.69])
AC_INIT([CaSCAD], [0.1.0])
AC_CONFIG_SRCDIR([src/main.c])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_HEADERS([src/config.h])
LT_INIT()

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([TKernel], [_ZN8Standard8AllocateEm])
AC_CHECK_LIB([TKMath], [_ZN6gp_Ax2C2ERK6gp_PntRK6gp_Dir])
AC_CHECK_LIB([TKBRep], [_ZNK13TopoDS_TSolid9EmptyCopyEv])
AC_CHECK_LIB([TKMesh], [_ZN24BRepMesh_IncrementalMeshC2ERK12TopoDS_Shapedbdb])
AC_CHECK_LIB([TKBO], [_ZN16BRepAlgoAPI_FuseC2ERK12TopoDS_ShapeS2_RK21Message_ProgressRange])
AC_CHECK_LIB([TKPrim], [_ZN20BRepPrimAPI_MakeConeC2Eddd])
AC_CHECK_LIB([TKSTL], [_ZN6StlAPI5WriteERK12TopoDS_ShapePKcb])

# Optional GTK4 frontend
AC_ARG_WITH([gtk4],
  [AS_HELP_STRING([--with-gtk4],
    [Add GTK4 GUI frontend @<:@default=check@:>@])],
  [],
  [: m4_divert_text([DEFAULTS], [with_gtk4=check])])

LIBGTK4=
AS_IF([test "x$with_gtk4" != xno],
  [AC_CHECK_LIB([gtk-4], [gtk_application_window_new],
    [AC_SUBST([LIBGTK4_LD], [`pkg-config --libs gtk4`])
     AC_SUBST([LIBGTK4_CPP], [`pkg-config --cflags gtk4`])
     AC_DEFINE([HAVE_LIBGTK4], [1],
               [Define if machine has GTK4])
    ],
    [if test "x$with_gtk4" != xcheck; then
       AC_MSG_FAILURE(
         [--with-gtk4 was given, but test for gtk4 failed])
     fi
    ], -lncurses)])

# Optional GL 4 frontend
AC_ARG_WITH([gl4],
  [AS_HELP_STRING([--with-gl4],
    [Add GL 4 GUI frontend @<:@default=check@:>@])],
  [],
  [: m4_divert_text([DEFAULTS], [with_gl4=check])])

LIBGTK4=
AS_IF([test "x$with_gl4" != xno],
  [AC_CHECK_LIB([GL], [glDrawBuffers],
    [AC_SUBST([LIBGL4_LD], ["`pkg-config --libs gl` -ldl"])
     AC_SUBST([LIBGL4_CPP], [`pkg-config --cflags gl`])
     AC_DEFINE([HAVE_LIBGL], [1],
               [Define if machine has GL])
    ],
    [if test "x$with_gl4" != xcheck; then
       AC_MSG_FAILURE(
         [--with-gl4 was given, but test for GL failed])
     fi
    ], -lncurses)])


# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([inttypes.h libintl.h limits.h malloc.h stddef.h stdint.h stdlib.h string.h threads.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([basename dirname isalpha isdigit memset realpath strchr strcmp strcspn strdup strndup strrchr vsnprintf])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
