/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Eva Banova
* @idnumber 5MI0600304
* @compiler VC
*
* whole project
*
*/


#include <iostream>
#include <cmath>

struct Point
{
    double x;
    double y;
    char name[100];
};

struct Line
{
    double a_coef;
    double b_coef;
    double c_coef;
    char name[100];
};

struct QuadraticFunction
{
    double a_coef;
    double b_coef;
    double c_coef;
};

bool nameValidation(char name[])
{
    bool correct_name = true;

    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] < 'A' || name[i] > 'Z')
        {
            if (name[i] < 'a' || name[i] > 'z')
            {
                if (name[i] < '0' || name[i] > '9')
                {
                    if (name[i] != '_')
                    {
                        correct_name = false;
                        break;
                    }
                }
            }
        }
    }

    return correct_name;
}

Point readPoint()
{
    Point p;

    do
    {
        std::cout << "Enter name of point: ";
        std::cin >> p.name;
    } while (!nameValidation(p.name));

    std::cout << "Enter x-coordinate: ";
    std::cin >> p.x;
    std::cout << "Enter y-coordinate: ";
    std::cin >> p.y;
    std::cout << std::endl;

    return p;
}

Line readLine() {
    Line l;

    do
    {
        std::cout << "Enter name of line: ";
        std::cin >> l.name;
    } while (!nameValidation(l.name));

    std::cout << "Enter coefficient a: ";
    std::cin >> l.a_coef;
    std::cout << "Enter coefficient b: ";
    std::cin >> l.b_coef;
    std::cout << "Enter coefficient c: ";
    std::cin >> l.c_coef;
    std::cout << std::endl;

    return l;
}

QuadraticFunction readQuadraticFunction()
{
    QuadraticFunction f;

    std::cout << "Enter coefficient a: ";
    std::cin >> f.a_coef;
    std::cout << "Enter coefficient b: ";
    std::cin >> f.b_coef;
    std::cout << "Enter coefficient c: ";
    std::cin >> f.c_coef;
    std::cout << std::endl;

    return f;
}

void coutLine(Line& line)
{
    std::cout << line.a_coef << "x + " << line.b_coef << "y + " << line.c_coef << " = 0\n";
}

void coutPoint(Point& point)
{
    std::cout << "(" << point.x << " , " << point.y << ")\n";
}

void displayBeginning()
{
    std::cout << std::endl <<
        "*************************************\n" <<
        "*                                   *\n" <<
        "*     WELLCOME TO GEOMETRY TOOL     *\n" <<
        "*                                   *\n" <<
        "*************************************\n" << std::endl;
}

void displayEnd()
{
    std::cout << std::endl <<
        "*************************************\n" <<
        "*                                   *\n" <<
        "*        END OF GEOMETRY TOOL       *\n" <<
        "*                                   *\n" <<
        "*************************************\n" << std::endl;
}

void displayMenu()
{
    std::cout << std::endl
        << "Choose operation:\n"
        << "1. Add point\n"
        << "2. Add line\n"
        << "3. Check if point lies on line\n"
        << "4. Derive an equation of a line, parallel to another line and passing through point\n"
        << "5. Derive an equation of a line, perpendicular to another line at a point\n"
        << "6. Find intersection point of two lines\n"
        << "7. Derive the equations of heights, medians and perpendicular bisectors of a triangle\n"
        << "8. Derive a eguation of tangent to guadratic function at a point\n"
        << "9. Find intersection points of a quadratic function and line\n"
        << "10. Determine the type of quadrangle four lines form when intersected\n"
        << "11. Exit\n" << std::endl;
}

bool isPointOnLine(Point& point, Line& line)
{
    return (line.a_coef * point.x + line.b_coef * point.y + line.c_coef) == 0;
}

Line parallelLine(Line& line, Point& point)
{
    Line g;

    g.a_coef = line.a_coef;
    g.b_coef = line.b_coef;
    g.c_coef = -1 * (point.x * line.a_coef + point.y * line.b_coef);

    return g;
}

Line perpendicularLine(Line& line, Point& point)
{
    Line g;

    g.a_coef = line.b_coef;
    g.b_coef = -1 * line.a_coef;
    g.c_coef = point.x * line.b_coef - point.y * line.a_coef;

    return g;
}

