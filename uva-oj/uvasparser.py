#!/bin/python3

import json

with open("./uva-oj/submissions.json") as f:
    submissions = json.load(f)

ac_submissions = []

for sub in submissions['subs']:
    if sub[2] == 90:
        ac_submissions.append([sub[1], sub[6], sub[0], sub[5]])

ac_submissions.sort()
unique_ac = []

for ac in ac_submissions:
    if len(unique_ac) > 0 and unique_ac[-1][1] == ac[0]:
        pass
    else:
        unique_ac.append([ac[2], ac[0], ac[1], ac[3]])

unique_ac.sort(reverse=True)

root_url = "https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&"
pro_url = root_url + 'problem' + '=' + '{problem_id}'

langs = {"1":"ANSI C", "2":"Java", "3":"C++", "4":"Pascal", "5":"C++11"}

print('|  #  | Submission ID | Problem ID | Submission Rank | Language |')
print('| :-: | :-----------: | :--------: | :-------------: | :------: |')
counter = len(unique_ac)

for ac in unique_ac:
    print('| ', counter, ' |', sep='', end='')
    print(' [', ac[0], '](./uva-oj/solutions/', ac[0], '.cpp)', sep='', end=' |')
    print(' [', ac[1], '](', pro_url.format(problem_id=ac[1]), ')', sep='', end=' |')
    print(' ', ac[2], sep='', end=' |')
    print(' ', langs['{}'.format(ac[3])], sep='', end=' |')
    print('')
    counter -= 1
