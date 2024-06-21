<!DOCTYPE html>
<link rel="stylesheet" href="css\estetica.css">
<html>
<head>
    <title>Logout</title>
</head>

<body>
    <div class = "container">

    <?php
    session_start();

    if(isset($_SESSION["user"])){
        if(isset($_POST["logout"])){
            session_destroy();
            header("Location: index.php");
        }
    }
    else{
        header("Location: index.php");
    }

    ?>
        <form action = "logout" method = "post">
            <div class = "form-btn">
                <input type="submit" value = 'logout' class="btn btn-primary" name="logout">
            </div>
        </form>
</body>

</html>