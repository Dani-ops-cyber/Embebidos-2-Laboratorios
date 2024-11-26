##                             Ejercicio 3 La 7
##   Un programa que gire 90 grados una imagen cada vez que un usuario
##   presione cualquier tecla del teclado.
import cv2

def rotar_imagen(imagen, angulo):
    centro = (imagen.shape[1] // 2, imagen.shape[0] // 2) #Coordenada del centro ancho y alto
    #matriz de rotación
    matriz_rotacion = cv2.getRotationMatrix2D(centro, angulo, 1.0) # Establece los parametros de rotacion y mantiene el tama;o original de la imagen al momento de rotarla
    return cv2.warpAffine(imagen, matriz_rotacion, (imagen.shape[1], imagen.shape[0]))# uso de la funcion de rotacion mediante el wafle

try:
    #imagen original
    image = cv2.imread('/home/banchan/Documents/visu/emb/imagenes/imga.jpg')
    if image is None:
        print("No se pudo cargar la imagen.")
    else:
        resized_image = cv2.resize(image, (720, 720)) #Escalamiento de la imagen a 720
        cv2.imwrite('reloj.jpg', resized_image)
        imagen_actual = resized_image

        print("'Q'->cerrar las ventanas")
        print("'D'-> rotar 90° en sentido horario")
        print("'I'-> rotar 90° en sentido antihorario")

        while True:
            cv2.imshow('reloj', imagen_actual)
            tecla = cv2.waitKey(1) & 0xFF
            if tecla == ord('q'):
                break
            elif tecla == ord('d'):
                #sentido horario
                imagen_actual = rotar_imagen(imagen_actual, -90)
            elif tecla == ord('i'):
                #sentido antihorario
                imagen_actual = rotar_imagen(imagen_actual, 90)

except KeyboardInterrupt:
    print("\nCierre del programa")

finally:
    cv2.destroyAllWindows()
