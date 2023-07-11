#ifndef CUBE_H
#define CUBE_H

#include <map>
#include <string>
#include <memory>

#include "../COMMON/config.h" // common
#include "../COMMON/types.h" // common
#include "../COMMON/macro.h" // common
#include "../COMMON/CubeError.h" // common

class Cube {
public:
    Cube();

    // copy constructor
    Cube(const Cube&);

    ~Cube();

    void init();

    std::shared_ptr<cubes_t> getCubeData();

    void randomCube();

    // used for save or load file
    std::string serialize();
    void deserialize(std::string);

    // perform cube rotation based on the given method
    void doMethod(CubeRotateMethod);
    // check cube status
    bool check();

    bool checkL();
    bool checkR();
    bool checkU();
    bool checkD();
    bool checkF();
    bool checkB();

    static const std::map<char, CubeColor> s_charColorMap;
    static const std::map<CubeColor, char> s_colorCharMap;
    
private:
    // single rotation
    // rotate one layer
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
    // rotate whole cube
    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();
    void rotateClockwise();
    void rotateCounterClockwise();

private:
    // current cube state
    std::shared_ptr<cubes_t> m_pSubCubes;
};


#endif
