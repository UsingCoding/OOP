import 'dart:io';
import 'dart:math';

class Main {

  final PATH_TO_INPUTS = 'Tests/Inputs';
  final PATH_TO_OUTPUTS = 'Tests/Outputs';
  final MAIN_FILE = './main';

  final testFiles = [
    'output1.txt',
    'output2.txt',
    'output3.txt',
    'output4.txt',
    'output5.txt'
  ];

  final inputFiles = [
    'input1.txt',
    'input2.txt',
    'input3.txt',
    'input4.txt',
    'input5.txt'
  ];

  final List<int> failedTests = [];

  Future<String> _readTestDataFromFile(String fileName) async
  {
    final output = File(PATH_TO_OUTPUTS + '/' + fileName);
    return (await output.readAsString()).trim();
  }

  Future<ProcessResult> _runProcess(List<String> args) async
  {
    return await Process.run(MAIN_FILE, args);
  }

  bool _compare(String original, String rawData)
  {
    if (original != rawData) {
      return false;
    }
    return true;
  }

  void _printResults()
  {
    print("Passed tests: ${testFiles.length - failedTests.length}");


    if (failedTests.length == 0) {
      return;
    }

    print("Failed test");
    failedTests.forEach((int testNum) {
      print("#" + (testNum + 1).toString());
    });
  }
  void execute() async
  {
    for (var i = 0; i < min(testFiles.length, inputFiles.length); i++) {
      final testData = await _readTestDataFromFile(testFiles[i]);
      final res = await _runProcess([PATH_TO_INPUTS + '/' + inputFiles[i]]);

      if (!_compare(testData, (res.stdout as String).trim()) && !_compare(testData, (res.stderr as String).trim()))
      {
        failedTests.add(i);
      }
    }

    _printResults();
  }
}

main() => Main().execute();
