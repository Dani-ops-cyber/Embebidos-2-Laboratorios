##Eje 4 practica

import cv2
import numpy as np

# Función para detectar y mostrar el color
def detectar_color(hsv_image):
    # Definir los rangos de colores en HSV
    rangos = {
        'Rojo': [(0, 100, 100), (10, 255, 255)],
        'Verde': [(40, 100, 100), (80, 255, 255)],
        'Azul': [(100, 100, 100), (140, 255, 255)]
    }
    
    # Iterar sobre cada color y sus rangos
    for color, (lower, upper) in rangos.items():
        # Crear máscara para el color
        mascara = cv2.inRange(hsv_image, np.array(lower), np.array(upper))
        # Encontrar los píxeles que coinciden con el color
        porcentaje = cv2.countNonZero(mascara) / (hsv_image.shape[0] * hsv_image.shape[1]) * 100
        
        # Mostrar el porcentaje de color encontrado
        if porcentaje > 0:
            print(f"{color}: {porcentaje:.2f}%")

# Leer la imagen
imagen = cv2.imread('/home/banchan/Documents/visu/emb/colores.png')  # Cambia la ruta por tu imagen
# Convertir la imagen a HSV
hsv_imagen = cv2.cvtColor(imagen, cv2.COLOR_BGR2HSV)

# Llamar a la función para detectar colores
detectar_color(hsv_imagen)
