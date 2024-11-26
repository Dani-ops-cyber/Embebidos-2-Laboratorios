#                                 Eje 6
#  capturar una imagen de un cuadro y guardarla como
#  imagen usando OpenCV. Luego, captura la imagen de la cámara web y
#  guarda el cuadro cada vez que se presione la tecla “c” con el formato
#  “Capturas/imagen1.jpg”. Al finalizar el proceso, aplica un filtro de escala de
#  grises a la imagen y divídela en cuadrantes.
####################################################################
import cv2
import os

def main():
    # Iniciar la captura de video
    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("Error: No se pudo abrir la cámara.")
        return

    while True:
        # Capturar un frame
        ret, frame = cap.read()
        if not ret:
            print("Error: No se pudo leer el frame.")
            break

        # Mostrar el frame
        cv2.imshow('Camera', frame)

        # Esperar a que se presione la tecla 'c'
        key = cv2.waitKey(1)
        if key == ord('c'):
            # Guardar la imagen
            image_path = 'captura.jpg'
            cv2.imwrite(image_path, frame)
            print(f'Imagen guardada como {image_path}')

            # Aplicar filtro de escala de grises
            gray_image = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

            # Cortar la imagen en 4 cuadrantes
            height, width = gray_image.shape
            half_height, half_width = height // 2, width // 2

            cuadrante1 = gray_image[0:half_height, 0:half_width]     # Cuadrante superior izquierdo
            cuadrante2 = gray_image[0:half_height, half_width:width]  # Cuadrante superior derecho
            cuadrante3 = gray_image[half_height:height, 0:half_width] # Cuadrante inferior izquierdo
            cuadrante4 = gray_image[half_height:height, half_width:width] # Cuadrante inferior derecho

            # Mostrar los cuadrantes
            cv2.imshow('Cuadrante 1', cuadrante1)
            cv2.imshow('Cuadrante 2', cuadrante2)
            cv2.imshow('Cuadrante 3', cuadrante3)
            cv2.imshow('Cuadrante 4', cuadrante4)

        # Salir si se presiona 'q'
        if key == ord('q'):
            break

    # Liberar la cámara y cerrar todas las ventanas
    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
