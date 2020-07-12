import 'dart:io';

import 'package:BodiesLab/Figures/BodiesCalculations.dart';
import 'package:BodiesLab/Figures/Body/Body.dart';
import 'package:BodiesLab/Figures/Compound/Compound.dart';
import 'package:BodiesLab/Figures/ShapesFactory/ShapesFactory.dart';

class CommandLineController
{
  static const List<String> _availabelTypesOfShapes = [
    ShapesFactory.COMPOUND,
    ShapesFactory.CONE,
    ShapesFactory.CYLINDER,
    ShapesFactory.PARALLELEPIPED,
    ShapesFactory.SPHERE
  ];

  static const _FIND_MAX_MASS = 'FindMaxMass';
  static const _FIND_MIN_WEIGHT = 'FindMinWeight';

  static const _STOP_COMMAND = 'Stop';

  final List<Body> _bodies = [];

  void _WriteInvitation()
  {
    stdout.writeln('Here is list of available Shapes');

    stdout.writeln(_availabelTypesOfShapes.join('\n'));

    stdout.writeln('To create a Shape use command: <SHAPE_TYPE> arg [..args]');

    stdout.writeln('To create a Compound use command: Compound <SHAPE_TYPE> arg [..args], [..<SHAPE_TYPE> arg [..args]]');

    stdout.writeln('To find out which body has MaxMass or Min weight in water write: ' + _FIND_MAX_MASS + ' or ' + _FIND_MIN_WEIGHT);

    stdout.writeln('To stop execution write "Stop"');
  }

  void _HandleBodyCreation(List<String> inputSegments)
  {
    _bodies.add(ShapesFactory.Create(inputSegments));
    stdout.writeln('Shape created - ' + inputSegments[0]);
  }

  void _HandleAddBodiesToCompound(List<String> inputSegments)
  {
    inputSegments.removeRange(0, 1);
    inputSegments = inputSegments.join(' ').split(', ');

    final Compound lastCompound = _bodies.last;

    inputSegments.forEach((String element) {
      final segments = element.split(' ');

      try
      {
        lastCompound.AddBody(ShapesFactory.Create(segments));
        stdout.writeln('Created and added to comppund body - ' + segments[0]);
      }
      catch (e)
      {
        stdout.writeln('Failed to create  - ' + segments[0]);
      }
    });
  }

  void Start()
  {
    _WriteInvitation();

    while(true)
    {
      String input = stdin.readLineSync();

      if (input == _STOP_COMMAND)
      {
        break;
      }

      final inputSegments = input.split(' ');

      if (inputSegments[0] == _FIND_MAX_MASS)
      {
        if (_bodies.length == 0)
        {
          stdout.writeln('No body created');
          continue;
        }

        stdout.writeln(BodiesCalculations.FindMaxMassBody(_bodies));
        continue;
      }

      if (inputSegments[0] == _FIND_MIN_WEIGHT)
      {
        if (_bodies.length == 0)
        {
          stdout.writeln('No body created');
          continue;
        }

        stdout.writeln(BodiesCalculations.FindMinWeightInWaterBody(_bodies));
        continue;
      }

      try
      {
        _HandleBodyCreation(inputSegments);
      }
      catch (e)
      {
        stdout.writeln(e);
        continue;
      }

      if (inputSegments[0] == ShapesFactory.COMPOUND)
      {
        _HandleAddBodiesToCompound(inputSegments);
      }

    }
  }
}
