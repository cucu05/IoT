<!DOCTYPE html>
<link rel="stylesheet" href="css\estetica.css">
<html lan="it">

<?php
    session_start();
    require_once "database.php";

    $list = "SELECT * FROM position";
    $result = mysqli_query($conn,$list);
    $row_count = mysqli_num_rows($result);
?>

<head>
    <meta charset="UTF-8">
    <title>Data</title>
</head>

<body>
        <h1>Tabella Posizioni</h1>
        <table class ="center">
            <thead>
                <tr>
                    <th>ID</th>
                    <th>latitudine</th>
                    <th>longitudine</th>
                </tr>    
            </thead>
            <tbody>
                <?php
                if($row_count > 0){
                    while($obj = mysqli_fetch_array($result, MYSQLI_ASSOC)){
                        echo "<tr>";
                        echo "<td>" . $obj['id'] . "</td>";
                        echo "<td>" . $obj['lat'] . "</td>";
                        echo "<td>" . $obj['lg'] . "</td>";
                        echo "</tr>";
                    }
                }
                else{
                    echo "<error>Nessuna posizione registrata</error>";
                }
                ?>
            </tbody>
        </table>
</body>

</html>