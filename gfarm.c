#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_gfarm.h"

#include <gfarm/gfarm.h>

/* True global resources - no need for thread safety here */
static int le_gfarm;
#define le_gfarm_name "Gfarm Buffer"

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_chmod, 0)
ZEND_ARG_INFO(0, gfarm_url)
ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_chown, 0)
ZEND_ARG_INFO(0, gfarm_url)
ZEND_ARG_INFO(0, username)
ZEND_ARG_INFO(0, groupname)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_mkdir, 0)
ZEND_ARG_INFO(0, gfarm_url)
ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_rmdir, 0)
ZEND_ARG_INFO(0, gfarm_url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_open, 0)
ZEND_ARG_INFO(0, gfarm_url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_close, 0)
ZEND_ARG_INFO(0, gfarm)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_read, 0)
ZEND_ARG_INFO(0, gfarm)
ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_write, 0)
ZEND_ARG_INFO(0, gfarm)
ZEND_ARG_INFO(0, buffer)
ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_seek, 0)
ZEND_ARG_INFO(0, gfarm)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, whence)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_flush, 0)
ZEND_ARG_INFO(0, gfarm)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gfarm_truncate, 0)
ZEND_ARG_INFO(0, gfarm)
ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

/* {{{ gfarm_functions[]
 *
 * Every user visible function must have an entry in gfarm_functions[].
 */
const zend_function_entry gfarm_functions[] = {
    /* gfarm functions */
    //    PHP_FE(gfarm_test, NULL)
    PHP_FE(gfarm_initialize, NULL)
    PHP_FE(gfarm_chmod, arginfo_gfarm_chmod)
    PHP_FE(gfarm_chown, arginfo_gfarm_chown)
    PHP_FE(gfarm_mkdir, arginfo_gfarm_mkdir)
    PHP_FE(gfarm_rmdir, arginfo_gfarm_rmdir)
    PHP_FE(gfarm_open, arginfo_gfarm_open)
    PHP_FE(gfarm_close, arginfo_gfarm_close)
    PHP_FE(gfarm_read, arginfo_gfarm_read)
    PHP_FE(gfarm_write, arginfo_gfarm_write)
    PHP_FE(gfarm_seek, arginfo_gfarm_seek)
    PHP_FE(gfarm_flush, arginfo_gfarm_flush)
    PHP_FE(gfarm_truncate, arginfo_gfarm_truncate)

    PHP_FE_END /* Must be the last line in gfarm_functions[] */
};
/* }}} */

/* {{{ gfarm_module_entry
 */
zend_module_entry gfarm_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "gfarm",
    gfarm_functions,
    PHP_MINIT(gfarm),
    PHP_MSHUTDOWN(gfarm),
    NULL, /* Replace with NULL if there's nothing to do at request start */
    NULL, /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(gfarm),
#if ZEND_MODULE_API_NO >= 20010901
    "0.1", /* Replace with version number for your extension */
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GFARM

ZEND_GET_MODULE(gfarm)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(gfarm) {
    /* If you have INI entries, uncomment these lines 
    REGISTER_INI_ENTRIES();
     */

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(gfarm) {
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
     */
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(gfarm) {
    php_info_print_table_start();
    php_info_print_table_header(2, "gfarm support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
     */
}

/* }}} */



//PHP_FUNCTION(gfarm_test) {
//    printf("hello!\n");
//    return;
//}


/* Every user-visible function in PHP should document itself in the source */

/* {{{ gfarm_initialize
 */
PHP_FUNCTION(gfarm_initialize) {
    gfarm_error_t gerr;
    gerr = gfarm_initialize(NULL, NULL);
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_TRUE;
    }
    return;
}
/* }}} */

/* {{{ gfarm_chmod
 */
PHP_FUNCTION(gfarm_chmod) {

    char *gfarm_url;
    int gfarm_url_len;
    mode_t mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "pl", &gfarm_url, &gfarm_url_len, &mode) == FAILURE) {
        RETURN_FALSE;
    }

    gfarm_error_t gerr;
    gerr = gfs_chmod(gfarm_url, mode);
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_TRUE;
    }

    return;
}
/* }}} */

/* {{{ gfarm_chown
 */
PHP_FUNCTION(gfarm_chown) {

    char *gfarm_url, *username, *groupname;
    int gfarm_url_len, username_len, groupname_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "pss", &gfarm_url, &gfarm_url_len, &username, &username_len, &groupname, &groupname_len) == FAILURE) {
        RETURN_FALSE;
    }

    gfarm_error_t gerr;
    gerr = gfs_chown(gfarm_url, username, groupname);
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_TRUE;
    }

    return;
}
/* }}} */

/* {{{ gfarm_mkdir
 */
PHP_FUNCTION(gfarm_mkdir) {

    char *gfarm_url;
    int gfarm_url_len;
    mode_t mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "pl", &gfarm_url, &gfarm_url_len, &mode) == FAILURE) {
        RETURN_FALSE;
    }

    gfarm_error_t gerr;
    gerr = gfs_mkdir(gfarm_url, mode);
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_TRUE;
    }

    return;
}
/* }}} */

/* {{{ gfarm_rmdir
 */
PHP_FUNCTION(gfarm_rmdir) {

    char *gfarm_url;
    int gfarm_url_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "p", &gfarm_url, &gfarm_url_len) == FAILURE) {
        RETURN_FALSE;
    }

    gfarm_error_t gerr;
    gerr = gfs_rmdir(gfarm_url);
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_TRUE;
    }

    return;
}
/* }}} */

