#ifndef NOXYZFILTER_H
#define NOXYZFILTER_H

#include <map>
#include <vector>

#include "../../COMMON/types.h" // common
#include "../../COMMON/macro.h" // common
#include "../../COMMON/utilities.h" // common

class NoXYZFilter {
public:
	CubeSteps Filter(CubeSteps&);

    static std::map<CubeRotateMethod, std::map<CubeRotateMethod, CubeRotateMethod> > XYZMapTables;
	
private:
	void CombineMapTable(std::map<CubeRotateMethod, CubeRotateMethod>&, std::map<CubeRotateMethod, CubeRotateMethod>&);
	bool isWholeRotate(CubeRotateMethod m);
	void copySteps(CubeSteps &src, CubeSteps &dest);
};


#endif
