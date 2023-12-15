<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="index.css">
    <title>Monitoring Solo Technopark</title>
</head>
<body>
    <header class="container">
        <h1>SisMon - NORK</h1>
        <ul>
            <li><a href=#>about SisMon</a></li>
            <li><a href=#>about Nork</a></li>
        </ul>
    </header>
    <section class="landing container">
        <h1>Hey</h1>
        <?php
            include "conn.php";
            $countVis = "SELECT COUNT(*) as rowCount FROM visitor";
            $countRes = $conn->query($countVis);
            if ($countRes !== FALSE) {
                $row = $countRes->fetch-assoc();
                $currentVisitor = $row['rowCount'];
                echo "current visitor is : '$currentVisitor'";
            } else {
                echo "No Visitor"
            } $conn->close();
        ?>
    </section>
</body>
</html>