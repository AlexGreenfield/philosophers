# Philosophers
42 project for learning algorithms and synchronization problems

## Paralelismo vs Concurrencia

Lo primero de todo, el problema de los filosofos explicado por una de mis series favoritas, [Pantheon](https://www.netflix.com/es-en/title/81937398) (hazte un favor, haz click en la imagen y miratela).

[![Pantheon](imgs/pantheon.gif)](https://www.youtube.com/watch?v=V0_PU7GEJPg)

Antes de hablar sobre hilos y procesos, tenemos que explicar la diferencia entre dos conceptos: el paralelismo y la concurrencia. Aunque son muy parecidos, hay algunas diferencias cruciales, sobre todo en la gestión de recursos.

* Paralelismo: varios procesos / hilos se ejecutan de manera totalmente paralela. Cada uno tiene sus propios recursos, por lo que no hay conflictos en la gestión de los mismos. Cada proceso / hilo puede operar de forma totalmente independiente.

* Concurrencia: varios procesos / hilos se ejecutan compartiendo los mismos recursos. Esto puede dar un conflicto de los mismos si dos procesos / hilos itnenta usar el mismo recurso (archivo, variable...) a la vez. Es necesario gestionar el orden y el uso de estos recursos.

Para que te hagas una idea, es como si en una oficina se organizan en dos filas para comprar un refresco. En el paralelismo, hay dos maquinas, por lo que cada fila avanza de forma independiente y no hay problemas para gestionar los recursos.

Pero en la concurrencia, aún habiendo dos filas, hay sólo una máquina. Por lo que cada fila se tiene que poner de acuerdo en el orden en el que van usando la misma máquina.

![Concurrency vs Parallelism](imgs/parallelism.png)

## Procesos e hilos

### ¿Qué es un hilo?

Un hilo se trata de la unidad de ejecución más pequeña dentro de un proceso. Es decir, cuando lanzamos un hilo en nuestro código estamos diciendole a nuestro programa que realize una serie de acciones de manera "simultanea" a nuestro proceso principal, lo que nos permite llamar a otras funciones dentro del orden de ejecución de nuestro programa. Para resumir, si pensamos en la ejecución normal de nuestro programa como el hilo principal, el uso de multiples hilos nos permite ejecutar otras funciones a la par.

![Single Thread vs Multi Thread](imgs/thread1.png)

Sin embargo, no hay que dejarse engañar. Los hilos normalmente no se ejecutan totalmente en paralelo de manera real, si no que se van alternando rápidamente entre ellos para que de la sensación de que se están ejecutando de manera paralela e independiente. Para que se puedan ejecutar de manera paralela de forma real es necesario que la CPU cuente con varios nucleos. Sólo así se puede asegurar que los hilos se ejecutan simultaneamente.

Para crear un proceso, podemos usar la librería `pthread.h` y la función `pthread_create`.

```c
#include <pthread.h>

pthread_t your_thread;

int pthread_create(
    pthread_t *thread,
    const pthread_attr_t *attr,
    void *(*start_routine) (void *),
    void *arg);
```

Para manejar `pthread`, primero necesitamos una estructura `pthread_t` que aloje la información sobre nuestro hilo, como su id. `pthread_create` es el encargado de crear un nuevo hilo, darle una id y ejecutar una función (llamada routine) en concreto. En error, `pthread_create` devuelve una flag, lo que se puede usar como mecanismo de control.

<details>
<summary>🔍 Ejemplo de código</summary>

```c
#include <pthread.h>
#include <unistd.h>

void* routine() {
    printf("Hello from threads\n");
    sleep(3);
    printf("Ending thread\n");
}

int main(int argc, char* argv[]) {
    pthread_t p1;

    if (pthread_create(&p1, NULL, &routine, NULL) != 0)
        return 1;
    return 0;
}
```
</details>

<br>

Pero al igual que con `fork`, tenemos que indicarle al proceso que espere a que estos hilos terminen de ejecutarse antes de acabar la ejecución del programa, si no puede que se queden con tareas pendientes por hacer. Para ello utilizamos `pthread_join` (muy parecida a `wait`). Al igual que `pthread_create`, `pthread_join` devuelve flag en caso de error, lo que podemos usar como mecanismo de control.

```c
#include <pthread.h>

int pthread_join(
    pthread_t thread,
    void **retval);
```

<details>
<summary>🔍 Ejemplo de código</summary>

```c
#include <pthread.h>
#include <unistd.h>

void* routine() {
    printf("Hello from threads\n");
    sleep(3);
    printf("Ending thread\n");
}

int main(int argc, char* argv[]) {
    pthread_t p1;

    if (pthread_create(&p1, NULL, &routine, NULL) != 0)
        return 1;
	if (pthread_join(p1, NULL) != 0)
        return 2;
    return 0;
}
```
</details>

### ¿En qué se diferencia un hilo de un proceso?

Cada proceso tiene asociados una serie de recursos asignados, como puede ser el stack o su registro, pero también otros elementos como las señales del sistema o el acceso a diferentes archivos y sus file descriptors. Por ejemplo, si desde una llamada a `fork` abrimos un file descriptor, no podremos acceder a él desde otro proceso. O si cambiamos una variable, su valor sólo se modificará dentro de ese `fork`, no afectará al conjunto del programa. Es decir, que una vez creados los procesos no comparten los mismos recursos entre entre ellos, sino que el sistema aloja unos nuevos recursos para cada proceso de manera individual.

![Processes don't share resources and it's harder for them to communicate](imgs/thread2.png)

Por el contrario, los hilos nacen de un mismo proceso, por lo que sí que comparten recursos y memoria. Esto los hace mucho más ligeros (no hay que destinar recursos nuevos) y hace más sencilla la comunicación entre ellos. Esto hace que si un hilo abre un file descriptor o accede a una variable, estos cambios afectan al resto de hilos, por lo que los cambios afectan al conjunto de hilos. Esto los hace mucho más eficientes para según que tareas.

![Threads share resources and it's easier for them to communicate](imgs/thread3.png)

En resumen, dependiendo del contexto es más útil utilizar uno u otro teniendo en cuenta sus diferencias.

| **Característica**  | **Proceso**                       | **Hilo**                             |
|---------------------|-----------------------------------|---------------------------------------|
| **Memoria**         | Aislada (independiente)           | Compartida con su proceso             |
| **Velocidad**       | Más lento (mayor sobrecarga)      | Más rápido (menos sobrecarga)         |
| **Comunicación**    | Más compleja (IPC)                | Más sencilla (memoria compartida)     |
| **Fallos**          | No afecta a otros procesos        | Puede afectar a otros hilos del proceso |
| **Uso**             | Programas independientes          | Tareas simultáneas dentro de un programa |

### Obtener el valor de retorno de un hilo

Uno de los puntos fuertes de los hilos es que, al compartir los mismos recursos que el proceso principal, es mucho más fácil obtener valores de retorno. Mientras que en un `fork` tendríamos que abrir un `pipe` para que ambos procesos se comunicen entre sí, con los hilos podemos obtener estos valores dentro de la propia llamada a `thread`.

Como has podido ver, el segundo valor de `pthread_create` es una función que devuelve un `void *` (recuerda que se pueden usar como cualquier valor con un casteo, como un `char *` o un `int *`). Para retornar y obtener el valor de esta función tenemos que usar el segundo argumento de `pthread_join`, `**retval`. Es decir, que obtenemos una dirección de memoria a un puntero (de ahí que emplee `**` y no sólo `*`).

El gran problema que tenemos a la hora de usar punteros de esta forma es que las variables que creemos dentro de la función del hilo se generan en el `stack`, por lo que al acabarse el hilo esa dirección de memoria se va a dealocar y nos va a dar un error. Por eso es importante que los valores que queramos devolver de una función usando hilos estén alojados con `malloc`.

<details>
<summary>🔴 Código erróneo retornando una variable local</summary>

```c
#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    int result = 42;  // Local variable (stored on stack)
    return &result;   // WARNING: Returning address of local variable
}

int main() {
    pthread_t thread;
    int* thread_result;

    // Create the thread
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish and retrieve the result
    if (pthread_join(thread, (void**)&thread_result) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    // Print the result (this will likely be garbage or crash)
    printf("Thread returned: %d\n", *thread_result);  // Undefined behavior!

    return 0;
}
```
</details>

<br>

<details>
<summary>✅ Código correcto, alojando dinámicamente el resultado de una variable local</summary>

```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* thread_function(void* arg) {
    int* result = malloc(sizeof(int));  // Allocate memory on the heap
    *result = 42;  // Store the value
    return result;  // Return the allocated memory
}

int main() {
    pthread_t thread;
    int* thread_result;

    // Create the thread
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish and retrieve the result
    if (pthread_join(thread, (void**)&thread_result) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    // Print the result
    printf("Thread returned: %d\n", *thread_result);

    // Free the allocated memory
    free(thread_result);

    return 0;
}
```
</details>

En este ejemplo la alocación de la memoria tiene lugar dentro de la rutina, mientras que la liberación de la memoria se hace en el main. Esto es una mala práctica (puede llevar a errores, hasta que no llegas al free no sabes result está alojado dinamicamente en otra función), así que lo mejor es pasar nuestras variables como un argumento para la rutina.

### Cómo pasar argumentos a un hilo

El cuarto argumento de `pthread_create` es un `void *`, por lo que podemos usar un puntero o la dirección de memoria de una variable para pasar toda la información necesaria a nuestra rutina a través de una estructura, por ejemplo. Recuerda siempre castear este `void *` al tipo que necesites dentro de la rutina para evitar warnigns en el compilador.

<details>
<summary>🔍 Ejemplo de código</summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function
void* print_number(void* arg) {
    int num = *((int*)arg);  // Cast and dereference the argument
    printf("Thread received number: %d\n", num);
    return NULL;
}

int main() {
    pthread_t thread;
    int value = 42;  // The argument to pass

    // Create a new thread and pass the address of 'value'
    if (pthread_create(&thread, NULL, print_number, &value) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);
    return 0;
}
```
</details>

Si juntamos la capacidad de pasar argumentos a la rutina con `pthread_create` y retornando su valor con `pthread_join`, nuestro código ya va cogiendo forma.

<details>
<summary>🔍 Ejemplo de código</summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function
void* return_number(void* arg) {
    int num = *((int*)arg);  // Cast and dereference the argument
    int* result = malloc(sizeof(int));  // Allocate memory for return value
    *result = num * 2;  // Example: Modify the number
    return (void*)result;
}

int main() {
    pthread_t thread;
    int value = 42;  // The argument to pass
    int* thread_result;

    // Create a new thread and pass the address of 'value'
    if (pthread_create(&thread, NULL, return_number, &value) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish and retrieve the returned value
    if (pthread_join(thread, (void**)&thread_result) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    // Print the returned value
    printf("Main received number from thread: %d\n", *thread_result);

    // Free allocated memory
    free(thread_result);

    return 0;
}
```
</details>

### Manejando varios hilos: qué son las Race Conditions y cómo gestionar recursos con Mutex

Que los threads compartan recursos es una ventaja... pero también puede suponer un problema si dos hilos quieren acceder al mismo recurso a la vez, como una variable. Esto es lo que se conoce como Race Conditions: cuando varios hilos intentan acceder al mismo recurso a la vez y se tienen que decidir las condiciones y el orden en el que los hilos van a acceder a este recurso.

Por ejemplo, si varios hilos intentan acceder a una misma variable, puede que modifiquen su valor de manera desordenada, lo que hace que el programa no funcione como se espera. Un ejemplo, en un programa en el que un hilo suma 300$ a una cuenta y otro hilo suma 200$, puede que el segundo hilo lea el valor total de la cuenta antes de que al primer hilo le de tiempo a cambiar su valor, por lo que sumará erroneamente el valor total.

| Thread #1                | Thread #2                | Bank Balance |
|--------------------------|--------------------------|--------------|
| Read Balance  <-----------|                          | 0            |
| balance = 0               |                          |              |
|                          | Read Balance  <-----------| 0            |
|                          | balance = 0              |              |
| Deposit +300              |                          | 300          |
| balance = 300             |                          |              |
|                          | Deposit +200             | 200          |
|                          | balance = 200            |              |
| Write Balance  ---------->|                          | 300          |
| balance = 300             |                          |              |
|                          | Write Balance  --------->| 200          |
|                          | balance = 200            |              |


La mala gestión de estas condiciones también puede llevar a que un hilo llegue a acceder a uno de estos recursos y nunca lo suelte, por lo que el resto de hilos se quedarán esperando hasta que esté liberado (osease, hasta el infinito).

Esto se conoce como **Deadlock**, y es uno de los problemas más recurrentes a la hora de utilizar varios hilos.

![Deadlock state where two process are waiting indefinitely](imgs/thread4.jpg)

Para establecer en qué orden los hilos van a acceder a los diferentes recursos del proceso, tenemos que usar `mutex`. `mutex` actua como una especie de semaforo que es capaz de evitar que un hilo acceda a una función mientras otro hilo la esté ejecutando, una protección frente a otros threads.

Para usarla, tenemos que  declarar una estructura `pthread_mutex_t`, inicializarla con `pthread_mutex_init` y elegir en qué rango del código queremos implementarla con `pthread_mutex_lock` y `pthread_mutex_unlock`. Por supuesto, esta estructura también se tiene que liberar con `pthread_mutex_destroy`.

```c
pthread_mutex_t your_mutex;

int pthread_mutex_init(
    pthread_mutex_t *mutex,
    const pthread_mutexattr_t *attr);

int pthread_mutex_lock(
    pthread_mutex_t *mutex);

int pthread_mutex_unlock(
    pthread_mutex_t *mutex);

int pthread_mutex_destroy(
    pthread_mutex_t *mutex);
```

<details>
<summary>🔍 Ejemplo de código</summary>

```c
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex; // Struct for mutex

void* routine() {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex); // Start of the area we want to protect
        mails++;
        pthread_mutex_unlock(&mutex); // End of mutex
    }
}

int main(int argc, char* argv[]) {
    pthread_t p1, p2, p3, p4;
    pthread_mutex_init(&mutex, NULL); // We init mutex in main
    if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&p2, NULL, &routine, NULL) != 0) {
        return 2;
    }
    if (pthread_create(&p3, NULL, &routine, NULL) != 0) {
        return 3;
    }
    if (pthread_create(&p4, NULL, &routine, NULL) != 0) {
        return 4;
    }
    if (pthread_join(p1, NULL) != 0) {
        return 5;
    }
    if (pthread_join(p2, NULL) != 0) {
        return 6;
    }
    if (pthread_join(p3, NULL) != 0) {
        return 7;
    }
    if (pthread_join(p4, NULL) != 0) {
        return 8;
    }
    pthread_mutex_destroy(&mutex); // We free our mutex struct
    printf("Number of mails: %d\n", mails);
    return 0;
}
```
</details>

<br>

### Separar hilos y optimizar recursos

Otra de las funciones que podemos usar es `pthread_detach`, que nos permite separar un hilo del proceso principal y liberar sus recursos automaticamente una vez que termine la ejecución. Es una alternativa para no tener que llamar a `pthread_join` dentro del proceso principal en caso de que no sepamos cuanto va a durar este hilo, si no queremos que la ejecución de un hilo detenga el procseo princiapl o si no nos importa su valor de retorno, como es el caso de tareas muy pequeñas (método conocido como Fire-and-Forget).

```c
       #include <pthread.h>

       int pthread_detach(pthread_t thread);
```

<details>
<summary>🔍 Ejemplo de código</summary>

```c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Function to be executed by the thread
void* background_task(void* arg) {
    printf("Background task started\n");
    sleep(2);  // Simulate some work (e.g., I/O operation or computation)
    printf("Background task finished\n");
    return NULL;
}

int main() {
    pthread_t thread;

    // Create a new thread to execute background_task
    if (pthread_create(&thread, NULL, background_task, NULL) != 0) {
        perror("Thread creation failed");
        return 1;
    }

    // Detach the thread, so it cleans up resources automatically when finished
    if (pthread_detach(thread) != 0) {
        perror("Thread detachment failed");
        return 1;
    }

    // Main thread continues doing its work without waiting for the background thread
    printf("Main thread is doing other work...\n");

    // Sleep for a short time to ensure the background task has time to finish
    // This is just for demonstration purposes.
    sleep(1);

    printf("Main thread finished\n");

    // No need to join the background thread because it is detached
    return 0;
}
```
</details>


## Videos y bibliografía

### Vídeos
- [Unix Threads in C (lista de reproducción, empieza por aquí)](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [The Dining Philosophers Problem](https://www.youtube.com/watch?v=FYUi-u7UWgw)
- [The dining Philosophers in C: threads, race conditions and deadlocks #codewithme](https://www.youtube.com/watch?v=zOpzGHwJ3MU)

### Artículos
- [Philosophers 42 Guide— “The Dining Philosophers Problem”](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
- [Philosophers 42 Guide](https://42-cursus.gitbook.io/guide/rank-03/philosophers)
- [Philosophers — Dining Philosophers problem. 42 project guide — Mandatory part](https://medium.com/@denaelgammal/dining-philosophers-problem-42-project-guide-mandatory-part-a20fb8dc530e)
