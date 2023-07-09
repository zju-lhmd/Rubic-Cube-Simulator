#ifndef CUBEMODEL_H
#define CUBEMODEL_H

#include <map>
#include <string>

#include "../COMMON/Config.h" // common
#include "../COMMON/types.h" // common
#include "../COMMON/Macro.h" // common
#include "../COMMON/CubeError.h" // common

class CubeModel {
public:
    CubeModel();

    // copy constructor
    CubeModel(const Cube&);

    ~CubeModel();

    void init();

    cubes_t getCubes();

    // TODO: Not Implement Yet
    void randomCube();

    // used for Save or Load file
    // TODO: Not Implement Yet
    std::string serialize();
    void deserialize(std::string);

    // perform cube rotation based on the given method
    void doMethod(CubeRotateMethod);

private:
    // single rotate operation
    // rotate single layer
    void R();
    void Ri();
    void L();
    void Li();
    void B();
    void Bi();
    void D();
    void Di();
    void F();
    void Fi();
    void U();
    void Ui();
    // rotate all layers
    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();
    void rotateClockwise();
    void rotateCounterClockwise();

private:
    // cube state
    cubes_t m_subCubes;
};


#endif
