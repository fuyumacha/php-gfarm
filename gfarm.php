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

echo "start file creation test\n";
gfarm_initialize();
$res = gfarm_open(md5(time()));
echo "------------------\nwrite start\n------------------\n";
$fuga = "fuga";
echo gfarm_write($res, $fuga);
echo "\n";
echo "------------------\nread1 start\n------------------\n";
echo "Seek set: ".gfarm_seek($res, 0)."\n";
echo gfarm_read($res);

echo "------------------\nread2 start\n------------------\n";
echo "Seek set: ".gfarm_seek($res, 0)."\n";
echo gfarm_read($res, 2);


gfarm_close($res);
gfarm_terminate();


echo "\n";
?>
