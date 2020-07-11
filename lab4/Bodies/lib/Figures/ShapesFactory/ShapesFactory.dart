import 'package:BodiesLab/Figures/Body/Body.dart';
import 'package:BodiesLab/Figures/Compound/Compound.dart';
import 'package:BodiesLab/Figures/Cone/Cone.dart';
import 'package:BodiesLab/Figures/Cylinder/Cylinder.dart';
import 'package:BodiesLab/Figures/Parallelepiped/Parallelepiped.dart';
import 'package:BodiesLab/Figures/ShapesFactory/IncorrectCountOfArgumentsException.dart';
import 'package:BodiesLab/Figures/ShapesFactory/UnknownTypeOfShape.dart';
import 'package:BodiesLab/Figures/Sphere/Sphere.dart';

abstract class ShapesFactory
{
  static const String COMPOUND = 'Compound';
  static const String CONE = 'Cone';
  static const String CYLINDER = 'Cylinder';
  static const String PARALLELEPIPED = 'Parallelepiped';
  static const String SPHERE = 'Sphere';

  static Body Create(List<String> input)
  {
    switch (input[0]) {
      case COMPOUND:
        return Compound();
      case CONE:
        if (input.length < 5) throw IncorrectCountOfArgumentsException('Not enough args to create Cone');
        return Cone(double.parse(input[1]), double.parse(input[2]), double.parse(input[3]), double.parse(input[4]));
      case CYLINDER:
        if (input.length < 5) throw IncorrectCountOfArgumentsException('Not enough args to create Cylinder');
        return Cylinder(double.parse(input[1]), double.parse(input[2]), double.parse(input[3]), double.parse(input[4]));
      case PARALLELEPIPED:
        if (input.length < 6) throw IncorrectCountOfArgumentsException('Not enough args to create Parallelepiped');
        return Parallelepiped(double.parse(input[1]), double.parse(input[2]), double.parse(input[3]), double.parse(input[4]), double.parse(input[5]));
      case SPHERE:
        if (input.length < 4) throw IncorrectCountOfArgumentsException('Not enough args to create Sphere');
        return Sphere(double.parse(input[1]), double.parse(input[2]), double.parse(input[3]));
      default:
        throw UnknwoTypeOfShape('Unknown type of shape ' + input[0]);
    }
  }
}
