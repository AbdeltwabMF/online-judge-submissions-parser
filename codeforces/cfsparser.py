#!/bin/python3

import json

with open('./codeforces/submissions.json') as f:
    submissions = json.load(f)

if submissions['status'] != 'OK':
    print('..Oops, something went wrong!')
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

# sort according to contestId, index, problem_name
accepted_subs.sort(reverse=True)

# pick the last Accepted submission to the problem if there is more than one according to the submissionId
for ac in accepted_subs:
    if len(unique_ac) > 0 and ac[0] == unique_ac[-1][1] and ac[1] == unique_ac[-1][2]:
        pass
    else:
        unique_ac.append([ac[3], ac[0], ac[1], ac[2], ac[4], ac[5], ac[6]])

# sort the unique submissions in descending order from the present to the past
unique_ac.sort(reverse=True);

print('| #    | Submission ID | Contest ID | Index | Problem Name | Rating | Language  |    Tags    |')
print('| :--: | :--------: | :-----: | :--: | :-----------------: | :----: | :-------: | :--------: |')

count = len(unique_ac)
# if the contestId <= contest_max_limit then it is a contest, otherwise it is a gym
contest_max_limit = 9999
root_url="https://codeforces.com/"

# print the result in markdown fashion
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
