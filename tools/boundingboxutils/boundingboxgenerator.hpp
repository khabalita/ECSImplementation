#pragma once

#include <raylib.h> // Necesario para Image y Color
#include <limits>   // Necesario para std::numeric_limits
#include <cstdint>  // Buena práctica para tipos de enteros fijos (opcional)

/**
 * @brief Estructura que define la caja delimitadora (Bounding Box) mínima.
 * Los valores son offsets (desplazamientos) desde el origen (0,0) del sprite.
 */
struct BoundingBox_t {
    // xLeft e yUp son los índices mínimos (más cercanos a 0)
    uint32_t xLeft;
    uint32_t yUp;
    // xRight e yDown son los índices máximos
    uint32_t xRight;
    uint32_t yDown;
};

/**
 * @brief Calcula el Bounding Box más ajustado alrededor de los píxeles opacos de una imagen.
 * * @param filename El path al archivo de imagen (ej: "assets/texture/sprite.png").
 * @return BoundingBox La estructura con los índices de los límites.
 */
BoundingBox_t calculate_bbox(const char* filename);