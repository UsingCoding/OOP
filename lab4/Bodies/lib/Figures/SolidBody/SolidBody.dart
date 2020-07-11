import '../Body/Body.dart';

abstract class SolidBody extends Body
{
  double _density;
  double _volume;

  SolidBody(double this._density, double this._volume);
  double GetDensity() => _density;
  double GetVolume() => _volume;
  double GetMass() => _density * _volume;
}
