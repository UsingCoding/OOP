import '../BodyRotation/BodyRotation.dart';

class Sphere extends BodyRotation
{
  Sphere(double density, double volume, double radius): super(density, volume, radius) {}

  @override
  String toString() {
    return 'Sphere';
  }
}
