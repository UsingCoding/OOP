import 'dart:ffi';
import 'dart:io';
import 'dart:math';

class Main {

  final PATH_TO_INPUT = 'Tests/Inputs/input';
  final PATH_TO_OUTPUT = 'Tests/Outputs/output';
  final PATH_TO_CURR_TEST_OUTPUT = 'Tests/output.txt';
  final MAIN_FILE = './main';

  List<Map<String, String>> tasks = [
    {
      'searchStr': 'replace',
      'replaceStr' : ''
    },
    {
      'searchStr': 'search',
      'replaceStr' : 'research'
    },
    {
      'searchStr': '',
      'replaceStr' : 'tiny'
    },
    {
      'searchStr': 'tione',
      'replaceStr' : 'finally'
    }
  ];

  final List<int> failedTests = [];

  Future<String> _readDataFromFile(String path) async
  {
    final output = File(path);
    return (await output.readAsString());
  }

  Future<ProcessResult> _runMainProcess(List<String> args) async
  {
    print('---- ' + args.join(' '));
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
    print("Passed tests: ${tasks.length - failedTests.length} of ${tasks.length}");


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
    for (var i = 0; i < tasks.length; i++) {
      final res = await _runMainProcess([PATH_TO_INPUT + (i + 1).toString() + '.txt', PATH_TO_CURR_TEST_OUTPUT, tasks[i]['searchStr'], tasks[i]['replaceStr']]);

      if (res.exitCode != 0) {
        failedTests.add(i);
      }

      final currOutput = await _readDataFromFile(PATH_TO_CURR_TEST_OUTPUT);
      final expectOutput = await _readDataFromFile(PATH_TO_OUTPUT + (i + 1).toString() + '.txt');

      if (!_compare(expectOutput, currOutput)) {
        failedTests.add(i);
        continue;
      }
    }

    _printResults();
  }
}

main() => Main().execute();
