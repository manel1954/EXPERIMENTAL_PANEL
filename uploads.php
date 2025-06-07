<?php
$upload_dir = '/home/pi/uploads/';

function limpiar_nombre($nombre) {
    return preg_replace('/[^a-zA-Z0-9._-]/', '_', $nombre);
}

$mensaje = '';
$imagen_subida = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_FILES['imagen']) && $_FILES['imagen']['error'] === UPLOAD_ERR_OK) {
        $tmp_name = $_FILES['imagen']['tmp_name'];
        $name = limpiar_nombre(basename($_FILES['imagen']['name']));

        $ext = strtolower(pathinfo($name, PATHINFO_EXTENSION));
        if ($ext === 'jpg' || $ext === 'jpeg') {
            $destino = $upload_dir . $name;

            if (move_uploaded_file($tmp_name, $destino)) {
                $mensaje = "Imagen subida y guardada correctamente.";
                $imagen_subida = "/uploads/" . $name;
            } else {
                $mensaje = "Error al mover el archivo.";
            }
        } else {
            $mensaje = "Solo se permiten archivos JPG/JPEG.";
        }
    } else {
        $mensaje = "No se ha recibido ningún archivo o hubo un error en la subida.";
    }
}
?>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8" />
    <title>Subir Imagen JPG</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
    <style>
        body { 
            max-width: 400px; 
            margin: 40px auto; 
            font-family: system-ui, sans-serif; 
        }
        img {
            max-width: 100%;
            height: auto;
            border: 1px solid #ddd;
            border-radius: 4px;
            margin-top: 1rem;
        }
    </style>
</head>
<body>
    <h3 class="mb-4 text-center">Subir imagen JPG</h3>

    <?php if ($mensaje): ?>
        <div class="alert alert-info" role="alert">
            <?= htmlspecialchars($mensaje) ?>
        </div>
    <?php endif; ?>

    <form method="post" enctype="multipart/form-data" class="d-flex flex-column gap-3">
        <input class="form-control" type="file" name="imagen" accept=".jpg,.jpeg" required>
        <button class="btn btn-primary" type="submit">Subir imagen</button>
    </form>



    <?php if ($mensaje): ?>
    <script>
        // Oculta el mensaje después de 3 segundos
        setTimeout(() => {
            const alert = document.querySelector('.alert');
            if(alert) alert.style.display = 'none';
        }, 3000);
    </script>
    <?php endif; ?>
</body>
</html>
