#pragma once
#include <SFML/Graphics.hpp>

void draw_home_without_login(sf::RenderWindow& window, sf::Texture backgroundTexture);
void draw_home_with_login(sf::RenderWindow& window, sf::Texture backgroundTexture, std::string playerName);
void draw_login_interface(sf::RenderWindow& window, sf::Sprite Back, sf::Sprite Submit, sf::Sprite Email, sf::Sprite Password);
void draw_register_interface(sf::RenderWindow& window, sf::Sprite Back, sf::Sprite Submit, sf::Sprite Email, sf::Sprite Password);