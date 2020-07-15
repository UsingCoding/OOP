#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

using namespace std;

struct Point
{
	int x, y;
};

// Холст, позволяющий рисовать графические примитивы
class ICanvas
{
public:
	virtual void DrawLine(int x0, int y0, int x1, int y1) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста, выполняющая вывод информации о рисуемых примитивах в stdout в виде:
// DrawLine:(<x0>, <y0>) - (<x1>, <y1>)
class CCanvas : public ICanvas
{
public:
	void DrawLine(int x0, int y0, int x1, int y1) override
	{
		std::cout << "DrawLine:(" << x0 << ", " << y0 << ") - (" << x1 << ", " << y1 << ")" << std::endl;
	}
};

// Интерфейс объектов, которые можно нарисовать на холсте
class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas & canvas) const = 0;
	virtual ~ICanvasDrawable() = default;
};

// Прямоугольник, обладающий координатами верхнего левого угла, шириной и высотой
class CRectangle : public ICanvasDrawable
{
private:
	Point m_point;
	int m_width, m_height;
public:
	CRectangle(Point x1, int width, int height): m_point(x1), m_width(width), m_height(height) {}

	void Draw(ICanvas & canvas) const override
	{
		canvas.DrawLine(m_point.x, m_point.y, m_point.x + m_width, m_point.y);
		canvas.DrawLine(m_point.x + m_width, m_point.y, m_point.x + m_width, m_point.y + m_height);
		canvas.DrawLine(m_point.x + m_width, m_point.y + m_height, m_point.x, m_point.y + m_height);
		canvas.DrawLine(m_point.x, m_point.y + m_height, m_point.x, m_point.y);
	}
};

// Треугольник, задается координатами трех вершин
class CTriangle : public ICanvasDrawable
{
private:
	Point m_p1, m_p2, m_p3;
public:
	CTriangle(Point x1, Point x2, Point x3): m_p1(x1), m_p2(x2), m_p3(x3) {}

	void Draw(ICanvas & canvas) const override
	{
		canvas.DrawLine(m_p1.x, m_p1.y, m_p2.x, m_p2.y);
		canvas.DrawLine(m_p2.x, m_p2.y, m_p3.x, m_p3.y);
		canvas.DrawLine(m_p3.x, m_p3.y, m_p1.x, m_p1.y);
	}
};

// Рисует картину picture на холсте canvas
void DrawPicture(ICanvas & canvas, const vector<shared_ptr<const ICanvasDrawable>> & picture)
{
	for (size_t i = 0; i < picture.size(); i++)
	{
		picture[i]->Draw(canvas);
	}
}

int main()
{
	auto triangle = make_shared<CTriangle>(Point{0, 4}, Point{4, 7}, Point{8, 4});
	auto rectangle = make_shared<CRectangle>(Point{1, 4}, 6, 4);

	auto canvas = CCanvas();

	vector<shared_ptr<const ICanvasDrawable>> picture = {triangle, rectangle};

	DrawPicture(canvas, picture);

	/*
	Задание:
		При помощи имеющихся фигур описать домик
		"Нарисовать" его при помощи функции DrawPicture на "холсте" CCanvas
	   /\
	  /  \
	 /    \
	--------
	 |    |
	 |    |
	 |    |
	 ------
	*/
	return 0;
}
