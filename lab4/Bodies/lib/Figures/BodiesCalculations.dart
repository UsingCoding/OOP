import 'package:BodiesLab/Figures/Body/Body.dart';

class BodiesCalculations
{
  static Body FindMaxMassBody(final List<Body> bodies)
  {
    bodies.sort((Body body1, Body body2) {
      if (body1.GetMass() == body2.GetMass())
      {
        return 0;
      }
      return body1.GetMass() > body2.GetMass() ? 1 : -1;
    });

    return bodies.last;
  }

  static Body FindMinWeightInWaterBody(final List<Body> bodies)
  {
    bodies.sort((Body body1, Body body2) {
      if (body1.GetVolume() == body2.GetVolume())
      {
        return 0;
      }
      return body1.GetVolume() > body2.GetVolume() ? 1 : -1;
    });

    return bodies.first;
  }
}
