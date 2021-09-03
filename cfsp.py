#!/bin/python3

import json

with open('submissions.json') as f:
    submissions = json.load(f)

if submissions['status'] != 'OK':
    print('failed to parse!')
    exit(0)

accepted_subs = []
unique_ac = []

for sub in submissions['result']:
    if sub['verdict'] == 'OK':
        if 'rating' in sub['problem']:
            pass
        else:
            sub['problem']['rating'] = ""

        if len(sub['problem']['tags']) == 0:
            sub['problem']['tags'] = ""

        accepted_subs.append([sub['problem']['contestId'], sub['problem']['index'], sub['problem']['name'], sub['id'], sub['problem']['rating'], sub['programmingLanguage'], sub['problem']['tags']])

accepted_subs.sort(reverse=True)

for ac in accepted_subs:
    if len(unique_ac) > 0 and ac[0] == unique_ac[-1][1] and ac[1] == unique_ac[-1][2]:
        pass
    else:
        unique_ac.append([ac[3], ac[0], ac[1], ac[2], ac[4], ac[5], ac[6]])

unique_ac.sort(reverse=True);

print('| #    | Submission ID | Contest ID | Index |   Problem Name   | Rating |  Language  |     Tags     |')
print('| :--: | :--------: | :-----: | :---: | :--------------------: | :----: | :--------: | :----------: |')

count = len(unique_ac)
contest_max_limit = 9999
root_url="https://codeforces.com/"

for ac in unique_ac:
    if ac[1] <= contest_max_limit:
        gymOrcontest = "contest"
    else:
        gymOrcontest = "gym"

    sol_url = root_url
    prb_url = root_url

    sol_url += gymOrcontest + '/' + str(ac[1]) + '/' + "submission" + '/' + str(ac[0])
    prb_url += gymOrcontest + '/' + str(ac[1]) + '/' + "problem"    + '/' + str(ac[2])

    print('|', count, sep=' ', end=' |')

    print(' [', ac[0], '](', sol_url, ')', sep='', end=' |')

    print(' ', ac[1], sep='', end=' |')
    print(' ', ac[2], sep='', end=' |')

    print(' [', ac[3], '](', prb_url, ')', sep='', end=' |')

    print(' ', ac[4], sep='', end=' |')
    print(' ', ac[5], sep='', end=' |')

    count -= 1

    # tags
    for tag in range(max(len(ac[6]) - 1, 0)):
        print(ac[6][tag], end=', ')

    if len(ac[6]) > 0:
        print(ac[6][-1], end='')

    print(' |')
