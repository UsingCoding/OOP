import 'dart:io';

import 'package:BodiesLab/Figures/Body/Body.dart';
import 'package:BodiesLab/Figures/Compound/Compound.dart';
import 'package:BodiesLab/Figures/ShapesFactory/ShapesFactory.dart';

class CommandLineController
{
  final List<String> _availabelTypesOfShapes = [
    ShapesFactory.COMPOUND,
    ShapesFactory.CONE,
    ShapesFactory.CYLINDER,
    ShapesFactory.PARALLELEPIPED,
    ShapesFactory.SPHERE
  ];

  final String _STOP_COMMAND = 'Stop';

  final List<Body> bodies = [];

  void _WriteInvitation()
  {
    stdout.writeln('Here is list of available Shapes');

    stdout.writeln(_availabelTypesOfShapes.join('\n'));

    stdout.writeln('To create a Shape use command: <SHAPE_TYPE> arg [..args]');

    stdout.writeln('To create a Compound use command: Compound <SHAPE_TYPE> arg [..args], [..<SHAPE_TYPE> arg [..args]]');

    stdout.writeln('To stop execution write "Stop"');
  }

  void _HandleBodyCreation(List<String> inputSegments)
  {
    bodies.add(ShapesFactory.Create(inputSegments));
    stdout.writeln('Shape created - ' + inputSegments[0]);
  }

  void _HandleAddBodiesToCompound(List<String> inputSegments)
  {
    inputSegments.removeRange(0, 1);
    inputSegments = inputSegments.join(' ').split(', ');

    final Compound lastCompound = bodies.last;

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
