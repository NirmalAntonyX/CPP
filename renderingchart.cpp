#include <iostream>
#include <functional>
#include <algorithm>
#include <memory>

using namespace std;

typedef pair<int, int> Coordinates;
typedef int Color[3];
typedef std::shared_ptr<int> RGBPtr;

class Chart
{
  public:
    Coordinates top, bottom;
    Color color;
    Chart() = delete;
    explicit Chart(int x1, int y1, int x2, int y2, int red, int green, int blue) : 
           top(x1, y1), bottom(x2, y2), color{red, green, blue} {}

    int getXCooridanate(Coordinates coordinates) const { return coordinates.first; }
    int getYCoordinate(Coordinates coordinates) const { return coordinates.second; }
    inline Coordinates getTopCoordinates() const { return top; }
    inline Coordinates getBottomCoordinates() const { return bottom; }
    inline int getColorByIndex(int index) const
    {
        if (index > 3)
            return 0;
        //  cout << "color index" << color[index] << endl;
        return color[index];
    }
};

class View
{
    Chart _A, _B;

  public:
    View() = delete;
    explicit View(Chart A, Chart B) : _A(A), _B(B){};

    bool validateCordinates(Chart &chart)
    {
        bool valid(true);
        Coordinates topCoordinates = chart.getTopCoordinates();
        Coordinates bottomCoordinates = chart.getBottomCoordinates();
        int topXCoord = chart.getXCooridanate(topCoordinates);
        int topYCoord = chart.getYCoordinate(topCoordinates);
        int bottomXCoord = chart.getXCooridanate(bottomCoordinates);
        int bottomYCoord = chart.getYCoordinate(bottomCoordinates);

        if ((topXCoord == bottomXCoord) ||
            (topYCoord == bottomYCoord))
        {
            cout << "straight line";
            valid = false;
        }

        if (topXCoord < 0 || topYCoord < 0 || bottomXCoord < 0 || bottomYCoord < 0)
        {
            cout << "negative args";
            valid = false;
        }

        if (!valid)
            cout << "Invalid Arguments"
                 << "topXCoord: " << topXCoord << endl
                 << "topYCoord: " << topYCoord << endl
                 << "bottomXCoord: " << bottomXCoord << endl
                 << "bottomYCoord: " << bottomYCoord << endl;

        return valid;
    }

    bool DoChartsOverlap(Chart &A, Chart &B)
    {

        if (!validateCordinates(A) ||
            !validateCordinates(B))
        {
            // Invalid Arguments
            cout << "Invalid Arguments" << endl;
            return false;
        }

        bool overlap(true);
        int chartAtopXCoord = A.getXCooridanate(A.getTopCoordinates());
        int chartAtopYCoord = A.getYCoordinate(A.getTopCoordinates());
        int chartAbottomXCoord = A.getXCooridanate(A.getBottomCoordinates());
        int chartAbottomYCoord = A.getYCoordinate(A.getBottomCoordinates());
        int chartBtopXCoord = B.getXCooridanate(B.getTopCoordinates());
        int chartBtopYCoord = B.getYCoordinate(B.getTopCoordinates());
        int chartBbottomXCoord = B.getXCooridanate(B.getBottomCoordinates());
        int chartBbottomYCoord = B.getYCoordinate(B.getBottomCoordinates());

        if (chartBtopXCoord > chartAbottomXCoord ||
            chartAtopXCoord > chartBbottomXCoord)
        {
            cout << "charts are way UP or BELOW without overlap" << endl;
            overlap = false;
        }

        if (chartAtopYCoord < chartBbottomYCoord ||
            chartBbottomYCoord < chartAbottomYCoord)
        {
            cout << "charts are way LEFT or RIGHT without overlap" << endl;
            overlap = false;
        }

        return overlap;
    }

    bool GetColour(int X, int Y)
    {

        vector<int> RGBVector = GetColourForGivenCoordinates(X, Y);

        if (RGBVector.size() == 0)
        {
            cout << "coordinates didnt fall inside the charts";
            return false;
        }

        // We've got the co-ordinates inside the chart/charts.
        int red = RGBVector[0];
        int green = RGBVector[1];
        int blue = RGBVector[2];

        cout << "THE RGB values are" << endl
             << "RED: " << red << endl
             << "GREEN: " << green << endl
             << "BLUE: " << blue << endl;
        return true;
    }

    vector<int> GetColourForGivenCoordinates(int X, int Y)
    {

        int chartAtopXCoord = _A.getXCooridanate(_A.getTopCoordinates());
        int chartAtopYCoord = _A.getYCoordinate(_A.getTopCoordinates());
        int chartAbottomXCoord = _A.getXCooridanate(_A.getBottomCoordinates());
        int chartAbottomYCoord = _A.getYCoordinate(_A.getBottomCoordinates());
        int chartBtopXCoord = _B.getXCooridanate(_B.getTopCoordinates());
        int chartBtopYCoord = _B.getYCoordinate(_B.getTopCoordinates());
        int chartBbottomXCoord = _B.getXCooridanate(_B.getBottomCoordinates());
        int chartBbottomYCoord = _B.getYCoordinate(_B.getBottomCoordinates());

        bool overlap(false);
        bool chartAmatch(false);
        bool chartBmatch(false);
        vector<int> RGBVector;

        if (X >= chartAtopXCoord && X <= chartAbottomXCoord &&
            Y <= chartAtopYCoord && Y >= chartAbottomYCoord)
        {
            chartAmatch = true;
        }

        if (X >= chartBtopXCoord && X <= chartBbottomXCoord &&
            Y <= chartBtopYCoord && Y >= chartBbottomYCoord)
        {
            chartBmatch = true;
        }

        overlap = DoChartsOverlap(_A, _B);

        if (chartAmatch || chartBmatch)
        {
            int red, green, blue;
            if (overlap)
            {
                cout << "overlap" << endl;
                red = (_A.getColorByIndex(0) + _B.getColorByIndex(0)) / 2;
                green = (_A.getColorByIndex(1) + _B.getColorByIndex(1)) / 2;
                blue = (_A.getColorByIndex(2) + _B.getColorByIndex(2)) / 2;
            }
            else if (chartAmatch)
            {
                cout << "coordinate in chart A" << endl;
                red = (_A.getColorByIndex(0));
                green = (_A.getColorByIndex(1));
                blue = (_A.getColorByIndex(2));
            }
            else if (chartAmatch)
            {
                cout << "coordinate in chart B" << endl;
                red = (_B.getColorByIndex(0));
                green = (_B.getColorByIndex(1));
                blue = (_B.getColorByIndex(2));
            }
            RGBVector.push_back(red);
            RGBVector.push_back(green);
            RGBVector.push_back(blue);
        }
        return RGBVector;
    }
};

int main(void)
{
    Chart chart1(1, 200, 300, 1, 100, 150, 120);
    Chart chart2(1, 200, 300, 1, 100, 200, 254);
    View view1(chart1, chart2);
    view1.GetColour(2, 2);
    cout << endl
         << endl;

    Chart chart3(1, 20, 3, 1, 100, 150, 120);
    Chart chart4(50, 200, 300, 100, 100, 200, 254);
    View view2(chart3, chart4);
    view2.GetColour(200, 300);

    return 1;
}