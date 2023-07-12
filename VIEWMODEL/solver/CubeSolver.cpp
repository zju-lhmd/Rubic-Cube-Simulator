#include "CubeSolver.h"

CubeSolver::CubeSolver(Cube cube): m_cube(cube)
{
}

CubeSolver::~CubeSolver()
{
}

void CubeSolver::Do(CubeRotateMethod method)
{
	m_cube.doMethod(method);
	m_steps.push_back(method);
}

std::vector<CubeRotateMethod> CubeSolver::GetSteps() {
    return m_steps;
}

void CubeSolver::solve()
{
    if (m_cube.check()) return;
    Stage1();
    if (m_cube.check()) return;
    Stage2();
    if (m_cube.check()) return;
    Stage3();
    if (m_cube.check()) return;
    Stage4();
    if (m_cube.check()) return;
    Stage5();
    if (m_cube.check()) return;
    Stage6();
    if (m_cube.check()) return;
    Stage7();
}

void CubeSolver::MoveToUp(CubeColor color)
{
    if (GET_UP((*m_cube.getCubeData())[U_CENTRE]) == color)
    {
        //nope
    }
    else if (GET_DOWN((*m_cube.getCubeData())[D_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEX);
        Do(ROTATE_WHOLEX);
        //can also do ROTATE_WHOLEZ * 2
    }
    else if (GET_LEFT((*m_cube.getCubeData())[L_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEZ);
    }
    else if (GET_RIGHT((*m_cube.getCubeData())[R_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEZi);
    }
    else if (GET_FRONT((*m_cube.getCubeData())[F_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEX);
    }
    else if (GET_BACK((*m_cube.getCubeData())[B_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEXi);
    }
}

void CubeSolver::MoveToDown(CubeColor color)
{
    if (GET_UP((*m_cube.getCubeData())[U_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEX);
        Do(ROTATE_WHOLEX);
        //can also do ROTATE_WHOLEZ * 2
    }
    else if (GET_DOWN((*m_cube.getCubeData())[D_CENTRE]) == color)
    {
        //nope
    }
    else if (GET_LEFT((*m_cube.getCubeData())[L_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEZi);
    }
    else if (GET_RIGHT((*m_cube.getCubeData())[R_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEZ);
    }
    else if (GET_FRONT((*m_cube.getCubeData())[F_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEXi);
    }
    else if (GET_BACK((*m_cube.getCubeData())[B_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEX);
    }
}

void CubeSolver::MoveToLeft(CubeColor color)
{
    if (GET_UP((*m_cube.getCubeData())[U_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEZi);
    }
    else if (GET_DOWN((*m_cube.getCubeData())[D_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEZ);
    }
    else if (GET_LEFT((*m_cube.getCubeData())[L_CENTRE]) == color)
    {
        //nope
    }
    else if (GET_RIGHT((*m_cube.getCubeData())[R_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEY);
        Do(ROTATE_WHOLEY);
        //can also ROTATE_WHOLEZ * 2
    }
    else if (GET_FRONT((*m_cube.getCubeData())[F_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEY);
    }
    else if (GET_BACK((*m_cube.getCubeData())[B_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEYi);
    }
}

void CubeSolver::MoveToRight(CubeColor color)
{
    if (GET_UP((*m_cube.getCubeData())[U_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEZ);
    }
    else if (GET_DOWN((*m_cube.getCubeData())[D_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEZi);
    }
    else if (GET_LEFT((*m_cube.getCubeData())[L_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEY);
        Do(ROTATE_WHOLEY);
        //can also ROTATE_WHOLEZ * 2
    }
    else if (GET_RIGHT((*m_cube.getCubeData())[R_CENTRE]) == color)
    {
        //nope
    }
    else if (GET_FRONT((*m_cube.getCubeData())[F_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEYi);
    }
    else if (GET_BACK((*m_cube.getCubeData())[B_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEY);
    }
}

void CubeSolver::MoveToFront(CubeColor color)
{
    if (GET_UP((*m_cube.getCubeData())[U_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEXi);
    }
    else if (GET_DOWN((*m_cube.getCubeData())[D_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEX);
    }
    else if (GET_LEFT((*m_cube.getCubeData())[L_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEYi);
    }
    else if (GET_RIGHT((*m_cube.getCubeData())[R_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEY);
    }
    else if (GET_FRONT((*m_cube.getCubeData())[F_CENTRE]) == color)
    {
        //nope
    }
    else if (GET_BACK((*m_cube.getCubeData())[B_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEY);
        Do(ROTATE_WHOLEY);
        //can also ROTATE_WHOLEX * 2
    }
}

void CubeSolver::MoveToBack(CubeColor color)
{
    if (GET_UP((*m_cube.getCubeData())[U_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEX);
    }
    else if (GET_DOWN((*m_cube.getCubeData())[D_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEXi);
    }
    else if (GET_LEFT((*m_cube.getCubeData())[L_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEY);
    }
    else if (GET_RIGHT((*m_cube.getCubeData())[R_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEYi);
    }
    else if (GET_FRONT((*m_cube.getCubeData())[F_CENTRE]) == color)
    {
        Do(ROTATE_WHOLEX);
        Do(ROTATE_WHOLEX);
        //can also ROTATE_WHOLEY * 2
    }
    else if (GET_BACK((*m_cube.getCubeData())[B_CENTRE]) == color)
    {
        //nope
    }
}

void CubeSolver::Stage1()
{
    //white centre piece on the top face
    MoveToUp(COLOR_WHITE);

    //blue, orange, green, red
    MoveToRight(COLOR_BLUE);

    auto colors = { COLOR_BLUE, COLOR_ORANGE, COLOR_GREEN, COLOR_RED };
    CubeColor lastColor = *(colors.end() - 1);
    bool isFirst = true;

    for (CubeColor color : colors)
    {
        //find ????/white edge and put it DR
        FIND_EDGE((*m_cube.getCubeData()), color, COLOR_WHITE,
                  {
                      //FL
                      Do(ROTATE_FRONTi); // -> FD
                      Do(ROTATE_DOWN); // -> DR
                      if (!isFirst) //is not first, need to restore
                      {
                          Do(ROTATE_FRONT);
                      }
                  },
                  {
                      //FR
                      Do(ROTATE_RIGHTi); // -> DR
                  },
                  {
                      //FU
                      Do(ROTATE_FRONT); // -> FR
                      Do(ROTATE_RIGHTi); // -> DR
                      if (!isFirst) //is not first, need to restore
                      {
                          Do(ROTATE_FRONTi);
                      }
                  },
                  {
                      //FD
                      Do(ROTATE_DOWN); // -> DR
                  },
                  {
                      //BL
                      Do(ROTATE_BACK); // -> BD
                      Do(ROTATE_DOWNi); // -> DR
                      if (!isFirst) //is not first, need to restore
                      {
                          Do(ROTATE_BACKi);
                      }
                  },
                  {
                      //BR
                      Do(ROTATE_RIGHT); // -> DR
                  },
                  {
                      //BU
                      Do(ROTATE_BACKi); // -> BR
                      Do(ROTATE_RIGHT); // -> DR
                      if (!isFirst) //is not first, need to restore
                      {
                          Do(ROTATE_BACK);
                      }
                  },
                  {
                      //BD
                      Do(ROTATE_DOWNi); // -> DR
                  },
                  {
                      //UL
                      Do(ROTATE_LEFT); // -> FL
                      Do(ROTATE_FRONTi); // -> FD
                      Do(ROTATE_DOWN); // -> DR
                      if (!isFirst) //is not first, need to restore
                      {
                          Do(ROTATE_FRONT);
                          Do(ROTATE_LEFTi);
                      }
                  },
                  {
                      //UR
                      Do(ROTATE_RIGHT); // -> BR
                      Do(ROTATE_RIGHT); // -> DR
                  },
                  {
                      //DL
                      Do(ROTATE_DOWN); // -> BR
                      Do(ROTATE_DOWN); // -> DR
                  },
                  {
                      //DR
                      //nope
                  })

        // -> UR
        Do(ROTATE_RIGHT); // -> FR
        Do(ROTATE_RIGHT); // -> UR

        if (GET_RIGHT((*m_cube.getCubeData())[UR_EDGE]) == COLOR_WHITE) {
            //state2
            Do(ROTATE_RIGHTi);
            Do(ROTATE_UP);
            Do(ROTATE_FRONTi);
            Do(ROTATE_UPi);
        }

        //is not last, rotate to next color
        if (color != lastColor) {
            Do(ROTATE_WHOLEY);
        }
        isFirst = false;
    }
}

void CubeSolver::Stage2()
{
    std::vector<std::vector<CubeColor> > colors = { { COLOR_GREEN, COLOR_RED }, { COLOR_RED, COLOR_BLUE }, { COLOR_BLUE, COLOR_ORANGE }, { COLOR_ORANGE, COLOR_GREEN } };
    auto lastColor = *(colors.end() - 1);

    for (auto color : colors)
    {
        //find white/????/???? corner and put it FRD
        FIND_CORNER((*m_cube.getCubeData()), COLOR_WHITE, color[0], color[1],
                    {
                        //FLU
                        Do(ROTATE_LEFT); // -> FLD
                        Do(ROTATE_DOWN); // -> FRD
                        Do(ROTATE_LEFTi); //restore left
                    },
                    {
                        //FLD
                        Do(ROTATE_DOWN); // -> FRD
                    },
                    {
                        //FRU
                        if (!(GET_UP((*m_cube.getCubeData())[FRU_CORNER]) == COLOR_WHITE &&
                              GET_FRONT((*m_cube.getCubeData())[FRU_CORNER]) == color[0] &&
                              GET_RIGHT((*m_cube.getCubeData())[FRU_CORNER]) == color[1]))
                        {
                            Do(ROTATE_RIGHTi); // -> FRD
                            Do(ROTATE_DOWNi); // -> FLD to save
                            Do(ROTATE_RIGHT); //restore right
                            Do(ROTATE_DOWN); // -> FRD
                        }
                    },
                    {
                        //FRD
                        //nope
                    },
                    {
                        //BLU
                        Do(ROTATE_LEFTi); // -> BLD
                        Do(ROTATE_DOWN); // -> FLD
                        Do(ROTATE_DOWN); // -> FRD
                        Do(ROTATE_LEFT); //restore left
                    },
                    {
                        //BLD
                        Do(ROTATE_DOWN); // -> FLD
                        Do(ROTATE_DOWN); // -> FRD
                    },
                    {
                        //BRU
                        Do(ROTATE_BACKi); // -> BRD
                        Do(ROTATE_DOWNi); // -> FRD
                        Do(ROTATE_BACK); //restore back
                    },
                    {
                        //BRD
                        Do(ROTATE_DOWNi); // -> FRD
                    })


        while (!(GET_UP((*m_cube.getCubeData())[FRU_CORNER]) == COLOR_WHITE &&
                 GET_FRONT((*m_cube.getCubeData())[FRU_CORNER]) == color[0] &&
                 GET_RIGHT((*m_cube.getCubeData())[FRU_CORNER]) == color[1]))
        {
            Do(ROTATE_RIGHTi);
            Do(ROTATE_DOWNi);
            Do(ROTATE_RIGHT);
            Do(ROTATE_DOWN);
        }

        if (color != lastColor)
        {
            Do(ROTATE_WHOLEY); //rotate to next color
        }
    }
}

bool CubeSolver::CheckStage3()
{
    CubeColor leftCentre = GET_LEFT((*m_cube.getCubeData())[0][1][1]);
    bool checkLeft = GET_LEFT((*m_cube.getCubeData())[0][0][0]) == leftCentre &&
                     GET_LEFT((*m_cube.getCubeData())[0][0][1]) == leftCentre &&
                     GET_LEFT((*m_cube.getCubeData())[0][0][2]) == leftCentre &&
                     GET_LEFT((*m_cube.getCubeData())[0][1][0]) == leftCentre &&
                     GET_LEFT((*m_cube.getCubeData())[0][1][1]) == leftCentre &&
                     GET_LEFT((*m_cube.getCubeData())[0][1][2]) == leftCentre;

    CubeColor rightCentre = GET_RIGHT((*m_cube.getCubeData())[2][1][1]);
    bool checkRight = GET_RIGHT((*m_cube.getCubeData())[2][0][0]) == rightCentre &&
                      GET_RIGHT((*m_cube.getCubeData())[2][0][1]) == rightCentre &&
                      GET_RIGHT((*m_cube.getCubeData())[2][0][2]) == rightCentre &&
                      GET_RIGHT((*m_cube.getCubeData())[2][1][0]) == rightCentre &&
                      GET_RIGHT((*m_cube.getCubeData())[2][1][1]) == rightCentre &&
                      GET_RIGHT((*m_cube.getCubeData())[2][1][2]) == rightCentre;

    CubeColor frontCentre = GET_FRONT((*m_cube.getCubeData())[1][1][2]);
    bool checkFront = GET_FRONT((*m_cube.getCubeData())[0][0][2]) == frontCentre &&
                      GET_FRONT((*m_cube.getCubeData())[1][0][2]) == frontCentre &&
                      GET_FRONT((*m_cube.getCubeData())[2][0][2]) == frontCentre &&
                      GET_FRONT((*m_cube.getCubeData())[0][1][2]) == frontCentre &&
                      GET_FRONT((*m_cube.getCubeData())[1][1][2]) == frontCentre &&
                      GET_FRONT((*m_cube.getCubeData())[2][1][2]) == frontCentre;

    CubeColor backCentre = GET_BACK((*m_cube.getCubeData())[1][1][0]);
    bool checkBack = GET_BACK((*m_cube.getCubeData())[0][0][0]) == backCentre &&
                     GET_BACK((*m_cube.getCubeData())[1][0][0]) == backCentre &&
                     GET_BACK((*m_cube.getCubeData())[2][0][0]) == backCentre &&
                     GET_BACK((*m_cube.getCubeData())[0][1][0]) == backCentre &&
                     GET_BACK((*m_cube.getCubeData())[1][1][0]) == backCentre &&
                     GET_BACK((*m_cube.getCubeData())[2][1][0]) == backCentre;

    return m_cube.checkD() && checkLeft && checkRight && checkFront && checkBack;
}

void CubeSolver::Stage3()
{
    MoveToUp(COLOR_YELLOW);

    std::map<CubeColor, CubeColor> leftColor = {
            { COLOR_RED, COLOR_BLUE },
            { COLOR_BLUE, COLOR_ORANGE },
            { COLOR_ORANGE, COLOR_GREEN },
            { COLOR_GREEN, COLOR_RED }
    };

    std::map<CubeColor, CubeColor> rightColor = {
            { COLOR_BLUE, COLOR_RED },
            { COLOR_ORANGE, COLOR_BLUE },
            { COLOR_GREEN, COLOR_ORANGE },
            { COLOR_RED, COLOR_GREEN}
    };


    while (!CheckStage3())
    {
        std::vector<CubeColor> colors = { COLOR_RED, COLOR_GREEN, COLOR_ORANGE, COLOR_BLUE };

        CubeColor foundColor = COLOR_INVALID;
        for (auto color : colors)
        {
            MoveToFront(color);
            if (GET_FRONT((*m_cube.getCubeData())[FU_EDGE]) == color && GET_UP((*m_cube.getCubeData())[FU_EDGE]) != COLOR_YELLOW)
            {
                //nope, found vertical row of color
                foundColor = color;
            }
            else if (GET_RIGHT((*m_cube.getCubeData())[UR_EDGE]) == color && GET_UP((*m_cube.getCubeData())[UR_EDGE]) != COLOR_YELLOW)
            {
                Do(ROTATE_UP);
                foundColor = color;
            }
            else if (GET_BACK((*m_cube.getCubeData())[BU_EDGE]) == color && GET_UP((*m_cube.getCubeData())[BU_EDGE]) != COLOR_YELLOW)
            {
                Do(ROTATE_UP);
                Do(ROTATE_UP);
                foundColor = color;
            }
            else if (GET_LEFT((*m_cube.getCubeData())[UL_EDGE]) == color && GET_UP((*m_cube.getCubeData())[UL_EDGE]) != COLOR_YELLOW)
            {
                Do(ROTATE_UPi);
                foundColor = color;
            }
            else
            {
                //sad :(
            }

            if (foundColor != COLOR_INVALID)
            {
                break;
            }
        }

        if (foundColor == COLOR_INVALID)
        {
            //truly SAD
            for (auto color : colors)
            {
                MoveToFront(color);
                if ((GET_FRONT((*m_cube.getCubeData())[FL_EDGE]) != color || GET_LEFT((*m_cube.getCubeData())[FL_EDGE]) != leftColor[color]) &&
                    GET_FRONT((*m_cube.getCubeData())[FL_EDGE]) != COLOR_YELLOW && GET_LEFT((*m_cube.getCubeData())[FL_EDGE]) != COLOR_YELLOW)
                {
                    Do(ROTATE_FRONT);
                    Do(ROTATE_UP);
                    Do(ROTATE_FRONTi);
                    Do(ROTATE_UPi);
                    Do(ROTATE_LEFTi);
                    Do(ROTATE_UPi);
                    Do(ROTATE_LEFT);
                    Do(ROTATE_UP);
                    break;
                }
                if ((GET_FRONT((*m_cube.getCubeData())[FR_EDGE]) != color || GET_RIGHT((*m_cube.getCubeData())[FR_EDGE]) != rightColor[color]) &&
                    GET_FRONT((*m_cube.getCubeData())[FR_EDGE]) != COLOR_YELLOW && GET_RIGHT((*m_cube.getCubeData())[FR_EDGE]) != COLOR_YELLOW)
                {
                    Do(ROTATE_FRONTi);
                    Do(ROTATE_UPi);
                    Do(ROTATE_FRONT);
                    Do(ROTATE_UP);
                    Do(ROTATE_RIGHT);
                    Do(ROTATE_UP);
                    Do(ROTATE_RIGHTi);
                    Do(ROTATE_UPi);
                    break;
                }
            }
        }
        else
        {
            //move found edge to correct position
            if (GET_UP((*m_cube.getCubeData())[FU_EDGE]) == leftColor[foundColor])
            {
                //2)
                Do(ROTATE_UPi);
                Do(ROTATE_LEFTi);
                Do(ROTATE_UP);
                Do(ROTATE_LEFT);
                Do(ROTATE_UP);
                Do(ROTATE_FRONT);
                Do(ROTATE_UPi);
                Do(ROTATE_FRONTi);
            }
            else if (GET_UP((*m_cube.getCubeData())[FU_EDGE]) == rightColor[foundColor])
            {
                //1)
                Do(ROTATE_UP);
                Do(ROTATE_RIGHT);
                Do(ROTATE_UPi);
                Do(ROTATE_RIGHTi);
                Do(ROTATE_UPi);
                Do(ROTATE_FRONTi);
                Do(ROTATE_UP);
                Do(ROTATE_FRONT);
            }
            else
            {
                //assert false
                throw SolverError("Stage3: cannot find valid edge");
            }
        }
    }
}

bool CubeSolver::CheckStage4State1()
{
    CubeColor centre = GET_UP((*m_cube.getCubeData())[1][2][1]);
    return GET_UP((*m_cube.getCubeData())[1][2][0]) == centre &&
           GET_UP((*m_cube.getCubeData())[0][2][1]) == centre &&
           GET_UP((*m_cube.getCubeData())[1][2][1]) == centre &&
           GET_UP((*m_cube.getCubeData())[2][2][1]) == centre &&
           GET_UP((*m_cube.getCubeData())[1][2][2]) == centre;
}

bool CubeSolver::CheckStage4State3()
{
    CubeColor centre = GET_UP((*m_cube.getCubeData())[1][2][1]);
    return GET_UP((*m_cube.getCubeData())[1][2][0]) == centre &&
           GET_UP((*m_cube.getCubeData())[0][2][1]) == centre &&
           GET_UP((*m_cube.getCubeData())[1][2][1]) == centre;
}

bool CubeSolver::CheckStage4State4()
{
    CubeColor centre = GET_UP((*m_cube.getCubeData())[1][2][1]);
    return GET_UP((*m_cube.getCubeData())[0][2][1]) == centre &&
           GET_UP((*m_cube.getCubeData())[1][2][1]) == centre &&
           GET_UP((*m_cube.getCubeData())[2][2][1]) == centre;
}

bool CubeSolver::CheckStage4State4i()
{
    CubeColor centre = GET_UP((*m_cube.getCubeData())[1][2][1]);
    return GET_UP((*m_cube.getCubeData())[1][2][0]) == centre &&
           GET_UP((*m_cube.getCubeData())[1][2][1]) == centre &&
           GET_UP((*m_cube.getCubeData())[1][2][2]) == centre;
}

void CubeSolver::Stage4()
{

    while (!CheckStage4State1())
    {
        //state4
        if (CheckStage4State4i())
        {
            Do(ROTATE_WHOLEY);
            //assert CheckStage4State4 == true
        }
        if (CheckStage4State4())
        {
            Do(ROTATE_FRONT);
            Do(ROTATE_RIGHT);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHTi);
            Do(ROTATE_UPi);
            Do(ROTATE_FRONTi);
            continue;
        }

        //state3
        bool state3 = false;
        for (int i = 0; i < 4; ++i)
        {
            if (CheckStage4State3())
            {
                Do(ROTATE_FRONT);
                Do(ROTATE_UP);
                Do(ROTATE_RIGHT);
                Do(ROTATE_UPi);
                Do(ROTATE_RIGHTi);
                Do(ROTATE_FRONTi);
                state3 = true;
                break;
            }
            if (i < 3)
            {
                Do(ROTATE_WHOLEY);
            }
        }
        if (state3) continue;

        //state2: .
        Do(ROTATE_FRONT);
        Do(ROTATE_UP);
        Do(ROTATE_RIGHT);
        Do(ROTATE_UPi);
        Do(ROTATE_RIGHTi);
        Do(ROTATE_FRONTi);
    }
    //must be state1
}

void CubeSolver::Stage5()
{

    while (!m_cube.checkU()) {
        CubeColor centre = GET_UP((*m_cube.getCubeData())[1][2][1]);
        int correctCount = (GET_UP((*m_cube.getCubeData())[0][2][0]) == centre) +
                           (GET_UP((*m_cube.getCubeData())[2][2][0]) == centre) +
                           (GET_UP((*m_cube.getCubeData())[0][2][2]) == centre) +
                           (GET_UP((*m_cube.getCubeData())[2][2][2]) == centre);

        if (correctCount == 2)
        {
            if (GET_FRONT((*m_cube.getCubeData())[FLU_CORNER]) == COLOR_YELLOW)
            {
                //nope
            }
            else if (GET_RIGHT((*m_cube.getCubeData())[FRU_CORNER]) == COLOR_YELLOW)
            {
                Do(ROTATE_WHOLEY); // -> FLU
            }
            else if (GET_BACK((*m_cube.getCubeData())[BRU_CORNER]) == COLOR_YELLOW)
            {
                Do(ROTATE_WHOLEY); // -> FRU
                Do(ROTATE_WHOLEY); // -> FLU
            }
            else if (GET_LEFT((*m_cube.getCubeData())[BLU_CORNER]) == COLOR_YELLOW)
            {
                Do(ROTATE_WHOLEYi); // -> FLU
            }
            else
            {
                --correctCount;
                //regard as correctCount = 1
            }
        }
        if (correctCount == 2)
        {
            Do(ROTATE_RIGHT);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHTi);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHT);
            Do(ROTATE_UP);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHTi);
            continue;
        }
        if (correctCount == 1)
        {
            if (GET_UP((*m_cube.getCubeData())[FLU_CORNER]) == COLOR_YELLOW)
            {
                //nope
            }
            else if (GET_UP((*m_cube.getCubeData())[FRU_CORNER]) == COLOR_YELLOW)
            {
                Do(ROTATE_WHOLEY); // -> FLU
            }
            else if (GET_UP((*m_cube.getCubeData())[BRU_CORNER]) == COLOR_YELLOW)
            {
                Do(ROTATE_WHOLEY); // -> FRU
                Do(ROTATE_WHOLEY); // -> FLU
            }
            else if (GET_UP((*m_cube.getCubeData())[BLU_CORNER]) == COLOR_YELLOW)
            {
                Do(ROTATE_WHOLEYi); // -> FLU
            }
            else
            {
                //assert false
                throw SolverError("Stage5: cannot find valid yellow (correctCount = 1)");
            }
            Do(ROTATE_RIGHT);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHTi);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHT);
            Do(ROTATE_UP);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHTi);
            continue;
        }
        if (correctCount == 0)
        {
            if (GET_LEFT((*m_cube.getCubeData())[FLU_CORNER]) == COLOR_YELLOW)
            {
                //nope
            }
            else if (GET_FRONT((*m_cube.getCubeData())[FRU_CORNER]) == COLOR_YELLOW)
            {
                Do(ROTATE_WHOLEY); // -> FLU
            }
            else if (GET_RIGHT((*m_cube.getCubeData())[BRU_CORNER]) == COLOR_YELLOW)
            {
                Do(ROTATE_WHOLEY); // -> FRU
                Do(ROTATE_WHOLEY); // -> FLU
            }
            else if (GET_BACK((*m_cube.getCubeData())[BLU_CORNER]) == COLOR_YELLOW)
            {
                Do(ROTATE_WHOLEYi); // -> FLU
            }
            else
            {
                //assert false
                throw SolverError("Stage5: cannot find valid yellow (correctCount = 0)");
            }
            Do(ROTATE_RIGHT);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHTi);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHT);
            Do(ROTATE_UP);
            Do(ROTATE_UP);
            Do(ROTATE_RIGHTi);
            continue;
        }
    }
}

void CubeSolver::CheckStage6ABCD(bool *A, bool *B, bool *C, bool*D)
{
    *A = (GET_LEFT((*m_cube.getCubeData())[BLU_CORNER]) == GET_LEFT((*m_cube.getCubeData())[L_CENTRE])) &&
         (GET_BACK((*m_cube.getCubeData())[BLU_CORNER]) == GET_BACK((*m_cube.getCubeData())[B_CENTRE]));

    *B = (GET_RIGHT((*m_cube.getCubeData())[BRU_CORNER]) == GET_RIGHT((*m_cube.getCubeData())[R_CENTRE])) &&
         (GET_BACK((*m_cube.getCubeData())[BRU_CORNER])  == GET_BACK((*m_cube.getCubeData())[B_CENTRE]));

    *C = (GET_LEFT((*m_cube.getCubeData())[FLU_CORNER])  == GET_LEFT((*m_cube.getCubeData())[L_CENTRE])) &&
         (GET_FRONT((*m_cube.getCubeData())[FLU_CORNER]) == GET_FRONT((*m_cube.getCubeData())[F_CENTRE]));

    *D = (GET_RIGHT((*m_cube.getCubeData())[FRU_CORNER]) == GET_RIGHT((*m_cube.getCubeData())[R_CENTRE])) &&
         (GET_FRONT((*m_cube.getCubeData())[FRU_CORNER]) == GET_FRONT((*m_cube.getCubeData())[F_CENTRE]));
}

void CubeSolver::Stage6()
{
    bool A, B, C, D;
    CheckStage6ABCD(&A, &B, &C, &D);

    if (A + B + C + D == 4) return;


    while (A + B + C + D < 2)
    {
        Do(ROTATE_UP);
        CheckStage6ABCD(&A, &B, &C, &D);
    }

    if (A + B + C + D == 4) return;


    while (!((A && B) || (A && D) || (B && C)))
    {
        Do(ROTATE_WHOLEY);
        CheckStage6ABCD(&A, &B, &C, &D);
    }

    if ((A && D) || (B && C))
    {
        Do(ROTATE_RIGHTi);
        Do(ROTATE_FRONT);
        Do(ROTATE_RIGHTi);
        Do(ROTATE_BACK);
        Do(ROTATE_BACK);
        Do(ROTATE_RIGHT);
        Do(ROTATE_FRONTi);
        Do(ROTATE_RIGHTi);
        Do(ROTATE_BACK);
        Do(ROTATE_BACK);
        Do(ROTATE_RIGHT);
        Do(ROTATE_RIGHT);
        Do(ROTATE_UPi);

        CheckStage6ABCD(&A, &B, &C, &D);

        while (A + B + C + D < 2)
        {
            Do(ROTATE_UP);
            CheckStage6ABCD(&A, &B, &C, &D);
        }


        while (!(A && B))
        {
            Do(ROTATE_WHOLEY);
            CheckStage6ABCD(&A, &B, &C, &D);
        }
    }

    if (A && B)
    {
        Do(ROTATE_RIGHTi);
        Do(ROTATE_FRONT);
        Do(ROTATE_RIGHTi);
        Do(ROTATE_BACK);
        Do(ROTATE_BACK);
        Do(ROTATE_RIGHT);
        Do(ROTATE_FRONTi);
        Do(ROTATE_RIGHTi);
        Do(ROTATE_BACK);
        Do(ROTATE_BACK);
        Do(ROTATE_RIGHT);
        Do(ROTATE_RIGHT);
        Do(ROTATE_UPi);
    }
    else
    {
        //assert false
        throw SolverError("Stage6: unexpected condition");
    }
}

void CubeSolver::CheckStage7EFGH(bool *E, bool *F, bool *G, bool*H)
{
    *E = (GET_LEFT((*m_cube.getCubeData())[UL_EDGE]) == GET_LEFT((*m_cube.getCubeData())[L_CENTRE]));

    *F = (GET_BACK((*m_cube.getCubeData())[BU_EDGE]) == GET_BACK((*m_cube.getCubeData())[B_CENTRE]));

    *G = (GET_RIGHT((*m_cube.getCubeData())[UR_EDGE]) == GET_RIGHT((*m_cube.getCubeData())[R_CENTRE]));

    *H = (GET_FRONT((*m_cube.getCubeData())[FU_EDGE]) == GET_FRONT((*m_cube.getCubeData())[F_CENTRE]));
}

void CubeSolver::Stage7()
{
    bool E, F, G, H;
    CheckStage7EFGH(&E, &F, &G, &H);


    while (E + F + G + H != 4)
    {
        if (E + F + G + H == 0)
        {
            Do(ROTATE_FRONT);
            Do(ROTATE_FRONT);
            Do(ROTATE_UP);
            Do(ROTATE_LEFT);
            Do(ROTATE_RIGHTi);
            Do(ROTATE_FRONT);
            Do(ROTATE_FRONT);
            Do(ROTATE_LEFTi);
            Do(ROTATE_RIGHT);
            Do(ROTATE_UP);
            Do(ROTATE_FRONT);
            Do(ROTATE_FRONT);

            CheckStage7EFGH(&E, &F, &G, &H);
        }

        if (E + F + G + H == 1)
        {
            CheckStage7EFGH(&E, &F, &G, &H);

            while (!F)
            {
                Do(ROTATE_WHOLEY);
                CheckStage7EFGH(&E, &F, &G, &H);
            }

            if (GET_FRONT((*m_cube.getCubeData())[FU_EDGE]) == GET_LEFT((*m_cube.getCubeData())[L_CENTRE]))
            {
                Do(ROTATE_FRONT);
                Do(ROTATE_FRONT);
                Do(ROTATE_UP);
                Do(ROTATE_LEFT);
                Do(ROTATE_RIGHTi);
                Do(ROTATE_FRONT);
                Do(ROTATE_FRONT);
                Do(ROTATE_LEFTi);
                Do(ROTATE_RIGHT);
                Do(ROTATE_UP);
                Do(ROTATE_FRONT);
                Do(ROTATE_FRONT);
            }
            else if (GET_FRONT((*m_cube.getCubeData())[FU_EDGE]) == GET_RIGHT((*m_cube.getCubeData())[R_CENTRE]))
            {
                Do(ROTATE_FRONT);
                Do(ROTATE_FRONT);
                Do(ROTATE_UPi);
                Do(ROTATE_LEFT);
                Do(ROTATE_RIGHTi);
                Do(ROTATE_FRONT);
                Do(ROTATE_FRONT);
                Do(ROTATE_LEFTi);
                Do(ROTATE_RIGHT);
                Do(ROTATE_UPi);
                Do(ROTATE_FRONT);
                Do(ROTATE_FRONT);
            }
            else {
                //assert false
                throw SolverError("Stage7: unexpected condition");
            }
        }
        CheckStage7EFGH(&E, &F, &G, &H);
    }
}