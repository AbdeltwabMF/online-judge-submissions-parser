#!/bin/python3

import json

with open("./atcoder/submissions.json") as f:
    submissions = json.load(f)

ac_submissions = []

for sub in submissions:
    if sub['result'] == 'AC':
        ac_submissions.append([sub['contest_id'], sub['problem_id'], sub['id'], sub['user_id'], sub['language']])

ac_submissions.sort(reverse=True)
unique_ac = []

for ac in ac_submissions:
    if len(unique_ac) > 0 and unique_ac[-1][1] == ac[0] and unique_ac[-1][2] == ac[1]:
        pass
    else:
        unique_ac.append([ac[2], ac[0], ac[1], ac[3], ac[4]])

unique_ac.sort(reverse=True)

root_url = "https://atcoder.jp/"
sol_url = root_url + 'contests' + '/' + '{contest_id}' + '/' + 'submissions' + '/' + '{id}'
pro_url = root_url + 'contests' + '/' + '{contest_id}' + '/' + 'tasks'       + '/' + '{problem_id}'

print('|  #  | Submission ID | contest_id | problem_id | language |')
print('| :-: | :-----------: | :--------: | :--------: | :------: |')
counter = len(unique_ac)

for ac in unique_ac:
    print('| ', counter, ' |', sep='', end='')
    print(' [', ac[0], '](', sol_url.format(contest_id=ac[1], id=ac[0]), ')', sep='', end=' |')
    print(' ', ac[1], sep='', end=' |')
    print(' [', ac[2], '](', pro_url.format(contest_id=ac[1], problem_id=ac[2]), ')', sep='', end=' |')
    print(' ', ac[4], sep='', end=' |')
    print('')
    counter -= 1
