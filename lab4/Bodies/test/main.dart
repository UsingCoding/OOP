import 'package:BodiesLab/Figures/Compound/Compound.dart';
import 'package:BodiesLab/Figures/Compound/SelfInsertException.dart';
import 'package:BodiesLab/Figures/Sphere/Sphere.dart';
import 'package:test/test.dart';

void main() {
  group('Adding bodies into compound and trying to add compound into compound',
      () {
    final compound = Compound();

    test('Adding bodies to compound', () {
      final sphere1 = Sphere(400, 300, 200);
      final sphere2 = Sphere(100, 20, 20);

      expect(() {
        try {
          compound.AddBody(sphere1);
          return true;
        } on SelfInsertException {
          return false;
        }
      }(), equals(true));

      expect(() {
        try {
          compound.AddBody(sphere2);
          return true;
        } on SelfInsertException {
          return false;
        }
      }(), equals(true));
    });

    test('Trying to add compound into himself and get exception', () {
      expect((() {
        try {
          compound.AddBody(compound);
          return false;
        } on SelfInsertException {
          return true;
        }
      })(), equals(true));
    });

    test(
        'Trying to add compound into himself via other compound body and got exception',
        () {
      final compound2 = Compound();
      expect(() {
        try {
          compound.AddBody(compound2);
          return true;
        } on SelfInsertException {
          return false;
        }
      }(), equals(true));

      expect(() {
        try {
          compound2.AddBody(compound);
          return false;
        } on SelfInsertException {
          return true;
        }
      }(), equals(true));
    });
  });
}
