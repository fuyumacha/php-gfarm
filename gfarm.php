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

$filename = md5(time());
$content = $filename.$filename.$filename.$filename.$filename;

// Gfarm initialize 
gfarm_initialize();

// Create and open the file
$fp = gfarm_open($filename);

// Write to file and get written size
echo gfarm_write($fp, $fuga);
echo "\n";

// Sets the file position indicator to 0 and get new file position;
echo gfarm_seek($fp, 0);
echo "\n";

// Read from file
echo gfarm_read($fp);


// Close the file
gfarm_close($fp);

// Gfarm terminate
gfarm_terminate();


echo "\n";
?>
