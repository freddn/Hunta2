#include "TextureManager.hpp"
#include "Texture.hpp"

TextureManager::TextureManager() {
    //ctor
}

TextureManager::~TextureManager() {
    //dtor
}

void TextureManager::loadTexture(std::string img) {
    if(hasTexture(img))
        return;
    Texture texture;
    texture.loadFromFile(img);
    //SDL_Texture *texturePtr = new SDL_Texture(texture.getTexture())
    //std::shared_ptr<SDL_Texture> temp(std::make_shared<SDL_Texture>(texture.getTexture()),SDL_DestroyTexture);
    SDL_Texture *temp = texture.getTexture();
    loadedTextures.insert(std::pair<std::string,SDL_Texture*>(img,temp));
}

bool TextureManager::hasTexture(std::string img) {
    if(loadedTextures.find(img) == loadedTextures.end())
        return false;
    return true;
}

SDL_Texture * TextureManager::getTexture(std::string img) {
    if(hasTexture(img))
        return loadedTextures.at(img);
    return nullptr;
}

