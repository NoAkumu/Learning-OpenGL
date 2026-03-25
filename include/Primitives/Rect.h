#pragma once

class Rect{
public:
    Rect();
    ~Rect();

    void draw() const;
    bool wireframe = false;
private:
    // Vertex buffer & Vertex array & Element Buffer
    unsigned int VBO, VAO, EBO;
    int setup();
};