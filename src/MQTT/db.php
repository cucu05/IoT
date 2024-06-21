<?php

require('vendor/autoload.php');

use \PhpMqtt\Client\MqttClient;


// DB
$servername = "localhost";      
$dBUsername = "root";
$dBPassword = "";
$dBName = "gps";

$conn = mysqli_connect($servername, $dBUsername, $dBPassword, $dBName);
if (!$conn) {
	die("Connection failed: ".mysqli_connect_error());
} else {
    printf("Database connected\n");
}

// MQTT Credentials
// EMQX Public
$server   =  '192.168.62.173' ; 
$port     = 1883;                
$clientId = 'gps_tracker';


$mqtt = new MqttClient($server, $port, $clientId);
$mqtt->connect();
printf("MQTT connected\n");

$mqtt->subscribe('GpsInfo/P1', function ($topic, $message) use ($conn) {
    printf("\n\n\nReceived message on topic [%s]: %s\n", $topic, $message);
    $data = json_decode($message);

    $icon = $data->icon;
    $lat = $data->lat;
    $lon = $data->lon;

    $query = "INSERT INTO position (lat, lg) VALUES ('$lat','$lon');";
    mysqli_query($conn, $query);
    printf("Data Stored Successfully :)");
}, 0);

$mqtt->loop(true);