#ifndef CUBE_H
#define CUBE_H

#include <map>
#include <string>

#include "../COMMON/Config.h" // common
#include "../COMMON/types.h" // common
#include "../COMMON/Macro.h" // common
#include "../COMMON/CubeError.h" // common

class Cube {
public:
    Cube();

    // copy constructor
    Cube(const Cube&);

    ~Cube();

    void Init();

    cubes_t GetCubes();

    void randomCube();

    // used for Save or Load file
    std::string Serialize();
    void Deserialize(std::string);

    // save cube state into oldcube state
    void SaveState();

    // perform cube rotation based on the given method
    void DoMethod(CubeRotateMethod);
    // check cube status
    bool Check();

    bool CheckL();
    bool CheckR();
    bool CheckU();
    bool CheckD();
    bool CheckF();
    bool CheckB();

    static const std::map<char, CubeColor> CharColorMap;
    static const std::map<CubeColor, char> ColorCharMap;
private:
    // single rotation
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
    void RotateLeft();
    void RotateRight();
    void RotateUp();
    void RotateDown();
    void RotateClockwise();
    void RotateCounterClockwise();

private:
    // current state
    cubes_t subCubes;
    // saved state
    cubes_t oldSubCubes;
};


#endif
