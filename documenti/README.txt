Il progetto è sviluppato per lavorare esclusivamente in locale (localhost) tramite il server web XAMPP.
Prima dell'esecuzione del software preliminarmente seguire le seguenti istruzioni per la corretta configurazione di XAMPP:
-Installare XAMPP 
-Inserire in "\xampp\htdocs" la cartella del progetto.
-Avviare lo XAMPP Control Panel.
-Avviare Apache e MySQL cliccando l'apposito tasto start.
-Cliccare l'apposito tasto admin per aprire la pagina web e il database tramite phpadmin.
-Creare in phpadmin un nuovo database.
-Importare il file database.dump fornito.

Per la connessione MQTT server invece va installata la libreria php-mqtt/client dal gestore di pacchetti php Composer.
Per installarlo scarica da getcomposer.org il Composer-setup.exe
Una volta avviato aprire il cmd e digitare il seguente comando : composer install php-mqtt/client.

Per l'installazione e configurazione del server MQTT si devono eseguire i seguenti comandi:
-sudo apt install -y mosquitto
-sudo systemctl enable mosquitto.service

Poi è necessaria la modifica del file mosquitto.conf con questo comando:
-sudo vim /etc/mosquitto/mosquitto.conf

Adesso scrivi nel file
listener 1883
allow_anonymoous true

Infine
-sudo systemctl restart mosquitto

Per l'esecuzione del programma va prima lanciato il file .ino .Avendo caricato sia il codice sorgente sull'esp32 e stabilito la connessione MQTT col broker, poi va eseguito il file db.php nella cartella MQTT per poter stabilire una connessione col database. Per l'utilizzo del sito web va inserito negli htdocs di xampp la cartella ESP_GPS-TRACKER.


Ora è tutto pronto per l'uso.