bool checkForIntersectionPoint(Line& line1, Line& line2)
{
    if (line1.a_coef == line2.a_coef && line1.b_coef == line2.b_coef)
        return false;
    else
        return true;
}

Point intersectionPoint(Line& line1, Line& line2)
{
    Point p;

    const double divider = line1.a_coef * line2.b_coef - line2.a_coef * line1.b_coef;

    p.x = (line1.b_coef * line2.c_coef - line2.b_coef * line1.c_coef) / divider;
    p.y = (line2.a_coef * line1.c_coef - line1.a_coef * line2.c_coef) / divider;

    return p;
}

Line getHeight(Point& point1, Point& point2, Point& point3)
{
    Line height;
    height.a_coef = point3.x - point2.x;
    height.b_coef = point3.y - point2.y;
    height.c_coef = -1 * height.a_coef * point1.x - height.b_coef * point1.y;

    return height;
}

Line getMedian(Point& point1, Point& point2, Point& point3)
{
    Point middle;
    middle.x = (point2.x + point3.x) / 2;
    middle.y = (point2.y + point3.y) / 2;

    Line median;
    median.a_coef = point1.y - middle.y;
    median.b_coef = middle.x - point1.x;
    median.c_coef = point1.x * middle.y - point1.y * middle.x;

    return median;
}

Line getPerpendicularBisector(Point& point1, Point& point2)
{
    Line sizeOfTriangle;
    sizeOfTriangle.a_coef = point1.y - point2.y;
    sizeOfTriangle.b_coef = point2.x - point1.x;
    sizeOfTriangle.c_coef = point1.x * point2.y - point2.x * point1.y;

    Point middle;
    middle.x = (point1.x + point2.x) / 2;
    middle.y = (point1.y + point2.y) / 2;

    return perpendicularLine(sizeOfTriangle, middle);
}

Line getTangentOfQuadraticFunctionInPoint(QuadraticFunction& function, Point& point)
{
    const double multiplier = 2 * function.a_coef * point.x + function.b_coef;

    Line tangent;
    tangent.a_coef = multiplier;
    tangent.b_coef = -1;
    tangent.c_coef = point.y - point.x * multiplier;

    return tangent;
}

void getIntersectionPointFunctionLine(QuadraticFunction& function, Line& line)
{
    double D = pow((line.a_coef + function.b_coef * line.b_coef), 2) -
        4 * line.b_coef * function.a_coef * (function.c_coef * line.b_coef + line.c_coef);

    if (D < 0)
        std::cout << "Intersection point does not exist.\n";

    else if (D == 0)
    {
        Point p;
        p.x = (-line.a_coef - function.b_coef * line.b_coef) / (2 * line.b_coef * function.a_coef);
        p.y = function.a_coef * pow(p.x, 2) + function.b_coef * p.x + function.c_coef;

        coutPoint(p);
    }

    else
    {
        Point p1;
        Point p2;

        p1.x = (-line.a_coef - function.b_coef * line.b_coef + sqrt(D)) / (2 * line.b_coef * function.a_coef);
        p1.y = function.a_coef * pow(p1.x, 2) + function.b_coef * p1.x + function.c_coef;

        p2.x = (-line.a_coef - function.b_coef * line.b_coef - sqrt(D)) / (2 * line.b_coef * function.a_coef);
        p2.y = function.a_coef * pow(p2.x, 2) + function.b_coef * p2.x + function.c_coef;

        coutPoint(p1);
        coutPoint(p2);
    }
}

void typeQuadrangle(Line& line1, Line& line2, Line& line3, Line& line4)
{
    if (!checkForIntersectionPoint(line1, line2) || !checkForIntersectionPoint(line2, line3) ||
        !checkForIntersectionPoint(line3, line4) || !checkForIntersectionPoint(line4, line1))
        std::cout << "A quadrangle does not exist.\n";

    else if (!checkForIntersectionPoint(line1, line3))
    {
        if (!checkForIntersectionPoint(line2, line4))
            std::cout << "The quadranhle is parallelogram.\n";
        else
            std::cout << "The quadranhle is trapezoid.\n";
    }

    else if (!checkForIntersectionPoint(line2, line4))
    {
        if (!checkForIntersectionPoint(line1, line3))
            std::cout << "The quadranhle is parallelogram.\n";
        else
            std::cout << "The quadranhle is trapezoid.\n";
    }

    else
        std::cout << "The quadrangle exists, but is no special type.\n";
}

