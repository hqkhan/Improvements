You have been hired as an intern at an Human Resources (HR) firm. Your manager 
hears that you are are good at computers and asks for a bash script to automatically 
order resumes by certain keywords.  The bash script should be named "HR_sorter", and 
read a file called "input.txt".  The "input.txt" file will have a keyword (or phrase) 
and a numerical weight on each line (separated by a space).  The ordering of the 
resumes by keywords should be based on a total score, which is the sum of the score 
for each keyword (or phrase).  The score for each keyword (or phrase) simply multiplies 
the number of times a keyword (or phrase) appears in the resume by its corresponding 
weight in input.txt.  Resumes will be simple ASCII files (with random extensions) in 
a subdirectory called "submissions".  The output of the "HR_sorter" script should show 
on each line the filename of the resume and total score of the resume, sorted by the 
total score (with higher scores being first).

- Resumes are in the "submissions" folder
- Template "HR_sorter" script
- Resumes in the "submissions" folder
- Three example input files (one in the main directory, and the others in "/testcases" directory)
- Expected output of HR_sorter script in "testcases/input.txt(1,2,3).sol"
- Script to check your script's output against the expected results can be run with "testcases/./testall"
- More challenging testcases in the "/too_hard" directory, but your assignment will not be graded against these
