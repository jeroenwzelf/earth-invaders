#pragma once

#include "GraphicObject.h"
#include "Texture.h"

class Skybox : public GraphicObject {
    public:
        Skybox(Texture *T);
        void draw_object() override;
        void move() override {};
    private:
        void setMaterial() override;
    public:
        const std::string name = "Skybox";
    private:
        Texture* texture;
};