<?php

include('IXR_Library.php');

$client = new IXR_Client('http://localhost:8080/RPC2');
//$client = new IXR_Client('http://localhost:8080/server.php');
if (!$client->query('sample.add', 5, 7)) {
   die('An error occurred - '.$client->getErrorCode().":".$client->getErrorMessage());
}
$returnValue = $client->getResponse();
printf("The first array is %d the second array value is %.2f and the third array value is %s\n",$returnValue[0],$returnValue[1],$returnValue[2]);
?>
