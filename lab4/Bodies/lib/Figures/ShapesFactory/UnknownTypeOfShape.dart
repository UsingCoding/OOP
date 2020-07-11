class UnknwoTypeOfShape implements Exception
{
  final String _msg;

  UnknwoTypeOfShape(this._msg);

  @override
  String toString() => _msg;
}
