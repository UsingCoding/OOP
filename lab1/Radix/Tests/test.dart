import 'dart:io';

Future<void> main() async {
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
    },
    {
      'input': '10 2 2147483647',
	    'number': '3',
      'awaitResult': '1111111111111111111111111111111',
      'currRes': '',
    },
    {
      'input': '10 2 -2147483647',
	    'number': '4',
      'awaitResult': '-1111111111111111111111111111111',
      'currRes': '',
    },
    {
      'input': 'F 2 47',
	    'number': '5',
      'awaitResult': 'Some bad symbol in notation',
      'currRes': '',
    },
    {
      'input': '2 10 47',
	    'number': '5',
      'awaitResult': 'Incorrect number for this notation',
      'currRes': '',
    },
    {
      'input': '36 10 36',
	    'number': '5',
      'awaitResult': '114',
      'currRes': '',
    },
    {
      'input': '36 10 0',
	    'number': '6',
      'awaitResult': '0',
      'currRes': '',
    },
    {
      'input': '2 10 2F',
	    'number': '7',
      'awaitResult': 'Incorrect number for this notation',
      'currRes': '',
    },
    {
      'input': '16 10 f',
	    'number': '8',
      'awaitResult': 'Incorrect number for this notation',
      'currRes': '',
    },
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
