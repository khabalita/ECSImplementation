#pragma once
#include <map>
#include <string>

// Usaremos la estructura la libreria
struct ColliderOffsets {
    int xLeft, yUp, xRight, yDown;
};

// Mapa que guarda los datos de colisión para cada nombre de sprite
using ColliderMetadataMap = std::map<std::string, ColliderOffsets>; 

// Extern me permite usar la variable en otros archivos
extern ColliderMetadataMap metadata_map;

// Definicion de la funcion para parsear el JSON y llenar este mapa.
ColliderMetadataMap LoadColliderMetadata(const char* filepath);