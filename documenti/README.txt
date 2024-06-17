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
Una volta avviato aprire il cmd e degitare il seguente comando : composer install php-mqtt/client.

Ora è tutto pronto per l'uso.