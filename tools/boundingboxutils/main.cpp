#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tools/boundingboxutils/boundingboxgenerator.hpp" // Incluye tu librería

// COMO COMPILAR LA LIBRERIA!!

// clang++ tools/boundingboxutils/main.cpp -o processor \
    -std=c++20 -I. -I/opt/homebrew/opt/raylib/include\
    -Llibs -lboundingbox \
    -L/opt/homebrew/opt/raylib/lib -lraylib


// Función auxiliar para guardar los resultados
void save_bbox_to_file(const std::string& output_filename, const std::string& asset_name, const BoundingBox_t& bbox) {
    std::ofstream outfile(output_filename, std::ios_base::app); // Abrir en modo 'append'
    if (outfile.is_open()) {
        
        // Formato simple de salida (ejemplo JSON/CSV)
        outfile << "\"" << asset_name << "\": {"
                << "\"xLeft\": " << bbox.xLeft << ", "
                << "\"yUp\": " << bbox.yUp << ", "
                << "\"xRight\": " << bbox.xRight << ", "
                << "\"yDown\": " << bbox.yDown
                << "}\n";
        
        outfile.close();
        std::cout << "SUCCESS: BBox generated for " << asset_name << " and saved to " << output_filename << std::endl;
    } else {
        std::cerr << "ERROR: Could not open output file: " << output_filename << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso correcto: " << argv[0] << " <archivo_input.png> <archivo_output.json>" << std::endl;
        std::cerr << "Ejemplo: " << argv[0] << " assets/textures/player.png metadata/colliders.json" << std::endl;
        return 1;
    }

    const std::string input_path = argv[1];
    const std::string output_path = argv[2];
    
    // 1. LLAMADA A LA LÓGICA DE LA LIBRERÍA
    BoundingBox_t bbox = calculate_bbox(input_path.c_str());

    // 2. OBTENER EL NOMBRE DEL ASSET (para la etiqueta)
    size_t last_slash = input_path.find_last_of('/');
    std::string asset_name = input_path.substr(last_slash + 1);
    
    // Opcional: Eliminar la extensión .png/.jpg
    size_t last_dot = asset_name.find_last_of('.');
    if (last_dot != std::string::npos) {
        asset_name = asset_name.substr(0, last_dot);
    }
    
    // 3. GUARDAR EL RESULTADO
    save_bbox_to_file(output_path, asset_name, bbox);

    return 0;
}