Tests for XParser
Author: Sander van der Hoog
Date: 5 Sept 2018

This test is meant for checking agent order of function execution.

1. The original order of agents in the 0.xml file is inverted due to the xml read-in function.
2. If the agents only print out their IDs (no messages send and read), the order is maintained:

Output:

------------------------
IT 1 ID 6
IT 1 ID 5
IT 1 ID 4
IT 1 ID 3
IT 1 ID 2
IT 1 ID 1
------------------------
IT 2 ID 6
IT 2 ID 5
IT 2 ID 4
IT 2 ID 3
IT 2 ID 2
IT 2 ID 1
------------------------
IT 3 ID 6
IT 3 ID 5
IT 3 ID 4
IT 3 ID 3
IT 3 ID 2
IT 3 ID 1
------------------------
IT 4 ID 6
IT 4 ID 5
IT 4 ID 4
IT 4 ID 3
IT 4 ID 2
IT 4 ID 1
------------------------

3. However, if messages are send and read, the order is again inverted upon activating the read function (function with message input).:

Test model:
- test_filtering: 

Output:

------------------------
IT 1 ID 6 adds info message
IT 1 ID 5 adds info message
IT 1 ID 4 adds info message
IT 1 ID 3 adds info message
IT 1 ID 2 adds info message
IT 1 ID 1 adds info message
IT 1 ID: 1 reads info messages:     6 5 4 3 
IT 1 ID: 2 reads info messages:     6 5 4 3 
IT 1 ID: 3 reads info messages:     6 5 4 3 
IT 1 ID: 4 reads info messages:     6 5 4 3 
IT 1 ID: 5 reads info messages:     6 5 4 3 
IT 1 ID: 6 reads info messages:     6 5 4 3 
------------------------
IT 2 ID 1 adds info message
IT 2 ID 2 adds info message
IT 2 ID 3 adds info message
IT 2 ID 4 adds info message
IT 2 ID 5 adds info message
IT 2 ID 6 adds info message
IT 2 ID: 6 reads info messages:     3 4 5 6 
IT 2 ID: 5 reads info messages:     3 4 5 6 
IT 2 ID: 4 reads info messages:     3 4 5 6 
IT 2 ID: 3 reads info messages:     3 4 5 6 
IT 2 ID: 2 reads info messages:     3 4 5 6 
IT 2 ID: 1 reads info messages:     3 4 5 6 
------------------------
IT 3 ID 6 adds info message
IT 3 ID 5 adds info message
IT 3 ID 4 adds info message
IT 3 ID 3 adds info message
IT 3 ID 2 adds info message
IT 3 ID 1 adds info message
IT 3 ID: 1 reads info messages:     6 5 4 3 
IT 3 ID: 2 reads info messages:     6 5 4 3 
IT 3 ID: 3 reads info messages:     6 5 4 3 
IT 3 ID: 4 reads info messages:     6 5 4 3 
IT 3 ID: 5 reads info messages:     6 5 4 3 
IT 3 ID: 6 reads info messages:     6 5 4 3 
------------------------
IT 4 ID 1 adds info message
IT 4 ID 2 adds info message
IT 4 ID 3 adds info message
IT 4 ID 4 adds info message
IT 4 ID 5 adds info message
IT 4 ID 6 adds info message
IT 4 ID: 6 reads info messages:     3 4 5 6 
IT 4 ID: 5 reads info messages:     3 4 5 6 
IT 4 ID: 4 reads info messages:     3 4 5 6 
IT 4 ID: 3 reads info messages:     3 4 5 6 
IT 4 ID: 2 reads info messages:     3 4 5 6 
IT 4 ID: 1 reads info messages:     3 4 5 6 
------------------------
