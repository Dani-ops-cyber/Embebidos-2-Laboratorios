## Ejercicio 4 Lab 7
## Usando OpenCV lea una imagen y realice las siguientes operaciones:
#        • Lee la imagen y muéstrala.
#        • Cambiar el tamaño de la imagen a 400x600 (ancho, alto).
#        • Corta la imagen horizontalmente y muestra las dos mitades.
#        • Corta la imagen verticalmente y muestra las dos mitades.
#        • Dividir la imagen en cuadrantes del mismo tamaño y mostrarlos con el título “Cuadrante N” 
#          según el número de cuadrantes.
############################################################################################
import cv2

def mostrar_imagen(imagen, titulo):
    cv2.imshow(titulo, imagen)

def cerrar_imagenes():
    cv2.destroyAllWindows()

def cortar_superior_inferior(imagen):
    alto, ancho = imagen.shape[:2]
    parte_superior = imagen[0:alto//2, :]
    parte_inferior = imagen[alto//2:alto, :]
    mostrar_imagen(parte_superior, 'Superior')
    mostrar_imagen(parte_inferior, 'Inferior')

def cortar_izquierda_derecha(imagen):
    alto, ancho = imagen.shape[:2]
    parte_izquierda = imagen[:, 0:ancho//2]
    parte_derecha = imagen[:, ancho//2:ancho]
    mostrar_imagen(parte_izquierda, 'Izquierda')
    mostrar_imagen(parte_derecha, 'Derecha')

def cortar_en_cuadrantes(imagen):
    alto, ancho = imagen.shape[:2]
    cuadrante_1 = imagen[0:alto//2, 0:ancho//2]  # Superior Izquierdo
    cuadrante_2 = imagen[0:alto//2, ancho//2:ancho]  # Superior Derecho
    cuadrante_3 = imagen[alto//2:alto, 0:ancho//2]  # Inferior Izquierdo
    cuadrante_4 = imagen[alto//2:alto, ancho//2:ancho]  # Inferior Derecho
    mostrar_imagen(cuadrante_1, 'Cuadrante 1')
    mostrar_imagen(cuadrante_2, 'Cuadrante 2')
    mostrar_imagen(cuadrante_3, 'Cuadrante 3')
    mostrar_imagen(cuadrante_4, 'Cuadrante 4')

def main():
    try:
        image = cv2.imread('/home/banchan/Documents/visu/emb/imagenes/imga.jpg')
        if image is None:
            print("No se pudo cargar la imagen.")
            return

        resized_image = cv2.resize(image, (400, 400))
        cv2.imwrite('imagen_redimensionada.jpg', resized_image)

        # Menú iterativo
        while True:
            print("\n--- Menú ---")
            print("1. Mostrar imagen redimensionada")
            print("2. Cortar en partes superior e inferior")
            print("3. Cortar en partes izquierda y derecha")
            print("4. Cortar en cuadrantes")
            print("5. Salir")

            opcion = input("Selecciona una opción: ")
            cerrar_imagenes()

            if opcion == '1':
                mostrar_imagen(resized_image, 'Imagen Redimensionada')
            elif opcion == '2':
                cortar_superior_inferior(resized_image)
            elif opcion == '3':
                cortar_izquierda_derecha(resized_image)
            elif opcion == '4':
                cortar_en_cuadrantes(resized_image)
            elif opcion == '5':
                break
            else:
                print("Opción no valida")

            # Instrucción para cerrar las ventanas
            #print("Presiona 'q' para cerrar las ventanas...")
            while True:
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    cerrar_imagenes()
                    break

    except KeyboardInterrupt:
        print("Cerrando programa")

    finally:
        cerrar_imagenes()

if __name__ == "__main__":
    main()
