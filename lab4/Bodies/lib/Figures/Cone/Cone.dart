import '../BodyRotation/BodyRotation.dart';

class Cone extends BodyRotation
{
  double _height;

  Cone(double density, double volume, double radius, double this._height): super(density, volume, radius) {}

  double GetHeight() => _height;

  @override
  String toString() {
    return 'Cone: ' + 'V = ' + GetVolume().toString() + ' R = ' + GetBaseRadius().toString() +
    ' Dens = ' + GetDensity().toString() + ' H = ' + _height.toString();
  }
}
