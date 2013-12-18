#include "Ressort.h"

Ressort::Ressort(const double & gravity, const double & kConst, const double & lConst) : cGravity(gravity), cKConst(kConst), cLConst(lConst)
{
}

void Ressort::drawTo(const CCPoint & point)
{
	mCurrentPoint = point;
}

void Ressort::update(const double & deltaTimeSec)
{
}

const CCPoint & Ressort::getCurrentPoint()
{
	return mCurrentPoint;
}
