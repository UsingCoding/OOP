class IncorrectCountOfArgumentsException implements Exception
{
  final String _msg;

  IncorrectCountOfArgumentsException(this._msg);

  @override
  String toString() => _msg;
}
