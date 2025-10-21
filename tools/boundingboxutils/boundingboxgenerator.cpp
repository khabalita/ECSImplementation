#include <raylib.h>
#include <limits> // Para inicializar correctamente

struct BoundingBox_t { int xLeft, yUp, xRight, yDown; };

BoundingBox_t calculate_bbox(const char* filename) {
    Image img = LoadImage(filename); // Carga la imagen

    BoundingBox_t bbox;
    // Inicializar límites: El mínimo debe ser el valor máximo posible, y viceversa.
    bbox.xLeft = std::numeric_limits<int>::max();
    bbox.yUp = std::numeric_limits<int>::max();
    bbox.xRight = 0;
    bbox.yDown = 0;

    // Obtener datos del color (asumiendo formato RGBA)
    Color *pixels = (Color*)img.data;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            Color pixel = pixels[y * img.width + x];
            
            // Comprobar la opacidad (componente 'a' o alfa)
            if (pixel.a > 0) {
                // Actualizar los límites
                if (x < bbox.xLeft)  bbox.xLeft = x;
                if (y < bbox.yUp)    bbox.yUp = y;
                if (x > bbox.xRight) bbox.xRight = x;
                if (y > bbox.yDown)  bbox.yDown = y;
            }
        }
    }
    
    UnloadImage(img); // Limpiar

    // Opcional: Sumar 1 a los límites máximos para incluir el píxel final.
    // bbox.xRight++;
    // bbox.yDown++;

    return bbox;
}