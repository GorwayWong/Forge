#include "class.h"
#include <iostream>

gorway_shape::gorway_shape(double _perimeter, double _area)
{
    this->area =_area;
    this->perimeter = _perimeter;
}

gorway_shape::gorway_shape(){
    this->area = 0;
    this->perimeter = 0;
}

double gorway_shape::getArea() const{
    return this->area;
}

double gorway_shape::getPerimeter() const{
    return this->perimeter;
}

void gorway_shape::setArea(double _area){
    this->area =_area;
}

void gorway_shape::setPerimeter(double _perimeter){
    this->perimeter = _perimeter;
}

bool gorway_shape::isValid() const{
    return (this->area >= 0) && (this->perimeter >= 0);
}

void gorway_shape::showShape() const{
    if(this->isValid()){
        std::cout << this->getArea()<<" "<< this->getPerimeter() << '\n';
    }
}

gorway_shape::~gorway_shape()
{
}