int main()
{
    int operation = 0;

    displayBeginning();

    while (true)
    {
        displayMenu();
        std::cout << "Enter operation code: ";
        std::cin >> operation;

        if (operation == 1)
        {
            Point p = readPoint();

            std::cout << "Added point " << p.name << " at: ";
            coutPoint(p);
        }

        else if (operation == 2)
        {
            Line l = readLine();

            std::cout << "Added line " << l.name << " with equation: ";
            coutLine(l);
        }

        else if (operation == 3)
        {
            Point p = readPoint();
            Line l = readLine();

            if (isPointOnLine(p, l))
                std::cout << "Point lies on the line.\n";
            else
                std::cout << "Point does not lie on the line.\n";
        }

        else if (operation == 4)
        {
            Line l = readLine();
            Point p = readPoint();

            Line parallel = parallelLine(l, p);

            std::cout << "Parallel line with equation: ";
            coutLine(parallel);
        }

        else if (operation == 5)
        {
            Line l = readLine();
            Point p = readPoint();

            if (!isPointOnLine(p, l))
            {
                do
                {
                    std::cout << "This point is not on the line, please enter another point.\n";
                    p = readPoint();
                } while (!isPointOnLine(p, l));
            }

            Line perpendicular = perpendicularLine(l, p);

            std::cout << "Perpendicular line with equation: ";
            coutLine(perpendicular);
        }

        else if (operation == 6)
        {
            Line l1 = readLine();
            Line l2 = readLine();

            if (!checkForIntersectionPoint(l1, l2))
                std::cout << "Intersection point of this two lines doesnt exist\n";

            else
            {
                Point intersection = intersectionPoint(l1, l2);

                std::cout << "The intersection point is: ";
                coutPoint(intersection);
            }
        }

        else if (operation == 7)
        {
            Point p1 = readPoint();
            Point p2 = readPoint();
            Point p3 = readPoint();

            Line height1 = getHeight(p1, p2, p3);
            Line height2 = getHeight(p2, p1, p3);
            Line height3 = getHeight(p3, p2, p1);

            Line median1 = getMedian(p1, p2, p3);
            Line median2 = getMedian(p2, p1, p3);
            Line median3 = getMedian(p3, p2, p1);

            Line per_bisector1 = getPerpendicularBisector(p1, p2);
            Line per_bisector2 = getPerpendicularBisector(p1, p3);
            Line per_bisector3 = getPerpendicularBisector(p3, p2);

            std::cout << "The triangle has equations of heights:\n";
            coutLine(height1);
            coutLine(height2);
            coutLine(height3);
            std::cout << "The triangle has equations of medianss:\n";
            coutLine(median1);
            coutLine(median2);
            coutLine(median3);
            std::cout << "The triangle has equations of perpendicular bisectors:\n";
            coutLine(per_bisector1);
            coutLine(per_bisector2);
            coutLine(per_bisector3);
        }

        else if (operation == 8)
        {
            QuadraticFunction f = readQuadraticFunction();
            Point p;

            do
            {
                p = readPoint();
            } while (pow(p.x, 2) * f.a_coef + p.x * f.b_coef + f.c_coef != p.y);

            Line t = getTangentOfQuadraticFunctionInPoint(f, p);
            coutLine(t);
        }

        else if (operation == 9)
        {
            QuadraticFunction f = readQuadraticFunction();
            Line l = readLine();

            getIntersectionPointFunctionLine(f, l);
        }

        else if (operation == 10)
        {
            Line l1 = readLine();
            Line l2 = readLine();
            Line l3 = readLine();
            Line l4 = readLine();

            typeQuadrangle(l1, l2, l3, l4);
        }

        else if (operation == 11)
        {
            break;
        }

        else
        {
            std::cout << "Invalid operation. Please choose again.\n";
        }
    }

    displayEnd();

    return 0;
}
