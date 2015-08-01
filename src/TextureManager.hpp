#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

/*
before:
total heap usage: 195,499 allocs, 195,030 frees, 269,178,360 bytes allocated

after:
total heap usage: 130,754 allocs, 130,285 frees, 126,580,570 bytes allocated
*/

#include <string>
#include <memory>
#include <map>
#include <SDL2/SDL_image.h>

class TextureManager {
public:
    TextureManager();
    void loadTexture(std::string img);
    void loadTexture(std::string img, bool clip);
    void loadTexture(std::string img, bool clip, int w, int h);
    bool hasTexture(std::string img);
    SDL_Texture* getTexture(std::string img);
    virtual ~TextureManager();
protected:
private:
    std::map<std::string, SDL_Texture*> loadedTextures;
};

#endif // TEXTUREMANAGER_H
