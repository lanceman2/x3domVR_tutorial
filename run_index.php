<!DOCTYPE html>
<html lang=en>
<head>
    <meta charset="UTF-8"/>
    <title>X3DOM Examples</title>
    <style>
        body {
            background-color: #B1D5E1;
        }
        td {
            padding: 10px;
            background-color: #A0B5D8;
        }
        th {
            background-color: #A0CAD8;
        }

    </style>
</head>
<body>

    <h1>X3DOM Examples</h1>

    <table border=3>

<?php


$files = array();

$dh = opendir(__DIR__);
while(($dir = readdir($dh)) !== false) {
    $rfile = '';
    if(is_dir($dir) && substr($dir, 0, 1) !== '.') {
        $rfile = $dir . DIRECTORY_SEPARATOR . 'run.html';
        if(file_exists(__DIR__ . DIRECTORY_SEPARATOR . $rfile)) {
        
            $sourcefiles = '';

            $h = opendir(__DIR__ . DIRECTORY_SEPARATOR . $dir);
            $readme = '';
            while(($f = readdir($h)) !== false) {
                if($f === '.description')
                    $readme = preg_replace('/\n$/','', file_get_contents(__DIR__ . DIRECTORY_SEPARATOR .
                        $dir . DIRECTORY_SEPARATOR . $f));
                else if(substr($f, 0, 1) !== '.')
                    $sourcefiles[] = $dir . DIRECTORY_SEPARATOR . $f;
            }
            closedir($h);

            $files[] = array($dir, $rfile, $sourcefiles, $readme);
        }
    }
}
closedir($dh);
sort($files);


echo <<<EOT

    <tr>
        <th>Description</th>
        <th>Directory</th>
        <th>Run</th>
        <th>View Source</th>
    </tr>

EOT;

$pre = 'view-source:' .
    $_SERVER['REQUEST_SCHEME'] . '://' .
    $_SERVER['SERVER_NAME'] . ':' .
    $_SERVER['SERVER_PORT'] . dirname($_SERVER['REQUEST_URI']);


foreach($files as $f) {
    echo <<<EOT
        <tr>
            <td>$f[3]</td>
            <td><a href="$f[0]">$f[0]</a></td>
            <td><a href="$f[1]">$f[1]</td>
            <td>
EOT;

    foreach($f[2] as $sf) {
        $name = basename($sf);
        $a = $pre . DIRECTORY_SEPARATOR . $sf;
        echo "<a href=\"$a\">$name</a>\n";
    }

    echo "            </td>\n       </tr>\n";
}

?>

    </table>

    <p>
    Note: view-source is broken on some versions of firefox.
    </p>

</body>
</html>
