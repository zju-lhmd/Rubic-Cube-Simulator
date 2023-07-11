#include "RotateCommand.h"

#include "../ViewModel.h"

RotateCommand::RotateCommand(ViewModel* pVM): m_pVM(pVM), m_method()
{
}

void RotateCommand::setParameter(const std::any& param)
{
    m_method = toUpperString(std::any_cast<std::string>(param));
}

void RotateCommand::exec()
{
    // get rotate method
    auto it = nameToMethod.find(m_method);
    if(it != nameToMethod.end()) {
		CubeSteps steps(1, it->second);
        *m_pVM->m_pRSteps = steps;
		m_pVM->notifyAllObservers(2);
    }
    // if not exist, abort
}

const std::map<std::string, CubeRotateMethod> RotateCommand::nameToMethod =
{
	{"NONE", ROTATE_NONE   },
	{"F"   , ROTATE_FRONT  },
	{"B"   , ROTATE_BACK   },
	{"L"   , ROTATE_LEFT   },
	{"R"   , ROTATE_RIGHT  },
	{"U"   , ROTATE_UP     },
	{"D"   , ROTATE_DOWN   },
	{"X"   , ROTATE_WHOLEX },
	{"Y"   , ROTATE_WHOLEY },
	{"Z"   , ROTATE_WHOLEZ },
	{"FI"  , ROTATE_FRONTi },
	{"BI"  , ROTATE_BACKi  },
	{"LI"  , ROTATE_LEFTi  },
	{"RI"  , ROTATE_RIGHTi },
	{"UI"  , ROTATE_UPi    },
	{"DI"  , ROTATE_DOWNi  },
	{"XI"  , ROTATE_WHOLEXi},
	{"YI"  , ROTATE_WHOLEYi},
	{"ZI"  , ROTATE_WHOLEZi}
};