/* {{{ gfarm_open
 */
PHP_FUNCTION(gfarm_open) {

    char *gfarm_url;
    int gfarm_url_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "p", &gfarm_url, &gfarm_url_len) == FAILURE) {
        RETURN_FALSE;
    }


    GFS_File gfs_file;
    gfarm_error_t gerr;
    gerr = gfs_pio_open(gfarm_url, GFARM_FILE_RDWR, &gfs_file);
    if (gerr != GFARM_ERR_NO_ERROR) {
        if (gerr == GFARM_ERR_NO_SUCH_FILE_OR_DIRECTORY) {
            gerr = gfs_pio_create(gfarm_url, GFARM_FILE_RDWR, 0000644, &gfs_file);
            if (gerr != GFARM_ERR_NO_ERROR) {
                php_error(E_ERROR, gfarm_error_string(gerr));
                RETURN_FALSE;
            } else {
                ZEND_REGISTER_RESOURCE(return_value, gfs_file, le_gfarm);
            }
        } else {
            php_error(E_ERROR, gfarm_error_string(gerr));
            RETURN_FALSE;
        }
    } else {
        ZEND_REGISTER_RESOURCE(return_value, gfs_file, le_gfarm);
    }

    return;
}
/* }}} */

/* {{{ gfarm_close
 */
PHP_FUNCTION(gfarm_close) {

    zval *z_gfs_file;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_gfs_file) == FAILURE) {
        RETURN_FALSE;
    }

    GFS_File gfs_file;
    ZEND_FETCH_RESOURCE(gfs_file, GFS_File, &z_gfs_file, -1, le_gfarm_name, le_gfarm);

    gfarm_error_t gerr;
    gerr = gfs_pio_close(gfs_file);
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_TRUE;
    }

    return;
}
/* }}} */

/* {{{ gfarm_read
 */
PHP_FUNCTION(gfarm_read) {

    zval *z_gfs_file;
    int size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &z_gfs_file, &size) == FAILURE) {
        RETURN_FALSE;
    }

    GFS_File gfs_file;
    ZEND_FETCH_RESOURCE(gfs_file, GFS_File, &z_gfs_file, -1, le_gfarm_name, le_gfarm);

    gfarm_error_t gerr;
    char *tmpbuf;
    int read_size;
    tmpbuf = emalloc(size + 1);
    gerr = gfs_pio_read(gfs_file, tmpbuf, size, &read_size);
    if (gerr != GFARM_ERR_NO_ERROR) {
        efree(tmpbuf);
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        tmpbuf = realloc(tmpbuf, read_size + 1);
        tmpbuf[read_size] = '\0';
        RETURN_STRING(tmpbuf, read_size + 1);
    }

    return;
}
/* }}} */

/* {{{ gfarm_write
 */
PHP_FUNCTION(gfarm_write) {

    zval *z_gfs_file;
    char *buffer;
    int buffer_len, size;


    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rsl", &z_gfs_file, &buffer, &buffer_len, &size) == FAILURE) {
        RETURN_FALSE;
    }

    GFS_File gfs_file;
    ZEND_FETCH_RESOURCE(gfs_file, GFS_File, &z_gfs_file, -1, le_gfarm_name, le_gfarm);

    gfarm_error_t gerr;
    int write_size;
    gerr = gfs_pio_read(gfs_file, buffer, MIN(size, buffer_len), &write_size);
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_LONG(write_size);
    }

    return;
}
/* }}} */

/* {{{ gfarm_seek
 */
PHP_FUNCTION(gfarm_seek) {

    zval *z_gfs_file;
    off_t offset, ret_offset;
    int whence;


    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &z_gfs_file, &offset, &whence) == FAILURE) {
        RETURN_FALSE;
    }

    GFS_File gfs_file;
    ZEND_FETCH_RESOURCE(gfs_file, GFS_File, &z_gfs_file, -1, le_gfarm_name, le_gfarm);

    gfarm_error_t gerr;
    gerr = gfs_pio_seek(gfs_file, offset, whence, &ret_offset); // SEEK_SET == GFARM_SEEK_SET?
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_LONG(ret_offset);
    }

    return;
}
/* }}} */

/* {{{ gfarm_flush
 */
PHP_FUNCTION(gfarm_flush) {

    zval *z_gfs_file;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &z_gfs_file) == FAILURE) {
        RETURN_FALSE;
    }

    GFS_File gfs_file;
    ZEND_FETCH_RESOURCE(gfs_file, GFS_File, &z_gfs_file, -1, le_gfarm_name, le_gfarm);

    gfarm_error_t gerr;
    gerr = gfs_pio_flush(gfs_file);
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_TRUE;
    }

    return;
}
/* }}} */

/* {{{ gfarm_flush
 */
PHP_FUNCTION(gfarm_truncate) {

    zval *z_gfs_file;
    int size;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &z_gfs_file, &size) == FAILURE) {
        RETURN_FALSE;
    }

    GFS_File gfs_file;
    ZEND_FETCH_RESOURCE(gfs_file, GFS_File, &z_gfs_file, -1, le_gfarm_name, le_gfarm);

    gfarm_error_t gerr;
    gerr = gfs_pio_truncate(gfs_file, size);
    if (gerr != GFARM_ERR_NO_ERROR) {
        php_error(E_ERROR, gfarm_error_string(gerr));
        RETURN_FALSE;
    } else {
        RETURN_TRUE;
    }

    return;
}
/* }}} */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
