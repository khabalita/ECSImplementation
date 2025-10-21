#include <Game/data/metadata.hpp>
#include <fstream>
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;

//ColliderMetadataMap metadata_map;

ColliderMetadataMap LoadColliderMetadata(const char* filepath) {
    ColliderMetadataMap metadata_map;
    
    // Abre el archivo
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "ERROR: Failed to open collider metadata file: " << filepath << std::endl;
        return metadata_map; // Retorna un mapa vacío si falla
    }

    try {
        // Parsea el archivo completo a un objeto JSON (Nlohmann/json)
        json j = json::parse(file);

        // Itera sobre todos los elementos del JSON
        for (auto const& [key, val] : j.items()) {
            
            // 'key' es el nombre del sprite (ej: "player")
            // 'val' es el objeto con los offsets
            
            ColliderOffsets offsets;
            offsets.xLeft   = val.at("xLeft").get<int>();
            offsets.yUp     = val.at("yUp").get<int>();
            offsets.xRight  = val.at("xRight").get<int>();
            offsets.yDown   = val.at("yDown").get<int>();

            // 4. Insertar en el mapa final
            metadata_map[key] = offsets;
        }

        std::cout << "SUCCESS: Loaded " << metadata_map.size() << " collider metadata entries." << std::endl;
        
    } catch (json::exception& e) {
        std::cerr << "ERROR parsing JSON: " << e.what() << std::endl;
    }

    return metadata_map;
}