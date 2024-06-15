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
$server   = 'broker.emqx.io' ; //prova con questo, prima era selezionato la public key del video "192.168.62.173"
$port     = 1883;
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

    printf("device_id: %s\n", $data->device_id);
    printf("type: %s\n", $data->type);
    printf("value: %s\n", $data->value);

    $device_id = $data->device_id;
    $type = $data->type;
    $value = $data->value;

    $query = "INSERT INTO position (device_id, lat, lg) VALUES ($device_id, '$type','$value');";
    mysqli_query($conn, $query);
    printf("Data Stored Successfully :)");
}, 0);

$mqtt->loop(true);