#ifndef CUBESOLVER_H
#define CUBESOLVER_H

#include <vector>

#include "../../COMMON/types.h" // common
#include "../../COMMON/macro.h" // common
#include "../../COMMON/SolverError.h" // common
#include "../../MODEL/Cube.h" // model

class CubeSolver {
public:

	CubeSolver(Cube cube);

	~CubeSolver();

	void solve();

    std::vector<CubeRotateMethod> GetSteps();

private:
    void Do(CubeRotateMethod);

    bool CheckStage3();
    bool CheckStage4State1(); // +
    bool CheckStage4State3();
    bool CheckStage4State4(); // -
    bool CheckStage4State4i(); // |
    void CheckStage6ABCD(bool*, bool*, bool*, bool*);
    void CheckStage7EFGH(bool*, bool*, bool*, bool*);

    void Stage1(); // solve the white cross
    void Stage2(); // solve the white corners
    void Stage3(); // solve the middle layer
    void Stage4(); // solve the top layer: get yellow cross
    void Stage5(); // solve the top layer: get all the yellow on top
    void Stage6(); // position the yellow corners correctly
    void Stage7(); // position yellow edges correctly

    void MoveToUp(CubeColor);
    void MoveToDown(CubeColor);
    void MoveToLeft(CubeColor);
    void MoveToRight(CubeColor);
    void MoveToFront(CubeColor);
    void MoveToBack(CubeColor);

private:
    Cube m_cube;
    std::vector<CubeRotateMethod> m_steps;
};

#endif