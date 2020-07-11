import 'dart:ffi';

import '../Body/Body.dart';

class Compound extends Body
{
  final List<Body> _bodies = [];
  Compound _parentBody = null;

  double _GetFromAll(double Function(Body body) getter)
  {
    double result;

    for (Body body in _bodies)
    {
      result += getter(body);
    }

    return result;
  }

  bool _CheckForPresence(Body body)
  {
    if (body == this)
    {
      return true;
    }

    if (_parentBody == null)
    {
      return false;
    }

    if (_parentBody == body)
    {
      return true;
    }

    return _parentBody._CheckForPresence(body);
  }

  double GetDensity()
  {
    return _GetFromAll((Body body) => body.GetDensity());
  }

  double GetVolume()
  {
    return _GetFromAll((Body body) => body.GetVolume());
  }

  double GetMass()
  {
    return _GetFromAll((Body body) => body.GetMass());
  }

  void AddBody(Body body)
  {
    if (body is Compound)
    {
      if (_CheckForPresence(body))
      {
        throw Exception("Self insert detected");
      }

      body._parentBody = this;
    }

    _bodies.add(body);
  }
}
