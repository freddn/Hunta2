#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>
#include <SDL2/SDL_render.h>

class TextureManager {
public:
    TextureManager();
    void loadTexture(std::string img);
    bool hasTexture(std::string img);
    SDL_Texture* getTexture(std::string img);
    virtual ~TextureManager();
protected:
private:
    std::map<std::string, SDL_Texture*> loadedTextures;
};

#endif // TEXTUREMANAGER_H
