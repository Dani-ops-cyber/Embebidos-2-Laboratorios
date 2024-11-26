import cv2
import numpy as np
import os

class ImageProcessor:
    def __init__(self, ruta_imagen):
        self.ruta_imagen = ruta_imagen
        self.imagen_original = None
        self.imagen_redimensionada = None
        self.imagen_rgb = None
        self.imagen_hsv = None
        self.imagen_gris = None

    def cargar_imagen(self):
        """Cargar la imagen desde la ruta especificada."""
        if not os.path.isfile(self.ruta_imagen):
            print(f'Error: El archivo no existe en la ruta {self.ruta_imagen}')
            return False
        
        self.imagen_original = cv2.imread(self.ruta_imagen)
        
        if self.imagen_original is None:
            print('Error: No se pudo cargar la imagen. Verifica la ruta o el formato del archivo.')
            return False

        return True

    def redimensionar_imagen(self, tamaño=(400, 400)):
        """Redimensionar la imagen a un tamaño específico."""
        if self.imagen_original is not None:
            self.imagen_redimensionada = cv2.resize(self.imagen_original, tamaño)
        else:
            print('Error: No hay imagen cargada para redimensionar.')

    def convertir_imagenes(self):
        """Convertir la imagen redimensionada a diferentes formatos de color."""
        if self.imagen_redimensionada is not None:
            self.imagen_rgb = cv2.cvtColor(self.imagen_redimensionada, cv2.COLOR_BGR2RGB)
            self.imagen_hsv = cv2.cvtColor(self.imagen_redimensionada, cv2.COLOR_BGR2HSV)
            self.imagen_gris = cv2.cvtColor(self.imagen_redimensionada, cv2.COLOR_BGR2GRAY)
        else:
            print('Error: No hay imagen redimensionada para convertir.')

    def mostrar_imagenes(self):
        """Mostrar las imágenes en diferentes formatos."""
        if self.imagen_rgb is not None:
            cv2.imshow('Imagen RGB', self.imagen_rgb)
        
        if self.imagen_hsv is not None:
            cv2.imshow('Imagen HSV', self.imagen_hsv)
        
        if self.imagen_gris is not None:
            cv2.imshow('Imagen Escala de Grises', self.imagen_gris)

        cv2.waitKey(0)
        cv2.destroyAllWindows()

# Uso de la clase
if __name__ == '__main__':
    ruta_imagen = '/home/banchan/Documents/visu/emb/colores.png'  # Cambia esto por la ruta de tu imagen
    procesador_imagen = ImageProcessor(ruta_imagen)

    if procesador_imagen.cargar_imagen():
        procesador_imagen.redimensionar_imagen()
        procesador_imagen.convertir_imagenes()
        procesador_imagen.mostrar_imagenes()
