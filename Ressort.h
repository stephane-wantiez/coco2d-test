#ifndef __RESSORT_H__
#define __RESSORT_H__

#include "cocos2d.h"

USING_NS_CC;


class Ressort
{
	private:
		CCPoint mCurrentPoint;
		const double cGravity;
		const double cKConst;
		const double cLConst;

	public:
		Ressort(const double & gravity, const double & kConst, const double & lConst);
		void drawTo(const CCPoint & point);
		void update(const double & deltaTimeSec);
		const CCPoint & getCurrentPoint();

};


#endif
