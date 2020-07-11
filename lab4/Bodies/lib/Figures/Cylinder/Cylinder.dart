import '../BodyRotation/BodyRotation.dart';

class Cylinder extends BodyRotation
{
  double _height;

  Cylinder(double density, double volume, double radius, double this._height): super(density, volume, radius) {}

  double GetHeight() => _height;

  @override
  String toString() {
    return 'Cylinder';
  }
}
