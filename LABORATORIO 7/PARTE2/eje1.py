##                                                 Ejercicio 6
## Crea una carpeta llamada “colores” con 3 imágenes de 3 colores diferentes.
## Luego, con OpenCV, abre cada imagen e imprime el valor del color en la terminal.
import cv2
import os

carpeta_colores = "/home/banchan/Documents/visu/colores"

colores_imagenes = {
    "1": "rojo",   
    "2": "verde",  
    "3": "azul"   
}

def mostrar_imagen(imagen, nombre):
    img_resized = cv2.resize(imagen, (400, 400))
    cv2.imshow(f'Imagen {nombre}', img_resized)
    
    #cierre la ventana
    while cv2.waitKey(1) & 0xFF != ord('q'):
        pass
    cv2.destroyWindow(f'Imagen {nombre}')

def mostrar_color_promedio(imagen):
    """Función para calcular y mostrar el color promedio en BGR y RGB."""
    promedio_bgr = cv2.mean(imagen)[:3]
    promedio_rgb = (promedio_bgr[2], promedio_bgr[1], promedio_bgr[0])  # de BGR a RGB
    print(f"Color promedio (BGR): {promedio_bgr}")
    print(f"Color promedio (RGB): {promedio_rgb}")

if not os.path.exists(carpeta_colores):
    print(f"La carpeta {carpeta_colores} no existe.")
else:
    # Menú tipo case
    while True:
        print("\n--- Menú de Colores ---")
        print("1. Color Rojo")
        print("2. Color Verde")
        print("3. Color Azul")
        print("4. Salir")

      #opción del usuario
        opcion = input("Selecciona una opción (1-4): ")
        
        if opcion == '4':
            print("Saliendo del programa.")
            break
        elif opcion in colores_imagenes:
            color = colores_imagenes[opcion]
            ruta_imagen = os.path.join(carpeta_colores, f"{color}.jpg")

            img = cv2.imread(ruta_imagen)

            if img is None:
                print(f"No se pudo cargar la imagen para el color {color}")
            else:
                print(f"\n--- Análisis de la Imagen: {color.capitalize()} ---")
    
                mostrar_color_promedio(img) ##Promedio de canales
                mostrar_imagen(img, color.capitalize()) 
        else:
            print("Opción no válida. Por favor, selecciona un número del menú.")

    cv2.destroyAllWindows()
