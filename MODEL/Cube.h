#ifndef CUBE_H
#define CUBE_H

#include <map>
#include <string>
<<<<<<< HEAD

#include "../COMMON/Config.h" // common
#include "../COMMON/types.h" // common
#include "../COMMON/Macro.h" // common
=======
#include <memory>

#include "../COMMON/config.h" // common
#include "../COMMON/types.h" // common
#include "../COMMON/macro.h" // common
#include "../COMMON/CubeError.h" // common
>>>>>>> 65d2fe78cec02a27f36f8be0d235b94eb2f39c66

class Cube {
public:
    Cube();

    // copy constructor
    Cube(const Cube&);

    ~Cube();

<<<<<<< HEAD
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
private:
    // single rotation
=======
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
>>>>>>> 65d2fe78cec02a27f36f8be0d235b94eb2f39c66
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
<<<<<<< HEAD
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
=======
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
>>>>>>> 65d2fe78cec02a27f36f8be0d235b94eb2f39c66
};


#endif
