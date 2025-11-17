#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PRODUCTOS 3  // <-- ÚNICO CAMBIO AQUÍ
#define MAX_NOMBRE 50
#define MAX_BUFFER 100

void leerLinea(char* buffer, int tamano) {
    fgets(buffer, tamano, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

int compararSinMayusculas(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            break;
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

void ingresarProductos(char nombres[][MAX_NOMBRE], float precios[], int *cantidad) {
    char buffer[MAX_BUFFER];
    int num_temp = 0;

    printf("\nINGRESO DE PRODUCTOS\n");
    printf("Ingrese el numero de productos (maximo %d): ", MAX_PRODUCTOS);
    
    while (1) {
        leerLinea(buffer, MAX_BUFFER);
        if (sscanf(buffer, "%d", &num_temp) == 1 && num_temp >= 1 && num_temp <= MAX_PRODUCTOS) {
            *cantidad = num_temp;
            break;
        } else if (sscanf(buffer, "%d", &num_temp) == 1 && (num_temp < 1 || num_temp > MAX_PRODUCTOS)) {
            printf("Cantidad fuera de rango (1 a %d). Se establecera en %d\n", MAX_PRODUCTOS, MAX_PRODUCTOS);
            *cantidad = MAX_PRODUCTOS;
            break;
        } else {
            printf("Entrada invalida. Ingrese un numero (1 a %d): ", MAX_PRODUCTOS);
        }
    }
    
    for (int i = 0; i < *cantidad; i++) {
        printf("\nProducto %d:\n", i + 1);
        printf("Nombre: ");
        leerLinea(nombres[i], MAX_NOMBRE);
        
        printf("Precio: $");
        while (1) {
            float precio_temp;
            leerLinea(buffer, MAX_BUFFER);
            if (sscanf(buffer, "%f", &precio_temp) == 1 && precio_temp >= 0) {
                precios[i] = precio_temp;
                break;
            } else {
                printf("Precio invalido. Ingrese un precio positivo: $");
            }
        }
    }
    
    printf("\nProductos ingresados exitosamente!\n");
}

float calcularTotal(float precios[], int cantidad) {
    float total = 0.0;
    for (int i = 0; i < cantidad; i++) {
        total += precios[i];
    }
    return total;
}

int encontrarMasCaro(float precios[], int cantidad) {
    int indiceMasCaro = 0;
    float precioMax = precios[0];
    
    for (int i = 1; i < cantidad; i++) {
        if (precios[i] > precioMax) {
            precioMax = precios[i];
            indiceMasCaro = i;
        }
    }
    return indiceMasCaro;
}

int encontrarMasBarato(float precios[], int cantidad) {
    int indiceMasBarato = 0;
    float precioMin = precios[0];
    
    for (int i = 1; i < cantidad; i++) {
        if (precios[i] < precioMin) {
            precioMin = precios[i];
            indiceMasBarato = i;
        }
    }
    return indiceMasBarato;
}

float calcularPromedio(float precios[], int cantidad) {
    if (cantidad == 0) return 0.0;
    float total = calcularTotal(precios, cantidad);
    return total / cantidad;
}

int buscarProducto(char nombres[][MAX_NOMBRE], int cantidad, char nombreBuscar[]) {
    for (int i = 0; i < cantidad; i++) {
        if (compararSinMayusculas(nombres[i], nombreBuscar) == 0) {
            return i;
        }
    }
    return -1;
}

void mostrarInventario(char nombres[][MAX_NOMBRE], float precios[], int cantidad) {
    printf("\nINVENTARIO COMPLETO\n");
    printf("%-5s %-30s %-10s\n", "No.", "Producto", "Precio");
    printf("---------------------------------------------\n");
    
    for (int i = 0; i < cantidad; i++) {
        printf("%-5d %-30s $%-10.2f\n", i + 1, nombres[i], precios[i]);
    }
    printf("\n");
}

void mostrarMenu() {
    printf("\n\nSISTEMA DE GESTION DE INVENTARIO\n");
    printf("  1. Ingresar productos\n");
    printf("  2. Mostrar inventario\n");
    printf("  3. Calcular precio total\n");
    printf("  4. Encontrar producto mas caro\n");
    printf("  5. Encontrar producto mas barato\n");
    printf("  6. Calcular precio promedio\n");
    printf("  7. Buscar producto por nombre\n");
    printf("  8. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    float precios[MAX_PRODUCTOS];
    int cantidad = 0;
    int opcion = 0;
    int productosIngresados = 0;
    char buffer[MAX_BUFFER];
    
    printf("\nBIENVENIDO AL SISTEMA DE INVENTARIO\n");
    
    do {
        mostrarMenu();
        
        leerLinea(buffer, MAX_BUFFER);
        if (sscanf(buffer, "%d", &opcion) != 1) {
            opcion = 0;
        }
        
        switch(opcion) {
            case 1:
                ingresarProductos(nombres, precios, &cantidad);
                productosIngresados = 1;
                break;
                
            case 2:
                if (!productosIngresados) {
                    printf("\nNo hay productos en el inventario. Ingrese productos primero.\n");
                } else {
                    mostrarInventario(nombres, precios, cantidad);
                }
                break;
                
            case 3:
                if (!productosIngresados) {
                    printf("\nNo hay productos en el inventario.\n");
                } else {
                    printf("\nPrecio total del inventario: $%.2f\n", 
                           calcularTotal(precios, cantidad));
                }
                break;
                
            case 4:
                if (!productosIngresados) {
                    printf("\nNo hay productos en el inventario.\n");
                } else {
                    int indiceCaro = encontrarMasCaro(precios, cantidad);
                    printf("\nProducto mas caro:\n");
                    printf("   Nombre: %s\n", nombres[indiceCaro]);
                    printf("   Precio: $%.2f\n", precios[indiceCaro]);
                }
                break;
                
            case 5:
                if (!productosIngresados) {
                    printf("\nNo hay productos en el inventario.\n");
                } else {
                    int indiceBarato = encontrarMasBarato(precios, cantidad);
                    printf("\nProducto mas barato:\n");
                    printf("   Nombre: %s\n", nombres[indiceBarato]);
                    printf("   Precio: $%.2f\n", precios[indiceBarato]);
                }
                break;
                
            case 6:
                if (!productosIngresados) {
                    printf("\nNo hay productos en el inventario.\n");
                } else {
                    printf("\nPrecio promedio: $%.2f\n", 
                           calcularPromedio(precios, cantidad));
                }
                break;
                
            case 7:
                if (!productosIngresados) {
                    printf("\nNo hay productos en el inventario.\n");
                } else {
                    char nombreBuscar[MAX_NOMBRE];
                    printf("\nIngrese el nombre del producto a buscar: ");
                    leerLinea(nombreBuscar, MAX_NOMBRE);
                    
                    int indice = buscarProducto(nombres, cantidad, nombreBuscar);
                    
                    if (indice != -1) {
                        printf("\nProducto encontrado:\n");
                        printf("   Nombre: %s\n", nombres[indice]);
                        printf("   Precio: $%.2f\n", precios[indice]);
                    } else {
                        printf("\nProducto '%s' no encontrado en el inventario.\n", 
                               nombreBuscar);
                    }
                }
                break;
                
            case 8:
                printf("\nGracias por usar el sistema\n");
                printf("Hasta pronto!\n\n");
                break;
                
            default:
                printf("\nOpcion invalida. Por favor, seleccione una opcion del 1 al 8.\n");
        }
        
    } while(opcion != 8);
    
    return 0;
}