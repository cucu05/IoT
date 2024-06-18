<?php

require('vendor/autoload.php');

use \PhpMqtt\Client\MqttClient;
//require ('Client/src/MqttClient.php');

// DB
$servername = "localhost";      //appena creato il database con quel nome su phpmyadmin inserisci questi dati
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
$server   =  '192.168.62.173' ; //prova con questo, prima era selezionato la public key del video  'broker.emqx.io'
$port     = 1883;                //1883
$clientId = 'gps_tracker';
// $username = 'emqx_user';
// $password = 'password';
// $clean_session = false;
// $mqtt_version = MqttClient::MQTT_3_1_1;

// $connectionSettings = (new ConnectionSettings)
//   ->setUsername($username)
//   ->setPassword($password)
//   ->setKeepAliveInterval(60)
//   ->setLastWillTopic('last-will')
//   ->setLastWillMessage('client disconnect')
//   ->setLastWillQualityOfService(1);

// $mqtt = new MqttClient($server, $port, $clientId, $mqtt_version);
// $mqtt->connect($connectionSettings, $clean_session);


$mqtt = new MqttClient($server, $port, $clientId);
$mqtt->connect();
printf("MQTT connected\n");

$mqtt->subscribe('GpsInfo/P1', function ($topic, $message) use ($conn) {
    printf("\n\n\nReceived message on topic [%s]: %s\n", $topic, $message);
    $data = json_decode($message);
    //$data = $message;

    //$pieces = explode(",", $data);

    //$position = $data->position;
    $icon = $data->icon;
    //$color = $data->color;
    $lat = $data->lat;
    $lon = $data->lon;

    $query = "INSERT INTO position (lat, lg) VALUES ('$lat','$lon');";
    mysqli_query($conn, $query);
    printf("Data Stored Successfully :)");
}, 0);

$mqtt->loop(true);