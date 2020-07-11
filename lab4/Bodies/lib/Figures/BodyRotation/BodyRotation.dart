// https://github.com/UsingCoding/OOP/issues/7#issue-621202695
import '../SolidBody/SolidBody.dart';

abstract class BodyRotation extends SolidBody
{
  double _radius;

  BodyRotation(double density, double volume, double this._radius): super(density, volume) {}
  double GetBaseRadius() => _radius;
}
