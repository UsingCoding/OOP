import 'dart:io';

Future<void> main() async {

  exit(42);

  List<Map<String, String>> test1 = [
    {
      'input': '16 2 1F',
	  'number': '1',
      'awaitResult': '11111',
      'currRes': '',
    },
    {
      'input': '20 10 FF',
	  'number': '2',
      'awaitResult': '315',
      'currRes': '',
    }
  ];

  for (var testData in test1) {
    ProcessResult res = await Process.run('./main', testData['input'].split(' '));
    if (res.exitCode != 0 || (res.stdout as String).trim() != testData['awaitResult']) {
			testData['currRes'] = (res.stdout as String).trim();
		}
  }

  for (var testData in test1) {
	  if (testData['currRes'] != '') {
		  print("""
Test #${testData['number']} failed with:
Input: ${testData['input']}
Await result: ${testData['awaitResult']}
Curr result: ${testData['currRes']}""");
	  }
	  else{
	  	print("Test #${testData['number']} passed");
	  }

	  print("------------------");
  }
}
