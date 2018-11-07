#pragma once

#include "GraphicObject.h"
#include "Texture.h"

class Nature : public GraphicObject {
    public:
        Nature(Texture *T, float s);
        void draw_object() override;
        void move() override {};
    private:
        void setMaterial() override;
        float random(float LO, float HI);
    public:
        const std::string name = "Nature";
    private:
        Texture* texture;
};
