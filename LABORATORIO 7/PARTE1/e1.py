## Ejercicio 1 ///////////   Laboratorio 7
#  Un programa que abra una imagen y la redimensione a 1000x1000
#  píxeles.
import cv2

try:

    image = cv2.imread('/home/banchan/Documents/visu/emb/imagenes/imga.jpg') # im read puede leer una imagen guardada segun el tipo
    if image is None:
        print("No se pudo cargar la imagen.")
    else:
        #Imagen original
        cv2.imshow('Imagen Original', image)
        resized_image = cv2.resize(image, (600, 600)) #Cambio de tamano de la imagen
        cv2.imwrite('imagen_redimensionada.jpg', resized_image) #guardar imagen estandar 
        cv2.imshow('Imagen Redimensionada', resized_image)
        print("Presiona 'q' para cerrar UWU") # Salida del programa

        #Mantiene las ventanas abiertas hasta interrupcion Q
        while True:
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

except KeyboardInterrupt:
    print("\nEjecución interrumpida por el usuario.")
finally:
    cv2.destroyAllWindows()
