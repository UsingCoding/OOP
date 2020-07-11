#!/usr/bin/dart

import 'package:BodiesLab/CommandLineController/CommandLineController.dart';
import 'Figures/Body/Body.dart';

void main(List<String> args)
{
  final handler = CommandLineController();

  handler.Start();
}

Body FindMaxMassBody(final List<Body> bodies)
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

Body FindMinWeightInWaterBody(final List<Body> bodies)
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
