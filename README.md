# Cómo ejecutar
* Descargar el [server](https://github.com/lleps/Optimus-Roleplay-V3/archive/master.zip).
* Descargar [XAMPP](https://www.apachefriends.org/es/download.html) para tener base de datos MySQL.
* Iniciar **XAMPP** y poner **start** en el servicio Apache y en el servicio MySQL.
* Abrir el navegador e ir a http://localhost/phpmyadmin. Ir a **bases de datos** y crear una de nombre, ej, **dboptimus**.
* Entrar a la carpeta *scriptfiles/database.ini* y editar los datos en caso de ser necesario. En mi caso sería ``127.0.0.1|root|dboptimus|``
* Ejecutar **samp-server.exe**.

Si no compila o no ejecuta, descargar e instalar [MS10 runtime](https://www.microsoft.com/en-us/download/details.aspx?id=5555).

# Cómo importar la base de datos real
Hay un archivo **optimusv3.sql** en el directorio principal que tiene todos los usuarios y vehículos de Optimus antes de cerrar. Les eliminé los correos y las IPs de la gente por privacidad. Las claves estan encriptadas.
Para importarla, abrir el phpmyadmin, seleccionar la base de datos, ir a "Importar" en la columna de arriba y seleccionar el archivo .sql. 
Las casas, negocios y todos los otros datos están en scriptfiles. Iguales que como estaban en el server antes de cerrar.

# Cómo hacerse admin
Comando **/seradmin** te pone admin dueño.

# Sistema de PC en los negocios
Sirve para hacerle pedido de stock a los camioneros.

![img](https://i.gyazo.com/dd636721f53eef890bb77c4fec65224a.gif)

# Celular
![img](https://i.gyazo.com/ae1be53a13825370449661ce3d720670.gif)

# Comando /verlogs
![img](https://i.gyazo.com/55584a4018b077f3b76b9d41156290e1.png)

# Fábrica de armas
## Localización
![img](https://i.gyazo.com/31dd51fcb0ebd992c86f7a73054720aa.png)

## Para fabricar armas
![img](https://i.gyazo.com/dc89bd806734701e6752e4f1e1919ea0.png)
![img](https://i.gyazo.com/03de090b6754f10fbfec63d4140c984d.png)

## Para cambiar el propietario del laboratorio
Para que la conquiste una familia, se usa **/conquistar** en la puerta. Para cambiar qué familia la conquista manualmente, se edita en *scriptfiles/Laboratorios/BlackAsociation.dat* (editas el archivo con notepad, y le pones **[id de familia]=[1 cerrado/2 abierto]**. Por ejemplo, quiero que el laboratorio sea de la familia 5 y esté abierto, le pongo **5=0** en el archivo .dat y lo guardo. Reiniciar el server para que se apliquen los cambios.

# Fábrica de drogas

## Localización
![img](https://i.gyazo.com/0d5a48e5f2b37e737a5d59610d4dc4dd.png)

## Cómo crear droga
![img](https://i.gyazo.com/84750f19f320e330ce2c3ab2593a276b.png)

## Cómo crear plantas de coca

Usar **/planta_crear**.

![img](https://i.gyazo.com/af7b33530e2cb16f60c32748bb4c92c3.png)

Cuando se crea la droga, se genera un paquete de coca, que es un objeto que se puede guardar en maleteros, armarios, etc y tirar al piso. Para sacar droga del paquete usar /paquete.

# Armas de materiales
Se pueden obtener armas de oro (**+50% de daño**) y de diamante (**+75% de daño**). Se dan sólo por administradores con **/dararma [id de jugador] [id del arma]** (ejemplo **/dararma 0 24 1**). 
Cada arma tiene hasta 30 balas, después hay un objeto que es un cargador, que se guarda en el inventario. Los cargadores también se fabrican en la fabrica de armas. Para recargar un arma, necesitas el cargador en tu inventario y poner **/rec** o **/recargar**. 

![img](https://i.gyazo.com/1b14f00e2ce9f1b7b402f67935ba37c0.png)

# Panel de facción
Los lideres pueden editar los rangos de su faccion, y ver todos los miembros desconectados.

![img](https://i.gyazo.com/82e2e70c0aef32722725f05b2b58eea2.png)
![img](https://i.gyazo.com/e39df48ceb9a8c76a956f85fa40e98a3.png)
![img](https://i.gyazo.com/0a2975b9c4c06da7cd219edc47d47059.png)

El comando es **/faccion**. Necesitas ser lider.

# Ban temporal
**/bancuenta** sirve para banear jugadores por dias, horas o meses. Tanto conectados como desconectados.

# Sistema de mapas dinamico
En la carpeta scriptfiles/maps se pueden meter mapas en formato CreateDynamicObject o CreateObject y cargarlos o descargarlos dinámicamente. Por ejemplo, supongamos el archivo **maplspd.txt** con ``CreateObject(...);`` podés meter el archivo en la carpeta *scriptfiles/maps* y cargarlo con **/mapcargar maplspd.txt**. Podés descargarlo
con **/mapdescargar**. Y podes ver la lista de mapas cargados con **/maplist**.

# Barco de importaciones de armas.
Todos los sábados a las 6 de la tarde, llega un buque al puerto de LSEM cargado con cajas de armas y cargadores. El barco tiene movimiento, es realista. Se retira luego de 50 minutos ahí. El barco se puede forzar con el comando **/forzarimportaciones**.

![img](https://i.gyazo.com/703283e2db6d7c5b330f0cc2b7c1d7dd.png)
![img](https://i.gyazo.com/631ae46bb7a64942679a1df08b36f282.png)
![img](https://i.gyazo.com/80945ee1a1ee179e8c0ecff9c628ba5c.png)

# Trabajo de minero
En la mina de Huntle Charry se crean minerales en posiciones aleatorias para picar. Se pueden re-generar con **/recargarminerales**. Hay pocas posibilidades de generar diamante, otras pocas de generar oro, y varias de generar carbón y hierro. Para picarlo, necesitas el trabajo de minero (puedes dartelo con **/editarcuenta [Nombre_Apellido] Trabajo 8**)
y usar **/picar**. Después apretar click hasta llenar la barra.

![img](https://i.gyazo.com/824f1d0be1a1a2af4f7566f174735160.png)
![img](https://i.gyazo.com/2e10dc0e0d8edbbac8bbedcd2de20139.png)
