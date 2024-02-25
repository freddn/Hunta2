#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>
#include "Texture.hpp"

class TextureManager {
public:
    TextureManager();
    void loadTexture(std::string img);
    bool hasTexture(std::string img);
    Texture* getTexture(std::string img);
    virtual ~TextureManager();
protected:
private:
    std::map<std::string, Texture*> loadedTextures;
};

#endif // TEXTUREMANAGER_H
