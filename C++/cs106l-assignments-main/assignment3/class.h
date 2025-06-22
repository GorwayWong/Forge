class gorway_shape
{
private:
    double perimeter;
    double area;
    bool isValid() const;
public:
    gorway_shape(double _perimeter, double _area);
    gorway_shape();
    double getArea() const;
    double getPerimeter() const;
    void showShape() const;
    void setArea(double _perimeter);
    void setPerimeter(double _area);
    ~gorway_shape();
};
