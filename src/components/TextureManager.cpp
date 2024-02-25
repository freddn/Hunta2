#include "TextureManager.hpp"
#include "Texture.hpp"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

void TextureManager::loadTexture(std::string img) {
    if(hasTexture(img))
        return;
    Texture texture;
    texture.loadFromFile(img);
    loadedTextures.insert(std::pair<std::string,Texture*>(img,&texture));
}

bool TextureManager::hasTexture(std::string img) {
    if(loadedTextures.find(img) == loadedTextures.end())
        return false;
    return true;
}

Texture* TextureManager::getTexture(std::string img) {
    if(hasTexture(img))
        return loadedTextures.at(img);
    return nullptr;
}
