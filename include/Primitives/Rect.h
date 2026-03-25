#pragma once

class Rect{
public:
    Rect();
    ~Rect();

    void draw() const;
private:
    // Vertex buffer & Vertex array & Element Buffer
    unsigned int VBO, VAO, EBO;
    int setup();
};