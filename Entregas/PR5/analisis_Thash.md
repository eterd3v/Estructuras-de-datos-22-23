# Análisis de tablas de dispersión

* *Autor: Antonio Javier Armenteros Martínez*
* *Email: [ajam0011@red.ujaen.es]()*

## Índice general
<!-- TOC -->
* [Análisis de tablas de dispersión](#análisis-de-tablas-de-dispersión)
  * [Índice de contenido general](#índice-de-contenido-general)
  * [Descripción de cada una de las funciones usadas](#descripción-de-cada-una-de-las-funciones-usadas)
    * [Dispersión cuadrática, f1(x)](#dispersión-cuadrática-f1--x-)
    * [Dispersión doble, f2(x)](#dispersión-doble-f2--x-)
    * [Dispersión doble, f3(x)](#dispersión-doble-f3--x-)
  * [Tamaños de tablas](#tamaños-de-tablas)
    * [Tamaño de tabla: 15391](#tamaño-de-tabla--15391)
    * [Tamaño de tabla: 14713](#tamaño-de-tabla--14713)
  * [Justificación de la configuración elegida](#justificación-de-la-configuración-elegida)
<!-- TOC -->

## Descripción de cada una de las funciones usadas
A continuación voy a describir el código y el origen de cada una de las funciones que he ido implementando para esta práctica.
Según me ha parecido conveniente, he puesto el código correspondiente a cada función por la complejidad de explicar cada función formalmente. 

### Dispersión cuadrática, f1(x)
En esta función de dispersión he decido tomar _f1(x) = ( x + i^2 ) % t_, teniendo en cuenta que _t_ es el tamaño de la tabla,
_x_, es la clave de la función e _i_ es el número de intentos tomados hasta el momento. Aún siendo una función simple, es capaz
de dispersar relativamente bien y es por ese motivo por el que lo he incluido. 

### Dispersión doble, f2(x)
El código correspondiente a f2(x) es el siguiente:
```c++
//La mayoría de datos son clave%2==0 (6032 elementos)
//La mayoría están entre 10^8 y 10^9. La minoría entre 10^5 y 10^6
unsigned long aux=1,aux2=1;

if(clave%2==0){                     //Más que dispersar
    for (int i = 0; i < 9; ++i)
        aux = aux << 1;             //Desplazo a la izqda el bit
    aux = (aux - clave) % 100000000;
    aux2 += clave % 1000000;
    aux2 *= aux2;
}else{                              //Menos que dispersar
    unsigned long bucle = clave;
    while (bucle){
        aux2 += bucle%1000;
        aux *= aux2 - aux;
        bucle /= 1000;
    }
}

while(!esPrimo(aux) && clave%aux == 0)
    ++aux;
while(!esPrimo(aux2) && clave%aux2 == 0)
    ++aux2;

unsigned long h1 = clave % aux, h2 = clave % aux2;
return (h1 + h2*intento) % capacidadTabla;
```
Para esta función decidí investigar un poco sobre los datos, sacando las siguientes imágenes para valerme de ello:

![](C:\Users\Antonio\Desktop\PR5\analisis\analisisIdes.png)
![](C:\Users\Antonio\Desktop\PR5\analisis\analisisIdes_II.png)

Tal y como aparece en las anteriores imágenes y en los comentarios del código, la mayoría de datos oscilan entre 10^8 y 10^9
mientras que la minoría está entre 10^5 y 10^6. Además la mayoría de los identificadores son pares, con un total de 6032 
identificadores pares. Probé satisfactoriamente con el siguiente código, donde según si el identificador es par o no, prueba
a realizar una dispersión más agresiva. Independientemente de lo anterior, siempre se busca el primo más próximo a _aux_ y _aux2_
para que sea más eficaz el rendimiento.

### Dispersión doble, f3(x)
El código correspondiente a f3(x) es el siguiente:
```c++
    unsigned long aux=clave,aux2=1,aux3=1;

    while(aux){
        aux2 += aux3++ * (aux%10);
        aux /= 10;
    }

    for (int i = 0; i < 5; ++i){
        aux2 = aux2*aux3;
        aux3 = aux3 << 1;
    }

    while(!esPrimo(aux2) && clave%aux2 == 0)
        ++aux2;
    while(!esPrimo(aux3) && clave%aux3 == 0)
        ++aux3;

    unsigned long h1 = clave % aux2, h2 = clave % aux3;
    return (h1 + h2*intento) % capacidadTabla;
```
Como se puede apreciar, uso varios operadores de números enteros, incluidos operaciones a nivel de bit.
Primero genero dos numeros relativamente pequeños, _aux2_ y _aux3_, a través de ir dividendo la clave entre 10 con la variable
_aux_. Luego paso a una fase de ampliación de estas variables con un bucle que itera 5 veces, ya que todas los identificadores
 de las imágenes son menores a 10^5. Por último paso a buscar los primos más cercanos de _aux2_ y de _aux3_.

## Tamaños de tablas
### Tamaño de tabla: 15391
| función | máximo de colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:---------------:|:----------------------:|
| f1(x)   |          19          |     0.64973     |         0.7115         |
| f2(x)   |          16          |     0.64973     |         0.5988         |
| f3(x)   |          15          |     0.64973     |         0.6018         |

### Tamaño de tabla: 14713
| función | máximo de colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:---------------:|:----------------------:|
| f1(x)   |          22          |    0.679671     |         0.7672         |
| f2(x)   |          16          |    0.679671     |         0.6643         |
| f3(x)   |          15          |    0.679671     |          0.68          |

## Justificación de la configuración elegida
He optado por la función de dispersión _f2(x)_ ya que, a pesar de tener más colisiones que _f3(x)_, es capaz de mantener
el promedio de colisiones aún más bajo que el resto de funciones. Además, como es una función de dispersión doble ideado con
algo de sentido, es más problable que no se den agrupamientos primarios o secundarios, por lo que _f1(x)_ tiene menos opciones
a ser usado para este sistema de imágenes.
