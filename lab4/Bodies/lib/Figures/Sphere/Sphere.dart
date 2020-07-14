import '../BodyRotation/BodyRotation.dart';

class Sphere extends BodyRotation
{
  Sphere(double density, double volume, double radius): super(density, volume, radius) {}

  @override
  String toString() {
    return 'Sphere: ' + 'V = ' + GetVolume().toString() + ' R = ' + GetBaseRadius().toString() +
    ' Dens = ' + GetDensity().toString();
  }
}
