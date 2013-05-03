dnl $Id$
dnl config.m4 for extension gfarm

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(gfarm, for gfarm support,
dnl Make sure that the comment is aligned:
dnl [  --with-gfarm             Include gfarm support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(gfarm, whether to enable gfarm support,
Make sure that the comment is aligned:
[  --enable-gfarm           Enable gfarm support])

if test "$PHP_GFARM" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-gfarm -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/gfarm.h"  # you most likely want to change this
  dnl if test -r $PHP_GFARM/$SEARCH_FOR; then # path given as parameter
  dnl   GFARM_DIR=$PHP_GFARM
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for gfarm files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GFARM_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GFARM_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the gfarm distribution])
  dnl fi

  dnl # --with-gfarm -> add include path
  dnl PHP_ADD_INCLUDE($GFARM_DIR/include)

  dnl # --with-gfarm -> check for lib and symbol presence
  LIBNAME=gfarm # you may want to change this
  LIBSYMBOL=gfarm_initialize # you most likely want to change this 

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GFARM_DIR/lib, GFARM_SHARED_LIBADD)
    AC_DEFINE(HAVE_GFARMLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong gfarm lib version or lib not found])
  ],[
    -L$GFARM_DIR/lib -lm
  ])
 
  PHP_SUBST(GFARM_SHARED_LIBADD)

  PHP_NEW_EXTENSION(gfarm, gfarm.c, $ext_shared)
fi
