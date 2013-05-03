#ifndef PHP_GFARM_H
#define PHP_GFARM_H

extern zend_module_entry gfarm_module_entry;
#define phpext_gfarm_ptr &gfarm_module_entry

#ifdef PHP_WIN32
#define PHP_GFARM_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#define PHP_GFARM_API __attribute__ ((visibility("default")))
#else
#define PHP_GFARM_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(gfarm);
PHP_MSHUTDOWN_FUNCTION(gfarm);
//PHP_RINIT_FUNCTION(gfarm);
//PHP_RSHUTDOWN_FUNCTION(gfarm);
PHP_MINFO_FUNCTION(gfarm);

/* gfarm functions */
PHP_FUNCTION(gfarm_initialize);
PHP_FUNCTION(gfarm_chmod);
PHP_FUNCTION(gfarm_chown);
PHP_FUNCTION(gfarm_mkdir);
PHP_FUNCTION(gfarm_rmdir);
PHP_FUNCTION(gfarm_open);
PHP_FUNCTION(gfarm_close);
PHP_FUNCTION(gfarm_read);
PHP_FUNCTION(gfarm_write);
PHP_FUNCTION(gfarm_seek);
PHP_FUNCTION(gfarm_flush);
PHP_FUNCTION(gfarm_truncate);
//PHP_FUNCTION(gfarm_test);


/* 
        Declare any global variables you may need between the BEGIN
        and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(gfarm)
        long  global_value;
        char *global_string;
ZEND_END_MODULE_GLOBALS(gfarm)
 */

/* In every utility function you add that needs to use variables 
   in php_gfarm_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as GFARM_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
 */

#ifdef ZTS
#define GFARM_G(v) TSRMG(gfarm_globals_id, zend_gfarm_globals *, v)
#else
#define GFARM_G(v) (gfarm_globals.v)
#endif

#endif	/* PHP_GFARM_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
