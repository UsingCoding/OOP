import 'dart:io';

import 'package:BodiesLab/Figures/BodiesCalculations.dart';
import 'package:BodiesLab/Figures/Body/Body.dart';
import 'package:BodiesLab/Figures/Compound/Compound.dart';
import 'package:BodiesLab/Figures/ShapesFactory/ShapesFactory.dart';

class CommandLineController
{
  static const _STOP_COMMAND = 'Stop';
  static const _CREATE_SHAPE_COMMAND = 'Create';
  static const _ADD_TO_COMPOUND_COMMAND = 'To';
  static const _PRINT_SHAPES_COMMAND = 'List';

  static const List<String> _availabelTypesOfShapes = [
    ShapesFactory.COMPOUND,
    ShapesFactory.CONE,
    ShapesFactory.CYLINDER,
    ShapesFactory.PARALLELEPIPED,
    ShapesFactory.SPHERE
  ];

  final List<Body> _holder = [];

  CommandLineController();

  void _PrintInvitation()
  {
    stdout.writeln('Here is list of available Shapes');

    stdout.writeln(_availabelTypesOfShapes.join('\n'));

    stdout.writeln('To create a Shape use command: "Create <SHAPE_TYPE> arg [..args]"');

    stdout.writeln('To create a Compound use command: Compound');

    stdout.writeln('To show figures list with their numbes - write "List"');

    stdout.writeln('To add body to compound write "To <COMPOUND_BODY_NUMBER> add: <BODY_NUMBER> [..<BODY_NUMBER>]"');

    stdout.writeln('To stop execution write "Stop"');
  }

  void Start()
  {
    _PrintInvitation();

    while (true)
    {
      String input = stdin.readLineSync();

      final inputSegments = input.split(' ');

      switch (inputSegments[0])
      {
        case _CREATE_SHAPE_COMMAND:
          _HandleCreateShapeCommand(inputSegments);
          break;
        case _ADD_TO_COMPOUND_COMMAND:
          _HandleAddToCompoundCommand(inputSegments);
          break;
        case _PRINT_SHAPES_COMMAND:
          _HandlePrintShapeCommand(inputSegments);
          break;
        case _STOP_COMMAND:
          _HandleStopCommand();
          return;
        default:
          _HandleUnknownCommand();
      }
    }
  }

  void _HandleCreateShapeCommand(List<String> inputSegments)
  {
    inputSegments.removeRange(0, 1);
    try
    {
      _holder.add(ShapesFactory.Create(inputSegments));
      stdout.writeln('Shape created - ' + inputSegments[0]);
    }
    catch (e)
    {
      stdout.writeln('Failed to create  - ' + inputSegments[0]);
    }
  }

  void _HandleAddToCompoundCommand(List<String> inputSegments)
  {
    final toIndex = inputSegments.indexOf('To', 0);
    final addIndex = inputSegments.indexOf('add:', 0);

    if (toIndex == -1 || toIndex != 0 || addIndex != 2 || addIndex == -1)
    {
      stdout.writeln('Incorrect syntax to add to compound body');
      return;
    }

    Compound compound;

    try
    {
      compound = _holder[int.parse(inputSegments[1])] as Compound;
    }
    catch (e)
    {
      stdout.writeln('No compound by this key doesnt exists');
      return;
    }

    inputSegments.removeRange(0, 3);

    inputSegments.forEach((String element) {
      try
      {
        compound.AddBody(_holder[int.parse(element)]);
        stdout.writeln("Added to compound");
      }
      catch (e)
      {
        stdout.writeln("Failed to add to compound body on number " + element);
      }
    });

  }

  void _HandlePrintShapeCommand(List<String> inputSegments)
  {
    if (inputSegments.length != 1)
    {
      _HandleUnknownCommand();
    }

    for (var i = 0; i < _holder.length; i++)
    {
      stdout.writeln(i.toString() + ': ' + _holder[i].toString());
    }
  }

  void _HandleUnknownCommand()
  {
    stdout.writeln("Unknown command");
  }

  void _HandleStopCommand()
  {
    if (_holder.length != 0)
    {
      stdout.writeln(BodiesCalculations.FindMaxMassBody(_holder));
      stdout.writeln(BodiesCalculations.FindMinWeightInWaterBody(_holder));
    }

    stdout.writeln("Stopped");
  }
}
