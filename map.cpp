//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <string>
//
//const int TILE_SIZE = 32; // Adjust according to your needs
//const std::vector<std::string> mapSketch = {
//    "############################",
//    "#            ##            #",
//    "#            ##            #",
//    "#  ###   ##  ##  ###   ##  #",
//    "#                          #",
//    "#                          #",
//    "#  ##      ######      ##  #",
//    "#  ##      ######      ##  #",
//    "#      #     ##     #      #",
//    "#      #     ##     #      #",
//    "#####  ###        ###  #####",
//    "#####  #            #  #####",
//    "#####  #            #  #####",
//    "          ##    ##          ",
//    "          #      #          ",
//    "          #      #          ",
//    "#####  #  ########  #  #####",
//    "#####  #            #  #####",
//    "#####  #            #  #####",
//    "#      #  ########  #      #",
//    "#            ##            #",
//    "#            ##            #",
//    "#  ###  ###      ###  ###  #",
//    "#    #                #    #",
//    "##   #                #   ##",
//    "##      #  #####   #      ##",
//    "#       #    #     #       #",
//    "#   #####    #     #####   #",
//    "#                          #",
//    "#                          #",
//    "############################",
//};
//
//void drawMap(sf::RenderWindow& window) {
//    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
//    tile.setOutlineColor(sf::Color::Black);
//    tile.setOutlineThickness(1.f);
//
//    for (size_t i = 0; i < mapSketch.size(); ++i) {
//        const std::string& row = mapSketch[i];
//        for (size_t j = 0; j < row.size(); ++j) {
//            if (row[j] == '#') { // Wall
//                tile.setFillColor(sf::Color::Blue);
//            }
//            else { // Empty space
//                tile.setFillColor(sf::Color::Black);
//            }
//            tile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
//            window.draw(tile);
//        }
//    }
//}
//
//int main() {
//    const int MAP_WIDTH = mapSketch[0].size();
//    const int MAP_HEIGHT = mapSketch.size();
//    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE), "Pacman Map");
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        window.clear(sf::Color::Black);
//        drawMap(window);
//        window.display();
//    }
//
//    return 0;
//}
