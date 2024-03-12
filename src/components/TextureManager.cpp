#include "TextureManager.hpp"
#include "Texture.hpp"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

void TextureManager::loadTexture(std::string img) {
    if(hasTexture(img))
        return;
    Texture texture;
    texture.loadFromFile(img);
    SDL_Texture* sTexture = texture.getTexture();
    loadedTextures.insert(std::pair<std::string,SDL_Texture*>(img,sTexture));
}

bool TextureManager::hasTexture(std::string img) {
    if(loadedTextures.find(img) == loadedTextures.end())
        return false;
    return true;
}

SDL_Texture* TextureManager::getTexture(std::string img) {
    if(hasTexture(img))
        return loadedTextures.at(img);
    return nullptr;
}
