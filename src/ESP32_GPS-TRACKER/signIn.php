<!DOCTYPE html>
<link rel="stylesheet" href="css\estetica.css">
<html>
<head>
    <title>Sign In</title>
</head>

<?php
    if(isset($_POST["submit"])){
        require_once "database.php";
        $admin = $_POST["admin"];
        $password = $_POST["password"];
        $passwordHash = password_hash($password, PASSWORD_DEFAULT);

        $errors = false;

        $query = "SELECT * FROM user WHERE admin = '$admin'";
        $result = mysqli_query($conn,$query);
        $row_count = mysqli_num_rows($result);

        if($row_count>0){
            $errors = true;
            echo "<error> Errore </error>";
        }

        if($errors==false){
            $query = "INSERT INTO user (admin, password) VALUES ('$admin', '$passwordHash')";
            mysqli_query($conn,$query);
            header("Location: index");
            die();
        }
        
    }

    ?>

<body>
    <div class = "contanier">
 
        <h2>Sign In</h2>
        <form action = "signIn" method = "post">

            <div class = "input">
                <input type="text" class="form-control" name="admin" id="admin" placeholder="admin">
            </div>

            <span><span>

            <div class = "input">
                <input type="password" name="password" id="password" placeholder="password">
            </div>

            <span><span>

            <div class = "submit">
                <input type="submit" class="btn btn-primary" value="Register" name="submit" id="submit">
            </div>
        </form>
    </div>
</body>



</html>