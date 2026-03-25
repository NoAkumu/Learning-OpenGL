#pragma once

class Triangle{
public:
    Triangle();
    ~Triangle();

    void draw() const;
private:
    // Vertex buffer & Vertex array & Element Buffer
    unsigned int VBO, VAO;
    int setup();
};