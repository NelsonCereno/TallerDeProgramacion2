# TallerDeProgramacion2

Solución Vertex Coloring Problem
Nelson Cereño

Para la persona que revise este codigo trate de ser lo mas pragmatico posible, realmente me costo mucho esta experiencia de laboratorio, asi que espero que se logre entender bien.

Descripción General

Este programa resuelve el problema de la coloración de vértices en grafos, donde se busca asignar el menor número posible de colores a los vértices de un grafo de manera que no haya dos vértices adyacentes con el mismo color. El programa utiliza una combinación de estructuras de datos y algoritmos para explorar posibles soluciones y encontrar el número mínimo de colores necesarios.

Funcionamiento del Programa

Entrada del Usuario: El programa mediante un menu se le posibilita al usuario que ingrese el nombre de un archivo que contiene las aristas del grafo en formato de dos columnas (vértice - vértice).

Lectura del Archivo: Utiliza la función `readEdgesFromFile` para leer las aristas del grafo desde el archivo especificado.

Inicialización: Crea un objeto `Graph` con las aristas leídas del archivo.

Resolución del Problema: Llama al método `branchAndBound` del objeto `BranchAndBound` para encontrar una solución al problema de coloración de vértices.

Medición del Tiempo: Mide el tiempo de ejecución del método `branchAndBound` y lo imprime en segundos.

Salida: Imprime el número de colores utilizados y el tiempo de ejecución.

Ejecución del Programa

Para ejecutar el programa, compílelo utilizando el Makefile ("make all" en la terminal) proporcionado e interactue con el menu ejecutanto "./main". A continuación, cargue el grafo e inicie BranchAndBound (para cargar el grafo deber usar el siguiente formato:
"nombreDeArchivo.txt", en resumen debe llevar la extension).

Ejecucion:

make all

./main

"Interactuar con el menu"

Detalle importante: Se recomienda re-ejecutar el programa si se quiere probar un nuevo grafo.

Si desea probar casa uno de los test facilitados aqui quedan sus codigos

./test_Graph
./test_State
./test_BranchAndBound

Desafíos y Limitaciones

El desarrollo de este programa presentó varios desafíos significativos. Sin embargo, a pesar de los retos, se logró implementar una solución eficiente para la mayoría de los casos. El programa funciona correctamente tanto para casos simples como para casos de dificultad media y alta, logrando encontrar una solución óptima en un tiempo razonable.

Intentos y Estrategias

Se implementaron varias estrategias para optimizar el rendimiento del programa, incluyendo:

Optimización de Estructuras de Datos: Se utilizaron estructuras de datos eficientes para manejar los vértices y sus colores, con el objetivo de acelerar las operaciones de búsqueda e inserción.

Heurísticas: Se implementaron heurísticas para guiar la búsqueda hacia una coloración óptima de manera más eficiente.

Algoritmos de Búsqueda: Se exploraron diferentes algoritmos de búsqueda, como el algoritmo de Branch and Bound, para encontrar la solución óptima.

Resultados
Gracias a estos esfuerzos, el programa logró resolver casos de dificultad media y alta en un tiempo razonable. La combinación de estructuras de datos optimizadas, heurísticas y algoritmos de búsqueda permitió manejar la complejidad del problema y encontrar soluciones eficientes para la coloración de vértices en grafos.

Conclusión
El programa representa un esfuerzo considerable para resolver el problema de la coloración de vértices, y ha demostrado ser eficiente en términos de rendimiento y precisión. A pesar de los desafíos iniciales, se logró implementar una solución robusta y efectiva.

A modo de observación personal, resultó un desafío implementar este problema tan complicado, sumándole el hecho de intentar buscar una heurística óptima. Sin embargo, el esfuerzo valió la pena y se logró un buen rendimiento.

Espero que para futuras entregas mi rendimiento continúe mejorando. Agradezco la atención.