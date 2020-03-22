import 'dart:io';

class Main {
  final PATH_TO_INPUT = 'Tests/Inputs/input';
  final PATH_TO_OUTPUT = 'Tests/Outputs/output';
  final PATH_TO_CURR_TEST_OUTPUT = 'Tests/output.txt';
  final MAIN_FILE = './main';

  final CRYPT_MODE = 'crypt';
  final DECRYPT_MODE = 'decrypt';

  List<Map<String, String>> tasks = [
    {'mode': 'crypt', 'key': '5'},
    {'mode': 'crypt', 'key': '4'},
    {'mode': 'crypt', 'key': 'A'},
    {'mode': 'crypt', 'key': '300'},
    {'mode': 'ecmacrypt', 'key': '300'},
    {'mode': 'crypt', 'key': '300'},
  ];

  final List<int> failedTests = [];

  Future<String> _readDataFromFile(String path) async {
    final output = File(path);
    return (await output.readAsString());
  }

  Future<ProcessResult> _runMainProcess(List<String> args) async {
    print('---- ' + args.join(' '));
    return await Process.run(MAIN_FILE, args);
  }

  bool _compare(String original, String rawData) {
    if (original != rawData) {
      return false;
    }
    return true;
  }

  void _printResults() {
    print(
        "Passed tests: ${tasks.length - failedTests.length} of ${tasks.length}");

    if (failedTests.length == 0) {
      return;
    }

    print("Failed test");
    failedTests.forEach((int testNum) {
      print("#" + (testNum + 1).toString());
    });
  }

  void execute() async {
    for (var i = 0; i < tasks.length; i++) {
      stdout.write('\n');
      final resCrypt = await _runMainProcess([
        tasks[i]['mode'],
        PATH_TO_INPUT + (i + 1).toString() + '.txt',
        PATH_TO_CURR_TEST_OUTPUT,
        tasks[i]['key'],
      ]);

      if (resCrypt.exitCode != 0) {
        final expectOutput = await _readDataFromFile(PATH_TO_OUTPUT + (i + 1).toString() + '.txt');

        if (!_compare(resCrypt.stderr, expectOutput)) {
          failedTests.add(i);
        }

        continue;
      }

      final resDecrypt = await _runMainProcess([
        DECRYPT_MODE,
        PATH_TO_CURR_TEST_OUTPUT,
        PATH_TO_OUTPUT + (i + 1).toString() + '.txt',
        tasks[i]['key'],
      ]);

      if (resDecrypt.exitCode != 0) {
        final expectOutput = await _readDataFromFile(PATH_TO_OUTPUT + (i + 1).toString() + '.txt');

        if (!_compare(resDecrypt.stderr, expectOutput)) {
          failedTests.add(i);
        }

        continue;
      }

      final inputData = await _readDataFromFile(PATH_TO_OUTPUT + (i + 1).toString() + '.txt');

      final expectOutput = await _readDataFromFile(PATH_TO_OUTPUT + (i + 1).toString() + '.txt');

      if (!_compare(expectOutput, inputData)) {
        failedTests.add(i);
        continue;
      }
    }

    _printResults();
  }
}

main() => Main().execute();
