##                        Ejercicio 2
# Una función que convierta el color rgb a escala de grises.
import cv2
import os
carpeta_colores = "/home/banchan/Documents/visu/colores"

colores_imagenes = {
    "1": "rojo",   
    "2": "verde",  
    "3": "azul"    
}

def mostrar_imagen(imagen, nombre):
    img_resized = cv2.resize(imagen, (300, 300))
    cv2.imshow(f'Imagen {nombre}', img_resized)

def mostrar_color_promedio(imagen):
    """Función para calcular y mostrar el color promedio en BGR y RGB."""
    promedio_bgr = cv2.mean(imagen)[:3]
    promedio_rgb = (promedio_bgr[2], promedio_bgr[1], promedio_bgr[0])  # Convertir de BGR a RGB
    print(f"Color promedio (BGR): {promedio_bgr}")
    print(f"Color promedio (RGB): {promedio_rgb}")

def convertir_a_grises(imagen):
    """Función para convertir una imagen a escala de grises."""
    return cv2.cvtColor(imagen, cv2.COLOR_BGR2GRAY)

# Verificar si la carpeta existe
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

        # Solicitar opción del usuario
        opcion = input("Selecciona una opción (1-4): ")
        
        if opcion == '4':
            print("Saliendo del programa.")
            break
        elif opcion in colores_imagenes:
            color = colores_imagenes[opcion]
            ruta_imagen = os.path.join(carpeta_colores, f"{color}.jpg")

            # Cargar y procesar la imagen
            img = cv2.imread(ruta_imagen)

            if img is None:
                print(f"No se pudo cargar la imagen para el color {color}")
            else:
                print(f"\n--- Análisis de la Imagen: {color.capitalize()} ---")
                # Mostrar color promedio
                mostrar_color_promedio(img)
                
                # Redimensionar y mostrar imagen original
                mostrar_imagen(img, f"{color.capitalize()} Original")
                
                # Convertir y mostrar imagen en escala de grises
                img_gris = convertir_a_grises(img)
                img_gris_resized = cv2.resize(img_gris, (300, 300))
                cv2.imshow(f'Imagen {color.capitalize()} en Escala de Grises', img_gris_resized)
                
                # Esperar a que el usuario cierre las ventanas antes de continuar
                print("Presiona 'q' para cerrar las imágenes y continuar...")
                while True:
                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        break

                # Cerrar las ventanas de la imagen actual
                cv2.destroyAllWindows()
        else:
            print("Opción no válida. Por favor, selecciona un número del menú.")

    # Cerrar todas las ventanas al salir
    cv2.destroyAllWindows()
