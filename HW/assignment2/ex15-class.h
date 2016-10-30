/* ECE373
 * Programming C++
 * Filename: ex15-class.h
 *
 */

class CRectangle {
  public:
	CRectangle(int x, int y);
	~CRectangle(void);
    int area (void);
  private:
	int valX,valY;
};

