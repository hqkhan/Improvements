/* ECE373
 * Programming C++
 * Filename: ex16-class.h
 *
 */

class CRectangle {
  public:
	CRectangle(int x, int y);
	CRectangle(void);
	~CRectangle(void);
    int area (void);
	void set_values(int x, int y);
	double diagonal;
  private:
	int valX,valY;
};

