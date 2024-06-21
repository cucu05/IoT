<!DOCTYPE html>
<link rel="stylesheet" href="css\estetica.css">
<html>

<?php
    session_start();

    if(isset($_SESSION["user"])){
        header("Location: gpsGUI.php");
        die();
    }

    else{
        if(isset($_POST["login"])){
            require_once "database.php";
            $admin = $_POST["admin"];
            $password = $_POST["password"];
    
            $errors = false;
    
            $query = "SELECT * FROM user WHERE admin = '$admin'";
            $result = mysqli_query($conn,$query);
            $user = mysqli_fetch_array($result, MYSQLI_ASSOC);
            if($user){
                if(strcmp($password, $user['password'])){
                    $_SESSION["user"] = $user;
                    $_SESSION["id"] = $user["id"];
                    header("Location: gpsGUI.php");
                    die();
                }
                else{
                    echo "<error> Password sbagliata</error>";
                }
            }
            else{
                echo "<error>username errato</error>";
            }
        }

    }

    ?>

<head>
    <title>Login</title>
</head>

<h2>Log In</h2>

<body>
    <div class = "container">
        <form action = "login" method = "post">
            
            <div class = "input">
                <input type="text" class="form-control" name="admin" id="admin" placeholder="admin">
            </div>

            <span><span>

            <div class = "input">
                <input type="password" class="form-control" name="password" id="password" placeholder="password">
            </div>

            <div class = "form-btn">
                <input type="submit" value = 'Login' class="btn btn-primary" value="Register" name="login" id="submit">
            </div>

            <span><span>
        </form> 
    </div>
</body>


</html>