<?php
include('IXR_Library.php');

function add($args) {
    $returnValue = array(7,2.78,"hello world");
    return $returnValue;
}

$server = new IXR_Server(array(
    'sample.add' => 'add',
));
?>
