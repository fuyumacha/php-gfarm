<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('gfarm')) {
	dl('gfarm.' . PHP_SHLIB_SUFFIX);
}
$module = 'gfarm';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";

gfarm_test();
gfarm_initialize();
$res = gfarm_open("file1");
gfarm_close($res);


echo "\n";
?>
