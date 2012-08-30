/**
 * Class:	Point2i
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#ifndef Point2i_H
#define Point2i_H

namespace JDHUtility
{
	class Vector2f;

	class Point2i
	{
	public:
		Point2i(int x, int y);
		Point2i(const Point2i &position);
		Point2i(void);
		~Point2i(void);

		int		getX		(void) const;
		int		getY		(void) const;
		void	rotate		(float theta);
		void	setPosition	(const Point2i &position);
		void	scale		(int xs, int ys);
		void	scaleX		(int s);
		void	scaleY		(int s);
		void	setX		(int x);
		void	setY		(int y);
		void	translate	(int xt, int yt);
		void	translate	(const JDHUtility::Vector2f &tv);
		void	translateX	(int t);
		void	translateY	(int t);

	protected:
		int x, y;

	};
}
#endif

