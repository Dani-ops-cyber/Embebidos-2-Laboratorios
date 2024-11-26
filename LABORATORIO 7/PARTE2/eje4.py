import cv2
import numpy as np

class ColorRecognizer:
    def __init__(self, ruta_imagen):
        self.ruta_imagen = ruta_imagen
        self.imagen = None
        self.imagen_hsv = None

    def cargar_imagen(self):
        """Cargar la imagen desde la ruta especificada."""
        self.imagen = cv2.imread(self.ruta_imagen)
        if self.imagen is None:
            print('Error: No se pudo cargar la imagen. Verifica la ruta o el formato del archivo.')
            return False
        return True

    def convertir_a_hsv(self):
        """Convertir la imagen a formato HSV."""
        self.imagen_hsv = cv2.cvtColor(self.imagen, cv2.COLOR_BGR2HSV)

    def calcular_promedio_bgr(self):
        """Calcular el promedio de los valores BGR de la imagen."""
        if self.imagen is not None:
            promedio_bgr = cv2.mean(self.imagen)[:3]  # Ignorar el cuarto valor (alpha)
            return promedio_bgr
        else:
            print('Error: No hay imagen para calcular el promedio BGR.')
            return None

    def calcular_promedio_hsv(self):
        """Calcular el promedio de los valores HSV de la imagen."""
        if self.imagen_hsv is not None:
            promedio_hsv = cv2.mean(self.imagen_hsv)[:3]  # Ignorar el cuarto valor (alpha)
            return promedio_hsv
        else:
            print('Error: No hay imagen en formato HSV para calcular el promedio.')
            return None

    def identificar_color_bgr(self, promedio_bgr):
        """Identificar el color predominante basado en los valores BGR promedio."""
        b, g, r = promedio_bgr
        if r > g and r > b:  # Rojo predominante
            return "Rojo"
        elif g > r and g > b:  # Verde predominante
            return "Verde"
        elif b > r and b > g:  # Azul predominante
            return "Azul"
        else:
            return "Color no identificado"

    def identificar_color_hsv(self, promedio_hsv):
        """Identificar el color predominante basado en los valores HSV promedio."""
        h, s, v = promedio_hsv
        if h < 10 or h > 170:  # Rango para rojo
            return "Rojo"
        elif 35 < h < 85:  # Rango para verde
            return "Verde"
        elif 100 < h < 130:  # Rango para azul
            return "Azul"
        else:
            return "Color no identificado"

    def mostrar_resultados(self, promedio_bgr, promedio_hsv):
        """Mostrar los resultados de los valores promedio BGR y HSV, y los colores identificados."""
        if promedio_bgr is not None:
            print(f'Valores promedio BGR:')
            print(f'Azul (B): {promedio_bgr[0]:.2f}')
            print(f'Verde (G): {promedio_bgr[1]:.2f}')
            print(f'Rojo (R): {promedio_bgr[2]:.2f}')
            color_identificado_bgr = self.identificar_color_bgr(promedio_bgr)
            print(f'Color predominante (BGR): {color_identificado_bgr}')

        if promedio_hsv is not None:
            print(f'Valores promedio HSV:')
            print(f'Matiz (Hue): {promedio_hsv[0]:.2f}')
            print(f'Saturación (Saturation): {promedio_hsv[1]:.2f}')
            print(f'Brillo (Value): {promedio_hsv[2]:.2f}')
            color_identificado_hsv = self.identificar_color_hsv(promedio_hsv)
            print(f'Color predominante (HSV): {color_identificado_hsv}')

    def mostrar_imagen(self):
        """Mostrar la imagen original."""
        if self.imagen is not None:
            cv2.imshow('Imagen Original', self.imagen)
            cv2.waitKey(0)
            cv2.destroyAllWindows()

# Uso de la clase
if __name__ == '__main__':
    ruta_imagen = '/home/banchan/Documents/visu/emb/colores.png'  # Cambia esto por la ruta de tu imagen
    reconocedor_colores = ColorRecognizer(ruta_imagen)

    if reconocedor_colores.cargar_imagen():
        reconocedor_colores.convertir_a_hsv()
        promedio_bgr = reconocedor_colores.calcular_promedio_bgr()
        promedio_hsv = reconocedor_colores.calcular_promedio_hsv()
        reconocedor_colores.mostrar_resultados(promedio_bgr, promedio_hsv)
        reconocedor_colores.mostrar_imagen()
