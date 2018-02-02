# Tarea-5---Detector-de-ca-da-libre

Diseñar, escribir y probar un módulo en la K64 para detectar caída libre, con sus respectivos archivos: free_fall.h y  free_fall.c, que dependan internamente del módulo de i2c. Este módulo tiene una función para inicializar lo que tenga que inicializar y otra para revisar si en ese momento se está o no en caída libre.

En el código main no se deberá acceder ni configurar nada de i2c directamente, todo eso deberá estar encapsulado en el módulo de free_fall.

Cuando se detecte caída libre y solo en ese caso (esto es únicamente cuando la tarjeta esta en el aire, no cuando la tienes en tus manos o tu la mueves), el led rojo debe parpadear a una frecuencia de 4Hz.

Todo el código deberá ser compatible con el standard de Michael Barr para C embebido (Esto incluye comentarios estilo Doxygen).

El equipo que genere la versión de este módulo mas robusta (la que mejor distinga entre una verdadera caída libre y un falso positivo: como agitar la tarjeta) se lleva un punto extra sobre 10 en el examen 1. 
