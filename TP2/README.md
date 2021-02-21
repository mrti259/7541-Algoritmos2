# Pokémon

Simulador de combate de Pokémon por consola.

## Introducción

Crea un personaje y elige a tu primero Pokémon.
Despues entrenta a tus enemigos para conseguir más Pokémon.
¿Podrás ser el mejor?

## Jugar

Para jugar es necesario que tengas gcc, make y estes en un sistema basado en *Unix.

En una consola ejecuta los siguientes comandos

> make

  Te creará el ejecutable y los directorios necessarios para empezar tu aventura.

> ./juego.bin

  Para iniciar el juego

## Desarrollo

Este trabajo fue hecho para la asignatura Algoritmos y Programación 2 de la Facultad de Ingeniería de la Universidad de Buenos Aires. La consigna se encuentra en la carpeta docs.

En juego.h se encuentran las funciones esenciales para reproducir la logica del juego.

En inicio.c se brindan las funciones que permiten darle una interfaz por consola al juego para facilitar su jugabilidad.

### Sobre el juego

#### Pokémon

Son pequeñas bestias hechas para combatir entre ellas.

#### Entrenadores

Son personajes que cuentan con uno o varios Pokémon.

#### Gimnasios

En ellos se encuentra uno o más entrenadores, donde el entrenador principal es el líder.

#### Personaje principal

Es el personaje que manejará el jugador, es un entrenador más. Su misión es combatir a los entrenadores de los Gimnasios y vencer a su lider hasta convertirse en un Maestro Pokémon.
