import '../SolidBody/SolidBody.dart';

class Parallelepiped extends SolidBody
{
  double _height;
  double _depth;
  double _width;

  Parallelepiped(double density, double volume, double this._height, double this._depth, double this._width):
  super(density, volume) {}

    double GetHeight() => _height;
    double GetWidht() => _width;
    double GetDepth() => _depth;

    @override
  String toString() {
    return 'Parallelepiped';
  }
}
