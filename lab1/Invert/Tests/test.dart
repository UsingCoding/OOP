import 'dart:io';
import 'dart:math';

class Main {
  final testFiles = [
    'Tests/Outputs/output1.txt'
  ];

  final inputFiles = [
    'Tests/Inputs/input1.txt'
  ];

  final failedTests = [];

  Future<String> _readTestDataFromFile(String fileName) async
  {
    final output = File('Tests/Outputs/output1.txt');
    return (await output.readAsString()).trim();
  }

  Future<ProcessResult> _runProcess(List<String> args) async
  {
    return await Process.run('./main', args);
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
    failedTests.forEach((testNum) {
      print(testNum + 1);
    });
  }
  void execute() async
  {
    for (var i = 0; i < min(testFiles.length, inputFiles.length); i++) {
      final testData = await _readTestDataFromFile(testFiles[i]);
      final res = await _runProcess([inputFiles[i]]);

      if (res.exitCode != 0) {
        failedTests.add(i);
        continue;
      }

      if (!_compare(testData, (res.stdout as String).trim()))
      {
        failedTests.add(i);
      }
    }

    _printResults();
  }
}

main() => Main().execute();
