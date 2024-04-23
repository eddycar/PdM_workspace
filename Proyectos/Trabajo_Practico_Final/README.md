# __Trabajo Práctico Final__
## Sistema de adquisición de datos de temperatura

El proyecto consiste en un sistema de adquisición de datos de temperatura mediante el uso de un sensor PT100 y el integrado MAX31865. La información recopilada se transmite a través de UART a una aplicación de escritorio diseñada para la visualización y almacenamiento de los datos obtenidos en un archivo .xlsx para su posterior análisis.

## Diagrama de Bloques
![](./media/img/Diagrama%20de%20bloques.jpg)


## Módulo MAX31865
Max61865: Permite obtener mediciones de temperatura de los sensores PT100/PT1000 de 2, 3 o 4 hilos. Mediante el conversor delta-sigma integrado, este producto convierte la señal analógica a digital, con una resolución de 15 bits, generando así una resolución nominal de 0.03125ºC.

![](./media/img/max31865.jpg)

## Maquina De Estados Finitos
![](./media/img/FEM.png)

## Arquitectura De Software
![](./media/img/Arquitectura%20de%20software.png)