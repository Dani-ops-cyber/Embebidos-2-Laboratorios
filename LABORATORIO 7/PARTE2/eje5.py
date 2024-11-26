##Eje 5
##  Abra una cámara web con OpenCV y muestre el cuadro en escala de grises
#   y luego en RGB. Cambie entre escala de grises y RGB con las teclas del
#   teclado.
#########################################################################
import cv2

def main():
    # Inicializa la captura de video desde la cámara
    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("Error: No se pudo abrir la cámara.")
        return

    # Variable para controlar el modo de visualización
    modo_grises = False

    try:
        while True:
            # Captura frame a frame
            ret, frame = cap.read()

            if not ret:
                print("Error: No se pudo leer el frame.")
                break

            # Cambia la imagen a escala de grises si modo_grises es True
            if modo_grises:
                frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

            # Muestra la imagen en una ventana
            cv2.imshow('Video', frame)

            # Espera a que el usuario presione una tecla
            key = cv2.waitKey(1) & 0xFF

            # Cambia entre modo RGB y escala de grises
            if key == ord('g'):
                modo_grises = True
            elif key == ord('r'):
                modo_grises = False
            elif key == 27:  # Tecla 'Esc' para salir
                break

    except KeyboardInterrupt:
        print("\nEjecución interrumpida por el usuario.")
    
    finally:
        # Libera la captura y cierra todas las ventanas
        cap.release()
        cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
