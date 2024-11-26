##                               Ejercicio 2 Lab 7
##  Un programa que solicite al usuario seleccionar entre tamaño original,
##  tamaño de imagen pequeño, mediano o grande y volver a escalar una imagen.
import cv2

def mostrar_imagen(image, width, height):
    resized_image = cv2.resize(image, (width, height))
    window_name = f'Imagen {width}x{height}'
    cv2.imshow(window_name, resized_image)
    cv2.imwrite(f'imagen_redimensionada_{width}x{height}.jpg', resized_image)

def menu_interactivo():
    image = cv2.imread('/home/banchan/Documents/visu/emb/imagenes/imga.jpg')

    if image is None:
        print("No se pudo cargar la imagen.")
        return

    while True:
        print("\n--- Menú de Escalado de Imagen ---")
        print("1. Escalar a 300x300")
        print("2. Escalar a 600x600")
        print("3. Escalar a 1000x1000")
        print("4. Escalar a tamaño personalizado")
        print("5. Salir")
        
        try:
            opcion = int(input("Selecciona una opción: "))
            if opcion == 1:
                mostrar_imagen(image, 300, 300)
            elif opcion == 2:
                mostrar_imagen(image, 600, 600)
            elif opcion == 3:
                mostrar_imagen(image, 1000, 1000)
            elif opcion == 4:
                #escalar la imagen de forma manual
                width = int(input("Ingresa el ancho deseado: "))
                height = int(input("Ingresa el alto deseado: "))
                mostrar_imagen(image, width, height)
            elif opcion == 5:
                print("Saliendo...")
                break
            else:
                print("Opción no válida. Intenta nuevamente.")
            print("Presiona 'q' en la ventana de la imagen para cerrarla...")
            while True:
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    cv2.destroyAllWindows()
                    break
        except ValueError:
            print("Por favor, ingresa un número válido.")
        except KeyboardInterrupt:
            print("\nEjecución interrumpida por el usuario.")
            break

    cv2.destroyAllWindows()

#menú interactivo
menu_interactivo()
